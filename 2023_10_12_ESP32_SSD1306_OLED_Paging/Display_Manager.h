#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "bitmaps.h"


enum DISPLAY_PAGE {
  page_one = 1,
  page_two = 2
};

class DisplayManager {
  public:

    DisplayManager();
    void setup();
    void updateScreen(int displayScreenNum);

  private:
    Adafruit_SSD1306 display;
    TwoWire I2Cdisplay = TwoWire(1);

    // Screens
    int displayScreenNumber = 0;
    int displayScreenNumMax = 3;

    // Display Indicator
    void displayIndicator(int displayNumber);
    
    // SCREEN NUMBER 1: DATE AND TIME
    void displayLocalTime();
    
    // SCREEN NUMBER 2: TEMPERATURE
    void displayTemperature();
    
    // SCREEN NUMBER 3: HUMIDITY
    void displayHumidity();
    
    // SCREEN NUMBER 4: PRESSURE
    void displayPressure();
};


#endif