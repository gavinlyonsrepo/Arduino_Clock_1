Overview
--------------------
* Name : clock_number_1
* Title : Arduino Real Time Clock with Alarm and environmental sensors
* Description : Arduino Clock, Features: RTC with battery (real time clock), Time, Date, Alarm, Temperature, Humidity, Pressure, LCD output, Keypad input, Sleep modes, LED LCD lighting (4X) white with dimmer control.
* Author: Gavin Lyons

Software Used
------------------
Arduino 1.8.5

Eagle 9.0.1

Libraries Used
------------------------

| Name | Function | Version | Link |
| --- | --- | --- | --- |
| Keypad.h | keypad | 3.1.1  | [URL](https://github.com/Chris--A/Keypad)  |
| SFE_BMP180.h | BMP180 sensor | n/a | [URL](https://github.com/LowPowerLab/SFE_BMP180) |
| LCD5110_Graph.h | LCD 5110 | 2.13  | [URL](http://www.rinkydinkelectronics.com/library.php?id=47)  |
| dht.h  | DHT11 sensor | 0.1.0  | [URL](https://github.com/RobTillaart/Arduino/tree/master/libraries/DHTlib) |
| DS1307RTC.h  | RTC | 1.4.1 |  [URL](https://github.com/PaulStoffregen/DS1307RTC) |
| Sleep_n0m1.h | Sleep mode | 1.1.0 | [URL](https://github.com/n0m1/Sleep_n0m1) |


Parts List
------------------------------
See eagle schematic in "doc" folder.

You will need following parts

>
>Nokia 5110 LCD module
>
>Arduino UNO rev 3 or NANO
>
>Keypad 4x3 (note: I use 4x4 but leave last column unconnected so its a 4x3 in effect)
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

1. 40mA, Unit On with LEDs on Nokia LCD set to max.
2. 26mA, Unit On with LEDs on Nokia LCD set to min.
3. 24mA, Above with Nokia LCD sleep mode On.
4. 15mA, Above with Atmega328p  (Unit) Sleep mode On.


Schematic
---------------------------

![ScreenShot schematic](https://github.com/gavinlyonsrepo/Arduino_Clock_1/blob/master/doc/eagle/clock1.png)

Keypad function
--------------------------------

* 1, LM35 sensor data
* 2, DHT11 sensor data
* 3, BMP180 sensor data 
* 4, Alarm Show
* 5, Alarm Set
* 6, Buzzer Test
* 7, Display keypad Help information
* 8, LCD screen Sleep mode on/off
* 9, Set date and time
* 0, Unit Sleep mode, wakes at Alarm.
* Asterisk, Alarm Stop
* Hash, LCD screen reset ( In event of LCD problem)

Copyright
-------------------------------

Copyright (C) 2016 G Lyons This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, see license.md for more details
