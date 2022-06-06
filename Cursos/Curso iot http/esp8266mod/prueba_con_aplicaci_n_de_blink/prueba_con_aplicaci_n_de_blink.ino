#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <DHT.h>
#include <BlynkSimpleEsp32.h>


#define INTPIN 2 
#define LED 4
#define DHTPIN 14 

char token[]="lfF1oRODknEx02kahSpyI4C-SfQx2YNx";

//instancia sensor DHT
DHT dht(DHTPIN,DHT11);
BlynkTimer timer;
WidgetLED led1(V1);

bool ext_intFlag=0;
bool pinChanged=0; //se activo la interrupcion

BLYNK_WRITE(V0){
  int V0Data = param.asInt();
  Serial.print("Valor de V0= ");
  Serial.println(V0Data);
  digitalWrite(LED,V0Data);
}

void sendSensor(){
  float t=dht.readTemperature();
  float h=dht.readHumidity();
  //Serial.println("temp: "+String(t)+" hum: "+String(h));
  Blynk.virtualWrite(V5,h);
  Blynk.virtualWrite(V6,t);
}

void checkPin(){
  ext_intFlag = !ext_intFlag;
  pinChanged=true;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(INTPIN,INPUT_PULLUP);
  pinMode(LED,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(INTPIN),checkPin,RISING);
  digitalWrite(LED,LOW);
  dht.begin();
  timer.setInterval(10000,sendSensor);
  Blynk.begin(token,"Familia RC","josefa1047"); 
  
}

void loop() {
  Blynk.run();
  timer.run();
  if(pinChanged){
    if(ext_intFlag){
      led1.on();
    }
    else{
      led1.off();
    }
    pinChanged=0;
  }  

}
