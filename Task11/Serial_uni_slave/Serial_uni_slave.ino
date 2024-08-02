#include <avr/interrupt.h>
#include<SPI.h>
volatile byte receivedData;
#define send 0x22
bool flag;
// Interrupt Service Routine for SPI
ISR(SPI_STC_vect) {
    //PORTB&=(~(1<<PORT2));// SS LOW OF SLAVE ALWAYS
    //while (!(SPSR & (1 << SPIF)));
    // Read the data from the SPI data register
    
    receivedData = SPDR;
    SPDR = send; // Set the data to send
    // Send response data (e.g., echo the received data)
    //while (!(SPSR & (1 << SPIF)));
    Serial.println(receivedData,BIN);
    Serial.print("sent by SLAVE ");
    Serial.println(send,HEX);
    
    
    
    
    
    
    //PORTB&=~(1<<PB2);// SS LOW OF SLAVE ALWAYS

}

void setup() {
    // Initialize serial communication
    Serial.begin(9600);

    // Pin declarations
    DDRB &= (~(1 << PB0)) & (~(1 << PB1))   ; // MOSI, SS, SCK as input
    DDRB |= (1 << PB4) | (1 << PB2); // MISO and SS as output

    SPCR=0;
    // Enable SPI, set as Slave, and enable SPI interrupt
    SPCR = (1 << SPE) | (1 << SPIE) | (1 << DORD)|(1 << SPR0); // MSTR=0 sets device as Slave
    // Optionally, set double SPI speed
    SPSR |= (1<<SPIF);//(1 << SPI2X)|
    SREG|=(1<<7);
    // Ensure global interrupts are enabled
    sei();
}

void loop() {
    // Main loop can be empty as SPI communication is handled by the ISR
   

}