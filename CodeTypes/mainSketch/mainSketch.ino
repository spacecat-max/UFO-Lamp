/*
NOTE: the sensor is ON THE BOARD

I want this lamp to:
- on off switch (using button?)
- color switch (cycle) when detect swip left or right gesture
- color gesture is cool
- bluetooth connection that allows for custom color selection of the lights

  Gesture directions are as follows:
  - UP:    from USB connector towards antenna
  - DOWN:  from antenna towards USB connector
  - LEFT:  from analog pins side towards digital pins side
  - RIGHT: from digital pins side towards analog pins side
*/
#include <Adafruit_NeoPixel.h>
#include <Arduino_APDS9960.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        14 // On Trinket or Gemma, suggest changing this to 1

#define NUMPIXELS 4 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

long CurrentTime = 0;
long StartTime = 0;


int rgbcolors[] = 
  {
    234085085, //red
    243156060, //orange
    236208063, //yellow
    110179094, //green
    073150200, //blue
    119078216 //purple
  };

int rgbCount = 0;

void setup() 
{
  Serial.begin(9600);
  //while (!Serial);

  if (!APDS.begin()) 
  {
    Serial.println("Error initializing APDS-9960 sensor!");
  }
  rgbCount = 0;
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.show();  // Initialize all pixels to 'off'
  pixels.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  Serial.println("Detecting gestures ...");
}

void loop() 
{
  if (APDS.gestureAvailable()) 
  {
    int gesture = APDS.readGesture();
    pixels.clear(); // Set all pixel colors to 'off'

    if(GESTURE_LEFT || GESTURE_RIGHT)
    {
      for (int i = 0; i < NUMPIXELS; i++) 
      {
        pixels.setPixelColor(i, pixels.Color((rgbcolors[rgbCount] >> 16) & 0xFF, (rgbcolors[rgbCount] >> 8) & 0xFF, rgbcolors[rgbCount] & 0xFF));
        pixels.show();   // Send the updated pixel colors to the hardware.
      }
    }
  }
}