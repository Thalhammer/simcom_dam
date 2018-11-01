# Hello World example

This example demonstrates the correct way of using the UART and implements a small wrapper
which handles buffering and provides simple functions for uart output.

## Async transmit
qapi_UART_Transmit is an async call. This means it returns directly and does not wait for all bytes being sent.
This is a problem if the buffer you try to send is not a constant string and might be get overridden. The wrapper
provided in this project aims to solve this problem by using an internal send buffer and waiting (using a semaphore) if
there is already a transmission in process.

## uart_write
If the message to send is smaller than the configured send buffer and there is no transmission in progress it copies the
provided data to an internal buffer starts the transmission and returns.
If the message is bigger than the buffer or there is already a transfer in progress the function blocks until it able to
copy the argument to its send buffer and then returns.
**It does not block until all data is sent**, however, it makes sure no collisions occur.