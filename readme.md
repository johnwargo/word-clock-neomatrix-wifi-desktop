# World Clock NeoMatrix 8x8 Wi-Fi Edition

This repository contains a forked version of the [WORD CLOCK - NeoMatrix 8x8 Desktop Edition](https://github.com/andydoro/WordClock-NeoMatrix8x8) project by [Andy Doro](https://andydoro.com/) & [Dano Wall](https://github.com/danowall).  Here's some details for the original project:

## Original Project

* [Andy Doro World Clock Desktop](https://andydoro.com/wordclockdesktop/)
* [Adafruit Learn Guide](https://learn.adafruit.com/neomatrix-8x8-word-clock/)
* [GitHub Repository](https://github.com/andydoro/WordClock-NeoMatrix8x8)

### Clock Grid Pattern

``` text
A T W E N T Y D
Q U A R T E R Y
F I V E H A L F
D P A S T O R O
F I V E I G H T
S I X T H R E E
T W E L E V E N
F O U R N I N E
```

Acknowledgements:

  - Thanks [Dano](https://github.com/danowall) for faceplate / 3D models & project inspiration! 

## Project Updates

I forked the project because my personal implementation of the clock got way behind time-wise, so I decided to rebuild the code for a Wi-Fi enabled device (Adafruit Feather) so it can periodically update the real-time clock (RTC) using an [Internet Time Server](https://tf.nist.gov/tf-cgi/servers.cgi) and [Network Time Protocol](https://en.wikipedia.org/wiki/Network_Time_Protocol) (NTP). 

I've tried to maintain as much of the original code as possible. So far, I made the following changes:

* Move the sketch's configuration settings to an external file I could exclude from the repo. By doing this, and by including a separate file users must rename before compiling the project, users can refresh their local code base from the public repository without wiping out their configuration settings. 
* Removed the `DateTime theTime` global variable and declared it locally and passed it around as needed (global variables are bad).
* Added more comments explaining the code in more detail (for users who want to better understand what's happening within the sketch).
* Renamed the project files using dashes instead of camelCase; this names them consistently and, when you're working on systems where file name case matters, you won't have to deal with anything in upper case.
* Updated the enclosure files to accommodate the Adafruit Feather board and added the files to a separate folder in the repo
* Added LASER cutter files for a 12-inch clock face for a wall mounted unit.

For this version of the project, I selected the [Feather Huzzah 32](https://www.adafruit.com/product/3405); I became a big fan of the board's ESP32 chipset last year, so I knew the selected board had enough horsepower and memory for anything I needed.  For the Real-time Clock (RTC) board, I selected the [DS3231 Precision RTC FeatherWing - RTC Add-on For Feather Boards](https://www.adafruit.com/product/3028); its a high precision board that deals properly with different temperature conditions.

## Clock Operation

In the original project, the code set the real-time clock time using the build date/time for the Arduino Sketch running on the board. The sketch did this the first time it ran, and there was no easy way to update it later. As I mentioned in the introduction, I ran into some time leakage problems (after about a year running, the time wasn't anywhere near the actual time) so I wrote a simple modification to the code that let you reset it manually (read more in [Word Clock Time Issues](https://johnwargo.com/internet-of-things-iot/word-clock-time-issues.html)).

This version still has the original code that sets the RTC date/time using the build date/time, but since the sketch runs on an Arduino-compatible device with Wi-Fi, I can use Network Time Protocol to periodically update the RTC from the network. 

So, here's the order of RTC-related things in the sketch:

1. On startup, if the sketch detects that the RTC lost power (or was reset), set the RTC date/time to the build date/time.
2. On startup, if the device has a network connection (access to the Internet via Wi-Fi), use NTP to update the RTC date/time to the current date/time.
3. At midnight every day, if the device has a Wi-Fi connection, use NTP to update the RTC date/time to the current date/time. If the device doesn't have a network connection, it uses the date/time value currently in the RTC.

Some things about Time:

* With the sketch setting the date/time at startup based on the build date/time, if the device never connects to the Internet (to use NTP) then the clock will be as accurate as it can be with the stand-alone RTC.

* With a network connection, the device will update the RTC date/time every day which should improve accuracy.
* If the device loses its network connection, it will try periodically to reconnect. (IF I EVER ADD THAT FEATURE)


Explain about RTC and NTP

There's a loophole.


## Instructions

To keep this readme as simple as possible, I moved the assembly and software configuration instructions into separate files:

* [Assembly](docs/assembly.md)
* [Software Configuration](docs/software.md)

## Open Tasks

* Add Wi-Fi reconnect: https://randomnerdtutorials.com/solved-reconnect-esp32-to-wifi/
* Update the `readme.md` documentation explaining how the RTC and NTP stuff works together
* Document all of the configuration settings in the software.md file
* Write assembly instructions
* Add instructions for installing software libraries 
