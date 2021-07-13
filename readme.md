# World Clock NeoMatrix 8x8 Wi-Fi Edition

This repository contains an updated version of the [WORD CLOCK - NeoMatrix 8x8 Desktop Edition](https://github.com/andydoro/WordClock-NeoMatrix8x8) project by [Andy Doro](https://andydoro.com/) & [Dano Wall](https://github.com/danowall). 

* [Adafruit Learn Guide](https://learn.adafruit.com/neomatrix-8x8-word-clock/)
* [Andy Doro World Clock Desktop](https://andydoro.com/wordclockdesktop/)
* [GitHub Repository](https://github.com/andydoro/WordClock-NeoMatrix8x8)

I forked the project because my implementation of the clock got way behind time-wise, so I decided to rebuild the code for a Wi-Fi enabled device (Adafruit Feather device) so it can periodically update the realtime clock using an [Internet Time Server](https://tf.nist.gov/tf-cgi/servers.cgi) and [Network Time Protocol](https://en.wikipedia.org/wiki/Network_Time_Protocol). 


Hardware:
-------

 - [Trinket Pro 5V](https://www.adafruit.com/product/2000) (should work with other Arduino-compatibles with minor modifications) 
 - [DS1307 RTC breakout](https://www.adafruit.com/products/3296)
 - [NeoPixel NeoMatrix 8x8](https://www.adafruit.com/products/1487)
 - LASER cut faceplate & enclosure

Software:
-------

This code requires the following libraries:

 - [RTClib](https://github.com/adafruit/RTClib)
 - [DST_RTC](https://github.com/andydoro/DST_RTC)
 - [Adafruit_GFX](https://github.com/adafruit/Adafruit-GFX-Library)
 - [Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
 - [Adafruit_NeoMatrix](https://github.com/adafruit/Adafruit_NeoMatrix)


Wiring:
-------

 - Solder DS1307 breakout to Trinket Pro, A2 to GND, A3 to PWR, A4 to SDA, A5 to SCL  
   If you leave off / clip the unused SQW pin on the RTC breakout, the breakout can sit right on top of the Trinket Pro for a compact design! It'll be difficult to reach the Trinket Pro reset button, but you can activate the bootloader by plugging in the USB.
 - Solder NeoMatrix 5V to Trinket 5V, GND to GND, DIN to Trinket Pro pin 8.


grid pattern:
-------

 ```
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

