/*
  This example reads audio data from the on-board PDM microphones, and prints
  out the samples to the Serial console. The Serial Plotter built into the
  Arduino IDE can be used to plot the audio data (Tools -> Serial Plotter)

  Circuit:
  - Arduino Nano 33 BLE Sense Rev2 board

  This example code is in the public domain.
*/

#include <Adafruit_NeoPixel.h>
#include <PDM.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        14 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 4 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// buffer to read samples into, each sample is 16-bits
short sampleBuffer[256];

// number of samples read
volatile int samplesRead;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // configure the data receive callback
  PDM.onReceive(onPDMdata);

  // optionally set the gain, defaults to 20
  // PDM.setGain(30);

  // initialize PDM with:
  // - one channel (mono mode)
  // - a 16 kHz sample rate
  if (!PDM.begin(1, 16000)) {
    Serial.println("Failed to start PDM!");
    while (1);
  }

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.show();  // Initialize all pixels to 'off'
  pixels.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  Serial.println("Detecting gestures ...");
}

void loop() {
  pixels.clear(); // Set all pixel colors to 'off'
  // wait for samples to be read
  if (samplesRead) {

    // print samples to the serial monitor or plotter
    for (int i = 0; i < samplesRead; i++) {
      Serial.println(sampleBuffer[i]);
      // check if the sound value is higher than 500
      if (sampleBuffer[i] >= 500) {
        // The first NeoPixel in a strand is #0, second is 1, all the way up
        // to the count of pixels minus one.
        for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

          // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
          pixels.setPixelColor(i, pixels.Color(255, 0, 0));

          pixels.show();   // Send the updated pixel colors to the hardware.
        }
      }
      // check if the sound value is higher than 250 and lower than 500
      if (sampleBuffer[i] >= 250 && sampleBuffer[i] < 500) {
        // The first NeoPixel in a strand is #0, second is 1, all the way up
        // to the count of pixels minus one.
        for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

          // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
          pixels.setPixelColor(i, pixels.Color(255, 0, 0));

          pixels.show();   // Send the updated pixel colors to the hardware.
        }
      }
      //check if the sound value is higher than 0 and lower than 250
      if (sampleBuffer[i] >= 0 && sampleBuffer[i] < 250) {
        // The first NeoPixel in a strand is #0, second is 1, all the way up
        // to the count of pixels minus one.
        for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

          // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
          pixels.setPixelColor(i, pixels.Color(0, 255, 0));

          pixels.show();   // Send the updated pixel colors to the hardware.
        }
      }
    }

    // clear the read count
    samplesRead = 0;
  }
}

void onPDMdata() {
  // query the number of bytes available
  int bytesAvailable = PDM.available();

  // read into the sample buffer
  PDM.read(sampleBuffer, bytesAvailable);

  // 16-bit, 2 bytes per sample
  samplesRead = bytesAvailable / 2;
}
