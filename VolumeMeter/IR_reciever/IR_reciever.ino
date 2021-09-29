/* This code is using an IR reciever, a remote, and an RGB LED. 
 *  The IR reciever is not taking in any information until a button 
 *  is pressed. It is automatically off, but you can turn it on
 *  using the power button, and you can turn it off using
 *  the Func/stop button. This code only works for the 
 *  ELEGOO remotes, as the values returned by the remote 
 *  are unique.
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
    RGB_color(255, 0, 0); // Red
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
  while (color_status == 2)
  {
    RGB_color(255, 0, 0); // Red
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
      input = 16769565; //value for power button
      return input;
    }
    if (results.value == 16753245)//stop button
    {
      input = 16753245; //value for stop button
      return input;
    }
    if (results.value == 16738455)//Button 0
    {
      input = 16738455; //value for button 0
      return input;
    }
    irrecv.resume();    // Receive the next value 
  }  
  delay(500); //delay 300ms
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
        RGB_color(0, 0, 0);
        irrecv.resume();
    }
    if (colorchange(results) == 16738455) //turns LED Red
    {
        color_status = 2;
        irrecv.resume();
    }
  }
}
  
