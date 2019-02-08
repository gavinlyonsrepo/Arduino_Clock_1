Overview
--------------------
* Name : clock_number_1
* Title : Arduino Real Time Clock with Alarm and environmental sensors
* Description : Arduino Clock , with , Battery backup (real time clock), Time, Date, Alarm, Temperature, Humidity, Pressure, LCD output, Keypad input, Sleep mode, LED LCD lighting (4X) white with dimmer control
* Author: Gavin Lyons

Libraries
------------------------

In src folder you will find the ino file which contains the source code 
It calls from a number of libraries.

* <LCD5110_Graph.h> //5110 Nokia
* <Keypad.h> //keypad
* <SFE_BMP180.h> //pressure sensor
* <dht.h> //DHT11 humidity sensor
* <DS1307RTC.h> //Real time clock
* <Sleep_n0m1.h> //sleep function https://github.com/n0m1/Sleep_n0m1

All are standard libraries which can be found on Arduino website site except "sleep_n0m1" see link.

Parts List
------------------------------
See eagle schematic "doc". 

You will need following parts

>Nokia 5110 LCD module
>
>Arduino UNO rev 3 or NANO
>
>Keypad 4x3 (note: 4x4 I use 4x4 but leave last column unconnected so its a 4x3 in effect)
>
>DS 1307 Real Time Clock module (with battery)
>
>7 X 10K , 1 X 10ohm  , 1 X 220ohm  resistors
>
>LM35 temperature sensor
>
>BMP180 pressure sensor module
>
>DHT11 humidity Sensor module
>
>one 10K potentiometer 
>
>one active buzzer (alarm)
>

Current Consumption:

1. 27mA, On with LEDs on Nokia LCD set to min.
2. 25mA, Nokia LCD sleep mode On.
3. 18mA, Atmega328p Sleep mode On.
4. 40mA, On with LEDs on Nokia LCD set to max.

Schematic
---------------------------

![ScreenShot schematic](https://github.com/gavinlyonsrepo/Arduino_Clock_1/blob/master/doc/eagle/clock1.png)


Keypad function
--------------------------------

* 1, LM35 sensor data
* 2, DHT11 sensor data
* 3, BMP180 sens data 
* 4, Alarm Show
* 5, Alarm Set
* 6, Alarm Test
* 7, Help Mode
* 8, LCD on/off
* 9, Set date and time
* 0, Sleep mode
* Asterisk, Alarm Stop
* Hash, LCD reset

Copyright
-------------------------------

Copyright (C) 2016 G Lyons This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, see license.md for more details
