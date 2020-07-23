/*  RF24 MODULESRF COMMUNICATION WITH ARDUINO
 *  IF THIS CODE DOESN'T RUN,FIRST CHECK CABLE AND PINS
 *  SECOND MAKE SURE THE TRANSMITTER IS RUNNING 
 *  I ADVISE LED CONNECTION TO THE CIRCUIT    *SEVERUS*
 */
#include <nRF24L01p.h>          //TRANSMITTER
#include <printf.h>
#include <RF24.h>
#include <SPI.h>

#define CE_PIN 7
#define CSN_PIN 8

const byte Address[5] = {'R','x','A','A','A'};        //CHANNEL ,IT HAS TO BE THE SAME WITH THE RECEIVER CHANEL
RF24 radio(CE_PIN, CSN_PIN);                          //CREATE RADIO  

char dataToSend[20] = "FIRSTCODE";
char txNum = '0';

unsigned long currentMillis;
unsigned long prevMillis;
unsigned long txIntervalMillis = 1000;                // SEND MESSAGE PER A SECOND

void setup() {
                                                      //START TRANSMITTER AND DECLARE PIPE
Serial.begin(9600);
Serial.println("SimpleTx Starting");
radio.begin();
radio.setDataRate( RF24_250KBPS );
radio.setRetries(3,5);                                // DELAY, COUNT
radio.openWritingPipe(Address);
}

//====================

void loop() {
currentMillis = millis();
  if (currentMillis - prevMillis >= txIntervalMillis) {
    send();
    prevMillis = millis();
  }
}

//====================

void send() {

bool rslt;
rslt = radio.write( &dataToSend,sizeof(dataToSend));   
Serial.print(dataToSend);
  if (rslt) {
    Serial.println(" Data Send");
   }
  else {
  Serial.println(" Data Couldn't be Send");
  }
}
