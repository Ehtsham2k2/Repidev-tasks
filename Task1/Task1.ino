// pin decleration
const int ledpin =13;
const int j=0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600); //initialize serial communication
pinMode(ledpin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

digitalWrite(ledpin,HIGH);
delay(100);
digitalWrite(ledpin,LOW);
delay(500);
}
