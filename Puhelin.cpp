#include <Arduino.h>
#include "Puhelin.h"

SoftwareSerial modem(PIN_RX,PIN_TX); //Määritetään pinnit
unsigned long data[100]; 

void clearBuffer(){ //Puskurin tyhjennys funktio
  char c;
  while(c = modem.read() != -1){//Kun modeemin vastaus on muuta kun -1
    Serial.println(c); //Tämän pitäisi tulostaa mitä modeemista löytyy, ei toimi
  }
  Serial.println("Puskuri tyhjä"); //Se tulostaa 'puskuri tyhjä'
}


bool cmdToModem(String str, String ans) { //Komentojen pohja
  Serial.print("Kom: "); //Kirjoittaa sarjaporttiin "Kom:"
  Serial.println(str); //Kirjoittaa sarjaporttiin komennon nimen
  modem.print(str); //Kirjoittaa moodemille komennon
  while(modem.available()<1){delay(2);}//Odotetaan vastausta
  String msg;
  msg=modem.readString();
  Serial.println(msg);
  if(msg.indexOf(ans)>=0){
    return false;//Odotettu vastaus
  }
  return true;
}


void initModem(){
  modem.begin(9600); //Alustetaan modeemi
  if(cmdToModem("AT\r\n", "OK")){
    Serial.println("ERROR: AT");
    while(1);
  }
  if(cmdToModem("AT+CMGF=1\r\n", "OK")){
    Serial.println("ERROR: CMGF");
    while(1);
  }
  if(cmdToModem("AT+CPMS=\"MT\",\"MT\",\"MT\"\r\n", "OK")){
    Serial.println("ERROR: CPMS");
    while(1);
  }
  if(cmdToModem("AT+CMGL=\"REC READ\",0\r\n", "OK")){
    Serial.println("ERROR: CMGL");
    while(1);
  }
  if(cmdToModem("AT+CMGR=3,0\r\n", "OK")){
    Serial.println("ERROR: CMGR");
    while(1);
  }
  if(cmdToModem("AT+CNMI=2,2,0,0,0\r\n", "OK")){
    Serial.println("ERROR: CNMI");
    while(1);
  }
   if(cmdToModem("AT+CMEE=1\r\n", "OK")){
    Serial.println("ERROR: CMEE");
    while(1);
   }
  if(cmdToModem("AT+CLIP=1\r\n", "OK")){
    Serial.println("ERROR: CLIP");
    while(1);
 }
}

void sendSMS(String message) { //Viestin lähetys funktio
  modem.println("AT+CMGS=\"+358451839030\""); //Lähettää viestin numeroon"-"
  delay(100);
  // Send the SMS
  modem.print(message);
  delay(100);
  Serial.println(message);
  // End AT command with a ^Z, ASCII code 26
  modem.println((char)26);
  delay(50);
  modem.println();
  delay(5000); // Annetaan modeemille aikaa lähettää viesti
}

void pinmode() {
   pinMode (kaiutin, OUTPUT);
  pinMode (Button, INPUT_PULLUP);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void mittaus(){
  unsigned long d=0;
  for(int i=0;i<10;i++){
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(8);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    d += pulseIn(echoPin, HIGH);
  }

  int distanceCm;
  distanceCm = (d/10)*0.034/2;
  Serial.println(distanceCm);
  delay (300);
}


int distanceCm;
void checkMessages(){
  Serial.read();

  if (modem.available() > 0) {
    String textMessage = modem.readString();
    Serial.print(textMessage);
    delay(10);
    
    if (textMessage.indexOf("Korkea") >= 0) {
      tone(kaiutin, 2000, 1000);
      //textMessage = "";
      String message = "Arsyttaako?";
      sendSMS(message);
    }
    if (textMessage.indexOf("Delete") >= 0) {
      cmdToModem("AT+CMGD=2,4\r\n", "OK");
      textMessage = "";
      String message = "Tyhjennetty";
      sendSMS(message);
    }
    if  (textMessage.indexOf("Matala") >= 0) {
      tone(kaiutin, 100, 1000);
      // textMessage = "";
      String message = "Arsyttaako?";
      sendSMS(message);
    }
    if (textMessage.indexOf(".") >= 0) {
      String message = "Hävisit pelin";
      sendSMS(message);
    }
    if (textMessage.indexOf("RING") >= 0) {
      if (cmdToModem("ATA\r\n", "OK")) {
        Serial.println ("Timeout");
    }
    
    if (textMessage.indexOf("?") >=0) {
       String message;
       char a[4];
       itoa(distanceCm, a, 10);
       message.concat(a);
      sendSMS(message); 
   }
  }
 }
}
