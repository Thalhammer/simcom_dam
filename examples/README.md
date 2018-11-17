# Examples

This folder contains a number of examples on how to use parts of the API.
I don't have the time give an example for every single available option,
but I will happily accept pullrequests that add examples.

## Compiling
In order to compile all examples and the reimplementation just run make in this folder.
Running make without TYPE specified will use ARMCC to compile everything, which is equivalent of `make TYPE=arm`.
To use GCC instead run `make TYPE=gcc`. Note that when switching between both you need to run distclean in between.
In order to upload an example run `make upload` in the examples folder. Note that if you used `TYPE=gcc` while compiling
you need to also specify it when doing an upload, since make upload would compile all changes if there are any.

## Index

Folder                          | Description
--------------------------------|------------
[common](common)                | Contains a reimplementation of txm_lib to keep my work independend of simcoms libs and allow using GCC in the future.
[00-helloworld](00-helloworld)  | Contains a really simple example that just outputs a hello world to the dam uart.
[01-uart](01-uart)              | Contains an example on how to use the uart in a real app including buffering and synchronisation.
[02-gpio](02-gpio)              | Good old blinking LED. Toogles an LED on GPIO3, to demonstrate basic GPIO usage.
[03-timer](03-timer)            | Simple example showing how to use timers provided by qapi.
[04-net](04-net)                | (2G) Cellular example, connects to network and configures DNS based on providers DNS.
[05-netmgr](05-netmgr)          | (2G) Cellular example, uses util/netmgr to connect to network.
[06-mqtt](06-mqtt)              | MQTT Example, connects to broker, subscribes to a topic and publishes responses.
[07-cpp](07-cpp)                | C++ Example, demonstrates working global initializers.
[08-location](08-location)      | GNSS Example, tracking mode
[09-locationbatching](09-locationbatching)  | GNSS Example, batching mode
[10-filesystem](10-filesystem)  | Filesystem example, write and read file
[11-deviceinfo](11-deviceinfo)  | Deviceinfo example
[12-psm](12-psm)                | PSM Deep sleep example
[13-rtc](13-rtc)                | RTC Example
[14-sleep](14-sleep)            | Sleep mode example
[15-vat](15-vat)                | Visual AT (AT commands from inside DAM) Example 
