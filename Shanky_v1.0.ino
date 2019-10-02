/*
 * Hello This is the Code for Neo-pixel LEDs for Tree Costume (Tentative name)
 * The Code has 3 main setting 
 * 1st is low voice color pattern, 2nd medium voice color pattern, 3rd high voice color pattern
 * 
 * The colors and settings can be changed as per requirement
 * The Lines are commented with instructions and suggestions 
 * 
 * Tune the mic for adjusting its sensitivity 
 * The adjustment of mic will be combination of Tuning its on Board Potentiometer and changing values in Code
 * 
 * Note: Keep the code Clean and Name the version as v1.0 and save it with this in name to prevent confusion 
 * Save the working code on cloud to prevent loss of data
 * 
 * For any more query
 * Instagram: shanky_rt
 * 
 * 01-10-2019
 * Shanky Robot© 
 * Open-source
 */

#include <Adafruit_NeoPixel.h> //Please Download the Library from : https://github.com/adafruit/Adafruit_NeoPixel
#ifdef __AVR__
#include <avr/power.h>
#endif

#define BRIGHTNESS  24      //The brightness of the neo-pixels is set around 24, 
                            //Highest Brightness of LEDs is 255 but it drains too much power 
                            //Little tweaking can be done but 24 is ideal     

#define PIN            5    // The LEDs are connected to Arduino Uno's Digital Pin 5

#define NUM_LEDS      100   // I have put in Approximate number of Leds as 100 Inc

#include <RBD_Timer.h>      //Please Download the Library from : https://www.arduinolibraries.info/libraries/rbd_timer

RBD::Timer timer;

int sound;                  //The value of sound is defined 

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 50;                         // delay for half a second

void setup() {
  pixels.begin();                          // This initializes the NeoPixel library.
  Serial.begin(9600);

}

void loop() {
  unsigned long currentMillis = millis(); // this is time delay for adjusting the leds from frequent changes 
  Serial.println(sound);

  sound = analogRead(A0);                //The Mic is connected to Arduino Uno's Analog Pin 0
  delay(100);

  if (sound < 200) {                     // Low Voice sounds are detected (Change the value for adjusting to low voice)
  meteorRain(0,255,40,45, 64, true, 40); // The patterns function is: AquaGreen
                                         //pattern(Red value (0-255), Green value (0-255), Bluevalue (0-255), ...
                                         //..Fading tail by 25% , True (randomness in tail)/ False (smoothness in tail), 40 - the time delay(in millisecs) for the pattern movement (0 means fast movement) ) 
                                         // This is a meteor rain pattern
                                         //can be replaced with pattern of liking from: https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/
                                         // I Can help you out making the changes if needed 
  
  }

  if (sound >= 201 & sound <= 599) {      // Medium Voice range is detected (Change the value for adjusting to medium (usual) voice)
   meteorRain(0,255,0,45, 64, true, 40);  // meteor pattern with Green Color
  }

  if (sound >= 600) {                     //High level voice (if someone is shouting) (Change the value for adjusting to high voice)
   meteorRain(0,170,70,45, 64, true, 40); // Metero pattern with Ocean green Color
  }

}

/*
 * The next part is taken from adafruit neopixel libraries from https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/
 * If any other pattern is needed replace the function to the pattern of your liking 
 * Some functions below are common for all 
 * If need be The link provided above has very detailed instructions 
 * Please Turn the potentiometer on mic for fine tuning the voice sensitivity 
 * 
 */

void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {  
  // Like previously mention the values in the meteor can be changed to your liking
  setAll(0,0,0);
 
  for(int i = 0; i < NUM_LEDS+NUM_LEDS; i++) { // for reverse direction of pattern for(int i = (NUM_LEDS+NUM_LEDS)-1; i >= 0; i--)
   
   
    // fade brightness all LEDs one step
    for(int j=0; j<NUM_LEDS; j++) {
      if( (!meteorRandomDecay) || (random(10)>5) ) {
        fadeToBlack(j, meteorTrailDecay );        
      }
    }
   
    // draw meteor
    for(int j = 0; j < meteorSize; j++) {
      if( ( i-j <NUM_LEDS) && (i-j>=0) ) {
        setPixel(i-j, red, green, blue);
      }
    }
   
    showStrip();
    delay(SpeedDelay);
  }
}

// fades the leds black after meteor loop 
void fadeToBlack(int ledNo, byte fadeValue) {
 #ifdef ADAFRUIT_NEOPIXEL_H
    // NeoPixel
    uint32_t oldColor;
    uint8_t r, g, b;
    int value;
   
    oldColor = strip.getPixelColor(ledNo);
    r = (oldColor & 0x00ff0000UL) >> 16;
    g = (oldColor & 0x0000ff00UL) >> 8;
    b = (oldColor & 0x000000ffUL);

    r=(r<=10)? 0 : (int) r-(r*fadeValue/256);
    g=(g<=10)? 0 : (int) g-(g*fadeValue/256);
    b=(b<=10)? 0 : (int) b-(b*fadeValue/256);
   
    strip.setPixelColor(ledNo, r,g,b);
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   leds[ledNo].fadeToBlackBy( fadeValue );
 #endif  
}

// This is common function for adafruit neopixel pattern
// If you want to change pattern only change the above function and let the function below as it is 
void showStrip() {
 #ifdef ADAFRUIT_NEOPIXEL_H
   // NeoPixel
   strip.show();
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   FastLED.show();
 #endif
}

// This is common function as well
void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H
   // NeoPixel
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}

//This is common function as well
void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue);
  }
  showStrip();
}
