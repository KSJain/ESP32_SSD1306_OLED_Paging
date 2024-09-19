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
// CODE DUMP BELOW
// #include <SPI.h>
// #include <Wire.h>
// #include <Adafruit_GFX.h>

// // #define SCREEN_WIDTH 128
// #define SCREEN_HEIGHT 32

// #define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// void setDisplayTextSmallWhite() {
//   display.setTextSize(1);
//   display.setTextColor(SSD1306_WHITE);
// }

// void updateNavigationBar(String title) {
//   setDisplayTextSmallWhite();

//   display.setCursor(50,0);
//   display.println(title);
  
//   display.display();
// }

// void displayDTHInfoCellSmall(String title, float value, int16_t x, int16_t y) {
//   setDisplayTextSmallWhite();

//   display.setCursor(x, y);
//   display.print(value);
//   display.println(title);

//   display.display();
// }

// void displayDHT11data(float tempF, float tempC, float humi) {
//   updateNavigationBar("DHT-11");

//   displayDTHInfoCellSmall(" F", tempF, 0, 8);
//   displayDTHInfoCellSmall(" C", tempC, 0, 18);
//   displayDTHInfoCellSmall("RH", humi, 50, 10);
// }

// // Code Below this line is setup and api to library functions
// void beginDisplayWithScreenAddress(byte screenAddress) {
//       if(!display.begin(SSD1306_SWITCHCAPVCC, screenAddress)) {
//     Serial.print(F("SSD1306 allocation failed for screen address: "));
//     Serial.print(screenAddress);
//     for(;;); // Don't proceed, loop forever
//   }
// }

// void displayDisplayBuffer() {
//   // Show initial display buffer contents on the screen --
//   // the library initializes this with an Adafruit splash screen.
//   Serial.println("displayDisplayBuffer");
//   display.display();
// }

// void clearDisplayBuffer() {
//   // Clear the buffer
//   Serial.println("cleanDisplayBuffer");
//   display.clearDisplay();
// }

// void clearDisplayScreen() {
//   // Clear the buffer
//   Serial.println("cleanDisplayBuffer");
//   display.clearDisplay();
//   display.display();
// }

// // Test Functions Below this line
// void drawTestPixelInWhite() {    
//   display.clearDisplay(); // Clear display buffer
//   // Draw a single pixel in white
//   display.drawPixel(64, 16, SSD1306_WHITE);
//   display.drawPixel(10, 16, SSD1306_WHITE);
//   display.drawPixel(64, 20, SSD1306_WHITE);

//   display.display();
//   Serial.println("drawTestPixelInWhite");
// }

// void testdrawline() {
//   int16_t i;

//   display.clearDisplay(); // Clear display buffer

//   for(i=0; i<(display.width()/1); i+=8) {
//     display.drawLine(0, 0, i, display.height()-1, SSD1306_WHITE);
//     display.display(); // Update screen with each newly-drawn line
//     delay(500);
//   }
//   for(i=0; i<display.height(); i+=4) {
//     display.drawLine(0, 0, display.width()-1, i, SSD1306_WHITE);
//     display.display();
//     delay(1);
//   }
//   delay(250);

//   display.clearDisplay();

//   for(i=0; i<display.width(); i+=4) {
//     display.drawLine(0, display.height()-1, i, 0, SSD1306_WHITE);
//     display.display();
//     delay(1);
//   }
//   for(i=display.height()-1; i>=0; i-=4) {
//     display.drawLine(0, display.height()-1, display.width()-1, i, SSD1306_WHITE);
//     display.display();
//     delay(1);
//   }
//   delay(250);

//   display.clearDisplay();

//   for(i=display.width()-1; i>=0; i-=4) {
//     display.drawLine(display.width()-1, display.height()-1, i, 0, SSD1306_WHITE);
//     display.display();
//     delay(1);
//   }
//   for(i=display.height()-1; i>=0; i-=4) {
//     display.drawLine(display.width()-1, display.height()-1, 0, i, SSD1306_WHITE);
//     display.display();
//     delay(1);
//   }
//   delay(250);

//   display.clearDisplay();

//   for(i=0; i<display.height(); i+=4) {
//     display.drawLine(display.width()-1, 0, 0, i, SSD1306_WHITE);
//     display.display();
//     delay(1);
//   }
//   for(i=0; i<display.width(); i+=4) {
//     display.drawLine(display.width()-1, 0, i, display.height()-1, SSD1306_WHITE);
//     display.display();
//     delay(1);
//   }

//   delay(2000); // Pause for 2 seconds
// }

// void testdrawstyles(void) {
//   display.clearDisplay();

//   display.setTextSize(1);             // Normal 1:1 pixel scale
//   display.setTextColor(SSD1306_WHITE);        // Draw white text
//   display.setCursor(0,0);             // Start at top-left corner
//   display.println(F("Love Olivia"));

//   display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
//   display.println(3.141592);

//   display.setTextSize(2);             // Draw 2X-scale text
//   display.setTextColor(SSD1306_WHITE);
//   display.println(F("Boobs")); display.println(0xDECAF, HEX);
//   display.setCursor(64,40);             // Start at top-left corner
//   display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
//   display.println(F("Cats"));


//   display.display();
//   delay(20000);
// }

// void testscrolltext(void) {
//   display.clearDisplay();

//   display.setTextSize(2); // Draw 2X-scale text
//   display.setTextColor(SSD1306_WHITE);
//   display.setCursor(10, 0);
//   display.println(F("Oliviaaaa"));
//   display.display();      // Show initial text
//   delay(100);

//   // Scroll in various directions, pausing in-between:
//   display.startscrollright(0x00, 0x0F);
//   delay(2000);
//   display.stopscroll();
//   delay(1000);
//   display.startscrollleft(0x00, 0x0F);
//   delay(2000);
//   display.stopscroll();
//   delay(1000);
//   display.startscrolldiagright(0x00, 0x07);
//   delay(2000);
//   display.startscrolldiagleft(0x00, 0x07);
//   delay(2000);
//   display.stopscroll();
//   delay(1000);
// }