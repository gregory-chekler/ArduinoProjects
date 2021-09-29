/* This code is using an IR reciever, a remote, and an RGB LED. 
 *  The IR reciever is not taking in any information until a button 
 *  is pressed. Currently, when the power button is pressed on the 
 *  ELEGOO remote, the LED turns off for a certain period of time
 *  and then resumes the cycle.
 */
#include <IRremote.h>  // use the IRRemote.h
const byte irReceiverPin = 2;  //the SIG of receiver module attach to pin2
int red_light_pin= 11;
int green_light_pin = 10;
int blue_light_pin = 9;
IRrecv irrecv(irReceiverPin); //Creates a variable of type IRrecv
decode_results results;    // define results
volatile int color_status = 0; //makes LED off by default

void setup()
{
  Serial.begin(9600);    //initialize serial,baudrate is 9600
  irrecv.enableIRIn();   // enable ir receiver module
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
  attachInterrupt(0, isr, CHANGE); //interrupt assignment
}

void loop() 
{
  while (color_status == 1)
  {
    RGB_color(255, 0, 0); // No color
    delay(500);
    RGB_color(0, 255, 0); // Green
    delay(500);
    RGB_color(0, 0, 255); // Blue
    delay(500);
    RGB_color(255, 255, 125); // Raspberry
    delay(500);
    RGB_color(0, 255, 255); // Cyan
    delay(500);
    RGB_color(255, 0, 255); // Magenta
    delay(500);
    RGB_color(255, 255, 0); // Yellow
    delay(500);
    RGB_color(255, 255, 255); // White
  }
  while (color_status == 0)
  {
    RGB_color(0, 0, 0); // No color
  }
}
void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}


unsigned long colorchange(decode_results &results)
{  
  unsigned long input;

  
   if (irrecv.decode(&results)) //if the ir receiver module receiver data
  {  
    Serial.print("irCode: ");    //print "irCode: "        
    Serial.print(results.value); //print the value in decimal
    Serial.print("\n");
    if (results.value == 16769565)//power button
    {
      input = 16769565;
      return input;
    }
    if (results.value == 16753245)//stop button
    {
      input = 16753245;
      return input;
    }
    irrecv.resume();    // Receive the next value 
  }  
  delay(600); //delay 600ms
}

void isr()
{
  if (irrecv.decode(&results)) //if the ir receiver module receiver data is being reveived
  {
    if (colorchange(results) == 16769565) //turns LED off
    {
        color_status = 0;
        irrecv.resume();
    }
    if (colorchange(results) == 16753245) //turns LED on
    {
        color_status = 1;
        irrecv.resume();
    }
  }
}
