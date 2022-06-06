#define BLYNK_PRINT Serial

//Librerias utilizadas
#include <DHTesp.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//Variables
bool ext_intFlag = 0;
bool pinChanged = 0; //Indica el cambio de estado
float t,h;

//def
#define dhtPin D0 // Pin DHT22
#define led1 D1 //Pin LED
#define relay D2 //Pin Relay
#define btn1 D3 //Pin Pulsador

//Init
DHTesp dht;
BlynkTimer timer;
WidgetLED wled(V1);

//WiFi & Token
char ssid[] = "Tu SSID";
char pass[] = "Tu contraseña";
char auth[] = "Tu token de Blynk";

BLYNK_WRITE(V0)
{
  int v0Data = param.asInt();
  /* Otros tipos de parametro:
   *  asString
   *  asDouble
   */
   Serial.print("Valor de V0:");
   Serial.println(v0Data);
   digitalWrite(led1,v0Data);
}

void sendSensors()
{
  t = dht.getTemperature();
  h = dht.getHumidity();

  Blynk.virtualWrite(V5,t);
  Blynk.virtualWrite(V6, h);
}

void checkPin()
{
  ext_intFlag = !ext_intFlag;
  pinChanged = 1;
  
}

void ICACHE_RAM_ATTR checkPin();

void setup()
{
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  
  timer.setInterval(2000L, sendSensors);
  
  pinMode(relay, OUTPUT);
  digitalWrite(relay,LOW);
  pinMode(btn1, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  digitalWrite(led1,LOW);
  dht.setup(dhtPin,DHTesp::DHT22);

  attachInterrupt(digitalPinToInterrupt(btn1),checkPin,RISING);
}

void loop()
{
  Blynk.run();
  timer.run();
  if(pinChanged)
  {
    if(ext_intFlag)
    {
      wled.on();
    }
    else
    {
      wled.off();
    }
    pinChanged = 0; //Volvemos el valor a 0 para evitar que se ejecute el if por error
  }
  if (t > 27.00)
  {
    digitalWrite(relay,HIGH);
  }
  else
  {
    digitalWrite(relay,LOW);
  }
}
