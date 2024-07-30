/* to generate pwm with freq of 1kHZ to 50KHZ  with 10 ranges of D_cycle Each 10%*/



#include <math.h>
uint16_t f =0;
float d = 0.0;
uint16_t top = 0;
float duty = 0.5;
float num,den,a1;
bool pinState0, pinState1, pinState2, pinState3;

void update_timer_less_32(int d, uint16_t f) {
  Serial.print(f);
  Serial.println(" Hz frequency and ");
  //Serial.print(d);
  //Serial.println("% duty cycle");
  num=16000000.0f;
  den=(64.0f)*(f);
  a1=num/den;
  top = round(a1- 1);
  //top=map(top,0,2499,4,2499)
  Serial.print(top);
  Serial.println(" is the top ");
  // TIMER DECLERATION
  //DDRB |= (1 << DDB5);  // SETTING DDRB BIT 7(LAST BIT)  OC1A  AS OUTPUT
  TCNT1 = 0x00;

  TCCR1A = 0;
  TCCR1A |= _BV(WGM11);
  TCCR1A |= _BV(COM1A1);

  TCCR1B = 0;
  TCCR1B |= _BV(WGM12) | _BV(WGM13) | _BV(CS10) | _BV(CS11);  // 64 pre_scaller
    //f=round(f_SF*f);
    //Serial.println("freq");
    //Serial.println(f);

  ICR1 = top;
  duty = d / 100.0f;
  OCR1A = round(duty * ICR1);
  //Serial.print(top);
  //Serial.print(" is the top ");
  //Serial.print(f);
  //Serial.print(" Hz frequency and ");
  //Serial.print(d);
  //Serial.println("% duty cycle");
}

void update_timer_greater_32(int d, uint16_t f) {
  Serial.print(f);
  Serial.println("above 32 Hz frequency");
  //Serial.print(d);
  //Serial.println("% duty cycle");
  num=16000000.0f;
  den=(1.0f)*(f);
  a1=num/den;
  top = round(a1- 1);
  //top=map(top,0,2499,4,2499)
  Serial.print(top);
  Serial.println(" is the top ");
  // TIMER DECLERATION
  //DDRB |= (1 << DDB5);  // SETTING DDRB BIT 7(LAST BIT)  OC1A  AS OUTPUT
  TCNT1 = 0x00;
  TCCR1A = 0;
  TCCR1A |= _BV(WGM11);
  TCCR1A |= _BV(COM1A1);
  TCCR1B = 0;
  TCCR1B |= _BV(WGM12) | _BV(WGM13) | _BV(CS10) ;  // no pre_scaller
    //f=round(f_SF*f);
    //Serial.println("freq");
    //Serial.println(f);

  ICR1 = top;
  duty = d / 100.0f;
  OCR1A = round(duty * ICR1);
  //Serial.print(top);
  //Serial.print(" is the top ");
  //Serial.print(f);
  //Serial.print(" Hz frequency and ");
  //Serial.print(d);
  //Serial.println("% duty cycle");
}



void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  DDRD &= (~(1 << DDD0)) & (~(1 << DDD1)) & (~(1 << DDD2)) & (~(1 << DDD3));  // D0 TO D3 ARE INPUTS



  // TIMER DECLERATION
  DDRB |= (1 << DDB5);  // SETTING DDRB BIT 7(LAST BIT)  OC1A  AS OUTPUT
  TCNT0 = 0x00;

  TCCR1A = 0;
  TCCR1A |= _BV(WGM11);
  TCCR1A |= _BV(COM1A1);

  TCCR1B = 0;
  TCCR1B |= _BV(WGM12) | _BV(WGM13) | _BV(CS10) | _BV(CS11);  // 64 pre_scaller

  ICR1 = 249;
  OCR1A = 125;
}

void loop() {
  // put your main code here, to run repeatedly:
  //PORTD &= (~(1 << DDD0)) & (~(1 << DDD1)) & (~(1 << DDD2)) & (~(1 << DDD3));
  pinState0 = PIND & (1 << PIND0);
  pinState1 = PIND & (1 << PIND1);
  pinState2 = PIND & (1 << PIND2);
  pinState3 = PIND & (1 << PIND3);
  if (pinState0 == HIGH) {
    // Button is pressed
    // Debounced action done with RC(LPF)
    delay(200);
    Serial.println(" B1 ");
    f = f + 1000;
    if (f > 50000) {
      f = 50000;
    }
  }
  if (pinState1 == HIGH) {
    delay(200);
    Serial.println(" B2 ");
    f = f - 1000;
    if (f < 100) {
      f = 100;
    }
  }
  if (pinState2 == HIGH) {
    delay(200);
    Serial.println(" B3 ");
    d = d + 10.0;
    if (d > 100) {
      d = 100.0;
    }
  }
  if (pinState3 == HIGH) {
    delay(200);
    Serial.println(" B4 ");
    d = d - 10.0;  // Example debounce delay
    if (d <10) {
      d = 10.0;
    }
  }
  if(f<=32000){
    update_timer_less_32(d, f);
    }
  else{
    update_timer_greater_32(d, f);
    }
  }



