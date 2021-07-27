#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <RTClib.h>

#define NEOPIN 26  // connect to DIN on NeoMatrix 8x8
#define LED_CONFIG NEO_RGB + NEO_KHZ800

RTC_DS3231 rtc; // Establish clock object

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, NEOPIN,
                            NEO_MATRIX_TOP  + NEO_MATRIX_LEFT +
                            NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
                            LED_CONFIG);

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
