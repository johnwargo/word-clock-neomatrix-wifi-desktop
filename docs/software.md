# Word Clock (Feather) Software Configuration

## Required Libraries

This project uses the following Arduino libraries:

- [RTClib](https://github.com/adafruit/RTClib)
- [DST_RTC](https://github.com/andydoro/DST_RTC)
- [Adafruit_GFX](https://github.com/adafruit/Adafruit-GFX-Library)
- [Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
- [Adafruit_NeoMatrix](https://github.com/adafruit/Adafruit_NeoMatrix)

To Install the libraries:

- [ ] Open the Arduino IDE, then open the Library Manager. To do this, open the **Tools** menu, then select **Manage Libraries** as shown in the following figure.

![Arduino IDE Tools Menu](images/arduino-ide-01.png)

- [ ] Locate each required library individually (its easiest to use Search) then install it into the IDE. 

**Note:** There are multiple RTC libraries, so make sure you select (and install) the right one.

![Arduino IDE Library Manager](images/arduino-ide-02.png)

## Configuration

I pulled the config into a separate file. Explain why

Before you try to compile and deploy this code, you must first copy the `config.copyme` file to `config.h`. When you're done, you'll have both files in the folder. The `config.copyme` is part of the source code repository, so any time you pull updates or changes down from GitHub, it may overwrite that file.  For that reason, the sketch uses the `config.h` file to store the configuration settings for the project. You can make any changes to the file that you want, and they won't be overwritten when you update the source code from the Internet.

To do this on Microsoft Windows, you can open Windows Explorer (the file system browser app) and copy it there.  If you're comfortable with the command line, you can open a Command Prompt, navigate to the project folder, and execute the following command:

```shell
copy config.copyme config.h
```

On Linux and macOS, open a terminal window, navigate to the project folder, and execute the following command:

```shell
cp config.copyme config.h
```



/*
    This is the configuration file for the project. The original source code repository
    for this project has the file included as `config.copyme` and you're supposed to
    copy the file to `config.h` before trying to compile and deploy the sketch to the
    Arduino hardware. This file won't appear in the Arduino IDE unless it's been copied
    to the right file name.

    Once you copy the file, make any configuration changes you want here and they won't
    be overwritten if you ever pull updated code from the Internet.
*/

#ifndef CONFIG_H
#define CONFIG_H

// Use the following to set the Wi-Fi name for the device
#define HOST_NAME "Word Clock (ESP32)"

// define pins
#define NEOPIN 26  // connect to DIN on NeoMatrix 8x8

// If using three-color (RGB) LEDs in your NeoMatrix, use the following
//#define LED_CONFIG NEO_GRB + NEO_KHZ800
// If using the four-color (RGBW) LEDs in your NeoMatrix, use the following
//#define LED_CONFIG NEO_GRBW + NEO_KHZ800
// If using Pixels wired for RGB bitstream (v1 FLORA pixels, not v2), use the following
#define LED_CONFIG NEO_RGB + NEO_KHZ800

// Do you live in a country or territory that observes Daylight Saving Time?
// https://en.wikipedia.org/wiki/Daylight_saving_time_by_country
// Use 1 if you observe DST, 0 if you don't. This is programmed for DST in the US / Canada. If your territory's DST operates differently,
// you'll need to modify the code in the calcTheTime() function to make this work properly.
#define OBSERVE_DST 1

/* NTP returns the current time as Greenwich Mean Time (GMT), so to
   display the current time for your time zone, you must provide an
   offset value that's automatically added to the time returned from
   NTP. Enter a value below calculated based on your current time
   zone difference from GMT as follows:

   GMT_OFFSET * 3600

   For example, I live in GMT-5, so I'd calculate mine as:

      -5 * 3600 = -18000

   Examples:

   -5 = -18000
   -4 = -14400
   -3 = -10800
   -2 = -7200
   -1 = -3600
   0 (GMT) = 0
   +1 = 3600
   +2 = 7200
   +3 = 10800
   +4 = 14400
   +5 = 18000
*/
#define GMT_OFFSET 0  

// Comment out the following line to display Date/Time values (in the monitor)
// in European format
#define USE_US_DATE_TIME_FORMAT

// Define US or EU rules for DST comment out as required. More countries could be added with different rules in DST_RTC.cpp
const char rulesDST[] = "US"; // US DST rules
// const char rulesDST[] = "EU";   // EU DST rules

// brightness based on time of day- could try warmer colors at night?
#define DAYBRIGHTNESS 40
#define NIGHTBRIGHTNESS 20

// cutoff times for day / night brightness. feel free to modify.
#define MORNINGCUTOFF 7  // when does daybrightness begin?   7am
#define NIGHTCUTOFF   22 // when does nightbrightness begin? 10pm

// define delays
#define FLASHDELAY 250  // delay for startup "flashWords" sequence
#define SHIFTDELAY 100   // controls color shifting speed

#define ENABLE_MONITOR

#define WIFI_SSID ""
#define WIFI_PSWD ""
#define WIFI_TIMEOUT 10 //seconds

#endif
