Purpose of this fork
----------------------------
I am attempting to expand functionality to the remote control feature of GQRX.  I would also like to add startup features and a serial communication stack.  

Ideally I would like to expose all of the GUI controls over the TCP/Telnet stack. In addition to being able to send "set/get" requests for variables such as the frequency, I would like to be able to send instructions to increase / decrease a variable by a value. 

For example the Frequency commands/variable:

f - returns current frequency 
F 145000000\n - sets frequency to 145mhz

I would like to add increase / decrease commands:

FI 1000000\n - increase current frequency by 1mhz
FD 1000000\n - decrease current frequency by 1mhz


Ideas for startup flags / features
------------------------
- Auto start DSP processing
- Start in Fullscreen mode
- Start with TCP control stack running
- Start with UDP audio stack running


Serial Stack
------------------------
This is basically taking the entire TCP control stack and copying it to run over a serial input, and accept commands from something like an Arduino. 



New Remote Control Features
----------
Gain
- get - g
- set - G
- increase - GI
- decrease - GD

LNB
- get - n 
- set - N
- increase - NI
- decrease - ND

PPM
- get - p
- set - P
- increase - PI
- decrease - PD

Squelch
- get - s
- set - S 
- increase - SI
- decrease - SD

RO
- get - r
- set - R
- increase - RI
- decrease - RD

Freq
- increase - FI
- decrease - FD

Audio Gain
- get - a
- set - A
- increase - AI
- decrease - AD

Bandwidth
- get - b
- set - B
- increase - BI
- decrease - BD

FFT
- get - t
- set - T
- increase - TI
- decrease - TD


FFT Rate
- get - y 
- set - Y
- increase - YI
- decrease - YD


Zoom
- center - ZC
- get - z
- set - Z
- increase - ZI
- decrease - ZD

USB - start / stop DSP processing
- start - x
- stop - X

Other
- Fullscreen 
 - on - k 
 - off - K

- UDP Audio Stream 
 - on - u
 - off - U