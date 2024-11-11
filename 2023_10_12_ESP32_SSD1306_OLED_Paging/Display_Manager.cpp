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

    display.setRotation(2);
    display.clearDisplay();
    display.setTextColor(WHITE);
  }
// PUBLIC - SHOW LAUNCH SCREEN
  void DisplayManager::showLaunchScreen() {
    display.clearDisplay();
    testdrawroundrect();
    delay(500);

    display.setTextColor(BLACK, WHITE);
    display.setTextSize(2);
    display.setCursor(40,12);
    display.print("RAMU");// 16px
    display.display();

    display.setTextColor(BLACK, WHITE);
    display.setTextSize(1);
    display.setCursor(25,40);
    display.print("HERE TO HELP!");// 16px
    display.display();
    delay(1000);
  }

// PRIVATE: Create display marker for each screen
  void DisplayManager::displayIndicator(int displayNumber) {
    Serial.print("displayIndicator ");
    Serial.println(displayNumber);

    int xCoordinates[5] = {44, 54, 64, 74, 84};
    for (int i = 0; i < 5; i++) {
      if (i == (displayNumber-1)) {
        display.fillCircle(xCoordinates[i], 60, 3, WHITE);
      }
      else {
        display.drawCircle(xCoordinates[i], 60, 2, WHITE);
      }
    }
  }  

// PRIVATE: SCREEN NUMBER 0: DEMO
  void DisplayManager::demoScreen() {
    display.clearDisplay();
    display.setTextColor(WHITE);

    display.setTextSize(1);
    display.setCursor(0,0);
    display.print("Size 1");// 8px

    display.setTextSize(2);
    display.setCursor(0,8);
    display.print("Size 2");// 16px

    display.setTextSize(3);
    display.setCursor(0,24);
    display.print("Size 3");// 24px

    display.drawBitmap(0, 48, temperature_icon, LOGO_WIDTH, LOGO_HEIGHT ,1);

    displayIndicator(displayScreenNumber);
    display.display();
  }

// PRIVATE: 
    void DisplayManager::testdrawroundrect() {
      display.clearDisplay();

      for(int16_t i=0; i<display.height()/2-2; i+=2) {
        display.drawRoundRect(i, i, display.width()-2*i, display.height()-2*i,
        display.height()/4, WHITE);
        display.display();
        delay(1);
      }

      // delay(2000);
    }
// PRIVATE: SCREEN NUMBER 1: DATE AND TIME
  void DisplayManager::displayLocalTime() {
    //Display Date and Time on OLED display
    display.clearDisplay();//
    display.setTextColor(WHITE);//

    display.setTextSize(1);//
    display.setCursor(0,0);//
    display.print("Wed, 18 Oct 2024");//

    display.setTextColor(BLACK, WHITE); // Draw 'inverse' text
    display.setCursor(16,8);
    display.print("Wed, 18 Oct 2024");
    display.invertDisplay(false);//
    display.setTextColor(WHITE);

    display.setTextSize(3);
    display.drawBitmap(110, 32, sun_icon, LOGO_WIDTH, LOGO_HEIGHT, WHITE);//
    
    display.setCursor(0,26);
    display.print("04:20");
    display.setCursor(110,26);
    display.setTextSize(1);
    display.print("AM");

    displayIndicator(displayScreenNumber);
    display.display();//
    // display.setRotation(1);//invertDisplay
  }

// PRIVATE: SCREEN NUMBER 2: TEMPERATURE
  void DisplayManager::displayTemperature() {
    display.clearDisplay();
    display.setTextSize(2);
    display.drawBitmap(15, 5, temperature_icon, LOGO_WIDTH, LOGO_HEIGHT ,1);
    display.setCursor(35, 5);
    display.print("31");
    display.cp437(true);//
    display.setTextSize(1);
    display.print(" ");
    display.write(167);//
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

// ROUTER
// PUBLIC: Display the right screen accordingly to the displayScreenNumber
  void DisplayManager::updateScreen(int displayScreenNum) {
    Serial.print("updateScreen ");
    Serial.println(displayScreenNum);

    displayScreenNumber = displayScreenNum;
    if (displayScreenNumber == 1){
      demoScreen();
    }
    else if (displayScreenNumber == 2) {
      displayTemperature();
    }
    else if (displayScreenNumber == 3) {
      displayHumidity();
    }
    else if (displayScreenNumber == 4) {
      displayPressure();
    }
    else if (displayScreenNumber == 5) {
      displayLocalTime();
    }
  }




// END