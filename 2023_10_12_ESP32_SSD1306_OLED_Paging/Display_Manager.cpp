#include "Display_Manager.h"

DisplayManager::DisplayManager() {}

// Setup
  void DisplayManager::setup() {
    I2Cdisplay.begin(I2Cdisplay_SDA, I2Cdisplay_SCL, 100000); 
    display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &I2Cdisplay, -1);
  
    // Initialize OLED Display
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
      Serial.println(F("SSD1306 allocation failed"));
      for(;;);
    }

    display.clearDisplay();
    display.setTextColor(WHITE);
  }

// PRIVATE: Create display marker for each screen
  void DisplayManager::displayIndicator(int displayNumber) {
    int xCoordinates[5] = {44, 54, 64, 74}; //84
    for (int i =0; i<4; i++) {
      if (i == displayNumber) {
        display.fillCircle(xCoordinates[i], 60, 2, WHITE);
      }
      else {
        display.drawCircle(xCoordinates[i], 60, 2, WHITE);
      }
    }
  }  

// PRIVATE: SCREEN NUMBER 1: DATE AND TIME
  void DisplayManager::displayLocalTime() {
    //Display Date and Time on OLED display
    display.clearDisplay();
    display.setTextColor(WHITE);

    display.setTextSize(1);
    display.setCursor(0,0);
    display.print("Wed, 18 Oct 2024");

    display.setTextColor(BLACK, WHITE); // Draw 'inverse' text
    display.setCursor(16,8);
    display.print("Wed, 18 Oct 2024");
    display.invertDisplay(false);
    display.setTextColor(WHITE);

    display.setTextSize(3);
    display.drawBitmap(110, 32, sun_icon, LOGO_WIDTH, LOGO_HEIGHT, WHITE);
    
    display.setCursor(0,26);
    display.print("04:20");
    display.setCursor(110,26);
    display.setTextSize(1);
    display.print("AM");

    displayIndicator(displayScreenNumber);
    display.display();
  }

// PRIVATE: SCREEN NUMBER 2: TEMPERATURE
  void DisplayManager::displayTemperature() {
    display.clearDisplay();
    display.setTextSize(2);
    display.drawBitmap(15, 5, temperature_icon, LOGO_WIDTH, LOGO_HEIGHT ,1);
    display.setCursor(35, 5);
    display.print("31");
    display.cp437(true);
    display.setTextSize(1);
    display.print(" ");
    display.write(167);
    display.print("C");
    display.setCursor(0, 34);
    display.setTextSize(1);
    display.print("Humidity: ");
    display.print("75");
    display.print(" %");
    display.setCursor(0, 44);
    display.setTextSize(1);
    display.print("Pressure: ");
    display.print("202");
    display.print(" hpa");
    displayIndicator(displayScreenNumber);
    display.display();
  }

// PRIVATE: SCREEN NUMBER 3: HUMIDITY
  void DisplayManager::displayHumidity() {
    display.clearDisplay();
    display.setTextSize(2);
    display.drawBitmap(15, 5, humidity_icon, 16, 16 ,1);
    display.setCursor(35, 5);
    display.print("76");
    display.print(" %");
    display.setCursor(0, 34);
    display.setTextSize(1);
    display.print("Temperature: ");
    display.print("29");
    display.cp437(true);
    display.print(" ");
    display.write(167);
    display.print("C");
    display.setCursor(0, 44);
    display.setTextSize(1);
    display.print("Pressure: ");
    display.print("333");
    display.print(" hpa");
    displayIndicator(displayScreenNumber);
    display.display();
  }

// PRIVATE: SCREEN NUMBER 4: PRESSURE
  void DisplayManager::displayPressure() {
    display.clearDisplay();
    display.setTextSize(2);
    display.drawBitmap(0, 5, arrow_down_icon, 16, 16 ,1);
    display.setCursor(20, 5);
    display.print("246");
    display.setTextSize(1);
    display.print(" hpa");
    display.setCursor(0, 34);
    display.setTextSize(1);
    display.print("Temperature: ");
    display.print("30");
    display.cp437(true);
    display.print(" ");
    display.write(167);
    display.print("C");
    display.setCursor(0, 44);
    display.setTextSize(1);
    display.print("Humidity: ");
    display.print("50");
    display.print(" hpa");
    displayIndicator(displayScreenNumber);
    display.display();
  }


// PUBLIC: Display the right screen accordingly to the displayScreenNumber
  void DisplayManager::updateScreen(int displayScreenNum) {
    displayScreenNumber = displayScreenNum;
    if (displayScreenNumber == 0){
      displayLocalTime();
    }
    else if (displayScreenNumber == 1) {
      displayTemperature();
    }
    else if (displayScreenNumber == 2) {
      displayHumidity();
    }
    else {
      displayPressure();
    }
  }




// END