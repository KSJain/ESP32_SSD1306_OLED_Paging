#include <time.h>
#include "Display_Manager.h"      

// Pushbutton
#define buttonPin 0    // BOOT pin on chip

int buttonState = LOW;
int lastButtonState = HIGH;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

// Screens
int displayScreenNum = 1;
int displayScreenNumMax = 5;

unsigned long lastTimer = 0;
unsigned long timerDelay = 5000;

DisplayManager displayManager;

void setup() {
  Serial.begin(9600);

  pinMode(buttonPin, INPUT);

  displayManager.setup();

  displayManager.showLaunchScreen();
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
        Serial.println("BUTTON PRESS");
        Serial.println(displayScreenNum);
        if(displayScreenNum < displayScreenNumMax) {
          displayScreenNum++;
        }
        else {
          displayScreenNum = 1;
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
      displayScreenNum = 1;
    }
    lastTimer = millis();
  }
}