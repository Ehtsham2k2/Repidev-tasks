/* varying pwm on 50 hz to have pre-sine wave*/
// WITH single TIMERS 1
#include <math.h>
#include <avr/interrupt.h>

#define FUNDAMENTAL_FREQUENCY 50.0
#define SAMPLES               20.0
#define SWICTHING_FREQUENCY   (FUNDAMENTAL_FREQUENCY * SAMPLES)
#define ICR                  8000
#define pi                   3.141592
#define k                    (1.0/6.0)
uint16_t f = 50.0;
uint16_t a1, num, den, top;
float  duty;

//const float pi = 3.141592;
float dutyCycles[20];
float dutyCycles2[20];

//FOR ISR VOLATILE MUST BE USED
volatile float D[20];
volatile float D2[20];

volatile int update=0;// must use volatile variable for isr so that compiler shouldn't try to optimize that



ISR(TIMER1_OVF_vect) {
  if(update<SAMPLES){
    update_timer(D[update]);
    update_timer_i(D2[update]);
    update=update+1;
  }
  else{
    update=0;
  }

}



void duty_cycle() {
  //float t=0;
  for (int i = 0; i < SAMPLES; i++) {
    if (i < 10){
      dutyCycles[i] = abs((sin(2 * pi * FUNDAMENTAL_FREQUENCY * (i * (1/SWICTHING_FREQUENCY))))+(k*sin((2 * pi * 3 * FUNDAMENTAL_FREQUENCY * (i * (1/SWICTHING_FREQUENCY))))));  // b/w 0 & 1 since map cant use for floating point numbers    + Third Harmonic Injection 
      dutyCycles2[i] = 0;
      Serial.println("+ve");
      Serial.println(dutyCycles[i]);
    }
    else{
      dutyCycles[i] = 0;
      dutyCycles2[i] = abs((sin(2 * pi * FUNDAMENTAL_FREQUENCY * (i * (1/SWICTHING_FREQUENCY))))+(k*sin((2 * pi * 3 * FUNDAMENTAL_FREQUENCY * (i * (1/SWICTHING_FREQUENCY))))));  // b/w 0 & 1 since map cant use for floating point numbers  + Third Harmonic Injection
    
    //t=(t+1)*0.001;
    Serial.println("-ve");
    Serial.println(dutyCycles2[i]);
    }
  }
}

void D_map() {
  for (int i = 0; i < SAMPLES; i++) {
    D[i] = (dutyCycles[i]) * 100.0f;  // b/w 0 & 100
    D2[i] = (dutyCycles2[i]) * 100.0f;  // b/w 0 & 100

  }
}
void update_timer(float d) {


  duty = d / 100.0f;
  OCR1A= round(duty * ICR);

 // duty = D2[update] / 100.0f;
  //OCR1B = round(duty * ICR1);
}
void update_timer_i(float d) {
  
  duty = d / 100.0f;
  // ICR1 = 15999;
  OCR1B = round(duty * ICR);


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
  TCCR1A |= _BV(COM1A1)|_BV(COM1B1);// B AND A TWO non-inv OUTPUTS

  TCCR1B = 0;
  TCCR1B |=  _BV(WGM13) | _BV(CS10);  // 1 pre_scaller

  ICR1 = ICR;
  OCR1A = (ICR/2);//8000
  
  OCR1B= (ICR/2);//
  

   // Enable Timer1 overflow interrupt
  TIMSK1 |= (1 << TOIE1);
// Enable global interrupts
sei();
}

void loop() {
  

}