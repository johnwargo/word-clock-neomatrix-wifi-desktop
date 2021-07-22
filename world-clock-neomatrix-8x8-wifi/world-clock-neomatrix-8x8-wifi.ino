/*
   WORD CLOCK - 8x8 NeoPixel Desktop Edition
   by Andy Doro

   A word clock using NeoPixel RGB LEDs for a color shift effect.

   Software:

   This code requires the following libraries:

   - RTClib https://github.com/adafruit/RTClib
   - DST_RTC https://github.com/andydoro/DST_RTC
   - Adafruit_GFX https://github.com/adafruit/Adafruit-GFX-Library
   - Adafruit_NeoPixel https://github.com/adafruit/Adafruit_NeoPixel
   - Adafruit_NeoMatrix https://github.com/adafruit/Adafruit_NeoMatrix

   grid pattern

    A T W E N T Y D
    Q U A R T E R Y
    F I V E H A L F
    D P A S T O R O
    F I V E I G H T
    S I X T H R E E
    T W E L E V E N
    F O U R N I N E

    Acknowledgements:
    - Thanks Dano for faceplate / 3D models & project inspiration!
*/

// ==============================================================================
/*
    Updated by John M. Wargo, July, 2021
    Updated the code to use the Wi-Fi enabled Adafruit Feather devices
    so the code updates the date/time once a day via Network Time
    Protocol (NTP) over the Wi-Fi network.

    Also refactored the code to move configuration settings to an
    external file to make it easier to separate code and config
    (for future updates).
*/
// ==============================================================================

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <DST_RTC.h>
#include <NTPClient.h>
#include <RTClib.h>
#include <strings.h>
#include <WiFi.h>
#include <WiFiUdp.h>
// sketch libraries
#include "config.h"

char DateAndTimeString[20];

// define how to write each of the words
// 64-bit "mask" for each pixel in the matrix- is it on or off?
uint64_t mask;

// define masks for each word. we add them with "bitwise or" to generate a mask for the entire "phrase".
#define MFIVE    mask |= 0xF00000000000        // these are in hexadecimal
#define MTEN     mask |= 0x5800000000000000
#define AQUARTER mask |= 0x80FE000000000000
#define TWENTY   mask |= 0x7E00000000000000
#define HALF     mask |= 0xF0000000000
#define PAST     mask |= 0x7800000000
#define TO       mask |= 0xC00000000
#define ONE      mask |= 0x43
#define TWO      mask |= 0xC040
#define THREE    mask |= 0x1F0000
#define FOUR     mask |= 0xF0
#define FIVE     mask |= 0xF0000000
#define SIX      mask |= 0xE00000
#define SEVEN    mask |= 0x800F00
#define EIGHT    mask |= 0x1F000000
#define NINE     mask |= 0xF
#define TEN      mask |= 0x1010100
#define ELEVEN   mask |= 0x3F00
#define TWELVE   mask |= 0xF600
#define ANDYDORO mask |= 0x8901008700000000

// Used to define the LEDs to illuminate when connecting to Wi-Fi
// and the NTP server
#define LETTER_W 3
#define LETTER_T 2

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//RTC_DS1307 RTC; // Establish clock object
RTC_DS3231 rtc; // Establish clock object
DST_RTC dst_rtc; // DST object

int lastMinute = -1;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

// Parameter 1 = number of pixels in the strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//Adafruit_NeoPixel matrix = Adafruit_NeoPixel(64, NEOPIN, NEO_GRB + NEO_KHZ800);
// configure for 8x8 neopixel matrix
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, NEOPIN,
                            NEO_MATRIX_TOP  + NEO_MATRIX_LEFT +
                            NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
                            // from the external config file (user configurable based on hardware)
                            LED_CONFIG);

void setup() {
  DateTime theTime;

  Serial.begin(115200);
  delay(2000);

  // set pinmodes
  pinMode(NEOPIN, OUTPUT);

  // ============================================
  // Don't think we'll need these on the Feather
  // ============================================
  //  // set analog pins to power DS1307 breakout!
  //  pinMode(RTCGND, OUTPUT); // analog 2
  //  pinMode(RTCPWR, OUTPUT); // analog 3
  //  digitalWrite(RTCGND, LOW);  // GND for RTC
  //  digitalWrite(RTCPWR, HIGH); // PWR for RTC
  // ============================================

  // Initialize the realtime clock
  if (! rtc.begin()) {
    Serial.println("\nUnable to initialize RTC");
    Serial.flush();
    abort();
  }
  // Check to see if the RTC has a time set
  // We don't really need to do this since we're going to get the time from
  // the network, but the RTC allows this thing to work even if the network
  // is down for a long period. Need to think about this.
  if ( !rtc.lostPower()) {
    // set the RTC time to the compile date/time on the sketch
    Serial.println("\nSetting RTC to sketch time");
    rtc.adjust(DateTime(__DATE__, __TIME__));
    // DST? If we're in it, let's subtract an hour from the RTC time to keep our DST calculation correct. This gives us
    // Standard Time which our DST check will add an hour back to if we're in DST.
    DateTime standardTime = rtc.now();
    if (dst_rtc.checkDST(standardTime) == true) { // check whether we're in DST right now. If we are, subtract an hour.
      standardTime = standardTime.unixtime() - 3600;
    }
    rtc.adjust(standardTime);

    // Double-check by pulling the time from the clock
    theTime = getAdjustedTime();
    // and printing it to the monitor
    printTimeValue(theTime);
  }

  matrix.begin();   // Initialize the NeoMatrix
  clearDisplay();   // empty/clear the display

  // Now, show the LED we're going to use to indicate we're connecting to Wi-Fi
  matrix.setPixelColor(LETTER_W, 0, 0, 255);  // Turn on the 'W' (Wi-Fi) LED
  matrix.show();

  // Connect to the Wi-Fi network
  int loopCounter = 0;
  Serial.print("\nConnecting to the '");
  Serial.print(WIFI_SSID);
  Serial.print("' network");
  WiFi.begin(WIFI_SSID, WIFI_PSWD);
  while (WiFi.status() != WL_CONNECTED) {
    // increment the loop counter
    ++loopCounter;
    // have we looped the configured number of times? Get out of the while loop
    if (loopCounter > WIFI_TIMEOUT) {
      Serial.println("\nWi-Fi connection timed out");
      break;
    }
    delay(1000);
    Serial.print(".");
  }
  // Are we connected?
  if (WiFi.status() == WL_CONNECTED) {
    // then tell the world
    Serial.print("\nConnected, IP address: ");
    Serial.println(WiFi.localIP());
    // Update the RTC from the network
    timeClient.begin();
    timeClient.setTimeOffset(GMT_OFFSET);
    getNetworkTime();
    // get the updated time
    theTime = getAdjustedTime();
    // write it to the monitor
    printTimeValue(theTime);
  }

  // Set the current minute (used to decide when to display the time on the monitor)
  lastMinute = rtc.now().minute();

  // Turn off all of the LEDS
  clearDisplay();

  matrix.setBrightness(DAYBRIGHTNESS);
  // startup sequence... do colorwipe?
  //  delay(500);
  //  rainbowCycle(1);
  delay(500);
  flashWords(); // briefly flash each word in sequence
  delay(500);
}

void loop() {
  // What's the current time (according to the RTC)?
  DateTime theTime = getAdjustedTime();

  // If it's just after midnight
  if (theTime.hour() == 0 && theTime.minute() == 1) {
    if (WiFi.status() == WL_CONNECTED) {
      // updated the RTC From the network
      getNetworkTime();
      // retrieve the updated time (to use in the rest of the loop)
      // since we're assuming it was just updated from the network
      theTime = getAdjustedTime();
      printTimeValue(theTime);
    } else {
      Serial.print("\nSkipping network time check; no Wi-Fi connection");
    }
  }

  // Did the minute just change?
  if (theTime.minute() != lastMinute) {
    // Then update our last minute variable
    lastMinute = theTime.minute();
    printTimeValue(theTime);
  }

  // and update the display with the new time
  adjustBrightness(theTime);
  displayTime(theTime);
  // uncomment to show moon mode instead!
  //mode_moon(theTime);
  delay(100);
}

void clearDisplay() {
  matrix.fillScreen(0);
  matrix.show();
}

DateTime getAdjustedTime() {
  DateTime theTime;
  theTime = dst_rtc.calculateTime(rtc.now()); // takes into account DST
  return theTime;
}

void getNetworkTime() {
  Serial.println("\nGetting network time...");
  // Illuminate the first T in the matrix in green when checking network time
  clearDisplay();
  matrix.setPixelColor(LETTER_T, 255, 0, 0);
  matrix.show();
  // Now check the network for the current time
  if (timeClient.forceUpdate()) {
    // NTPClient returned true; so we must have gotten a time
    Serial.println("Updating RTC");
    // Set the clock with the retrieved network time
    rtc.adjust(timeClient.getEpochTime());
  } else {
    Serial.println("Unable to get time from NTP server (not sure why)");
    // Fill the matrix with RED
    matrix.fillScreen(matrix.Color(0, 255, 0));
    matrix.show();
    delay(2000);
  }
  clearDisplay();
}

void printTimeValue(DateTime timeVal) {
  Serial.print(daysOfTheWeek[timeVal.dayOfTheWeek()]);
  Serial.print(", ");
#ifdef USE_US_DATE_TIME_FORMAT
  // Get the hour in 12 hour format
  int theHour;
  theHour = timeVal.hour();
  if (theHour > 12) {
    theHour -= 12;
  }
  // Build the date/time string
  sprintf(DateAndTimeString, "%02d-%02d-%4d @ %d:%02d ", timeVal.month(), timeVal.day(), timeVal.year(), theHour, timeVal.minute());
  // Append our AM/PM
  if (timeVal.hour() > 12) {
    strcat(DateAndTimeString, "PM");
  } else {
    strcat(DateAndTimeString, "AM");
  }
#else
  // Build the European date/time string
  sprintf(DateAndTimeString, "%4d-%02d-%02d %d:%02d", timeVal.year(), timeVal.month(), timeVal.day(), timeVal.hour(), timeVal.minute());
#endif
  Serial.println(DateAndTimeString);
}
