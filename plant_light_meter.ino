/*
  Plant Light Meter
  A meter to determine if your plants are 
  getting the type of light they require
*/

const int lightSensorPin = A0;

const int lowLightLEDPin = 13;
const int mediumLightLEDPin = 12;
const int indirectLightLEDPin = 11;
const int directLightLEDPin = 10;


int lightSensorValue = 0;
int lightSensorMax = 1023;
int lightSensorMin = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(lowLightLEDPin, OUTPUT);
  pinMode(mediumLightLEDPin, OUTPUT);
  pinMode(indirectLightLEDPin, OUTPUT);
  pinMode(directLightLEDPin, OUTPUT);

  // Make sure all lights are off at start up
  digitalWrite(lowLightLEDPin, LOW);
  digitalWrite(mediumLightLEDPin, LOW);
  digitalWrite(indirectLightLEDPin, LOW);
  digitalWrite(directLightLEDPin, LOW);
}

void loop() {
  lightSensorValue = analogRead(lightSensorPin);

  // Map lightSensorValue to range of Lux
  lightSensorValue = map(lightSensorValue, lightSensorMin, lightSensorMax, 0, 4000);

  Serial.print("Sensor Value: ");
  Serial.print(lightSensorValue);
  Serial.println(" Lux");

  if(lightSensorValue == 0){
    digitalWrite(lowLightLEDPin, LOW);
    digitalWrite(mediumLightLEDPin, LOW);
    digitalWrite(indirectLightLEDPin, LOW);
    digitalWrite(directLightLEDPin, LOW);
  } else if(lightSensorValue < 500) {
    digitalWrite(lowLightLEDPin, HIGH);
    digitalWrite(mediumLightLEDPin, LOW);
    digitalWrite(indirectLightLEDPin, LOW);
    digitalWrite(directLightLEDPin, LOW);
  } else if(lightSensorValue >= 500 && lightSensorValue < 1000) {
    digitalWrite(lowLightLEDPin, HIGH);
    digitalWrite(mediumLightLEDPin, HIGH);
    digitalWrite(indirectLightLEDPin, LOW);
    digitalWrite(directLightLEDPin, LOW);
  } else if(lightSensorValue >= 1000 && lightSensorValue < 2000) {
    digitalWrite(lowLightLEDPin, HIGH);
    digitalWrite(mediumLightLEDPin, HIGH);
    digitalWrite(indirectLightLEDPin, HIGH);
    digitalWrite(directLightLEDPin, LOW);
  } else if(lightSensorValue >= 2000) {
    digitalWrite(lowLightLEDPin, HIGH);
    digitalWrite(mediumLightLEDPin, HIGH);
    digitalWrite(indirectLightLEDPin, HIGH);
    digitalWrite(directLightLEDPin, HIGH);
  }
}
