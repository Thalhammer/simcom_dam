# Examples

This folder contains a number of examples on how to use parts of the API.
I don't have the time give an example for every single available option,
but I will happily accept pullrequests that add examples.

## Index

Folder                          | Description
--------------------------------|------------
[common](common)                | Contains a reimplementation of txm_lib to keep my work independend of simcoms libs and allow using GCC in the future.
[00-helloworld](00-helloworld)  | Contains a really simple example that just outputs a hello world to the dam uart.
[01-uart](01-uart)              | Contains an example on how to use the uart in a real app including buffering and synchronisation.
[02-gpio](02-gpio)              | Good old blinking LED. Toogles an LED on GPIO3, to demonstrate basic GPIO usage.