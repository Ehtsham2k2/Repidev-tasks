/* Task3_part
part1__To control output of portB Bit 7 using register level programming
and then toggle even and odd*/
volatile bool ledState = HIGH;  // Variable to hold the state of the LED

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  // pin 13 as output
  DDRB |= (1 << DDB7);  // SETTING DDRB BIT 7(LAST BIT)  AS OUTPUT
  DDRB |= (1 << DDB5);  // SETTING DDRB BIT 5  AS OUTPUT
  DDRB |= (1 << DDB3);  // SETTING DDRB BIT 3  AS OUTPUT
  DDRB |= (1 << DDB1);  // SETTING DDRB BIT 1  AS OUTPUT
  DDRB |= (1 << DDB0);  // SETTING DDRB BIT 0  AS OUTPUT
  DDRB |= (1 << DDB2);  // SETTING DDRB BIT 2  AS OUTPUT
  DDRB |= (1 << DDB4);  // SETTING DDRB BIT 4  AS OUTPUT
  DDRB |= (1 << DDB6);  // SETTING DDRB BIT 6  AS OUTPUT
  // Initially set all pins to LOW
  PORTB &= ~(1 << PORTB7) & ~(1 << PORTB5) & ~(1 << PORTB3) & ~(1 << PORTB1) & ~(1 << PORTB0) & ~(1 << PORTB2) & ~(1 << PORTB4) & ~(1 << PORTB6);
}

void loop() {
  // put your main code here, to run repeatedly:
  PORTB |= (1 << PORTB7) | (1 << PORTB5) | (1 << PORTB3) | (1 << PORTB1) | (1 << PORTB0);  // SETTING  OUTPUT odd high
 // digitalWrite(13,HIGH);
  PORTB &= ~(1 << PORTB2) &(~(1 <<PORTB4)) &(~(1 << PORTB6));                       // SETTING  OUTPUT even low
  delay(1000);
  
  PORTB &= ~(1 << PORTB7) & (~(1 << PORTB5)) & (~(1 << PORTB3)) & (~(1 << PORTB2)) & (~(1 << PORTB1)) & (~(1 << PORTB0));  // SETTING  OUTPUT odd low
  PORTB |= (1 << PORTB2) | (1 << PORTB4) | (1 << PORTB6); 
 // digitalWrite(13,LOW);                                                           // SETTING  OUTPUT even high
  delay(1000);
}