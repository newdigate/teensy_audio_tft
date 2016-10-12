# teensy_audio_tft
Using teensy 3.2 with audio board and tft display
![teensy lcd and audio circuit diagram](https://github.com/newdigate/teensy_audio_tft/blob/master/teensylcd1.png?raw=true)
```c
#define TFT_DC      20
#define TFT_CS      21
#define TFT_RST    255  // 255 = unused, connect to 3.3V
#define TFT_MOSI     7
#define TFT_SCLK    14
#define TFT_MISO    12
