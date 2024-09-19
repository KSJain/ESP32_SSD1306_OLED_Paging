#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

void setupDisplay();
void displayIndicator(int displayNumber);
void displayLocalTime();
void displayTemperature();
void displayHumidity();
void displayPressure();
void updateScreen(int displayScreenNum);

#endif
// void beginDisplayWithScreenAddress(byte screenAddress);
// void displayDisplayBuffer();
// void clearDisplayBuffer();
// void clearDisplayScreen();

// void displayDHT11data(float tempF, float tempC, float humi);

// void setDisplayTextSmallWhite();
// void updateNavigationBar(String title);
// void displayDTHInfoCellSmall(String title, float value, int16_t x, int16_t y);
// void displayDisplayBuffer();
// void clearDisplayBuffer();
// void clearDisplayScreen();
// void drawTestPixelInWhite();
// void testdrawline();
// void testdrawstyles(void);
// void testscrolltext(void);