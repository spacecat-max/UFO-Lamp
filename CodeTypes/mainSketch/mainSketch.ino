/*
NOTE: the sensor is ON THE BOARD

I want this lamp to:
- on off switch (using button?)
- color switch (cycle) when detect swip left or right gesture
- bluetooth connection that allows for custom color selection of the lights (via website idk)

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

long pastTime = millis();
int rgbCount = 0;
int colorsLength;

//color generated using https://coolors.co/palettes/trending and https://coolors.co/generate
long rgbcolors[] = 
  {
    16069029,
    45198083
  };

void setup() 
{
  Serial.begin(9600);
  //while (!Serial);

  if (!APDS.begin()) 
  {
    Serial.println("Error initializing APDS-9960 sensor!");
  }
  rgbCount = 0;
  colorsLength = sizeof(rgbcolors) / sizeof(int); //determine item length of array 
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

    if((GESTURE_LEFT || GESTURE_RIGHT) && millis() - pastTime > 200)
    {
      if(rgbCount >= colorsLength - 1)
      {
        rgbCount = 0;
      }
      else
      {
        rgbCount++;
      }

      //bit shifting doesn't work to get decimal digits (base 10). it's easeir to mult/div by powers of 10 not shifts
      int r = rgbcolors[rgbCount] / 1000000; //remove last 6 digits 
      int g = int(rgbcolors[rgbCount] / 1000) % 1000; 
      int b =  rgbcolors[rgbCount] % 1000;

      Serial.println("color switch: " + String(rgbCount));
      Serial.println("Color: " + String(r) + ", " + String(g) + ", " + String(b));

      for (int i = 0; i < NUMPIXELS; i++) //loop for lighting up all the LEDs
      {
        pixels.setPixelColor(i, pixels.Color(r, g, b));
        pixels.show();   // Send the updated pixel colors to the hardware.
      }
    }
  }
}