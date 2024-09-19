#include <time.h>
#include "Display_Manager.h"      

// Pushbutton
#define buttonPin 2    

int buttonState;
int lastButtonState = LOW;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

// Screens
int displayScreenNum = 0;
int displayScreenNumMax = 3;

unsigned long lastTimer = 0;
unsigned long timerDelay = 15000;

DisplayManager displayManager;

void setup() {
  Serial.begin(9600);

  pinMode(buttonPin, INPUT);

  displayManager.setup();
}

void loop() {
  int reading = digitalRead(buttonPin);

  // Change screen when the pushbutton is pressed
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        displayManager.updateScreen(displayScreenNum);
        Serial.println(displayScreenNum);
        if(displayScreenNum < displayScreenNumMax) {
          displayScreenNum++;
        }
        else {
          displayScreenNum = 0;
        }
        lastTimer = millis();
      }
    }
  }
  lastButtonState = reading;
  
  // Change screen every 15 seconds (timerDelay variable)
  if ((millis() - lastTimer) > timerDelay) {
    displayManager.updateScreen(displayScreenNum);
    Serial.println(displayScreenNum);
    if(displayScreenNum < displayScreenNumMax) {
      displayScreenNum++;
    }
    else {
      displayScreenNum = 0;
    }
    lastTimer = millis();
  }
}