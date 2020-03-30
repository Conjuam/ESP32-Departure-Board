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

**Software**
* Arduino IDE with support files installed [see here for a tutorial](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/)
* ArduinoJson Library (Tested with Version 6.15.0)
* [Realtime Trains Developer Account](https://api.rtt.io/)

## Wiring
| LCD | ESP32 |
|---|---|
| VSS | GND |
| VDD | 5V |
| V0 | GND |
| RS | 14 |
| RW | GND |
| E | 27 |
| D0 | N/C |
| D1 | N/C |
| D2 | N/C |
| D3 | N/C |
| D4 | 26 |
| D5 | 25 |
| D6 | 33 |
| D7 | 32 |
| A | 5V |
| K | GND |

## Configuration
* Input your WiFi Network Name & Password
* Change LCD Pins to match your set up [see here for help](https://www.arduino.cc/en/Tutorial/HelloWorld)
* Input your Realtime Trains Username and Password
* Add your [station code](https://www.nationalrail.co.uk/stations_destinations/48541.aspx) to the end of the URL
* Change the value for the Capacity Variable by inputting your JSON data in [this assistant](https://arduinojson.org/v6/assistant/)

## Done!
All you need to do now is upload the code and power on.
