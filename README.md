# nexagateway

A very simple gateway app for Nexa automation units running on Arduino. This is just a toy software, with time I will port to other languages and make it better.

## How it works

It just opens a TCP port and waits for data, when it gets forwards to a serial port where the Arduino is connected. 

## Usage

```
./haabnexa [OPT]
HAAB Nexa Gateway
Possible options:
-o [PORT] should be something like /dev/ttyUSB0 (linux)
-p [PARITY] setup parity and data bits as XYZ

    [XYZ]
    X - Data bits can be 5,6,7 or 8
    Y - Parity can O,E or N
    Z - Stop bits can be 1 or 2

-s [SPEED] as a integer like 9600, 14400 etc... you know...
-n [PORT] as a integer network port number, being 5697 the dedault
```

