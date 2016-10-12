// Color TFT 320x240 (ILI9341) Audio Spectrum Analyzer Display
// Copied and modified from original repository https://github.com/PaulStoffregen/Audio 
//
// This example code is in the public domain.


#include <ILI9341_t3.h>
#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>


// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=382,279
AudioMixer4              mixer1;         //xy=546,280
AudioAnalyzeFFT1024      fft1024;        //xy=707,275
AudioRecordQueue         queue1;         //xy=725,329
AudioOutputI2S           i2s2;           //xy=848,390
AudioConnection          patchCord1(i2s1, 0, mixer1, 0);
//AudioConnection          patchCord2(i2s1, 1, mixer1, 1);
AudioConnection          patchCord3(mixer1, fft1024);
AudioConnection          patchCord4(mixer1, queue1);
AudioConnection          patchCord5(mixer1, 0, i2s2, 0);
AudioConnection          patchCord6(mixer1, 0, i2s2, 1);
AudioControlSGTL5000     audioShield;    //xy=537,427
// GUItool: end automatically generated code



const int myInput = AUDIO_INPUT_LINEIN;
// const int myInput = AUDIO_INPUT_MIC;

 
// For optimized ILI9341_t3 library
#define TFT_DC      20
#define TFT_CS      21
#define TFT_RST    255  // 255 = unused, connect to 3.3V
#define TFT_MOSI     7
#define TFT_SCLK    14
#define TFT_MISO    12
ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_MISO);

// Run setup once
void setup() {
  Serial.begin(9600);
  while (!Serial) {
    delay(10);
  }
  Serial.println("Initialing Soundcard...");
  
  // set up the TFT screen
  SPI.setMOSI(TFT_MOSI);
  SPI.setSCK(TFT_SCLK);
  tft.begin();
  tft.fillScreen(ILI9341_BLACK);

  Serial.println("Initialing Soundcard complete...");

  // start the audio library
  AudioMemory(24);
  audioShield.enable();
  audioShield.inputSelect(myInput);
  
  audioShield.volume(1);
  Serial.print("volume()");
  //fft1024.averageTogether(160);
   queue1.begin();
}

unsigned int line[320];
unsigned int previous[320];

int8_t wave_buf_l[128]; 
int8_t wave_buf_r[128]; 

int8_t color = 0; 

uint16_t Color565(uint8_t r, uint8_t g, uint8_t b) {
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

uint16_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return Color565(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return Color565(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return Color565(WheelPos * 3, 255 - WheelPos * 3, 0);
}

// Run repetitively
void loop() {
  unsigned int y;

//  if (fft1024.available()) {
//    //Serial.println("fft...");
//    // first, grab the first 320 frequency bins
//    for (y=0; y < 320; y++) {
//      previous[y] = line[y];
//      line[y] = fft1024.read(y) * 240.0 * 5;
//      if (line[y] > 240) line[y] = 240;
//    }
//
//    // draw horizontal lines for each frequency
//    for (y=0; y < 320; y++) {
//      //tft.drawPixel(previous[y], y, ILI9341_BLACK);
//      if (line[y] > 0) {        
//        //tft.drawFastHLine(0, y, line[y], ILI9341_YELLOW);
//        tft.drawPixel(line[y], y, ILI9341_YELLOW);
//      }
//    }
//  }
  
  if (queue1.available()) {
      //tft.fillScreen(ILI9341_BLACK);
    int16_t *buf = queue1.readBuffer();
    for (int k =0; k<128; k++) {
      //tft.drawPixel(k, wave_buf_l[k], ILI9341_BLACK);
      wave_buf_r[k] = wave_buf_l[k];
      wave_buf_l[k] = 64 - 64*buf[k]/2048; 
      //tft.drawPixel(k, wave_buf_l[k], ILI9341_GREEN);  
    }

   for (int k =1; k<128; k++) {
      //tft.drawLine(k-1, wave_buf_r[k-1], k, wave_buf_r[k], ILI9341_BLACK);
      //tft.drawLine(k-1, wave_buf_l[k-1], k, wave_buf_l[k], Wheel(color));
    
      tft.drawPixel(k, wave_buf_r[k], ILI9341_BLACK);  
   }
    
    for (int k =1; k<128; k++) {
      //tft.drawLine(k-1, wave_buf_r[k-1], k, wave_buf_r[k], ILI9341_GREEN);
      //tft.drawLine(k-1, wave_buf_l[k-1], k, wave_buf_l[k], Wheel(color));
    
      tft.drawPixel(k, wave_buf_l[k], Wheel(color));  
    }
      color++;
    queue1.freeBuffer();
  }

}
