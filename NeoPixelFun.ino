#include <Adafruit_NeoPixel.h>
#include <avr/power.h> // Comment out this line for non-AVR boards (Arduino Due, etc.)

#define PIN 4
#define NUMBEROFPIXELS 4

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBEROFPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(64);
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  //Colors need to be expressed as combinations of Red, Green, and Blue.  We call this RGB.
  //Use this site to find the RGB value for the color you want: http://www.rapidtables.com/web/color/RGB_Color.htm
  
  //Counting LEDs: The first LED is actually numbered 0. 
  
  //Turn on an individual LED with a delay
  //colorSet(pixelNumber,Red,Green,Blue,delay);
  
  colorSet(0,255,0,0,300); //Turn pixel 0 Red
  colorSet(1,0,255,0,300); //Turn pixel 1 Green
  colorSet(2,0,255,0,300); //Turn pixel 2 Blue
  colorSet(3,204,66,232,300); //Turn pixel 3 Purple
  colorSet(3,0,0,0,50); //Turn pixel 3 Off
  colorSet(2,0,0,0,50); //Turn pixel 2 Off
  colorSet(1,0,0,0,50); //Turn pixel 1 Off
  colorSet(0,0,0,0,50); //Turn pixel 1 Off

  
  //Set all the leds to one color
//  colorWipe(Red, Green, Blue, delay);
  colorWipe(255, 0, 0, 50); // Red
  colorWipe(0, 0, 255, 50); // Green

  //Send a theater pixel chase in...
  //theaterChase(Red, Green, Blue, Delay)
  theaterChase(127,   0,   0, 50); // Red
  
//  larsonScanner(Red, Green, Blue, scannerSpeed, numberOfScans);
  larsonScanner(255,255,51,100,10); //Yellow
  

}

/*********************************************/
/*   Don't change anything below here        */
/*********************************************/

//Set an individual pixel with a color
void colorSet(int pixelNumber, int red, int green, int blue, int wait){
  uint32_t color=strip.Color(red, green, blue);
  strip.setPixelColor(pixelNumber, color);
  strip.show();
  delay(wait);
}

// Fill the dots one after the other with a color
void colorWipe(int red, int green, int blue, uint8_t wait) {
  uint32_t color=strip.Color(red, green, blue);
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, color);
      strip.show();
      delay(wait);
  }
}


void larsonScanner(int red, int green, int blue, int scannerSpeed, int numberOfScans) {
  uint32_t c=strip.Color(red, green, blue);
  int count=0;
  int pos = 0, dir = 1; // Position, direction of "eye"
  while(count<numberOfScans){
    
    int j;
   
    strip.setPixelColor(pos    , c); // Center pixel is brightest
   
    strip.show();
    delay(scannerSpeed);
   
    // Rather than being sneaky and erasing just the tail pixel,
    // it's easier to erase it all and draw a new one next time.
    for(j=-2; j<= 2; j++) {
      strip.setPixelColor(pos+j, 0);
    }
   
    // Bounce off ends of strip
    pos += dir;
    if(pos < 0) {
      pos = 0;
      dir = -dir;
      count++;
    } else if(pos >= strip.numPixels()) {
      pos = strip.numPixels() - 1;
      dir = -dir;
    }
  }
 
}




//Theatre-style crawling lights.
void theaterChase(int red, int green, int blue, uint8_t wait) {
   uint32_t c=strip.Color(red, green, blue);
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

