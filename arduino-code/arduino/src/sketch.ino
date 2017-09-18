// the setup function runs once when you press reset or power the board
int pumpPin = 3;
int sensorPin = 0;
int sensorPowerPin = 5;
int sensorValue = 0;
int oldSensorVal = 0;
int threshold = 300;
int pumpPowerLevel = 150;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(pumpPin, OUTPUT);
  pinMode(sensorPowerPin, OUTPUT);
  digitalWrite(sensorPowerPin, LOW);
  digitalWrite(pumpPin, LOW);
  sensorValue = getSensorRead();
  oldSensorVal = sensorValue;
  Serial.begin(9600);
}

int findPumpPower(){
    for(int i = 0; i<255; i++){
    }
    return 0;
}

int getSensorRead(){
  // Do sensor reading
  digitalWrite(sensorPowerPin, HIGH);
  delay(200);
  int val = analogRead(sensorPin);
  delay(50);
  digitalWrite(sensorPowerPin, LOW);
  return val;
}

void printReading(){
  Serial.print(sensorValue);
  Serial.print("/");
  Serial.print(threshold);
  Serial.println("...");
}
boolean checkDry(){
    if(sensorValue<threshold){
        return true;
    }
    return false;
}

boolean waterPlantDigital(){
    if(sensorValue < threshold){
        Serial.println("WATERING...");
        digitalWrite(pumpPin, HIGH);    // turn the Pump on (HIGH is the voltage level)
        delay(2500);               // wait for a second
        digitalWrite(pumpPin, LOW);     // turn the Pump off by making the voltage LOW
        delay(500);                // wait for a second
        Serial.println("WATERING COMPLETE...");
        return true;
    }
    return false;
}
boolean waterPlantAnalog(){
    if(sensorValue < threshold){
        Serial.println("WATERING...");
        analogWrite(pumpPin, pumpPowerLevel);    // turn the Pump on (HIGH is the voltage level)
        delay(2500);
        analogWrite(pumpPin, 0);     // turn the Pump off by making the voltage LOW
        delay(500);                // wait for a second
        Serial.println("WATERING COMPLETE...");
        return true;
    }
    return false;
}

// the loop function runs over and over again forever
void loop() {
  sensorValue = getSensorRead();
  printReading();
  if(!waterPlantAnalog()){
      Serial.println("PLANT IS CHILL...");
  }
  delay(10000);
}