/* varying pwm on 50 hz to have pre-sine wave*/
// WITH single TIMERS 1
#include <math.h>
#include <avr/interrupt.h>

#define FUNDAMENTAL_FREQUENCY 50.0
#define SAMPLES               20.0
#define SWICTHING_FREQUENCY   (FUNDAMENTAL_FREQUENCY * SAMPLES)

uint16_t f = 50.0;
uint16_t a1, num, den, top;
float  duty;
//int j = 0;
const float pi = 3.141592;
float dutyCycles[20];
float dutyCycles2[20];
volatile float D[20];
volatile float D2[20];

volatile int update=0;

ISR(TIMER1_OVF_vect) {
  if(update<20){
    update_timer(D[update]);
    update_timer_i(D2[update]);
    update=update+1;
  }
  /*else if(update>=10 && update<20){
    update_timer_i(D[update]);
    update_timer(D[0]);
    update=update+1;
  }*/
  else{
    update=0;
  }

  
}



void duty_cycle() {
  //float t=0;
  for (int i = 0; i < 20; i++) {
    if (i <= 10){
      dutyCycles[i] = abs(sin(2 * pi * FUNDAMENTAL_FREQUENCY * (i * (1/SWICTHING_FREQUENCY))));  // b/w 0 & 1 since map cant use for floating point numbers
      dutyCycles2[i] = 0;

    }
    else{
      dutyCycles[i] = 0;
      dutyCycles2[i] = abs(sin(2 * pi * FUNDAMENTAL_FREQUENCY * (i * (1/SWICTHING_FREQUENCY))));  // b/w 0 & 1 since map cant use for floating point numbers
    
    //t=(t+1)*0.001;
    Serial.println(dutyCycles[i]);
    }
  }
}

void D_map() {
  for (int i = 0; i < 20; i++) {
    D[i] = (dutyCycles[i]) * 100.0f;  // b/w 0 & 100
    D2[i] = (dutyCycles2[i]) * 100.0f;  // b/w 0 & 100

  }
}
void update_timer(float d) {
  // TIMER DECLERATION
  //DDRB |= (1 << DDB6);  // SETTING DDRB BIT 7(LAST BIT)  OC1A  AS OUTPUT
  //TCNT0 = 0x00;

  //TCCR1A = 0;
  //TCCR1A |= _BV(WGM11);
  //TCCR1A |= _BV(COM1A1);

  //TCCR1B = 0;
  //TCCR1B |= _BV(WGM12) | _BV(WGM13) | _BV(CS10);  // 1 pre_scaller

  duty = d / 100.0f;
  OCR1A= round(duty * ICR1);

 // duty = D2[update] / 100.0f;
  //OCR1B = round(duty * ICR1);
}
void update_timer_i(float d) {
  // TIMER DECLERATION
  //DDRB |= (1 << DDB5);  // SETTING DDRB BIT 7(LAST BIT)  OC1B  AS OUTPUT
  // TCNT1 = 0x00;

  //TCCR1A = 0;
  //TCCR1A |= _BV(WGM11);
  //TCCR1A |= _BV(COM1B1)|_BV(COM1B0);

  //TCCR1B = 0;
  //TCCR1B |= _BV(WGM12) | _BV(WGM13) | _BV(CS10);  // 1 pre_scaller
  duty = d / 100.0f;
  // ICR1 = 15999;
  OCR1B = round(duty * 15999);
  // Serial.print(duty);
  // Serial.println("is d and");
  // Serial.print(OCR1B);


}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // put your setup code here, to run once:

  duty_cycle();  // to get duty cycles b/w 0 and 1
  D_map();       // to get duty cycles b/w 0 and 100


  // TIMER DECLERATION
  DDRB |= (1 << DDB5);  // SETTING DDRB BIT 7(LAST BIT)  OC1A  AS OUTPUT(for non-inv)
  DDRB |= (1 << DDB6);  // SETTING DDRB BIT 7(LAST BIT)  OC1B  AS OUTPUT(for inv)
  
  TCNT0 = 0x00;

  TCCR1A = 0;
  TCCR1A |= _BV(WGM11);
  TCCR1A |= _BV(COM1A1)|_BV(COM1B1);// B AND A TWO OUTPUTS

  TCCR1B = 0;
  TCCR1B |= _BV(WGM12) | _BV(WGM13) | _BV(CS10);  // 1 pre_scaller

  ICR1 = 15999;
  OCR1A = 8000;//8000
  
  OCR1B= 8000;//
  

   // Enable Timer1 overflow interrupt
  TIMSK1 |= (1 << TOIE1);
// Enable global interrupts
sei();
}

void loop() {
  // put your main code here, to run repeatedly:
   /*
   for (int i = 0; i < 20; i++) {
      update_timer(D[i]);
      update_timer_i(D[i]);
      delay(1); // Delay to achieve desired frequency
  }
  */

}

      
    



