// include the library code:
#include <LiquidCrystal.h>
#define ENABLE 5
#define DIRA 3
#define DIRB 4

const int buttonPin = 2;

int state = 0; //0 is the regular direction; 1 is opposite; 2 is off
int isr_count = 0;
volatile int isr_state = 0;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);   
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("RPM:255;Fwd Dir");
  lcd.setCursor(0, 1);
  lcd.print("0  ");

  digitalWrite(ENABLE,HIGH); //enable on
  digitalWrite(DIRA,HIGH); //one way
  digitalWrite(DIRB,LOW);

  attachInterrupt(digitalPinToInterrupt(buttonPin), button_ISR, RISING);

  cli();//stop interrupts
  
//set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15626;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei();//allow interrupts  
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(isr_count);
  delay(1000);
}


void button_ISR()
{
  if (state == 0){
    isr_state = 1;
    state = 1;
    isr_count = 0;
    Serial.println("ISR_STATE IS 1");
    lcd.setCursor(0, 0);  
    lcd.print("                 ");
    lcd.setCursor(0, 0);
    lcd.print("RPM:255;RVRS Dir");
    lcd.setCursor(0, 1);
    lcd.print("0   ");
    digitalWrite(ENABLE,HIGH); //enable on
    digitalWrite(DIRA,LOW); //Reverse
    digitalWrite(DIRB,HIGH);
  }
  else if (state = 1){
    isr_state = 0;
    state = 0;
    isr_count = 0;
    Serial.println("ISR STATE IS 0");
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print("RPM:255;Fwd Dir");
    lcd.setCursor(0, 1);
    lcd.print("0  ");
    digitalWrite(ENABLE,HIGH); //enable on
    digitalWrite(DIRA,HIGH); //one way
    digitalWrite(DIRB,LOW);
  }
}

ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggle
//generates pulse wave of frequency 1Hz/2 = 0.5kHz
  ++isr_count;
  Serial.println(isr_count);
  if (isr_count == 31){
    if (state == 0){
      state = 2;
      isr_count = 0;
      lcd.setCursor(0, 0);  
      lcd.print("                 ");
      lcd.setCursor(0, 0);
      lcd.print("RPM:0;OFF");
      lcd.setCursor(0, 1);
      lcd.print("0   ");
      digitalWrite(ENABLE,HIGH); //enable on
      digitalWrite(DIRA,LOW);
      digitalWrite(DIRB,LOW);
      }
    else if (state == 1){
      state = 2;
      isr_count = 0;
      lcd.setCursor(0, 0);  
      lcd.print("                 ");
      lcd.setCursor(0, 0);
      lcd.print("RPM:0;OFF");
      lcd.setCursor(0, 1);
      lcd.print("0   ");
      digitalWrite(ENABLE,HIGH); //enable on
      digitalWrite(DIRA,LOW);
      digitalWrite(DIRB,LOW);
    }
    else if (state = 2){
      if (isr_state == 0){
        lcd.setCursor(0, 0);
        lcd.print("                ");
        lcd.setCursor(0, 0);
        lcd.print("RPM:255;Fwd Dir");
        lcd.setCursor(0, 1);
        lcd.print("0  ");
        isr_count = 0;
        digitalWrite(ENABLE,HIGH); //enable on
        digitalWrite(DIRA,HIGH); //one way
        digitalWrite(DIRB,LOW);
      }
      else if (isr_state == 1){
        lcd.setCursor(0, 0);  
        lcd.print("                 ");
        lcd.setCursor(0, 0);
        lcd.print("RPM:255;RVRS Dir");
        lcd.setCursor(0, 1);
        lcd.print("0   ");
        isr_count = 0;
        state = 1;
        digitalWrite(ENABLE,HIGH); //enable on
        digitalWrite(DIRA,LOW); //Reverse
        digitalWrite(DIRB,HIGH);
      }
    }
 }
}
