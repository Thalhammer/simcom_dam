# Download and run a DAM on the modem
## Required Tools
* Qualcomm QPST (EFS Explorer)
* Simcom Module connected via USB

## Setting up
In order to download modules to your modem you need to use Qualcomm's QPST EFS Explorer, which unfortunately isn't available freely. It is however available from various websites which use it to revive bricked phones. Find a source and install it. If you get an error message about a missing Internet Explorer try a newer version (Version 2.7 Build 438 seems to work). Open "QPST Configuration" and navigate to the "Ports" tab. Click on "Add new Port" and enter the Diagnostics port of your module. If you did everything correctly your phone tab should look similar to this.

![QPST](images/qpst1.png)

## Uploading a DAM
To upload a DAM to your Modem you need to open "EFS Explorer". You can do this either from within QPST Configuration by clicking on "Start Clients" => "EFS Explorer" or by directly starting "EFS Explorer" from the windows start menu.
A new window and a Phone selection dialog should appear. Select your Modem (if not preselected) and click on OK. "EFS Explorer" will now load the contents of the Embedded Filesystem. We need to upload our DAM to the modem's alternate Filesystem. To select it click on the blue/green cylinder icon:

![EFSE](images/qpst2.png)

Select the folder "custapp" or create it if there is none and upload your DAM to the folder by right clicking in the right folder view and selecting "Copy Data File from PC". In the new dialog select your DAM image using the "Browse" button and make sure the opions match those in the following image. It is mandatory to name your file "cust_app.bin" on the phone or it won't load.

![Upload](images/qpst3.png)

Once done you can reset your modem and you should see your module start running.

## Linux
Unfortunately I don't know a way to upload a module without using a windows machine (or VM). However since the compiler is best run on linux I'm currently looking for a way to upload modules using only linux. There are currently two ways I can think of:
* [libopenpst](https://github.com/openpst/libopenpst) seems to implement a efs manager, however I did not yet try it and it seems to be no more supported (last commit was 2 years ago).
* Capturing USB traffic on windows and implementing a subset using libusb on linux (the way i'll probably go, but I didn't have time to do so yet).
* Implement a bootloader and upload images via serial (you still need qpst for initial upload and if you screw up).

None of those three ways are anywhere near a working condition.

## Troubleshooting
### My image does not load
Make sure you did upload it to the correct filesystem and you named it correctly.
