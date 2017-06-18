Overview
--------------------
* Name : clock_number_1
* Title : Arduino Real Time Clock with Alarm and environmental sensors
* Description : Arduino Clock , with , Battery backup (real time clock), Time, Date, Alarm, Temperature, Humidity, Pressure, LCD output, Keypad input, Sleep mode, LED LCD lighting (4X) white with dimmer control
* Author: Gavin Lyons


Libraries
------------------------
* <LCD5110_Graph.h> //5110 Nokia
* <Keypad.h> //keypad
* <SFE_BMP180.h> //pressure sensor
* <dht.h> //DHT11 humidity sensor
* <DS1307RTC.h> //Real time clock
* <Sleep_n0m1.h> //sleep function https://github.com/n0m1/Sleep_n0m1

All can be found on Arduino website site except "sleep_n0m1"

Parts List
------------------------------
See fritzing diagram in "doc" for assembly instruction.

You will need following parts

>Nokia 5110 LCD module
>
>Arduino UNO rev 3
>
>Keypad 4x3 or 4x4 I use 4x4 but leave last column unconnected so its a 4x3 in effect
>
>DS 1307 Real Time Clock module (with battery)
>
>9 Volt power supply unit or battery
>
>2 X10K resistors pullups for I2C bus
>
>LM35 temperature sensor
>
>BMP180 pressure sensor module
>
>DHT11 humidity Sensor module
>
>one 10K potentimeter + nut and knob (adjust brightness of LCD LEDs)
>
>one active piezo buzzer (alarm)
>
>Protoboard, wire, solder, tape,small screws and nuts
>
>one enclosure 

Copyright
-------------------------------

Copyright (C) 2016 G Lyons This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, see license.md for more details
