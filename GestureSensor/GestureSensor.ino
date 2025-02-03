/*
  APDS-9960 - Gesture Sensor

  This example reads gesture data from the on-board APDS-9960 sensor of the
  Nano 33 BLE Sense and prints any detected gestures to the Serial Monitor.

  Gesture directions are as follows:
  - UP:    from USB connector towards antenna
  - DOWN:  from antenna towards USB connector
  - LEFT:  from analog pins side towards digital pins side
  - RIGHT: from digital pins side towards analog pins side

  The circuit:
  - Arduino Nano 33 BLE Sense
  - Neopixel

  This example code is in the public domain.
*/
#include <Adafruit_NeoPixel.h>
#include <Arduino_APDS9960.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        14 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 4 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

  int r = 0;
  int b = 0;
  int g = 0;
  int w = 0;
  long CurrentTime = 0;
  long StartTime = 0;


void setup() {
  Serial.begin(9600);
  //while (!Serial);

  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor!");
  }

  // for setGestureSensitivity(..) a value between 1 and 100 is required.
  // Higher values make the gesture recognition more sensitive but less accurate
  // (a wrong gesture may be detected). Lower values makes the gesture recognition
  // more accurate but less sensitive (some gestures may be missed).
  // Default is 80
  //APDS.setGestureSensitivity(80);

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.show();  // Initialize all pixels to 'off'
  pixels.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  Serial.println("Detecting gestures ...");

}
void loop() {
  if (APDS.gestureAvailable()) {
    // a gesture was detected, read and print to Serial Monitor
    int gesture = APDS.readGesture();

    StartTime = CurrentTime;
    CurrentTime = millis();

  //Serial.println(StartTime);
    //Serial.println(CurrentTime-StartTime);


    pixels.clear(); // Set all pixel colors to 'off'

    switch (gesture) {
      case GESTURE_UP:
        //Serial.println("Detected UP gesture");
        // The first NeoPixel in a strand is #0, second is 1, all the way up
        // to the count of pixels minus one.
        for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

          // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
          pixels.setPixelColor(i, pixels.Color(255, 0, 0));

          pixels.show();   // Send the updated pixel colors to the hardware.
        }
        r = 1;
          Serial.println("red");
        break;

      case GESTURE_DOWN:
        //Serial.println("Detected DOWN gesture");
        // The first NeoPixel in a strand is #0, second is 1, all the way up
        // to the count of pixels minus one.
        for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

          // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
          pixels.setPixelColor(i, pixels.Color(0, 255, 0));
          
          pixels.show();   // Send the updated pixel colors to the hardware.
        }
        g = 1;
          Serial.println("green");
        break;

      case GESTURE_LEFT:
        //Serial.println("Detected LEFT gesture");
        // The first NeoPixel in a strand is #0, second is 1, all the way up
        // to the count of pixels minus one.
        for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

          // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
          pixels.setPixelColor(i, pixels.Color(0, 0, 255));
          pixels.show();   // Send the updated pixel colors to the hardware.
        }
        b = 1;
          Serial.println("blue");
        break;

      case GESTURE_RIGHT:
        //Serial.println("Detected RIGHT gesture");
        // The first NeoPixel in a strand is #0, second is 1, all the way up
        // to the count of pixels minus one.
        for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

          // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
          pixels.setPixelColor(i, pixels.Color(255, 255, 255));

          pixels.show();   // Send the updated pixel colors to the hardware.
        }
        w = 1;
          Serial.println("white");
        break;

      default:
        // ignore
        break;
    }
  }

  //color combined!!
  if(CurrentTime - StartTime <= 1000 && CurrentTime != 0){
    
    //RED + WHITE
    if(w == 1 && r == 1){
      for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

          pixels.setPixelColor(i, pixels.Color(255, 0, 127));
          pixels.show();   // Send the updated pixel colors to the hardware.
        }
        Serial.println("light red");
    }

    //GREEN + RED
    if(g == 1 && r == 1){
      for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

          pixels.setPixelColor(i, pixels.Color(128, 91, 0));
          pixels.show();   // Send the updated pixel colors to the hardware.
        }
        Serial.println("brown");
    }

    //BLUE + RED
    if(b == 1 && r == 1){
      for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

          pixels.setPixelColor(i, pixels.Color(153, 51, 255));
          pixels.show();   // Send the updated pixel colors to the hardware.
        }
        Serial.println("purple");
    }

    //GREEN + BLUE
    if(g == 1 && b == 1){
      for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

          pixels.setPixelColor(i, pixels.Color(0, 126, 86));
          pixels.show();   // Send the updated pixel colors to the hardware.
        }
        Serial.println("forest green");
    }

    //GREEN + WHITE
    if(g == 1 && w == 1){
      for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

          pixels.setPixelColor(i, pixels.Color(255, 0, 127));
          pixels.show();   // Send the updated pixel colors to the hardware.
        }
        Serial.println("light green");
    }

    //BLUE + WHITE
    if(b == 1 && w == 1){
      for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

          pixels.setPixelColor(i, pixels.Color(153, 204, 255));
          pixels.show();   // Send the updated pixel colors to the hardware.
        }
        Serial.println("light blue");
    }

    //reset all variables
    w = 0;
    r = 0;
    g = 0;
    b = 0;
  }

}