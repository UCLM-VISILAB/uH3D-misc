#include <Adafruit_NeoPixel.h>
#define RELAY_PIN 12
#define LED_PIN    8
#define LED_COUNT 12
 
Adafruit_NeoPixel ring(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
  ring.begin();
  ring.show();
  uint32_t color = ring.Color(0, 0, 0, 255);
  ring.setBrightness(255);
  ring.fill(color, 0);
  ring.show();  
}


void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    if( (data.compareTo("L012 1")) == 0){
      digitalWrite(RELAY_PIN, HIGH);
      Serial.println(data);
    }else if((data.compareTo("L012 0")) == 0){
       digitalWrite(RELAY_PIN, LOW);
       Serial.println(data);
    }else if(data.startsWith("L008")){
      updateRingLight(data);
      Serial.println(data);
    }
    else{
      Serial.println("Unknown");
    }

  }
}

void updateRingLight(String data){
  //L008 Rxxx Gxxx Bxxx Wxxx LXX
  int red = data.substring(6,9).toInt();
  int green = data.substring(11,14).toInt();
  int blue = data.substring(16,19).toInt();
  int white = data.substring(21,24).toInt();
  uint32_t color = ring.Color(red,green,blue,white);
  if(data.length() == 24){
    //all leds
    ring.fill(color, 0); 
       Serial.println(red);
    Serial.println(green);
    Serial.println(blue);
    Serial.println(white);
  }else{
    int led = data.substring(26,28).toInt();
    if(led < 12){
    ring.setPixelColor(led,red,green,blue,white);
  }

  }
  ring.show();
}

void colorines() {
  for(int red=0; red<=255;red++){
    for(int green=0; green<=255;green++){
      for(int blue=0; blue<=255;blue++){
          for(int i=0;i<12; i++){
            ring.setPixelColor(i, red, green, blue,0);
            ring.show();
            delay(10);
        }
      }
    }
  }
}
