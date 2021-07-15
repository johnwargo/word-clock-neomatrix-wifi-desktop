/*
   WORD CLOCK - 8x8 NeoPixel Desktop Edition
   by Andy Doro

   A word clock using NeoPixel RGB LEDs for a color shift effect.

   Hardware:
   - Trinket Pro 5V (should work with other Arduino-compatibles with minor modifications)
   - DS1307 RTC breakout
   - NeoPixel NeoMatrix 8x8


   Software:

   This code requires the following libraries:

   - RTClib https://github.com/adafruit/RTClib
   - DST_RTC https://github.com/andydoro/DST_RTC
   - Adafruit_GFX https://github.com/adafruit/Adafruit-GFX-Library
   - Adafruit_NeoPixel https://github.com/adafruit/Adafruit_NeoPixel
   - Adafruit_NeoMatrix https://github.com/adafruit/Adafruit_NeoMatrix


   Wiring:
   - Solder DS1307 breakout to Trinket Pro, A2 to GND, A3 to PWR, A4 to SDA, A5 to SCL
   If you leave off / clip the unused SQW pin on the RTC breakout, the breakout can sit right on top of the Trinket Pro
   for a compact design! It'll be difficult to reach the Trinket Pro reset button, but you can activate the bootloader by
   plugging in the USB.
   - Solder NeoMatrix 5V to Trinket 5V, GND to GND, DIN to Trinket Pro pin 8.


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

// Equipment
// ===========================================================
//Adafruit HUZZAH32 – ESP32 Feather Board
//https://learn.adafruit.com/adafruit-huzzah32-esp32-feather
//DS3231 Precision RTC FeatherWing - RTC Add-on For Feather Boards
//https://www.adafruit.com/product/3028
//Adafruit 2.13" Monochrome eInk / ePaper Display FeatherWing - 250x122 Monochrome with SSD1680
//https://www.adafruit.com/product/4195
// ===========================================================

#include <RTClib.h>
#include <DST_RTC.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
// sketch libraries
#include "config.h"

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

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//RTC_DS1307 RTC; // Establish clock object
RTC_DS3231 rtc; // Establish clock object
DST_RTC dst_rtc; // DST object

int j;   // an integer for the color shifting effect
int lastHour = -1;
int lastMinute = -1;

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

  Serial.begin(115200);
  delay(1000);

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
    Serial.println("Unable to initialize RTC");
    Serial.flush();
    abort();
  }
  // Check to see if the RTC has a time set
  if ( !rtc.lostPower()) {
    // set the RTC time to the compile date/time on the sketch
    Serial.println("Setting RTC to sketch time");
    rtc.adjust(DateTime(__DATE__, __TIME__));
    // DST? If we're in it, let's subtract an hour from the RTC time to keep our DST calculation correct. This gives us
    // Standard Time which our DST check will add an hour back to if we're in DST.
    DateTime standardTime = rtc.now();
    if (dst_rtc.checkDST(standardTime) == true) { // check whether we're in DST right now. If we are, subtract an hour.
      standardTime = standardTime.unixtime() - 3600;
    }
    rtc.adjust(standardTime);
  }

  // Initialize the NeoMatrix
  matrix.begin();
  matrix.setBrightness(0.1);
  // Set the LEDs to blue while connecting to the network
  //  matrix.setColor();
  matrix.fillScreen(1); // Turn on all of the LEDs
  matrix.show();

  // Connect to the Wi-Fi network
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PSWD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Wi-Fi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Turn off all of the LEDS
  //  matrix.setColor();
  matrix.setBrightness(DAYBRIGHTNESS);
  matrix.fillScreen(0);
  matrix.show();

  // Update the RTC from the network
  getNetworkTime();

  // Set the current time variables (used to decide when to check network time)
  //lastHour =
  //lastMinute=

  // startup sequence... do colorwipe?
  //  delay(500);
  //  rainbowCycle(1);
  delay(500);
  flashWords(); // briefly flash each word in sequence
  delay(500);
}

void loop() {
  DateTime theTime; // Holds current clock time

  // get the time
  theTime = dst_rtc.calculateTime(rtc.now()); // takes into account DST
  // add 2.5 minutes to get better estimates
  theTime = theTime.unixtime() + 150;
#ifdef ENABLE_MONITOR
  printTimeValue(theTime);
#endif

  adjustBrightness(theTime);
  displayTime(theTime);
  // uncomment to show moon mode instead!
  //mode_moon(theTime);

  // Put a little delay in the loop
  // no need to be in such a hurry
  delay(100);
}

void getNetworkTime() {

}

void printTimeValue(DateTime timeVal) {
  Serial.print(timeVal.year(), DEC);
  Serial.print('/');
  Serial.print(timeVal.month(), DEC);
  Serial.print('/');
  Serial.print(timeVal.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[timeVal.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(timeVal.hour(), DEC);
  Serial.print(':');
  Serial.print(timeVal.minute(), DEC);
  Serial.print(':');
  Serial.print(timeVal.second(), DEC);
  Serial.println();
}
