# Simple-ZigBee-CC2530-switch-to-Zigbee2MQTT
Simple ZigBee switch based on TI's CC2530 connecting to Zigbee2MQTT

This is a prototype of a simple switch connecting to Zigbee2MQTT. It is based on a CC2530 from Texas Instruments using Z-Stack 3.0.2 and IAR 10.30 as compiler.

The foundation for the code is the GenericApp example with the ON-OFF Cluster functionality taken from the SampleSwitch example.

It is programmed as an End Device and is intended as a simple platform as starting point for future upgrades, where more switches, temperature sensors etc.can be implemented.

![IMG2](https://github.com/LemmeDasker/TestZigbee/assets/38005465/5e3acf4f-fb30-45d9-8a93-845ba9567916)

## Using the device
You will first have to connect two switches to pin P2.0, P0.1. The pins are interrupt enabled.

P2.0:
When powered on for the first time, the device will connect to the ZigBee network by pressing the switch.

P0.1:
When the switch is openend it will send an 'ON' commmand, and when put to GND it will send the 'OFF' command.

That's it.

## ZigBee2MQTT
You will need to use the file CC2530Converter.js as the ZigBee2MQTT converter file. Please refer to ZigBee2MQTT's support page for more info about configuring ZigBee2MQTT:
https://www.zigbee2mqtt.io/advanced/support-new-devices/01_support_new_devices.html


## HEX file
I have precopiled the code so you don't have to do it yourself. It is attached as 'CC2530App.hex'. You can use the CC Debugger to upload.
