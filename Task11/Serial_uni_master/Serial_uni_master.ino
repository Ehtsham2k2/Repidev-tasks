#include<SPI.h>

#include <avr/interrupt.h>

byte receivedData;

// ISR(SPI_STC_vect) {
//     PORTB&=(~(1<<PORT2));// SS LOW OF SLAVE ALWAYS
//     //PORTB&=(~(1<<PORT0));// SS LOW OF SLAVE ALWAYS
//     //while (!(SPSR & (1 << SPIF)));
//     // Read the data from the SPI data register
//     receivedData = SPDR;
//     //while (!(SPSR & (1 << SPIF)));
//     // Read the data from the SPI data register
//     //receivedData = SPDR;}
//     Serial.print("Received from slave: ");
//     Serial.println(receivedData,HEX);
// }

void SPI_MasterTransmit_Recieve(byte data) {
    // Ensure SS (Slave Select) is low before transmission
    PORTB &= ~(1 << PORTB0); // PB0 is the SS pin
    PORTB |=(1 << PORTB1);
    // Load data into the SPI data register AND WAIT TFOR TRANSMISSION
    
    //PORTB &= ~(1 << PB0); // PB0 is the SS pin
    SPDR = data;
    receivedData=SPDR;
    while (!(SPSR & (1 << SPIF)));
    
    // Debug prints
    Serial.print("sent by master");
    Serial.println(data,BIN);

    // Wait until transmission is complete
    //while (!(SPSR & (1 << SPIF)));

    // Read the received data (this clears the SPIF flag)
    
   
    // Print the received data
    Serial.print("Received from slave: ");
    Serial.println(receivedData,HEX);
    // Optionally, set SS high after transmission
    PORTB |= (1 << PORTB0);
}

void setup() {
    // Initialize serial communication
    Serial.begin(9600);

    // Pin declarations
    DDRB |= (1 << PB2) | (1 << PB0) | (1 << PB1); // MOSI, SS, SCK as output
    DDRB &= ~(1 << PB3); // MISO as input
    SPCR=0;
    // Enable SPI, Set as Master, and set clock rate (fosc/64)*2
    SPCR = (1 << SPE) | (1 << MSTR)|(1 << DORD)|(1 << SPR1);//| (1 << SPR1) | (1 << SPR0) AND READ FRIM MSB;

    // Optionally, set double SPI speed
    SPSR |= (1<<SPIF);//(1 << SPI2X)|
    SREG|=(1<<7);
    // Ensure SS (Slave Select) is high before starting communication
    PORTB |= (1 <<PB0);
}

void loop() {
    // Transmit data
    SPI_MasterTransmit_Recieve(0X06);
    
    //delay(1000);
}
