# SleepDevice-Simple-ZigBee-CC2530-switch-to-Zigbee2MQTT
Simple sleeping ZigBee switch based on TI's CC2530 connecting to Zigbee2MQTT.
This version is similar to Simple-ZigBee-CC2530-switch-to-Zigbee2MQTT. The only but important difference is that this device goes into Sleep Mode when not used. This is ideal for battery powered devices. The power consumption is extremly low - about a few uA. 

It is based on a CC2530 from Texas Instruments using Z-Stack 3.0.2 and IAR 10.30 as compiler.

The foundation for the code is the GenericApp example with the ON-OFF Cluster functionality taken from the SampleSwitch example.

It is programmed as an End Device with Power Saving enabled and is intended as a simple platform as starting point for future upgrades, where more switches, temperature sensors etc.can be implemented.

![IMG2](https://github.com/LemmeDasker/TestZigbee/assets/38005465/5e3acf4f-fb30-45d9-8a93-845ba9567916)

## Compiling
Make sure you use these compile flags in the IAR compiler:

SECURE=1, TC_LINKKEY_JOIN, NV_INIT, NV_RESTORE, POWER_SAVING, NWK_AUTO_POLL
xZTOOL_P1, xMT_TASK, xMT_APP_FUNC, xMT_SYS_FUNC, xMT_ZDO_FUNC, xMT_ZDO_MGMT
xMT_APP_CNF_FUNC, xLEGACY_LCD_DEBUG, xLCD_SUPPORTED=DEBUG, MULTICAST_ENABLED=FALSE
ZCL_READ, ZCL_WRITE, ZCL_BASIC, ZCL_IDENTIFY, xZCL_SCENES, xZCL_GROUPS, ZCL_ON_OFF
xZCL_DISCOVER

And in the file: 8wConfig.cfg:

Change -DRFD_RCVC_ALWAYS_ON=TRUE

to

-DRFD_RCVC_ALWAYS_ON=FALSE.


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
