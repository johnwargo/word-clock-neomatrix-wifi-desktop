# World Clock NeoMatrix 8x8 Wi-Fi Edition

This repository contains an updated version of the [WORD CLOCK - NeoMatrix 8x8 Desktop Edition](https://github.com/andydoro/WordClock-NeoMatrix8x8) project by [Andy Doro](https://andydoro.com/) & [Dano Wall](https://github.com/danowall). Here's some details from the original project:

* [Andy Doro World Clock Desktop](https://andydoro.com/wordclockdesktop/)
* [Adafruit Learn Guide](https://learn.adafruit.com/neomatrix-8x8-word-clock/)
* [GitHub Repository](https://github.com/andydoro/WordClock-NeoMatrix8x8)

I forked the project because my personal implementation of the clock got way behind time-wise, so I decided to rebuild the code for a Wi-Fi enabled device (Adafruit Feather device) so it can periodically update the real-time clock (RTC) using an [Internet Time Server](https://tf.nist.gov/tf-cgi/servers.cgi) and [Network Time Protocol](https://en.wikipedia.org/wiki/Network_Time_Protocol). 

## Updates

When I first started looking at the code in detail, it took me longer than I expected to figure out what the code was doing. There were some things in the wrong place (in my opinion), so I decided to refactor the code a bit as I worked on it. So far, I made the following changes:

* Move the sketch's configuration settings to an external file I could exclude from the repo. By doing this, and by including a separate file users must rename before compiling the project, users can refresh their local code base from the public repository without wiping out their configuration settings. 
* Added more comments explaining the code in more detail (for users who want to better understand what's happening in the sketch).
* Renamed all the project files using dashes instead of camelCase. Why? Just because - makes it more consistent and, I think, easier to read.

**Goals** 

* Update the readme with more detailed hardware requirements, configuration and setup instructions.

## Hardware

- [Feather whatever]
- [Feather RTC]
- [NeoPixel NeoMatrix 8x8](https://www.adafruit.com/products/1487)
- LASER cut faceplate & enclosure
- Enclosure bolts
- Enclosure Nuts
- Feather mounting bolts
- Feather mounting nuts

## Software

This code requires the following libraries:

- [RTClib](https://github.com/adafruit/RTClib)
- [DST_RTC](https://github.com/andydoro/DST_RTC)
- [Adafruit_GFX](https://github.com/adafruit/Adafruit-GFX-Library)
- [Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
- [Adafruit_NeoMatrix](https://github.com/adafruit/Adafruit_NeoMatrix)


## Wiring

- Solder DS1307 breakout to Trinket Pro, A2 to GND, A3 to PWR, A4 to SDA, A5 to SCL  
   If you leave off / clip the unused SQW pin on the RTC breakout, the breakout can sit right on top of the Trinket Pro for a compact design! It'll be difficult to reach the Trinket Pro reset button, but you can activate the bootloader by plugging in the USB.
- Solder NeoMatrix 5V to Trinket 5V, GND to GND, DIN to Trinket Pro pin 8.

## Grid Pattern


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

