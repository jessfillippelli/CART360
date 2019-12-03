//good file
#include <Adafruit_NeoPixel.h>


#define BUTTON  4
//#define NUMPIXELS 8
#define NUMPIXELS 60 
#define PIN 6 //neo

//sound
#define MICRO 8
int sensorValue = 0;

//for  8 led
//Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//for 60 LED
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_RGBW + NEO_KHZ800);
#define DELAYVAL 100

int buttonPushCounter = 0;
int buttonState = 0;
int lastButtonState = 0;
int counterMicro =0;


//sunrise
unsigned long timePassed= 0;
unsigned long startTime= 0;
int interval = 5000;
int sunStrip =0;
boolean justArrived =true;


int blueVal;
int fadeIn = false;
boolean activateNeoPixel = false;
boolean fadeNeoPixel = false;
int numNeoPixel;
boolean micActive = false;
void setup() {
  pinMode(BUTTON, INPUT);
  pinMode(MICRO, INPUT);
  Serial.begin(9600);
  pixels.begin();

}

void loop() {
//sensorValue = digitalRead(MICRO);
//delay(200);
  
  //Serial.println(sensorValue);
  pixels.clear();
  // howmanyPresses();
  //fadeInOut();
  // sunRise()
  //delay(100);
  howmanyPresses();
  //turn it on
  if (buttonPushCounter == 1) {
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 255));
      
    }
    pixels.show();
  }

  //fade in and out
  if (buttonPushCounter == 2) {
    fadeInOut();
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, blueVal));
      
    }
    pixels.show();
  }

  //sunrise
  if (buttonPushCounter == 3) {
    if(justArrived ==true){
      startTime = millis();
      timePassed = 0;
      sunStrip =0;
      justArrived =false;
    }
    
    sunRise();
  }

  //wave
  if (buttonPushCounter == 4) {
    if (micActive == false) {
      speekUp();
    }
    if (micActive == true) {
      //Serial.println("on");
      for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 255, 0));
        pixels.show();
        delay(200);
        howmanyPresses();
      }
    }
  }

  //turn off
  if (buttonPushCounter == 5) {
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      pixels.show();
      howmanyPresses() ;
    }

    buttonPushCounter = 0;
  }
}



void howmanyPresses() {
  buttonState = digitalRead(BUTTON);

  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);
    } else {
      Serial.println("off");
    }
    delay(50);
  }
  lastButtonState = buttonState;

}

void sunRise() {

timePassed = millis()-startTime;

// change to next led strip
if(timePassed > interval){
  sunStrip++;
  if(sunStrip > 2) sunStrip = 0;
  timePassed =0;
  startTime =millis();
  
  for (int i = 0; i < NUMPIXELS; i++) {
     pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      
    }
    pixels.show();
}

  if (sunStrip == 0) {
    for (int i = 0; i < 15; i++) {
     pixels.setPixelColor(i, pixels.Color(0, 0, blueVal));
      
    }
    pixels.show();
  }
  if (sunStrip == 1) {
    for (int i = 16; i < 30; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, blueVal));
     
    }
    pixels.show();
  }
  if (sunStrip == 2) {
    for (int i = 31; i < 45; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, blueVal));
      
    }
    pixels.show();
  }

}

void speekUp() {
  //sensorValue = analogRead(MICRO);
  sensorValue = digitalRead(MICRO);
  Serial.println(sensorValue);
  if (sensorValue==0) {
    counterMicro++;
    Serial.println(counterMicro);
    if(counterMicro > 20){
     Serial.println("active");
      micActive = true;
     

    }
   
  }
}

void fadeInOut() {

  // FADE IN
  if (fadeIn == true) {
    if (blueVal < 128) {
      blueVal += 2;
    }
    else fadeIn = false;

  }
  // FADE OUT
  else {
    if (blueVal > 0) {
      blueVal -= 2;
    }

    else fadeIn = true;
  }
  Serial.print("BlueVal: ");
  Serial.println(blueVal);

}
