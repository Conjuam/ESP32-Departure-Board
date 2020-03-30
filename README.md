# ESP32-Departure-Board
ESP32 Real Time Trains-powered Departure Board

## Credits
* swlines Ltd. - Realtime Trains API
* Network Rail - Provider of Data to Realtime Trains
* Benoît Blanchon - ArduinoJson Library

## Why?
I initially got the idea from an article about a Desktop Departure Board from [here](https://ukdepartureboards.co.uk/store/). However I was not prepared to pay £150(!) for their cheapest model. I had an ESP32 laying around and an LCD display so I thought I'd try and make something similar ~~and far worse-looking~~ for a fraction of the price. After about 9 of intermittent tinkering, I've finally achieved something what works and is stable.

## What Do I Need To Make My Own?
**Hardware**
* ESP-WROOM-32 Based Dev Board
* LCD Display (I used a 16x2 but a 20x4 is better suited)
* Plentiful supply of Jumper Leads
* Breadboard
* 2x 10k Potentiometer (optional - used for backlight and contrast control)
