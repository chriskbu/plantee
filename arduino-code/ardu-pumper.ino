
/*
 * Optimal humidity: 170 - 250
 * Max water : 166
 * Min water : 500
*/

int led1Red     = 3;
int led2Yellow  = 5;
int led3Yellow  = 6;
int led4Green   = 9;
int led5Green   = 10;
int led6Green   = 11;

int fader = 150;

int numLEDs = 0;

int soilSensor = A0;

int ledList[6] = {0, 1, 2, 3, 4, 5};

void setup() {
  Serial.begin(115200);
  // Set all Digital Pins as Output for LED's:
  pinMode(led1Red, OUTPUT);
  pinMode(led2Yellow, OUTPUT);
  pinMode(led3Yellow, OUTPUT);
  pinMode(led4Green, OUTPUT);
  pinMode(led5Green, OUTPUT);
  pinMode(led6Green, OUTPUT);

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
    case 5:
      digitalWrite(led6Green, state);
      break;
    default:
      break;
  }
}

float getPercentageHumid(int analogData){
  float fullHumid = 500.0;
  float offset = 120.0;
  float percentageHumidity = ((fullHumid-(analogData-offset))/fullHumid) * 100;
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

void loop() {
  int analogData = analogRead(soilSensor);
  float percentageHumid = getPercentageHumid(analogData);
  numLEDs = numLEDsOn(percentageHumid);
  Serial.println(analogData);
  Serial.println(percentageHumid);
  Serial.println(numLEDs);
  cycleLEDs(numLEDs);
  delay(1000);
  setLEDs(ledList, LOW);
  delay(500);
  setLEDs(ledList, HIGH);
  delay(500);
  setLEDs(ledList, LOW);
  delay(500);
}