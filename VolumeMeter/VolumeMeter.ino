/* This is code to create a volume meter using the KY-038 sound sensor.
 *It uses 8 LEDS (3 green, 3 yellow, 2 red), 8 330 Ohm resistors, and  
 *and an arduino. The sound sensor can be quite finicky, so to use it 
 *correctly, adjust the potentiometer on the KY-038 module so that when
 *the room is silent, the sound displayed on the serial monitor is about 
 *518.
 */
//The pins connecting the LED's are from 2-9
int sensorPin = A0;
float sensorValue = 0;
int GreenPin1 = 2;
int GreenPin2 = 3;
int GreenPin3 = 4;
int YellowPin1 = 5;
int YellowPin2 = 6;
int YellowPin3 = 7;
int RedPin1 = 8;
int RedPin2 = 9;

//sets all pins as outputs
void setup() {
  Serial.begin(9600);
  pinMode(GreenPin1, OUTPUT);
  pinMode(GreenPin2, OUTPUT);
  pinMode(GreenPin3, OUTPUT);
  pinMode(YellowPin1, OUTPUT);
  pinMode(YellowPin2, OUTPUT);
  pinMode(YellowPin3, OUTPUT);
  pinMode(RedPin1, OUTPUT);
  pinMode(RedPin2, OUTPUT);
}
void loop() {
  sensorValue = analogRead(sensorPin);    
  Serial.println(sensorValue); 
  //The input values for the sensor go from 519 - 540
  if (sensorValue < 519)
  {
    digitalWrite(GreenPin1, LOW);
    digitalWrite(GreenPin2, LOW);
    digitalWrite(GreenPin3, LOW);
    digitalWrite(YellowPin1, LOW);
    digitalWrite(YellowPin2, LOW);
    digitalWrite(YellowPin3, LOW);
    digitalWrite(RedPin1, LOW);
    digitalWrite(RedPin2, LOW);
  }
  if ((sensorValue > 519) && (sensorValue <= 522)) {
    digitalWrite(GreenPin1, HIGH);
    digitalWrite(GreenPin2, LOW);
    digitalWrite(GreenPin3, LOW);
    digitalWrite(YellowPin1, LOW);
    digitalWrite(YellowPin2, LOW);
    digitalWrite(YellowPin3, LOW);
    digitalWrite(RedPin1, LOW);
    digitalWrite(RedPin2, LOW);
  }
  if ((sensorValue > 522) && (sensorValue <= 525))
  {
    digitalWrite(GreenPin1, HIGH);
    digitalWrite(GreenPin2, HIGH);
    digitalWrite(GreenPin3, LOW);
    digitalWrite(YellowPin1, LOW);
    digitalWrite(YellowPin2, LOW);
    digitalWrite(YellowPin3, LOW);
    digitalWrite(RedPin1, LOW);
    digitalWrite(RedPin2, LOW);
  }
  if ((sensorValue > 525) && (sensorValue <= 528))
  {
    digitalWrite(GreenPin1, HIGH);
    digitalWrite(GreenPin2, HIGH);
    digitalWrite(GreenPin3, HIGH);
    digitalWrite(YellowPin1, LOW);
    digitalWrite(YellowPin2, LOW);
    digitalWrite(YellowPin3, LOW);
    digitalWrite(RedPin1, LOW);
    digitalWrite(RedPin2, LOW);
  }
  if ((sensorValue > 528) && (sensorValue <= 531))
  {
    digitalWrite(GreenPin1, HIGH);
    digitalWrite(GreenPin2, HIGH);
    digitalWrite(GreenPin3, HIGH);
    digitalWrite(YellowPin1, HIGH);
    digitalWrite(YellowPin2, LOW);
    digitalWrite(YellowPin3, LOW);
    digitalWrite(RedPin1, LOW);
    digitalWrite(RedPin2, LOW);
  }
  if ((sensorValue > 531) && (sensorValue <= 534))
  {
    digitalWrite(GreenPin1, HIGH);
    digitalWrite(GreenPin2, HIGH);
    digitalWrite(GreenPin3, HIGH);
    digitalWrite(YellowPin1, HIGH);
    digitalWrite(YellowPin2, HIGH);
    digitalWrite(YellowPin3, LOW);
    digitalWrite(RedPin1, LOW);
    digitalWrite(RedPin2, LOW);
  }
  if ((sensorValue > 534) && (sensorValue <= 537))
  {
    digitalWrite(GreenPin1, HIGH);
    digitalWrite(GreenPin2, HIGH);
    digitalWrite(GreenPin3, HIGH);
    digitalWrite(YellowPin1, HIGH);
    digitalWrite(YellowPin2, HIGH);
    digitalWrite(YellowPin3, HIGH);
    digitalWrite(RedPin1, LOW);
    digitalWrite(RedPin2, LOW);
  }
  if ((sensorValue > 537) && (sensorValue <= 540))
  {
    digitalWrite(GreenPin1, HIGH);
    digitalWrite(GreenPin2, HIGH);
    digitalWrite(GreenPin3, HIGH);
    digitalWrite(YellowPin1, HIGH);
    digitalWrite(YellowPin2, HIGH);
    digitalWrite(YellowPin3, HIGH);
    digitalWrite(RedPin1, HIGH);
    digitalWrite(RedPin2, LOW);
  }
  if (sensorValue > 540)
  {
    digitalWrite(GreenPin1, HIGH);
    digitalWrite(GreenPin2, HIGH);
    digitalWrite(GreenPin3, HIGH);
    digitalWrite(YellowPin1, HIGH);
    digitalWrite(YellowPin2, HIGH);
    digitalWrite(YellowPin3, HIGH);
    digitalWrite(RedPin1, HIGH);
    digitalWrite(RedPin2, HIGH);
  }
}
