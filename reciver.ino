#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 8);  // CE, CSN

//addresses through which two modules communicate.
const byte addresses[][6] = {"00001", "00002"};

//LED pins
const int led1Pin = 2;
const int led2Pin = 3;

void setup()
{
  //initialize LED pins
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);

  radio.begin();
  
  //set the addresses
  radio.openReadingPipe(0, addresses[0]);
  radio.openReadingPipe(1, addresses[1]);
  
  //Set module as receiver
  radio.startListening();
}

void loop()
{
  if (radio.available()) 
  {
    char text[32];
    radio.read(&text, sizeof(text));
    
    // check which transmitter the message is coming from
    if (strcmp(text, "Hello from Transmitter 1") == 0)
    {
      digitalWrite(led1Pin, HIGH);
      digitalWrite(led2Pin, LOW);
    }
    else if (strcmp(text, "Hello from Transmitter 2") == 0)
    {
      digitalWrite(led1Pin, LOW);
      digitalWrite(led2Pin, HIGH);
    }
  }
}
