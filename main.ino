#include <FastLED.h>
#include <AnalogSmooth.h>

#define LED_PIN     6
#define COLOR_ORDER GRB
#define CHIPSET     WS2811
#define NUM_LEDS    60
int upperLED = NUM_LEDS-1;

#define BRIGHTNESS  15
#define FRAMES_PER_SECOND 144
#define SENSOR_MINIMUM 2

bool gReverseDirection = false;
const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;

CRGB leds[NUM_LEDS];

void setup() {
  delay(3000); // sanity delay
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}


int i=0;
int j;
bool distanceOverflow = false;

CRGB whitePure=CRGB(255,255,255);
CRGB redPure=CRGB(255,0,0);
CRGB greenPure=CRGB(0,255,0);
CRGB greenPale=CRGB(0,25,0);
CRGB bluePure=CRGB(0,0,255);
CRGB yellowPure=CRGB(255,255,0);
CRGB dimgray=CRGB(105,105,105);
CRGB magenta=CRGB(255,0,255);

CRGB ALLBACK=CRGB(0,0,0);
uint8_t gHue = 0;

AnalogSmooth as = AnalogSmooth();
AnalogSmooth as4 = AnalogSmooth(4);

void loop(){
  FastLED.setBrightness( BRIGHTNESS );
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
/////////////////////////////////////////////////
  distanceOverflow = false;
  if (distance>59+SENSOR_MINIMUM){
    distance=59+SENSOR_MINIMUM;
    distanceOverflow = true;
  }

  Serial.print("Distance: ");
  Serial.println(distance);
  
  float distanceSmooth = as.smooth(distance);
  Serial.print("Smooth (5): ");  
  Serial.println(distanceSmooth);
  
  for (j=0;j<59;j++){
    leds[j]=ALLBACK;
  }
/////////////////////////////////////////////////
  CRGB color = magenta;
  CRGB backgroundColor = yellowPure;
  CRGB idleColor = yellowPure;
/////////////////////////////////////////////////
  move4(distanceSmooth-SENSOR_MINIMUM, color, backgroundColor, idleColor);
  //dotBouncy();
  //rainbow();
  
/////////////////////////////////////////////////
  FastLED.show(); // display this frame
  FastLED.delay(250 / FRAMES_PER_SECOND);
  
  
}

void move4(int startLED, CRGB color, CRGB backgroundColor, CRGB idleColor){
  
  if ( distanceOverflow == true ){
    for (j=0;j<59;j++){
    //FastLED.setBrightness( 10 );
    leds[j]=idleColor;
    }
  }
  
  if ( distanceOverflow == false ){
    if ( startLED == NUM_LEDS-1 ){
      setBackgroundColor(backgroundColor);
      leds[startLED]=color;
    } else
    if ( startLED == NUM_LEDS-2 ){
      setBackgroundColor(backgroundColor);
      leds[startLED]=color;
      leds[startLED+1]=color;
    } else
    if ( startLED == NUM_LEDS-3 ){
      setBackgroundColor(backgroundColor);
      leds[startLED]=color;
      leds[startLED+1]=color;
      leds[startLED+2]=color;
    } else {
    setBackgroundColor(backgroundColor);
   move4Child(startLED,color);
    }
  }
}

void move4Child (int startLED, CRGB color){
  leds[startLED]=color;
  leds[startLED+1]=color;
  leds[startLED+2]=color;
  leds[startLED+3]=color;
}

void setBackgroundColor (CRGB backgroundColor){
  int b;
  for (b=0;b<59;b++){
    leds[b]=backgroundColor;
  }
}

void dotBouncy (int upperLED){
  int cycle=0;
  
  
    leds[upperLED]=whitePure;
  
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}
void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

