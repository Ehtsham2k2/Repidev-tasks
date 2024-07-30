/* varying pwm on 50 hz to have pre-sine wave*/
// WITH TWO DIFFERENT TIMERS 1 AND 3
#include <math.h>
uint16_t f = 50.0;
uint16_t a1, num, den, top;
float duty;
//int j = 0;
const float pi = 3.141592;
float dutyCycles[10];
float D[10];

void duty_cycle() {
  //float t=0;
  for (int i = 0; i < 10; i++) {
    dutyCycles[i] = sin(2 * pi * f * (i * 0.001));  // b/w 0 & 1 since map cant use for floating point numbers
    //t=(t+1)*0.001;
    Serial.println(dutyCycles[i]);
  }
}

void D_map() {
  for (int i = 0; i < 10; i++) {
    D[i] = (dutyCycles[i]) * 100.0f;  // b/w 0 & 100
  }
}
void update_timer(float d) {
  // TIMER DECLERATION
  DDRB |= (1 << DDB5);  // SETTING DDRB BIT 7(LAST BIT)  OC1A  AS OUTPUT
  TCNT0 = 0x00;

  TCCR1A = 0;
  TCCR1A |= _BV(WGM11);
  TCCR1A |= _BV(COM1A1);

  TCCR1B = 0;
  TCCR1B |= _BV(WGM12) | _BV(WGM13) | _BV(CS10);  // 1 pre_scaller

  duty = d / 100.0f;
  ICR1 = 15999;
  OCR1A = round(duty * 15999);
}
void update_timer_i(float d) {
  // TIMER DECLERATION
  DDRB |= (1 << DDB5);  // SETTING DDRB BIT 7(LAST BIT)  OC1A  AS OUTPUT
  TCNT3 = 0x00;

  TCCR3A = 0;
  TCCR3A |= _BV(WGM31);
  TCCR3A |= _BV(COM3A1)|_BV(COM3A0);

  TCCR3B = 0;
  TCCR3B |= _BV(WGM32) | _BV(WGM33) | _BV(CS30);  // 1 pre_scaller
  duty = d / 100.0f;
  ICR3 = 15999;
  OCR3A = round(duty * 15999);;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // put your setup code here, to run once:

  duty_cycle();  // to get duty cycles b/w 0 and 1
  D_map();       // to get duty cycles b/w 0 and 100


  // TIMER DECLERATION
  DDRB |= (1 << DDB5);  // SETTING DDRB BIT 7(LAST BIT)  OC1A  AS OUTPUT
  TCNT0 = 0x00;

  TCCR1A = 0;
  TCCR1A |= _BV(WGM11);
  TCCR1A |= _BV(COM1A1);

  TCCR1B = 0;
  TCCR1B |= _BV(WGM12) | _BV(WGM13) | _BV(CS10);  // 1 pre_scaller

  ICR1 = 15999;
  OCR1A = 8000;//8000

  // TIMER 3 DECLERATION FOR Inverting 
  DDRE |= (1 << DDE3);  // SETTING DDRE BIT 3 D5  OC3A  AS OUTPUT
  TCNT3 = 0x00;

  TCCR3A = 0;
  TCCR3A |= _BV(WGM31);
  TCCR3A |= _BV(COM3A1)|_BV(COM3A0);

  TCCR3B = 0;
  TCCR3B |= _BV(WGM32) | _BV(WGM33) | _BV(CS30);  // 1 pre_scaller

  ICR3 = 15999;
  OCR3A = 0x00;//8000
}

void loop() {
  // put your main code here, to run repeatedly:
  /*if (j == 0) {
    for (int i = 0; i < 10; i+2) {
      //Serial.println(D[i]);
      update_timer(D[i]);
      delay(1);  //1 ms delay to have fs=1khz and fout(sine_wave)=50HZ
      
    }
    j=1;
    }

  else if(j==1){
      for (int i = 1; i < 10; i+2) {
        //Serial.println(D[i]);
        update_timer_i(D[i]);
        delay(1);  //1 ms delay to have fs=1khz and fout(sine_wave)=50HZ
       
    }
   j=0;
  }*/


for (int i = 0; i < 10; i++) {
  //Serial.println(D[i]);
  update_timer(D[i]);
  
  update_timer_i(D[i]);

  delay(1);  //1 ms delay to have fs=1khz and fout(sine_wave)=50HZ
}



/*
for (int i = 1; i < 10; i+=2) {
  //Serial.println(D[i]);
  update_timer_i(D[i]);
  delay(1);  //1 ms delay to have fs=1khz and fout(sine_wave)=50HZ
}*/

      
    

  }

