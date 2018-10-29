# Powersaving
In order to save power you basically have two options:
* PSM Mode
* Sleep Mode
Depending on your application one or a combination of both might make sense.

## PSM Mode
PSM Mode is the lowest current mode. When enabled current drops to around 7µA for the specified time. However this is not free:
* You loose Network connectivity, so you won't be able to wake your module up via SMS or TCP/IP
* The minimal supported time is 10 minutes
This mode makes most sense for devices that do not require constant network connections, like (non realtime) data collection. Example:
* Boot
* Measure value and store it to flash (the module has about 20M free flash so you can cache a lot of data).
* Sleep for some time
* If cache is full or after larger time, activate network and upload all data

## Sleep Mode
You can enable sleep mode lower to current to about 1mA as long as there is no data transfered. This makes sense if you need a low response time.
In this mode your Application will still be active as normal and you can do what ever you want to do.
The only downside is that you need to power off UART during sleep and receiving data might have an initial delay depending on the eDRX setting you choose.
