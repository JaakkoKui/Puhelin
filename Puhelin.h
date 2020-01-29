#ifndef Puhelin_h
#define Puhelin_h
#include <Arduino.h>
#include <SoftwareSerial.h> //Kirjasto 
#define PIN_RX    7 //Pinnit laitteiden väliseen keskusteluun
#define PIN_TX    8
#define kaiutin 11
#define Button 2

const int trigPin = 5;
const int echoPin = 4;

void pinmode();
void clearBuffer();
void initModem();
void sendSMS(String);
void mittaus();
void checkMessages();
bool cmdToModem(String str, String ans);

#endif
