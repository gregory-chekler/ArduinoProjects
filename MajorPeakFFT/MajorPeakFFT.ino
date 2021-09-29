
//Reads sounds from 100 Hz to 500 Hz very well

#include "arduinoFFT.h"
 
#define SAMPLES 128             //Must be a power of 2
#define SAMPLING_FREQUENCY 10000 //Hz, must be less than 10000 due to ADC
 
arduinoFFT FFT = arduinoFFT();

//The pins connecting the LED's are from 2-9
int GreenPin1 = 2;
int GreenPin2 = 3;
int GreenPin3 = 4;
int YellowPin1 = 5;
int YellowPin2 = 6;
int YellowPin3 = 7;
int RedPin1 = 8;
int RedPin2 = 9;
 
unsigned int sampling_period_us;
unsigned long microseconds;
 
double vReal[SAMPLES];
double vImag[SAMPLES];
 
void setup() {
    Serial.begin(115200);
 
    sampling_period_us = round(1000000*(1.0/SAMPLING_FREQUENCY));
    
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
   
    /*SAMPLING*/
    for(int i=0; i<SAMPLES; i++)
    {
        microseconds = micros();    //Overflows after around 70 minutes!
     
        vReal[i] = analogRead(0);
        vImag[i] = 0;
     
        while(micros() < (microseconds + sampling_period_us)){
        }
    }
 
    /*FFT*/
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
 
    /*PRINT RESULTS*/
    
    Serial.println(peak);     //Print out what frequency is the most dominant.

    /*Display the results on the volume meter */

    //The peak values go from 200 to 5000
  if (peak < 300)
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
  if ((peak > 830) && (peak <= 1360)) {
    digitalWrite(GreenPin1, HIGH);
    digitalWrite(GreenPin2, LOW);
    digitalWrite(GreenPin3, LOW);
    digitalWrite(YellowPin1, LOW);
    digitalWrite(YellowPin2, LOW);
    digitalWrite(YellowPin3, LOW);
    digitalWrite(RedPin1, LOW);
    digitalWrite(RedPin2, LOW);
  }
  if ((peak > 1360) && (peak <= 1890))
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
  if ((peak > 1890) && (peak <= 2420))
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
  if ((peak > 2420) && (peak <= 2950))
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
  if ((peak > 2950) && (peak <= 3480))
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
  if ((peak > 3480) && (peak <= 4010))
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
  if ((peak > 4010) && (peak <= 4540))
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
  if (peak > 4540)
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
