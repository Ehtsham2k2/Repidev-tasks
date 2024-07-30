bool pinState0, pinState1, pinState2, pinState3;
/* to generate variable freq (100 to 50khz)and D_cylce(0% ( to 100%) 
this task has low resoultion at high freq or change of output freq w.r.t input is low after 32.1k
*/
#include <math.h>
 uint16_t f = 100;
int d = 10;
int top = 4;
float duty = 0.5;
float num,den,a1;
//const float ISR_SF = (2499 - 4) / (100 - 0);
//const float f_SF = (50000 - 100) / (100 - 0);
void update_timer(int d, uint16_t f) {
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

  ICR1 = 2499;
  OCR1A = 1249;
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
    d = d + 10;
    if (d > 100) {
      d = 100;
    }
  }
  if (pinState3 == HIGH) {
    delay(200);
    Serial.println(" B4 ");
    d = d - 10;  // Example debounce delay
    if (d <10) {
      d = 10;
    }
  }
  update_timer(d, f);
  //Serial.println("Pin D0 is LOW");
}
