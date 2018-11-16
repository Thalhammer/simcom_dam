# GNSS Example (Batching)

This example demonstrates how to use the integrated GNSS receiver in batching mode.
One batch seems to be 40 samples and when everything is configured to automatic (mintime=0, mindistance=0)
The delay between two samples is 2 seconds meaning the batching callback will get called every 80 seconds.
Note that the first batch might take longer as it can take some time until the module gets a position fix,
which might take some time. In my tests the module almost always managed to get a fix (even inside a building)
but it might take multiple minutes if it does not have line of sight to the sky. If you can't get a fix or don't wan't
to wait some minutes try moving it to a window or retry outdoors.