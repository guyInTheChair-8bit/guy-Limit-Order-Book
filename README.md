# Limit Order Book

A small limit order book project with implementations in C and Python. The C source sketches an order book using price-indexed FIFO lists, while the Python source models order submission, cancellation, best bid/ask selection, and matching.

## Files

- `book.c` — C implementation using doubly linked order queues for each price point. Prices are currently represented as integers from 0 to 100, and the order arrays are sized for up to 1,000 buy and 1,000 sell orders.
- `book.py` — Python prototype with `Book` and `Order` classes for managing buy and sell orders.

## C source

The C file can be compiled with a C compiler, for example:

```sh
gcc -Wall -Wextra -std=c11 book.c -o order_book
```

The current `main` function is empty, so the program does not yet provide a command-line interface or sample run. The Python file is also a prototype and may need corrections before it can be run as a complete simulator.

## Current scope

The C implementation includes order creation and cancellation organized by price. The Python prototype includes intended best-price selection and trade matching logic. A useful next step is to add a runnable driver and connect the matching behavior to order submission and cancellation in a single consistent interface.
