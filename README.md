### Teensy audio display projects (work in progress)
Electronics projects using the [teensy 3.2](https://www.pjrc.com/store/teensy32.html) connected to an [audio board](https://www.pjrc.com/store/teensy3_audio.html) [SGTL5000] (http://www.nxp.com/products/media-and-audio-processing/data-converters/audio-converters/audio-codec/ultra-low-power-audio-codec:SGTL5000) codec and a [2.2" tft display] (https://www.pjrc.com/store/display_ili9341.html)
* Digital oscilliscope: 
  * Display waveform captured from the teensy audio board on the 2.2" tft display 
* Digital audio processor and oscilliscope: 
  * Process incomming audio while displaying incomming and/or outgoing audio on tft display 

![teensy lcd and audio circuit diagram](https://github.com/newdigate/teensy_audio_tft/blob/master/teensylcd1.png?raw=true)
```c
#define TFT_DC      20
#define TFT_CS      21
#define TFT_RST    255  // 255 = unused, connect to 3.3V
#define TFT_MOSI     7
#define TFT_SCLK    14
#define TFT_MISO    12
```
* original arduino source code from [this thread](https://forum.pjrc.com/threads/24793-Audio-Library?p=55821&viewfull=1#post55821) on pjrc forums...
