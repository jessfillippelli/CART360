//good file
#include <Adafruit_NeoPixel.h>

//#define LED  12
#define BUTTON  4
#define NUMPIXELS 8 //60
#define PIN 6 //neo

//sound
#define MICRO A4
int sensorValue = 0;

//for  8 led
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//for 60 LED
//Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_RGBW + NEO_KHZ800);
#define DELAYVAL 100

int buttonPushCounter = 0;
int buttonState = 0;
int lastButtonState = 0;

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
      pixels.show();
    }
  }

  //fade in and out
  if (buttonPushCounter == 2) {
    fadeInOut();
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, blueVal));
      pixels.show();
    }
  }

  //sunset
  if (buttonPushCounter == 3) {

    for (int i = 0; i < NUMPIXELS; i++) {
      if (i % 2 == 0) {
        pixels.setPixelColor(i, pixels.Color(0, 0, blueVal));
      }
      pixels.show();
    }
  }
  //turn off
  if (buttonPushCounter == 4) {
    if (micActive == false) {
      speekUp();
    }
    if (micActive == true) {
      for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(255, 0, 0));
        pixels.show();
        delay(200);
        howmanyPresses() ;
      }
    }
  }

  //turn off
  if (buttonPushCounter == 5) {
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      pixels.show();
    }
  }
}

// was a loop but chnage it to boolean or void ???
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

  //add code you dont know how to do here jessica

}

void speekUp() {
  sensorValue = analogRead(MICRO);

  if (sensorValue > 220) {
    Serial.println("active");
    micActive = true;

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
