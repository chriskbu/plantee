#include <dht.h>
dht DHT;

#define DHT11_PIN 5

int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int moistSensor_value = 0;  // variable to store the value coming from the sensor
int maxValTemp = 658;
int difference = 0;

int temp_offset = -10;
int humidity_offset = 0;
int moist_offset = 0;

void setup() {
  // declare the ledPin as an OUTPUT:
  Serial.begin(115200);
  Serial.println("---SUPER GARDENER---");
  Serial.println("Libraries used: DHT");
  Serial.println("Garderner Version: v1.0");
  Serial.println("Status,\t\tHumidity (%),\t\tTemperature (C),\t\tMoistness");
  pinMode(ledPin, OUTPUT);
}

void printReadingsToSerial(){
  // DISPLAY DATA
  Serial.print("\t\t");
  Serial.print(DHT.humidity, 1);
  Serial.print("\t\t\t");
  Serial.print(DHT.temperature, 1);
  Serial.print("\t\t\t\t");
  Serial.println(808-moistSensor_value, DEC);
}

void doOffset(){
  DHT.humidity = DHT.humidity + humidity_offset;
  DHT.temperature = DHT.temperature + temp_offset;
  moistSensor_value = moistSensor_value + moist_offset;
}

void checkSensors(){
  // read the value from the moisture sensor:
  moistSensor_value = analogRead(sensorPin);
  // Check temp sensor
  int chk = DHT.read11(DHT11_PIN);
  switch(chk){
    case DHTLIB_OK:  
      Serial.print("OK,\t"); 
      break;
    case DHTLIB_ERROR_CHECKSUM: 
      Serial.print("Checksum error,\t"); 
      break;
    case DHTLIB_ERROR_TIMEOUT: 
      Serial.print("Time out error,\t"); 
      break;
    case DHTLIB_ERROR_CONNECT:
      Serial.print("Connect error,\t");
      break;
    case DHTLIB_ERROR_ACK_L:
      Serial.print("Ack Low error,\t");
      break;
    case DHTLIB_ERROR_ACK_H:
      Serial.print("Ack High error,\t");
      break;
    default: 
      Serial.print("Unknown error,\t"); 
      break;
  } 
}

void loop() {
  checkSensors();
  doOffset();
  printReadingsToSerial();
  delay(2000);
}
