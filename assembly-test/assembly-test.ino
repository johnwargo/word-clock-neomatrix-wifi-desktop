#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <RTClib.h>

/* Change this value if you connected the NeoPixel Matrix to a different
    Feather pin. The current value of 26 reflects A0 for the Feather 
    Huzzah 32 board as described here: 
    https://learn.adafruit.com/adafruit-huzzah32-esp32-feather/pinouts#gpio-and-analog-pins-2816355-15
*/
#define NEOPIN 26

RTC_DS3231 rtc; // Establish clock object

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, NEOPIN,
                            NEO_MATRIX_TOP  + NEO_MATRIX_LEFT +
                            NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
                            NEO_RGB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("setup()");

  // Initialize the realtime clock
  if (! rtc.begin()) {
    Serial.println("RTC Initialization Failed");
    Serial.flush();
    abort();
  }

  // Initialize the NeoMatrix
  Serial.println("Initializing the NeoPixel Matrix");
  pinMode(NEOPIN, OUTPUT);
  matrix.begin();
}

void loop() {
  Serial.println("loop()");
  Serial.println("Clearing display");
  matrix.fillScreen(0);
  matrix.show();
  delay(1000);
  Serial.println("Filling display with Blue");
  matrix.fillScreen(matrix.Color(0, 0, 255));
  matrix.show();
  delay(1000);
}
