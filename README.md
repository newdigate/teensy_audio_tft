# Goals
* Display waveform captured from the teensy audio board on the 2.2" tft display 
* Process incomming audio while displaying incomming and/or outgoing audio on tft display 

Using the teensy 3.2 connected to an audio board [SGT5000] (http://www.nxp.com/products/media-and-audio-processing/data-converters/audio-converters/audio-codec/ultra-low-power-audio-codec:SGTL5000)

![teensy lcd and audio circuit diagram](https://github.com/newdigate/teensy_audio_tft/blob/master/teensylcd1.png?raw=true)
```c
#define TFT_DC      20
#define TFT_CS      21
#define TFT_RST    255  // 255 = unused, connect to 3.3V
#define TFT_MOSI     7
#define TFT_SCLK    14
#define TFT_MISO    12
