# SleepDevice-CC2530-3_switches-to-Zigbee2MQTT
This sleeping ZigBee switch is based on TI's CC2530 connecting to Zigbee2MQTT.
It incoorporates 3 switches this device goes into Sleep Mode when not used. This is ideal for battery powered devices. The power consumption is extremly low - about a few uA. 

It is based on a CC2530 from Texas Instruments using Z-Stack 3.0.2 and IAR 10.30 as compiler.

The foundation for the code is the GenericApp example with the ON-OFF Cluster functionality taken from the SampleSwitch example.

It is programmed as an End Device with Power Saving enabled and is intended as a simple platform as starting point for future upgrades, where more switches, temperature sensors etc.can be implemented.

![IMG2](https://github.com/LemmeDasker/TestZigbee/assets/38005465/5e3acf4f-fb30-45d9-8a93-845ba9567916)

## Compiling
The compile flags are embedded in the IAR project file. But they can also be ssen in the Compile-flags.txt file.


## Connecting the device
You will first have to connect tree switches to pin P0.1, P1.2, P1.7 and a button to P2.0. The pins are interrupt enabled.
The LED indicator are on P1.0

## Using the device
P2.0:
When powered on for the first time, the device will connect to the ZigBee network by pressing the switch. The LED will blink during the process and turn off when joined.
Pressing and holding the button for 5 seconds will remove the device from the network and perform a Factory Reset. The LED will turn on when the reset begins and turn off when finished resetting.

P0.1, P1.2, P1.7:
When the switch is openend it will send an 'ON' commmand, and when put to GND it will send the 'OFF' command.

That's it.

## ZigBee2MQTT
You will need to use the file CC2530Converter.js as the ZigBee2MQTT converter file. Please refer to ZigBee2MQTT's support page for more info about configuring ZigBee2MQTT:
https://www.zigbee2mqtt.io/advanced/support-new-devices/01_support_new_devices.html


## HEX file
I have precopiled the code so you don't have to do it yourself. It is attached as 'CC2530App.hex'. You can use the CC Debugger to upload.
