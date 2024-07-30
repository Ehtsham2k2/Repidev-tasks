// pin decleration
int ledpin = 12;
volatile int button = 20;
volatile bool ledState = HIGH;  // Variable to hold the state of the LED

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  //initialize serial communication
  pinMode(ledpin, OUTPUT);
  pinMode(button, INPUT);
  // Attach the user-defined ISR to the button pin interrupt
  attachInterrupt(digitalPinToInterrupt(button), off_led, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledpin, ledState);
}
void off_led() {
  ledState = !ledState;
}
