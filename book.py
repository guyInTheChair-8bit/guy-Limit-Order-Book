from collections import defaultdict
from hashlib import sha256
import time

class Book:
    def init(self):
        self.buy_orders = defaultdict(str)
        self.sell_orders = defaultdict(str)
        self.spread = 0
        self.bid = Order()
        self.ask = Order()
        self.executed_orders = []

    def buy_order(self, no_of_shares, bid_price):
        id = str(time.time()) + str(len(self.buy_orders)) + str(no_of_shares) + str(bid_price)
        id = sha256(id.encode('utf-8'))
        self.buy_orders[id] = (Order(id, time.time(), "buy", no_of_shares, bid_price))
        return id
    
    def sell_order(self, no_of_shares, ask_price):
        id = str(time.time()) + str(len(self.sell_orders)) + str(no_of_shares) + str(ask_price)
        id = sha256(id.encode('utf-8'))
        self.sell_orders[id] = (Order(id, time.time(), "sell", no_of_shares, ask_price))
        return id
    
    def cancel_order(self, orderID):
        if orderID in self.buy_orders:
            del self.buy_orders[orderID]
        else:
            del self.sell_orders[orderID] 
    
    def simulate(self):
        self.ask = self.sell_orders.values()[0] #assingning random sell order so that the code doesn't crash

        while True:
            for order in self.buy_orders.values():
                if self.bid.price < order.price:
                    self.bid = order
                elif self.bid.price == order.price and self.bid.time > order.time:
                    self.bid = order        

            for order in self.sell_orders.values():
                if self.ask.price > order.price:
                    self.ask = order
                elif self.ask.price == order.price and self.ask.time > order.time:
                    self.ask = order

            self.spread = self.ask.price - self.bid.price
            if self.spread >= 0:
                continue
            else:
                for order in self.sell_orders.itmes():
                    if order[1].price == self.bid.price: #this will happen because in a real market if spread is -ve then we can assume the required liquidity exists otherwise the book is illiquid and remains like that until liquidity appears
                        if self.bid.no_of_shares == order[1].no_of_shares:
                            self.executed_orders.append((order[0], self.bid.id, self.bid.no_of_shares))
                            del self.buy_orders[self.bid.id]
                            del self.sell_orders[order[0]]
                        elif self.bid.no_of_shares < order[1].no_of_shares:
                            self.executed_orders.append((order[0], self.bid.id, self.bid.no_of_shares))
                            order[1].no_of_shares -= self.bid.no_of_shares
                            del self.buy_orders[self.bid.id]
                        else:
                            self.executed_orders.append((order[0], self.bid.id, order[1].no_of_shares))
                            self.bid.no_of_shares -= order[1].no_of_shares
                            del self.sell_orders[order[0]]

class Order:
    def init(self):
        self.id = None
        self.type = None
        self.no_of_shares = 0
        self.price = 0
        self.time = 0

    def init(self, orderID, time, type, no_of_shares, price):
        self.id = orderID
        self.type = type
        self.no_of_shares = no_of_shares
        self.price = price
        self.time = time

