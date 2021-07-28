# Word Clock (Feather) Software Configuration

This document contains information about the software configuration for the Word Clock. 

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

## Sketch Configuration

When I forked the original project, I pulled all of the configuration settings into a separate file, then hid that file from the repository. I then made a copy of the configuration file under a different name and included that file in the repository. I did this because if I kept the 'real' configuration file in the repo, after you make changes in the file to support your needs, any subsequent update from the repository would overwrite your changes. 

Before you try to compile and deploy the project's code, you must first copy the `config.copyme` file to `config.h`. When you're done, you'll have both files in the folder. The `config.copyme` is part of the source code repository, so any time you pull updates or changes down from GitHub, it may overwrite that file. You can make whatever changes you want to the `config.h` file, and they won't be overwritten when you update the source code from the Internet.

To do this on Microsoft Windows, you can open Windows Explorer (the file system browser app) and copy it there.  If you're comfortable with the command line, you can open a Command Prompt, navigate to the project folder, and execute the following command:

```shell
copy config.copyme config.h
```

On Linux and macOS, open a terminal window, navigate to the project folder, and execute the following command:

```shell
cp config.copyme config.h
```

**Note:** If you ever refresh your local files from the repository, you may want to check the project's `changelog.md` file for any new configuration settings you'll need to copy over to your project's `config.h` file.

## Configuration Settings


### Host Setting


// Use the following to set the Wi-Fi name for the device
```c
#define HOST_NAME "Word Clock (ESP32)"
```


### LED Settings

// brightness based on time of day- could try warmer colors at night?
```c
#define DAYBRIGHTNESS 40
#define NIGHTBRIGHTNESS 20
```


// cutoff times for day / night brightness. feel free to modify.
```c
#define MORNINGCUTOFF 7  // when does daybrightness begin?   7am
#define NIGHTCUTOFF   22 // when does nightbrightness begin? 10pm
```


// define delays
```c
#define FLASHDELAY 250  // delay for startup "flashWords" sequence
#define SHIFTDELAY 100   // controls color shifting speed
```




### NeoPixel Settings


```c
#define NEOPIN 26  
```


If using three-color (RGB) LEDs in your NeoMatrix, use the following
#define LED_CONFIG NEO_GRB + NEO_KHZ800
If using the four-color (RGBW) LEDs in your NeoMatrix, use the following
#define LED_CONFIG NEO_GRBW + NEO_KHZ800
If using Pixels wired for RGB bitstream (v1 FLORA pixels, not v2), use the following

```c
#define LED_CONFIG NEO_GRBW + NEO_KHZ800
```

```c
#define LED_CONFIG NEO_RGB + NEO_KHZ800
```

### Network Settings


```c
#define WIFI_SSID ""
#define WIFI_PSWD ""
```


```c
#define WIFI_TIMEOUT 10 //seconds
```


### Time Settings

Do you live in a country or territory that observes Daylight Saving Time?
https://en.wikipedia.org/wiki/Daylight_saving_time_by_country
Use 1 if you observe DST, 0 if you don't. This is programmed for DST in the US / Canada. If your territory's DST operates differently,
you'll need to modify the code in the calcTheTime() function to make this work properly.

```c
#define OBSERVE_DST 1
```

NTP returns the current time as Greenwich Mean Time (GMT), so to
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

```c
#define GMT_OFFSET 0  
```

// Comment out the following line to display Date/Time values (in the monitor)
// in European format
```c
#define USE_US_DATE_TIME_FORMAT
```


// Define US or EU rules for DST comment out as required. More countries could be added with different rules in DST_RTC.cpp
```c
const char rulesDST[] = "US"; // US DST rules
// const char rulesDST[] = "EU";   // EU DST rules
```

```c
// const char rulesDST[] = "US"; // US DST rules
const char rulesDST[] = "EU";   // EU DST rules
```


