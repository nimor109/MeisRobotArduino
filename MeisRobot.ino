/*
 * Interfacing Arduino with ST7789 tft1 display (240x240 pixel).
 * Graphics test example.
 * This is a free software with NO WARRANTY.
 * https://simple-circuit.com/
 */
/**************************************************************************
  This is a library for several Adafruit displays based on ST77* drivers.

  Works with the Adafruit 1.8" tft1 Breakout w/SD card
    ----> http://www.adafruit.com/products/358
  The 1.8" tft1 shield
    ----> https://www.adafruit.com/product/802
  The 1.44" tft1 breakout
    ----> https://www.adafruit.com/product/2088
  as well as Adafruit raw 1.8" tft1 display
    ----> http://www.adafruit.com/products/618

  Check out the links above for our tutorials and wiring diagrams.
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional).

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 **************************************************************************/

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>             // Arduino SPI library
#include <SoftwareSerial.h>

// ST7789 tft1 module connections
#define tft1_CS    4  // define chip select pin (CS pin pour activer ecran 1 ou non)
#define tft2_CS    5  // define chip select pin (CS pin pour activer ecran 2 ou non) 
#define tft1_DC    6  // define data/command pin
#define tft1_RST   -1  // define reset pin, or set to -1 and connect to Arduino RESET pin
#define tft2_DC    6  // define data/command pin
#define tft2_RST   -1  // define reset pin, or set to -1 and connect to Arduino RESET pin

// Initialize Adafruit ST7789 tft library for screen 1 (RIGHT EYE)
Adafruit_ST7789 tft1 = Adafruit_ST7789(tft1_CS, tft1_DC, tft1_RST);
// Initialize Adafruit ST7789 tft library for screen 2 (LEFT EYE)
Adafruit_ST7789 tft2 = Adafruit_ST7789(tft2_CS, tft2_DC, tft2_RST);

// Create the Bluetooth Serial Port
SoftwareSerial hc06(2,3);
// Empty global variable that will contain the Bluetooth values
String cmd="";

// Arduino setup method to initialize everything
void setup(void) {
  
  //Initialize Bluetooth Serial Port
  hc06.begin(9600);

  //Initialize the regular Serial Port (debugging withing Arduino IDE)
  Serial.begin(9600);

  //Initialize both screens 
  //if the display has CS pin try with SPI_MODE0
  tft1.init(135, 240, SPI_MODE0);    // Init ST7789 display 135x240 pixel
  tft2.init(135, 240, SPI_MODE0);    // Init ST7789 display 135x240 pixel

  // if the screen is flipped, remove this command
  tft1.setRotation(2);
  tft2.setRotation(2);

  // Fill the screen with black to reset them
  tft1.fillScreen(ST77XX_BLACK);
  tft2.fillScreen(ST77XX_BLACK);

  // Set the normal centered eyes
  normalEye(0x4f7c);
  normalEye2(0x4f7c);  

  // Invert the display (not sure if needed here)
  tft1.invertDisplay(true);
  tft2.invertDisplay(true);
}


// Arduino loop method (this runs as long as the arduino has power)
void loop() {
  
  //Short delay to make sure we receive the whole bluetooth command if more than 1 char  
  delay(500);

  // Check if anything received by bluetooth
  while(hc06.available()>0){
      // Get all chars received from bluetooth
      cmd+=(char)hc06.read();
  }

  // Check which command we received if any
  if(cmd!=""){
   if(cmd=="LR"){
       lookRight();
       hc06.println("I look right");
   }else if(cmd=="LL"){
       lookLeft();
       hc06.println("I look Left");
   }else if(cmd=="N"){
       getNormal();
       hc06.println("I look normal");
   }else if(cmd=="W"){
       getWinky();
       hc06.println("I Wink");
   }else if(cmd=="HT"){
       getHappyTriangle();
       hc06.println("I look happy with triangles");
   }else if(cmd=="H"){
       getHappy();
       hc06.println("I look happy");
   }else if(cmd=="S"){
       getSad();
       hc06.println("I look Sad");
   }else if(cmd=="M"){
       getMad();
       hc06.println("I look mad");
   }else{
       hc06.println(cmd + "is not a valid command");
   }

   // Clear cmd before next check
   cmd="";
 }
}

// CUSTOM METHODS FOR OUR PROJECT //

//-------------------------------
//------SCREEN 1 : RIGHT EYE-----
//-------------------------------
void normalEye(uint16_t color) {
  int x = tft1.width()/2-(tft1.width()/1.5)/2;
  int y = 1;
  int w = tft1.width()/1.5;
  int h = tft1.height()-2;
  tft1.fillRoundRect(x, y, w, h, 80, color);
}
void eraseNormalEye() {
  int x = tft1.width()/2-(tft1.width()/1.5)/2;
  int y = 1;
  int w = tft1.width()/1.5;
  int h = tft1.height()-2;
  tft1.fillRoundRect(x, y, w, h, 80, ST77XX_BLACK);
}

void normalEyeLeft(uint16_t color) {
  int x = tft1.width()-tft1.width()/1.5;
  int y = 1;
  int w = tft1.width()/1.5;
  int h = tft1.height()-2;
  tft1.fillRoundRect(x, y, w, h, 80, color);
}
void eraseNormalEyeLeft() {
  int x = tft1.width()-tft1.width()/1.5;
  int y = 1;
  int w = tft1.width()/1.5;
  int h = tft1.height()-2;
  tft1.fillRoundRect(x, y, w, h, 80, ST77XX_BLACK);
}

void normalEyeRight(uint16_t color) {
  int x = 1;
  int y = 1;
  int w = tft1.width()/1.5;
  int h = tft1.height()-2;
  tft1.fillRoundRect(x, y, w, h, 80, color);
}
void eraseNormalEyeRight() {
  int x = 1;
  int y = 1;
  int w = tft1.width()/1.5;
  int h = tft1.height()-2;
  tft1.fillRoundRect(x, y, w, h, 80, ST77XX_BLACK);
}

void sadLeftEye(uint16_t color) {
  tft1.fillCircle(tft1.width()/2, tft1.height()/2, tft1.width()/2, color);
  tft1.fillCircle(tft1.width()/2+24, tft1.height()/2-50, tft1.width()/1.5, ST77XX_BLACK);
}
void eraseSadLeftEye() {
  tft1.fillCircle(tft1.width()/2, tft1.height()/2, tft1.width()/2, ST77XX_BLACK);
}

void sadRightEye(uint16_t color) {
  tft1.fillCircle(tft1.width()/2, tft1.height()/2, tft1.width()/2, color);
  tft1.fillCircle(tft1.width()/2-24, tft1.height()/2-50, tft1.width()/1.5, ST77XX_BLACK);
}
void eraseSadRightEye() {
  tft1.fillCircle(tft1.width()/2, tft1.height()/2, tft1.width()/2, ST77XX_BLACK);
}


void happyEye(uint16_t color) {
  tft1.fillCircle(tft1.width()/2, tft1.height()/2, tft1.width()/2, color);
  tft1.fillCircle(tft1.width()/2, tft1.height()/2+50, tft1.width()/1.5, ST77XX_BLACK);
}
void eraseHappyEye() {
  tft1.fillCircle(tft1.width()/2, tft1.height()/2, tft1.width()/2, ST77XX_BLACK);
}

void happyEyeTriangle(uint16_t color) {
  tft1.fillTriangle(1,tft1.height()/3, tft1.width()/2, tft1.height()/3-tft1.height()/3+1,    tft1.width()-1, tft1.height()/3, color);
  tft1.fillTriangle(1,tft1.height()/3, tft1.width()/2, tft1.height()/3-tft1.height()/3+31, tft1.width()-1, tft1.height()/3, ST77XX_BLACK); 
}
void eraseHappyEyeTriangle() {
  tft1.fillTriangle(1,tft1.height()/3, tft1.width()/2, tft1.height()/3-tft1.height()/3+1,    tft1.width()-1, tft1.height()/3, ST77XX_BLACK);
}


//-------------------------------
//------SCREEN 2 : LEFT EYE-----
//-------------------------------

void normalEye2(uint16_t color) {
  int x = tft2.width()/2-(tft2.width()/1.5)/2;
  int y = 1;
  int w = tft2.width()/1.5;
  int h = tft2.height()-2;
  tft2.fillRoundRect(x, y, w, h, 80, color);
}
void eraseNormalEye2() {
  int x = tft2.width()/2-(tft2.width()/1.5)/2;
  int y = 1;
  int w = tft2.width()/1.5;
  int h = tft2.height()-2;
  tft2.fillRoundRect(x, y, w, h, 80, ST77XX_BLACK);
}

void normalEyeLeft2(uint16_t color) {
  int x = tft2.width()-tft2.width()/1.5;
  int y = 1;
  int w = tft2.width()/1.5;
  int h = tft2.height()-2;
  tft2.fillRoundRect(x, y, w, h, 80, color);
}
void eraseNormalEyeLeft2() {
  int x = tft2.width()-tft2.width()/1.5;
  int y = 1;
  int w = tft2.width()/1.5;
  int h = tft2.height()-2;
  tft2.fillRoundRect(x, y, w, h, 80, ST77XX_BLACK);
}

void normalEyeRight2(uint16_t color) {
  int x = 1;
  int y = 1;
  int w = tft2.width()/1.5;
  int h = tft2.height()-2;
  tft2.fillRoundRect(x, y, w, h, 80, color);
}
void eraseNormalEyeRight2() {
  int x = 1;
  int y = 1;
  int w = tft2.width()/1.5;
  int h = tft2.height()-2;
  tft2.fillRoundRect(x, y, w, h, 80, ST77XX_BLACK);
}

void sadLeftEye2(uint16_t color) {
  tft2.fillCircle(tft2.width()/2, tft2.height()/2, tft2.width()/2, color);
  tft2.fillCircle(tft2.width()/2+24, tft2.height()/2-50, tft2.width()/1.5, ST77XX_BLACK);
}
void eraseSadLeftEye2() {
  tft2.fillCircle(tft2.width()/2, tft2.height()/2, tft2.width()/2, ST77XX_BLACK);
}

void sadRightEye2(uint16_t color) {
  tft2.fillCircle(tft2.width()/2, tft2.height()/2, tft2.width()/2, color);
  tft2.fillCircle(tft2.width()/2-24, tft2.height()/2-50, tft2.width()/1.5, ST77XX_BLACK);
}
void eraseSadRightEye2() {
  tft2.fillCircle(tft2.width()/2, tft2.height()/2, tft2.width()/2, ST77XX_BLACK);
}

void happyEye2(uint16_t color) {
  tft2.fillCircle(tft2.width()/2, tft2.height()/2, tft2.width()/2, color);
  tft2.fillCircle(tft2.width()/2, tft2.height()/2+50, tft2.width()/1.5, ST77XX_BLACK);
}
void eraseHappyEye2() {
  tft2.fillCircle(tft2.width()/2, tft2.height()/2, tft2.width()/2, ST77XX_BLACK);
}

void happyEyeTriangle2(uint16_t color) {
  tft2.fillTriangle(1,tft2.height()/3, tft2.width()/2, tft2.height()/3-tft2.height()/3+1,    tft2.width()-1, tft2.height()/3, color);
  tft2.fillTriangle(1,tft2.height()/3, tft2.width()/2, tft2.height()/3-tft2.height()/3+31, tft2.width()-1, tft2.height()/3, ST77XX_BLACK);
}
void eraseHappyEyeTriangle2() {
  tft2.fillTriangle(1,tft2.height()/3, tft2.width()/2, tft2.height()/3-tft2.height()/3+1,    tft2.width()-1, tft2.height()/3, ST77XX_BLACK);
}

//-------------------
//------Emotions-----
//-------------------
// Command M
void getMad(){
  tft1.fillScreen(ST77XX_BLACK);
  tft2.fillScreen(ST77XX_BLACK);
  sadLeftEye(0x4f7c);
  sadRightEye2(0x4f7c);
}

// Command S
void getSad() {
  tft1.fillScreen(ST77XX_BLACK);
  tft2.fillScreen(ST77XX_BLACK);
  sadRightEye(0x4f7c);
  sadLeftEye2(0x4f7c);
}

// Command H
void getHappy() {
  tft1.fillScreen(ST77XX_BLACK);
  tft2.fillScreen(ST77XX_BLACK);
  happyEye(0x4f7c);
  happyEye2(0x4f7c);
}

// Command HT
void getHappyTriangle() {
  tft1.fillScreen(ST77XX_BLACK);
  tft2.fillScreen(ST77XX_BLACK);
  happyEyeTriangle(0x4f7c);
  happyEyeTriangle2(0x4f7c);
}

// Command W (Wink Left Eye)
void getWinky() {
  tft1.fillScreen(ST77XX_BLACK);
  tft2.fillScreen(ST77XX_BLACK);
  normalEye(0x4f7c);
  happyEye2(0x4f7c);
}

// Command N
void getNormal() {
  tft1.fillScreen(ST77XX_BLACK);
  tft2.fillScreen(ST77XX_BLACK);
  normalEye(0x4f7c);
  normalEye2(0x4f7c);
}

// Command LL
void lookLeft() {
  tft1.fillScreen(ST77XX_BLACK);
  tft2.fillScreen(ST77XX_BLACK);
  normalEyeLeft(0x4f7c);
  normalEyeLeft2(0x4f7c);
}

// Command LR
void lookRight() {
  tft1.fillScreen(ST77XX_BLACK);
  tft2.fillScreen(ST77XX_BLACK);
  normalEyeRight(0x4f7c);
  normalEyeRight2(0x4f7c);
}
