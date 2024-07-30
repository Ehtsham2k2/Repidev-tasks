/*task4 
To Generate 8.5khz wirth 37% Duty cycle*/
/*
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  DDRB |= (1 << DDB7);  // SETTING DDRB BIT 7(LAST BIT)  OC0A  AS OUTPUT

  //TIMER 0 CONFIGURATION
  TCCR0A=_BV(COM0A1)|_BV(WGM00)|_BV(WGM01);
  TCCR0B=_BV(CS01)|_BV(CS00);

  //Set Duty Cycle
  OCR0A=95;//THIS IS AFTER THE CALCULATION OF DUTY CUYCLE FORMULA
  // Set the compare match value
  TCNT0 = 235;
  // Enable Timer0 Compare Match A Interrupt
  TIMSK0 = (1 << OCIE0A);
  // Enable global interrupts
  // sei();
}

void loop() {
//
}

*/

/*task4 
To Generate 8.5khz */

// void setup() {
//   //Serial.begin(9600);
//   // put your setup code here, to run once:
//   DDRB |= (1 << DDB7);  // SETTING DDRB BIT 7(LAST BIT)  OC0A  AS OUTPUT
//   TCNT0=0x00;

//   TCCR0A = 0;
//   TCCR0A |= _BV(COM0A0)|_BV(WGM00)|_BV(WGM01);//
 
//   TCCR0B &= ~(1<<CS00)&~(1<<CS02);
//   TCCR0B |=_BV(CS01) |_BV(WGM02);//8 prescaler there must be |_BV(WGM02) as per the table

//    // Set the match value or last tick
//    OCR0A= 235;
//   // Enable Timer0 Compare Match A Interrupt
//   //TIMSK0 = (1 << OCIE0A) ;//

//   // Enable global interrupts
//   //sei();


// }
/* 8.5k HZ with 5.313% duty cycle  
void setup()
{
  DDRB |= (1 << DDB1);  // SETTING DDRB BIT 7(LAST BIT)  OC0A  AS OUTPUT
  TCNT0=0x00;

  TCCR1A = 0;
  TCCR1A |= _BV(WGM11);
  TCCR1A |= _BV(COM1A1);

  TCCR1B = 0;
  TCCR1B |= _BV(WGM12) | _BV(WGM13) | _BV(CS10);

  ICR1 = 1882;
  OCR1A = 100;
}

void loop() {
// 
}
*/


// 200 HZ with 37% duty cycle
void setup()
{
DDRB |= (1 << DDB5);  // SETTING DDRB BIT 7(LAST BIT)  OC0A  AS OUTPUT
  TCNT0=0x00;

  TCCR1A = 0;
  TCCR1A |= _BV(WGM11);
  TCCR1A |= _BV(COM1A1);

  TCCR1B = 0;
  TCCR1B |= _BV(WGM12) | _BV(WGM13) | _BV(CS10)| _BV(CS11);

  ICR1 = 1249;
  OCR1A = 463;
}

void loop() {


}
