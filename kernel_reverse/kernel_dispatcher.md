## Kernel Dispatcher
Location in memory: 0x800A6088

Dumping the kernel dispatcher from memory reveals a quite simple function:
First it checks if the argument structure provided is on the stack (and has correct size).
If not it returns TX_SIZE_ERROR (5).
After this it checks if the call belongs to basic ThreadX functions (id < 95) and uses a jump table if it does.
If not it checks if the value is higher than 0x10000 (which is the base index for APP defined ids) and substracts this value.
It then restores the arguments and jumps to 0x800bf130, which should handle all user defined calls.
If the id is between 95 and 0x10000 it returns TX_NOT_AVAILABLE (0x1d). So note that despite the "NetX TCP/IP API" is listed in txm_module.h,
it is impossible to call it.

#### Jump table
The jump table uses "tbh [pc, ip, lsl 1]" which means it uses a jump table that starts immediatly after the opcode and is indexed by "ip" which is the call id.
The opcode reads the uint16_t at table\[ip\], multiplies it with to ("lsl 1") and jumps to "pc + offset". Dumping the table and calculating the resulting offsets leads to this:
Note that offset is *not* mutliplied.
Call ID | Offset | Destination | Description
--------|--------|-------------|-------------
1       | 0x5f   | 0x800A6182  | Target restores arguments and jumps to 0x800bebc8
2       | 0x66   | 0x800A6190  |
3       | 0x9a   | 0x800A61F8  |
4       | 0xa7   | 0x800A6212  |
5       | 0xb6   | 0x800A6230  |
6       | 0xc1   | 0x800A6246  |
7       | 0xca   | 0x800A6258  |
8       | 0xd0   | 0x800A6264  |
9       | 0xd6   |             |
10      | 0xdf   |             |
11      | 0x111  |             |
12      | 0x11e  |             |
13      | 0x12d  |             |
14      | 0x140  |             |
15      | 0x14f  |             |
16      | 0x155  |             |
17      | 0x15b  |             |

#### QAPI Handler
Checks if adjusted id is between 0 and 0x10000 and jumps to 0x801c42c0 if it is, otherwise jumps to 0x80091346.