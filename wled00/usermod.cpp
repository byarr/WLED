#include "wled.h"
#include <U8x8lib.h> // from https://github.com/olikraus/u8g2/

//The SCL and SDA pins are defined here. 
//Lolin32 boards use SCL=5 SDA=4 
#define U8X8_PIN_SCL 5
#define U8X8_PIN_SDA 4


/*
 128 x 32 pixels

 16 cols x 4 rows in coord system

 fonts have different sizes e.g. u8x8_font_chroma48medium8_r is 6 pixels high so fits in a single row
*/


// If display does not work or looks corrupted check the
// constructor reference:
// https://github.com/olikraus/u8g2/wiki/u8x8setupcpp
// or check the gallery:
// https://github.com/olikraus/u8g2/wiki/gallery
U8X8_SSD1306_128X32_UNIVISION_SW_I2C u8x8(U8X8_PIN_SCL, U8X8_PIN_SDA);


void writeDylan() {
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(2, 1, "Hello Dylan");
}

void writeTurtleNames() {
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(0, 0, "Leonardo");
  u8x8.drawString(0, 1, "Raphael");
  u8x8.drawString(0, 2, "Michelangelo");
  u8x8.drawString(0, 3, "Donatello");
}

void writeTeenageMutantNinjaTurtles() {
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(0, 0, "Teenage");
  u8x8.drawString(1, 1, "Mutant");
  u8x8.drawString(2, 2, "Ninja");
  u8x8.drawString(3, 3, "Turtles");
}

void writeMeatSweats() {
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(4, 1, "Meat");
  u8x8.drawString(6, 2, "Sweats!");
}


void writeTMNT() {
  u8x8.setFont(u8x8_font_lucasarts_scumm_subtitle_o_2x2_r);
  u8x8.drawString(0, 0, "TMNT");
}

typedef void(*DrawFunction)();
DrawFunction drawFunctions[] = {&writeDylan, &writeTurtleNames, &writeTeenageMutantNinjaTurtles, &writeMeatSweats, &writeTMNT};
int functionIdx = 0;


// gets called once at boot. Do all initialization that doesn't depend on
// network here
void userSetup() {
  u8x8.begin();
  u8x8.setPowerSave(0);
    u8x8.setContrast(10); //Contrast setup will help to preserve OLED lifetime. In case OLED need to be brighter increase number up to 255
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(0, 0, "Loading...");
}

// gets called every time WiFi is (re-)connected. Initialize own network
// interfaces here
void userConnected() {}

long lastUpdate = 0;
// How often we are redrawing screen
#define USER_LOOP_REFRESH_RATE_MS 5000

void userLoop() {

  // Check if we time interval for redrawing passes.
  if (millis() - lastUpdate < USER_LOOP_REFRESH_RATE_MS) {
    return;
  }
  lastUpdate = millis();
  
  u8x8.clear();
  (*drawFunctions[functionIdx])();
  functionIdx++;
  if (functionIdx >= sizeof(drawFunctions)/sizeof(drawFunctions[0])) {
      functionIdx = 0;
  }

}


