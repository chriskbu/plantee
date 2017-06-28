
/*
 * Optimal humidity: 170 - 250
 * Feels wet : 150
 * Feels dry : 350
 * Max water : 166
 * Min water : 350
*/

float maxWater = 600;
float minWater = 0;
float analogData = 0;

float seconds_per_poll = 300.0;

int led1Red     = 3;
int led2Yellow  = 5;
int led3Yellow  = 6;
int led4Green   = 9;
int led5Green   = 10;
int pwrSensor   = 11;

int fader = 100;

int numLEDs = 5;

int soilSensor = A0;

int ledList[5] = {0, 1, 2, 3, 4};

void setup() {
  Serial.begin(9600);

  // Set all Digital Pins as Output for LED's:
  pinMode(led1Red, OUTPUT);
  pinMode(led2Yellow, OUTPUT);
  pinMode(led3Yellow, OUTPUT);
  pinMode(led4Green, OUTPUT);
  pinMode(led5Green, OUTPUT);

  pinMode(pwrSensor, OUTPUT);

}


void setLED(int ledNum, int state){
  switch(ledNum){
    case 0:
      digitalWrite(led1Red, state);
      break;
    case 1:
      digitalWrite(led2Yellow, state);
      break;
    case 2:
      digitalWrite(led3Yellow, state);
      break;
    case 3:
      digitalWrite(led4Green, state);
      break;
    case 4:
      digitalWrite(led5Green, state);
      break;
    default:
      break;
  }
}


float getPercentageHumid(int analogData){
  float percentageHumidity = (analogData/maxWater)*100;
  return percentageHumidity;
}

void setLEDs(int ledList [], int state){
  for(int i = 0; i<numLEDs; i++){
    setLED(ledList[i], state);
  }
}

void cycleLEDs(int currLEDs){
  for(int i = 0; i < currLEDs; i++){
    setLED(i, HIGH);
    delay(fader);
  }
}

void cycleLEDsReverse(int currLEDs){
  for(int i = currLEDs; 0 < i; i--){
    setLED(i, LOW);
    delay(fader);
  }
}

// TODO: Needs work to dynamicly adjust to numLeds
int numLEDsOn(float percentage){
  if(80.0 < percentage)
    return 6;
  if(60.0 < percentage)
    return 5;
  if(50.0 < percentage)
    return 4;
  if(35.0 < percentage)
    return 3;
  if(25.0 < percentage)
    return 2;
  return 1;
}

float getSensorReading(){
  digitalWrite(pwrSensor, HIGH);
  delay(1000);
  float data = analogRead(soilSensor);
  delay(1000);
  digitalWrite(pwrSensor, LOW);
  return data;
}

void loop() {
  analogData = getSensorReading();
  float percentageHumid = getPercentageHumid(analogData);
  numLEDs = numLEDsOn(percentageHumid);
  Serial.print(analogData);
  Serial.print(",    ");
  Serial.print(percentageHumid);
  Serial.print(",    ");
  Serial.println(numLEDs);
  cycleLEDs(numLEDs);
  delay(seconds_per_poll*1000);
  cycleLEDsReverse(numLEDs);
  //setLEDs(ledList, LOW);
  //delay(250);
  //setLEDs(ledList, HIGH);
  //delay(250);
  //setLEDs(ledList, LOW);
  delay(250);
}