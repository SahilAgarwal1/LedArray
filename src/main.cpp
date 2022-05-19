#include <Arduino.h>
#include <ArtnetESP32.h>
#include <FastLED.h>

#define UNIVERSE_SIZE 150 

#define NUM_LEDS 750
#define num_leds_pin1  750

//#define num_leds_pin1  1180
//#define num_leds_pin2  1196
//#define num_leds_pin3  1200
//#define num_leds_pin4  979
//#define NUM_LEDS  num_leds_pin1  + num_leds_pin2 + num_leds_pin3 + num_leds_pin4

#define dataPin  13
#define dataPin2  12
#define dataPin3  14
#define dataPin4  27

//const char* ssid = "SETUP-BBDD";
//const char* password = "bagel6057folded";

const char* ssid = "1200-1202@Gainesville_place";
const char* password = "cRX2ZZbYy";

CRGB leds[NUM_LEDS];

ArtnetESP32 artnet;

void displayfunction()
{
  if (artnet.frameslues%100==0)
   Serial.printf("nb frames read: %d  nb of incomplete frames:%d lost:%.2f %%\n",artnet.frameslues,artnet.lostframes,(float)(artnet.lostframes*100)/artnet.frameslues);
   //here the buffer is the led array hence a simple FastLED.show() is enough to display the array
   FastLED.show();
}


void initTest()
{
  for (int i = 0 ; i < NUM_LEDS ; i++) {
    leds[i] = CRGB(127, 0, 0);
  }
  FastLED.show();
  delay(500);
  for (int i = 0 ; i < NUM_LEDS ; i++) {
    leds[i] = CRGB(0, 127, 0);
  }
  FastLED.show();
  delay(500);
  for (int i = 0 ; i < NUM_LEDS ; i++) {
    leds[i] = CRGB(0, 0, 127);
  }
  FastLED.show();
  delay(500);
  for (int i = 0 ; i < NUM_LEDS ; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
  FastLED.show();
}




void setup() {

   Serial.begin(9600);
   WiFi.mode(WIFI_STA);

    Serial.printf("Connecting ");
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      Serial.println(WiFi.status());

        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

//set up your FastLED to your configuration ps: the more pins the better
    FastLED.addLeds<WS2812, dataPin, GRB>(leds, 0, num_leds_pin1);
    //FastLED.addLeds<WS2812, dataPin2, GRB>(leds, num_leds_pin1, num_leds_pin2);
    //FastLED.addLeds<WS2812, dataPin3, GRB>(leds, num_leds_pin1+num_leds_pin2, num_leds_pin3);
    //FastLED.addLeds<WS2812, dataPin4, GRB>(leds, num_leds_pin1 + num_leds_pin2 + num_leds_pin3, num_leds_pin4);

    initTest();

    artnet.setFrameCallback(&displayfunction); //set the function that will be called back a frame has been received
    artnet.setLedsBuffer((uint8_t*)leds); //set the buffer to put the frame once a frame has been received

    artnet.begin(NUM_LEDS,UNIVERSE_SIZE); //configure artnet



}

void loop() {
  // put your main code here, to run repeatedly:
  artnet.readFrame();
}