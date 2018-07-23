#include <FastLED.h>

#define LED_PIN     6
#define NUM_LEDS    60
#define CHIPSET     WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
#define BRIGHTNESS  10

const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;

void setup() {
  delay( 3000 ); // power-up safety delay
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalSMD5050 );
  FastLED.setBrightness( BRIGHTNESS );

  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  
  Serial.begin(9600); 
}

int color1=CRGB(255,0,0);
int color2=CRGB(20,90,110);
int color=color1;

int midPoint1 = NUM_LEDS/2;
int midPoint2 = midPoint1+1;
void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  Serial.print("Distance: ");
  Serial.println(distance);

  
  if (midPoint1==0){
    midPoint1 = NUM_LEDS/2;
    midPoint2 = midPoint1+1;
  }
  
  
  
    leds[midPoint1]=color;
    leds[midPoint2]=color;
    FastLED.show();
    FastLED.delay(16.6666667);
  midPoint1--;
  midPoint2++;
  if (color==color1){
    color==color2;
  } 
  if (color==color2){
    color==color1;
  } 
 
}




