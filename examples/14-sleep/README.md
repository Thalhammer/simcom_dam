# Sleep mode example

Example showing how to use the builtin sleep mode. In order to enter sleep mode, three conditions need to be meet:
* Module must be idle (i.e. all threads suspended/waiting)
* UART needs to be powered off
* USB needs to be disconnected
If this is the case the module will enter into a sleep mode with a current draw of about 2ma, while still being able to receive SMS.
Note that you can have the data connection online, but if you have an open connection (e.g. a mqtt client) the module won't enter
Sleep mode. Make sure you close all network connections if they are not needed. Also make sure you set your timers to not be deferrable
or the timing will be way off once the module enters sleep mode.