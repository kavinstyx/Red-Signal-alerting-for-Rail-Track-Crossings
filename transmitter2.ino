#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 8);  // CE, CSN

//address through which the module communicates.
const byte address[6] = "00002";

// message to be sent by the transmitter
const char text[] = "Hello from Transmitter 2";

void setup()
{
  radio.begin();
  
  //set the address
  radio.openWritingPipe(address);
  
  //Set module as transmitter
  radio.stopListening();
}

void loop()
{
  //Send message to receiver
  radio.write(&text, sizeof(text));
  
  // wait for a little bit before sending another message
  delay(1000);
}
