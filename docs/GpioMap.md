# GPIO Mapping between Pinout and DAM Pinid (Qualcomm SoC pin)

Name     | Pin | DAM Pin | Description
---------|-----|---------|------------
GPIO4    |   48|       26| GPIO Pin 4
GPIO3    |   68|       11| GPIO Pin 3
GPIO2    |   67|       10| GPIO Pin 2
NETLIGHT |   52|       50| Netlight LED Output (Seems like after boot it can be reconfigured and used by DAM)
I2C_SDA  |   37|        2| I2C Port Data
I2C_SCL  |   38|        3| I2C Port Clock
ADC      |   25|        ?| ADC Port, seems to be not usable
LOG_TX   |   23|      32?| LOG TX, no pin found
PCM_DOUT |   14|       22| PCM Data out
PCM_DIN  |   13|       21| PCM Data in
PCM_SYNC |   12|       20| PCM Sync
PCM_CLK  |   11|       23| PCM Clock
RXD      |   10|        ?| AT UART RX
TXD      |    9|        ?| AT UART TX
RTS      |    8|        ?| AT UART RTS
CTS      |    7|        ?| AT UART CTS
BOOT_CFG |    6|       37| Bootconfig pin
DCD      |    5|       18| AT UART DCD
RI       |    4|       19| AT UART RI (No pullup ?)
DTR      |    3|        ?| AT UART DTR

There seems to be a total of 80 GPIO's which can be opened from software, but they are most likely not available in any sensable way.
Reconfiguring GPIO 4,5,6 or 7 to a Input with pullup seems to crash the module and enter some mode of qualcomms sock, because the USB device disconnects and reappears as 
"QHSUSB_BULK" Vendor "Qualcomm CDMA Technologies MSN".