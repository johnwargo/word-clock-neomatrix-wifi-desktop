# World Clock NeoMatrix 8x8 Wi-Fi Edition

This repository contains an updated version of the [WORD CLOCK - NeoMatrix 8x8 Desktop Edition](https://github.com/andydoro/WordClock-NeoMatrix8x8) project by [Andy Doro](https://andydoro.com/) & [Dano Wall](https://github.com/danowall). Here's some details from the original project:

* [Andy Doro World Clock Desktop](https://andydoro.com/wordclockdesktop/)
* [Adafruit Learn Guide](https://learn.adafruit.com/neomatrix-8x8-word-clock/)
* [GitHub Repository](https://github.com/andydoro/WordClock-NeoMatrix8x8)

## Updates

I forked the project because my personal implementation of the clock got way behind time-wise, so I decided to rebuild the code for a Wi-Fi enabled device (Adafruit Feather device) so it can periodically update the real-time clock (RTC) using an [Internet Time Server](https://tf.nist.gov/tf-cgi/servers.cgi) and [Network Time Protocol](https://en.wikipedia.org/wiki/Network_Time_Protocol). 

I've tried to maintain as much of the original code (as well as readme content) as possible. So far, I made the following changes:

* Move the sketch's configuration settings to an external file I could exclude from the repo. By doing this, and by including a separate file users must rename before compiling the project, users can refresh their local code base from the public repository without wiping out their configuration settings. 
* Removed the `DateTime theTime` global variable and declared it locally and passed it around as needed (global variables are bad).
* Added more comments explaining the code in more detail (for users who want to better understand what's happening in the sketch).
* Renamed the project files using dashes instead of camelCase; this names them consistently and, when you're working on systems where file name case matters, you won't have to deal with anything in upper case

**Goals** 

* Update the readme with more detailed hardware requirements, configuration and setup instructions.

* 

## Instructions

To keep this readme as simple as possible, I moved the assembly and software configuration instructions into separate files:

* [Assembly](assembly.md)
* [Software Configuration](software.md)
* 

## Clock Grid Pattern


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

