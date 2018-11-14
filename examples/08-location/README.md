# GNSS Example (Tracking)

This example demonstrates how to use the integrated GNSS receiver in tracking mode.
When everything is configured to automatic (mintime=0, mindistance=0) the delay between
two samples is 1 second. Note that it might take some time until the module gets a position fix.
In my tests the module almost always managed to get a fix (even inside a building)
but it might take multiple minutes if it does not have line of sight to the sky. 
If you can't get a fix or don't wan't to wait some minutes try moving it to a window or retry outdoors.

## Capabilities callback
There is a mandatory capabilities callback which is expected to give you information about what modes are supported,
but it does not seem to get called at all. However the capabilities depend on the hardware, so it is not realy needed anyway.