# Word Clock (Feather) Software Configuration

This document contains information about the software configuration and installation for the Word Clock. 

## Required Software

Depending on your hardware setup and personal preferences, you'll need to make some changes to the Word Clock sketch and deploy it to the clock. You can use any text editor you want to edit the sketch's configuration settings, but you'll need one of the following Arduino development tools to compile and deploy the sketch to the clock

* [Arduino IDE](https://www.arduino.cc/en/software)
* [Arduino Web IDE](https://create.arduino.cc/editor)
* [Visual Studio Code](https://code.visualstudio.com/) with the [Arduino](https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino) extension.

Follow Adafruit's online instructions for configuring the developer tools for the Feather board you selected for this project.


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

If you skip this step, compilation of the sketch will generate a whole bunch of errors starting with:

```text
world-clock-neomatrix-wifi-desktop:110:54: error: 'NEOPIN' was not declared in this scope

 Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, NEOPIN,

                                                      ^

world-clock-neomatrix-wifi-desktop:114:29: error: 'LED_CONFIG' was not declared in this scope

                             LED_CONFIG);

                             ^
```

**Note:** If you ever refresh your local files from the repository, you may want to check the project's `changelog.md` file for any new configuration settings you'll need to copy over to your project's `config.h` file.

## Configuration Settings

The following sections describe the different configuration options for the project. I tried to break them up into groups to make it easier to find the settings you're looking for. 

**Note:** Many of the settings are defined as C language `#define` components. According to the [Arduino Documentation](https://www.arduino.cc/reference/en/language/structure/further-syntax/define/):

> `#define` is a useful C++ component that allows the programmer to give a name to a constant value before the program is compiled. Defined constants in arduino don’t take up any program memory space on the chip. The compiler will replace references to these constants with the defined value at compile time.

As you modify these settings, pay special attention to the format of the constant. For example, they're not code, so there's no need to end the line with a semi-colon (;). Strings, however, must be in double quotes.

### Host

The Arduino WiFi library allows a sketch to set the device name before initializing the Wi-Fi connection. With this value set, the device identifies itself on the network with this name. [Arduino Documentation](https://www.arduino.cc/en/Reference/WiFiNINAsetHostname).

```c
#define HOST_NAME "Word Clock (ESP32)"
```

### LED Settings

The project allows you to set LED brightness for day and night through these two constants:

```c
#define DAYBRIGHTNESS 40
#define NIGHTBRIGHTNESS 20
```

You can also control the cutoff time (in hours) for day and night through these two constants:

```c
#define MORNINGCUTOFF 7  // when does daybrightness begin?   7am
#define NIGHTCUTOFF   22 // when does nightbrightness begin? 10pm
```

When the sketch starts, you can have it flash each word on the display for the number of milliseconds defined in this constant.

```c
#define FLASHDELAY 250  // delay for startup "flashWords" sequence
``` 

While the sketch displays time, the colors behind the words shift over time; this constant defines how many milliseconds pass between each color shift.

```c
#define SHIFTDELAY 100   // controls color shifting speed
```

### NeoPixel Settings

The `NEOPIN` constant defines the Feather GPIO pin connected to the `DIN` connector on the NeoMatrix. If you assembled the electronics components as instructed in the assembly documentation, you don't need to make any changes here. If you connected the NeoMatrix to a different output pin on the Feather, you must change the value here accordingly. 

The Pinout labeling on the Feather is a little weird - the instructions I provided tell you to connect the NeoMatrix `DIN` to `A0` on the Feather, but that actually corresponds to GPIO 26 which is what you see in this constant.

```c
#define NEOPIN 26  
```

If you're using the NeoMatrix board listed in the [Hardware Components](https://github.com/johnwargo/world-clock-neomatrix-8x8-wifi#hardware-components) section of the repository's `readme.md` file, then you don't need to make any changes here. If you're using different hardware, you must adjust the code to accommodate your hardware configuration using the instructions provided in [Arduino Library Use](https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-use).

For example, if you're using three-color (RGB) LEDs in your NeoMatrix, use the following:

```c
#define LED_CONFIG NEO_RGB + NEO_KHZ800
```

If using four-color (RGBW) LEDs in your NeoMatrix, use the following:

```c
#define LED_CONFIG NEO_GRBW + NEO_KHZ800
```

### Network Settings

The whole point of this forked project is to enable a network connection in the clock so it can automatically update its real-time clock (RTC) over the network. The constants below define the SSID and password for the Wi-Fi network. Enter the appropriate values for your local between the quote marks.

```c
#define WIFI_SSID ""
#define WIFI_PSWD ""
```

For example:

```c
#define WIFI_SSID "MyHomeNetwork"
#define WIFI_PSWD "What are you looking at?"
```

The constant below defines how many seconds the device will attempt to connect to the Wi-Fi network before it aborts the connection.

```c
#define WIFI_TIMEOUT 10 //seconds
```

### Time Settings

The settings in this section specify how the sketch deals with locale, time zone, and Daylight Savings Time.

If you live in a country or territory that observes [Daylight Saving Time](https://en.wikipedia.org/wiki/Daylight_saving_time_by_country), adjust the following constant appropriately. Use 1 if you observe DST, 0 if you don't. 

**Note:** From the original repo's notes: This is programmed for DST in the US / Canada. If your territory's DST operates differently,
you'll need to modify the code in the calcTheTime() function to make this work properly.

```c
#define OBSERVE_DST 1
```

NTP returns the current time as Greenwich Mean Time (GMT), so to display the current time for your time zone, you must provide an offset value that's automatically added to the time returned from NTP. Enter a value below calculated based on your current time zone difference from GMT as follows:

> GMT_OFFSET * 3600

For example, I live in GMT-5, so I'd calculate mine as:

> -5 * 3600 = -18000

Examples:

* GMT-5 = -18000
* GMT-4 = -14400
* GMT-3 = -10800
* GMT-2 = -7200
* GMT-1 = -3600
* GMT = 0
* GMT+1 = 3600
* GMT+2 = 7200
* GMT+3 = 10800
* GMT+4 = 14400
* GMT+5 = 18000

So, if your clock operates at GMT, or you want the clock to show GMT, use the following:

```c
#define GMT_OFFSET 0  
```

For a clock running in Charlotte, North Carolina (US), use:

```c
#define GMT_OFFSET -18000
```

Every minute, the clock prints the current date/time value to the Serial Monitor. To display the date/time in US format (Month/Day/Year Hour:Minute), use:

```c
#define USE_US_DATE_TIME_FORMAT
```

To print the date/time value to the Serial Monitor in European format (Year-Month-Day 24Hour:Minute), comment out the constant like this: 

```c
// #define USE_US_DATE_TIME_FORMAT
```

The original project's author published a library that automatically deals with Daylight Savings Time issues in the sketch. You can control which rules the library uses for the clock. 

To use the US rules, comment out the EU string as shown in the following example:

```c
const char rulesDST[] = "US"; // US DST rules
// const char rulesDST[] = "EU";   // EU DST rules
```

To use the European rules, comment out the US string as shown in the following example:

```c
// const char rulesDST[] = "US"; // US DST rules
const char rulesDST[] = "EU";   // EU DST rules
```

## Deploying the Software

Once you've made all of the required changes to the configuration file, compile and deploy the sketch to your Word Clock and enjoy!
