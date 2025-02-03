/*
  Arduino BMI270_BMM150 - Simple Accelerometer

  This example reads the acceleration values from the BMI270_BMM150
  sensor and continuously prints them to the Serial Monitor
  or Serial Plotter.

  The circuit:
  - Arduino Nano 33 BLE Sense Rev2

  created 10 Jul 2019
  by Riccardo Rizzo

  This example code is in the public domain.
*/

#include <Arduino_BMI270_BMM150.h>
#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        14 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 4 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

float x, y, z;
int degreesX = 0;
int degreesY = 0;

void setup() {
  Serial.begin(9600);
  //while (!Serial);
  Serial.println("Started");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {
  float x, y, z;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);
    pixels.clear(); // Set all pixel colors to 'off'

    if (x > 0.1) {
      x = 100 * x;
      degreesX = map(x, 0, 97, 0, 90);
      Serial.print("Tilting up ");
      Serial.print(degreesX);
      Serial.println("  degrees");
      // The first NeoPixel in a strand is #0, second is 1, all the way up
      // to the count of pixels minus one.
      for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        pixels.setPixelColor(i, pixels.Color(255, 255, 255));

        pixels.show();   // Send the updated pixel colors to the hardware.
      }
    }
    if (x < -0.1) {
      x = 100 * x;
      degreesX = map(x, 0, -100, 0, 90);
      Serial.print("Tilting down ");
      Serial.print(degreesX);
      Serial.println("  degrees");
      // The first NeoPixel in a strand is #0, second is 1, all the way up
      // to the count of pixels minus one.
      for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        pixels.setPixelColor(i, pixels.Color(0, 0, 255));

        pixels.show();   // Send the updated pixel colors to the hardware.
      }
    }
    if (y > 0.1) {
      y = 100 * y;
      degreesY = map(y, 0, 97, 0, 90);
      Serial.print("Tilting left ");
      Serial.print(degreesY);
      Serial.println("  degrees");
      // The first NeoPixel in a strand is #0, second is 1, all the way up
      // to the count of pixels minus one.
      for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        pixels.setPixelColor(i, pixels.Color(0, 255, 0));

        pixels.show();   // Send the updated pixel colors to the hardware.
      }
    }
    if (y < -0.1) {
      y = 100 * y;
      degreesY = map(y, 0, -100, 0, 90);
      Serial.print("Tilting right ");
      Serial.print(degreesY);
      Serial.println("  degrees");
      // The first NeoPixel in a strand is #0, second is 1, all the way up
      // to the count of pixels minus one.
      for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        pixels.setPixelColor(i, pixels.Color(255, 0, 0));

        pixels.show();   // Send the updated pixel colors to the hardware.
      }
    }
  }
}
