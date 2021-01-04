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



void writeTmntLogo1() {
    uint8_t tile_0[40] = { 0x03,0x05,0x09,0x09,0xF9,0x01,0x01,0xF9,0x09,0xF9,0x05,0x03,0xC2,0x84,0x08,0x84,0xC2,0x01,0x01,0xFF,0x01,0x02,0xC4,0x88,0x1F,0x03,0x05,0xF9,0x09,0xF9,0x01,0x01,0xF9,0x09,0x09,0x05,0x03,0x00,0x00,0x00};
    u8x8.drawTile(5, 1, 5, tile_0);
    uint8_t tile_1[40] = { 0x00,0x00,0x00,0x00,0x03,0x02,0x02,0x03,0x00,0x03,0x02,0x02,0x03,0x00,0x01,0x00,0x03,0x04,0x08,0x1F,0x08,0x04,0x03,0x00,0x01,0x02,0x02,0x03,0x00,0x03,0x02,0x02,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    u8x8.drawTile(5, 2, 5, tile_1);
}

typedef void(*DrawFunction)();
DrawFunction drawFunctions[] = {&writeDylan, &writeTurtleNames, &writeTeenageMutantNinjaTurtles, &writeMeatSweats, &writeTmntLogo1};
int lastFunctionIdx = -1;


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

   long now = millis();
  // Check if we time interval for redrawing passes.
  if (now - lastUpdate < USER_LOOP_REFRESH_RATE_MS) {
    return;
  }
  lastUpdate = now;

  u8x8.clear();
  
  int num_funcs = sizeof(drawFunctions)/sizeof(drawFunctions[0]);
  int functionIdx;
  do {
      functionIdx = random8(num_funcs);
  } while (functionIdx == lastFunctionIdx);
  
  (*drawFunctions[functionIdx])();
  lastFunctionIdx = functionIdx;
}


