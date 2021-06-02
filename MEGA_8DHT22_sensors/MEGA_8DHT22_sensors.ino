#include <DHT.h>

// Sensor type:
#define DHTTYPE    DHT22     // DHT 22 (AM2302)

//sensors in digital pins 3,5,6,7,8,9,10,11
DHT dht1(3, DHTTYPE);
DHT dht2(5, DHTTYPE);
DHT dht3(6, DHTTYPE);
DHT dht4(9, DHTTYPE);
DHT dht5(10, DHTTYPE);
DHT dht6(11, DHTTYPE);
DHT dht7(7, DHTTYPE);
DHT dht8(8, DHTTYPE);

//strings for sensor id
String id_1 = "Sensor1  - ";
String id_2 = "Sensor2  - ";
String id_3 = "Sensor3  - ";
String id_4 = "Sensor4  - ";
String id_5 = "Sensor5  - ";
String id_6 = "Sensor6  - ";
String id_7 = "Sensor7  - ";
String id_8 = "Sensor8  - ";

//strings for serial communication
String str_h1;
String str_t1; 
String str_h2;
String str_t2;
String str_h3;
String str_t3;
String str_h4;
String str_t4;
String str_h5;
String str_t5;
String str_h6;
String str_t6;
String str_h7;
String str_t7;
String str_h8;
String str_t8;

String temp = "  Temperature: ";
String hum = "  Humidity: ";
String strOut;

//variables for storing measurement values
float h1 = 0.0;
float t1 = 0.0;

float h2 = 0.0;
float t2 = 0.0;

float h3 = 0.0;
float t3 = 0.0;

float h4 = 0.0;
float t4 = 0.0;

float h5 = 0.0;
float t5 = 0.0;

float h6 = 0.0;
float t6 = 0.0;

float h7 = 0.0;
float t7 = 0.0;

float h8 = 0.0;
float t8 = 0.0;

int incomingByte = 0; // for incoming serial data

void DHTloop(unsigned long RT) {
  float h1 = dht1.readHumidity();
  float t1 = dht1.readTemperature();

  float h2 = dht2.readHumidity();
  float t2 = dht2.readTemperature();

  float h3 = dht3.readHumidity();
  float t3 = dht3.readTemperature();

  float h4 = dht4.readHumidity();
  float t4 = dht4.readTemperature();

  float h5 = dht5.readHumidity();
  float t5 = dht5.readTemperature();

  float h6 = dht6.readHumidity();
  float t6 = dht6.readTemperature();

  float h7 = dht7.readHumidity();
  float t7 = dht7.readTemperature();

  float h8 = dht8.readHumidity();
  float t8 = dht8.readTemperature();
  //timestamp
  unsigned long ts = (millis() - RT)/1000;
  //  Serial.println(id_1 + temp + t1 + hum + h1);
  //  Serial.println(id_2 + temp + t2 + hum + h2);
  //  Serial.println(id_3 + temp + t3 + hum + h3);
  //  Serial.println(id_4 + temp + t4 + hum + h4);
  //  Serial.println(id_5 + temp + t5 + hum + h5);
  //  Serial.println(id_6 + temp + t6 + hum + h6);
  //  Serial.println(id_7 + temp + t7 + hum + h7);
  //  Serial.println();
  
  //create string to be sent to Raspberry Pi via serial connection (USB)
  str_h1 = String(h1);
  str_t1 = String(t1);

  str_h2 = String(h2);
  str_t2 = String(t2);

  str_h3 = String(h3);
  str_t3 = String(t3);

  str_h4 = String(h4);
  str_t4 = String(t4);

  str_h5 = String(h5);
  str_t5 = String(t5);

  str_h6 = String(h6);
  str_t6 = String(t6);

  str_h7 = String(h7);
  str_t7 = String(t7);

  str_h8 = String(h8);
  str_t8 = String(t8);

  //create output string 
  strOut = String(ts) + "," + str_t1 + "," + str_h1 + "," + str_t2 + "," + str_h2 + "," + str_t3 + "," + str_h3 + "," + str_t4 + "," + str_h4 + "," +  
  str_t5 + "," + str_h5 + "," + str_t6 + "," + str_h6 + "," + str_t7 + "," + str_h7 + "," + str_t8 + "," + str_h8;

  //Send string to serial --> Raspberry Pi
  Serial.println(strOut);
  Serial.flush();
  //print to serial monitor for debugging
//  Serial.println(strOut);
//  
//  Serial.println(id_1 + t1);
//  Serial.println(id_2 + t2);
//  Serial.println(id_3 + t3);
//  Serial.println(id_4 + t4);
//  Serial.println(id_5 + t5);
//  Serial.println(id_6 + t6);
//  Serial.println(id_7 + t7);
//  Serial.println(id_8 + t8);
//  Serial.println();
  
  delay(10000);
}

void setup() {
  // put your setup code here, to run once:
  // Setup Serial 
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  
  //setup DHT
  dht1.begin();
  dht2.begin();
  dht3.begin();
  dht4.begin();
  dht5.begin();
  dht6.begin();
  dht7.begin();
  dht8.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available() > 0) {
    unsigned long RefTime = millis(); //time to extract from next readings
    incomingByte = Serial.read();
//    Serial.println(incomingByte);
    // if we send a through serial we continue to loop
    while (incomingByte == 97) {     
      DHTloop(RefTime);
      
      //if input from serial read it --> for stopping read loop and getting new RefTime
      if (Serial.available() > 0) {
        incomingByte = Serial.read();
      }
      
    }    
  }  
}
