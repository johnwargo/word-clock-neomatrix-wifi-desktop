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

Before you try to compile and deploy this code, you must first copy the `config.copyme` file to `config.h`. When you're done, you'll have both files in the folder. The `config.copyme` is part of the source code repository, so any time you pull updates or changes down from GitHub, it may overwrite that file.  For that reason, the sketch uses the `config.h` file to store the configuration settings for the project. You can make any changes to the file that you want, and they won't be overwritten when you update the source code from the Internet.

To do this on Microsoft Windows, you can open Windows Explorer (the file system browser app) and copy it there.  If you're comfortable with the command line, you can open a Command Prompt, navigate to the project folder, and execute the following command:

```shell
copy config.copyme config.h
```

On Linux and macOS, open a terminal window, navigate to the project folder, and execute the following command:

```shell
cp config.copyme config.h
```

