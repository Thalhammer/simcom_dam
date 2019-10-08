# Debricking

When doing development on a plattform without a lot of support, you might sometimes find yourself in a situation where it looks like you really screwed up. However the solution is often quite simple once you know it. This document aims to collect reasons why the module does not work as expected anymore and provide solutions to get back to a working condition.

## My module reboots and is only visible as QHSUSB_BULK
This usally means something went horribly wrong while loading your module. However this results in a state where normal boot does not work anymore and thus removing or updating the DAM is not possible. You can however solve this by completely wiping the firmware and restarting it from scratch.
You need to get a Windows machine to do this.
* Download and install QPST Tool and SIM7000 QDL (you can find both [here](https://github.com/botletics/SIM7000-LTE-Shield/tree/master/SIM7000%20Documentation/Firmware%20Updater%20Tool))
* If your Modem shows up as "QHSUSB_BULK" in Device Manager, install the driver provided by Qualcom (TODO: Add to repo and link here)
* Bridge BOOT_CFG to VDD_EXT and reset the module
* QPST Tool should now report the module to be in "Download mode"
* Open "SIM7000 QDL" and select MDM9206 as platform
* It might ask you for the firmware location, if it does, select the extracted firmware image.
* Make sure "Backup/Recover QCN" is checked and click start
* If it fails reset the module, reopen "SIM7000 QDL" and retry
* If it was successful it should show up as SimTech SIM7000 in Device Manager. Install drivers if not already done (TODO: Add driver link)
* If QPST does not pick up the phone by it self, manually add a port using the Diagnostics com port. (Make sure you specify both Port and Port Label, or QPST will silently ignore your request to add it)
* After the upload is done reboot the module and connect to the AT port
* ATI should report the module as "SIM7000A"
* Open "QPST Software Download" and select the "Restore" tab
* Choose your modem and open the xqcn file provided in the "other" directory
* Click start and after it finished the module should respond as "SIM7000E" to ATI
* You now only need to execute "AT+SIMEI=[your imei]" and after a reboot everything should work normal again (IMEI is written on the modules sticker)
