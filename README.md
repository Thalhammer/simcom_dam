# simcom_dam
Examples and documentation for simcoms downloadable modules (Qualcomm SoC)
All information is tested and based on SIM7000E modules, but they are identical for all other SIM7000 modules and might be useful for other simcom modules as well.

## NOTE
I do not recommend this module for any new projects at all (at least not in its current state). It has pretty much no public support or documentation from its manufacturer nor has it received any firmware updates since its release (which it definitly would need). It has the tendency to crash for random reasons, with not debug info about why it crashed or where it crashed, behaves differently depending on whether or not usb is connected and the list goes on. Dont get me wrong, it certainly is a very powerful module (multiple megs of free ram & flash, gps&modem built in and a whole rtos "for free") for a relative cheap price. **However if you plan to use this in any kind of commercial product: DONT**. The time you need to spend to get a reliable firmware (even with the groundwork of this repo) which does what you want far outways the potential benefits.

If you already have the modules, do this for fun or enjoy hunting bugs with no documentation, unpredictable behaviour and no debugger (and limited serial output), go ahead and feel free to leave me a star (cause you seem to have similar hobbies to me :) ).

**TLDR: I have since moved on to other projects, so consider this repo unmaintained.** This is subject to change in case I find a new use case for them or get bored in my free time (dont count on this, I have a huge backlog of toy projects).

## Building the examples
You need an arm cross compiler installed in `/opt/` and update `build_scripts/config.mk` to point to it.
I tested both `gcc-arm-none-eabi-9-2019-q4-major` and `gcc-arm-none-eabi-7-2018-q2-update` but newer ones should work just fine.
I highly recommend sticking to the official arm distributions of gcc as it makes things a lot more predictable.
You can get it [here](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads).

Once you have the compiler setup, change into the examples directory and run `make` to build everything needed and `make upload` to transfer it to the module.
If you have other serial devices plugged into your pc (like a serial to usb adapter) you might need to update the tty in `config.mk`.

## Disclamer
I am in no way associated with simcom. I wrote an email to them once which did not even get a response.
