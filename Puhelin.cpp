#include <Arduino.h>
#include "Puhelin.h"

SoftwareSerial modem(PIN_RX,PIN_TX); //Määritetään pinnit


void clearBuffer(){ //Puskurin tyhjennys funktio
  char c;
  while(c = modem.read() != -1){//Kun modeemin vastaus on muuta kun -1
    (modem.read() == 0);
    Serial.println("joo");
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

int distanceCm;
void mittaus(){
  unsigned long d=0;
  for(int i=0;i<5;i++){
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(8);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    d += pulseIn(echoPin, HIGH);
}

  distanceCm = (d/5)*0.034/2;
  Serial.println(distanceCm);
  delay(1000);
}
  void Metallica(){
      tone(kaiutin, 329, 300);//E
       delay(300);
      tone(kaiutin, 493, 300); //B
       delay(300);
      tone(kaiutin, 698, 300); //F^
       delay(300);
      tone(kaiutin, 659, 300); //E^
       delay(400);
       
      tone(kaiutin, 329, 150); //G^
       delay(150);
      tone(kaiutin, 493, 150); //F^
       delay(300);
      tone(kaiutin, 783, 300); //E^
       delay(300);
      tone(kaiutin, 698, 300); 
       delay(400);
       
      tone(kaiutin, 329, 300); 
       delay(300);
      tone(kaiutin, 493, 300);
       delay(300); 
      tone(kaiutin, 698, 300);
       delay(300);
      tone(kaiutin, 590, 300); 
       delay(400);
       
      tone(kaiutin, 392, 150); 
       delay(150);
      tone(kaiutin, 440, 150); 
       delay(150);
      tone(kaiutin, 587, 300);
       delay(400);
       
      tone(kaiutin, 349, 300); 
       delay(300);
      tone(kaiutin, 587, 300); 
       delay(600);

      tone(kaiutin, 329, 300);
       delay(300);
      tone(kaiutin, 493, 300);
       delay(300);
      tone(kaiutin, 698, 300);
       delay(300);
      tone(kaiutin, 659, 300);
       delay(400);
       
      tone(kaiutin, 329, 150);
       delay(150);
      tone(kaiutin, 493, 150);
       delay(300);
      tone(kaiutin, 783, 300); 
       delay(300);
      tone(kaiutin, 698, 300); 
       delay(400);
       
      tone(kaiutin, 329, 300); 
       delay(300);
      tone(kaiutin, 493, 300);
       delay(300); 
      tone(kaiutin, 698, 300);
       delay(300);
      tone(kaiutin, 590, 300); 
       delay(400);
       
      tone(kaiutin, 392, 150); 
       delay(150);
      tone(kaiutin, 440, 150); 
       delay(150);
      tone(kaiutin, 587, 300);
       delay(400);
       
      tone(kaiutin, 349, 300); 
       delay(300);
      tone(kaiutin, 587, 300); 
       delay(600);
      
      
  }
  void CharlieBrown(){
      tone(kaiutin, 196,200);
          delay(200);
      tone(kaiutin, 293,200);
          delay(200);
      tone(kaiutin, 392,300);
          delay(300);
      tone(kaiutin, 196,200);
          delay(200);
      tone(kaiutin, 293,200);
          delay(200);
      tone(kaiutin, 392,600);
          delay(600);
      tone(kaiutin, 100,200);
          delay(200);
      tone(kaiutin, 196,200);
          delay(200);
      tone(kaiutin, 293,200);
          delay(200);
      tone(kaiutin, 392,500);
         delay(500);
      tone(kaiutin, 100,100);
          delay(100);
      tone(kaiutin, 196,200);
          delay(200);
      tone(kaiutin, 293,200);
          delay(200);
      tone(kaiutin, 329,500);
          delay(500);
      tone(kaiutin, 196,200);
          delay(200);
      tone(kaiutin, 293,200);
          delay(200);
      tone(kaiutin, 392,300);
          delay(300);
      tone(kaiutin, 196,200);
          delay(200);
      tone(kaiutin, 293,200);
          delay(200);
      tone(kaiutin, 392,600);
          delay(600);
      tone(kaiutin, 100,200);
          delay(200);
      tone(kaiutin, 196,200);
          delay(200);
      tone(kaiutin, 293,200);
          delay(200);
      tone(kaiutin, 329,300);
          delay(300);
      tone(kaiutin, 100,100);
          delay(100);
      tone(kaiutin, 196,200);
          delay(200);
      tone(kaiutin, 293,300);
          delay(300);
      tone(kaiutin, 329,800);
          delay(1300);
          
      tone(kaiutin, 196,200);
          delay(200);
      tone(kaiutin, 293,200);
          delay(200);
      tone(kaiutin, 392,300);
          delay(300);
      tone(kaiutin, 196,200);
          delay(200);
      tone(kaiutin, 293,200);
          delay(200);
      tone(kaiutin, 392,600);
          delay(600);
      tone(kaiutin, 100,200);
          delay(200);
      tone(kaiutin, 196,200);
          delay(200);
      tone(kaiutin, 293,200);
          delay(200);
      tone(kaiutin, 329,300);
          delay(300);
      tone(kaiutin, 100,100);
          delay(100);
      tone(kaiutin, 196,200);
          delay(200);
      tone(kaiutin, 293,300);
          delay(300);
      tone(kaiutin, 329,800);
          delay(1300);
          
      tone(kaiutin, 196,200);
          delay(200);
      tone(kaiutin, 293,200);
          delay(200);
      tone(kaiutin, 392,300);
          delay(300);
      tone(kaiutin, 196,200);
          delay(200);
      tone(kaiutin, 293,200);
          delay(200);
      tone(kaiutin, 392,600);
          delay(600);
      tone(kaiutin, 100,200);
          delay(200);
      tone(kaiutin, 196,200);
          delay(200);
      tone(kaiutin, 293,200);
          delay(200);
      tone(kaiutin, 329,300);
          delay(300);
      tone(kaiutin, 100,100);
          delay(100);
      tone(kaiutin, 196,200);
          delay(200);
      tone(kaiutin, 293,300);
          delay(300);
      tone(kaiutin, 329,800);
          delay(800);
      tone(kaiutin, 50,30);
          delay(30);
      tone(kaiutin, 196,400); 
          delay(400);
      tone(kaiutin, 220,200);
          delay(200);
      tone(kaiutin, 246,400); 
          delay(400);
      tone(kaiutin, 50,30); 
          delay(30);
      tone(kaiutin, 246,300); 
          delay(300);
      tone(kaiutin, 50,30);
          delay(30);
      tone(kaiutin, 220,200); 
          delay(200);
      tone(kaiutin, 196,200); 
          delay(200);
      tone(kaiutin, 220,700); 
          delay(700);
      tone(kaiutin, 196,800); 
          delay(800);
      tone(kaiutin, 50,30);
          delay(30);
      tone(kaiutin, 196,200);
          delay(200);
      tone(kaiutin, 220,400);
          delay(400);
      tone(kaiutin, 246,400);
          delay(400);
      tone(kaiutin, 50,30);
          delay(30);
      tone(kaiutin, 246,1000);
          delay(1500);
          
      tone(kaiutin, 50,30);
          delay(30);
      tone(kaiutin, 196,400); 
          delay(400);
      tone(kaiutin, 220,200);
          delay(200);
      tone(kaiutin, 246,400);
          delay(400);
      tone(kaiutin, 50,30);
          delay(30);
      tone(kaiutin, 246,300);
          delay(300);
      tone(kaiutin, 50,30);
          delay(30);
      tone(kaiutin, 220,200); 
          delay(200);
      tone(kaiutin, 196,200); 
          delay(200);
      tone(kaiutin, 220,700); 
          delay(700);
      tone(kaiutin, 196,800); 
          delay(800);
      tone(kaiutin, 50,30);
          delay(30);
      tone(kaiutin, 196,200);
          delay(700);
          
      tone(kaiutin, 50,30);
          delay(30);
      tone(kaiutin, 196,500); 
          delay(500);
      tone(kaiutin, 220,400); 
          delay(400);
      tone(kaiutin, 50,30);
          delay(30);
      tone(kaiutin, 220,1000); 
          delay(1000);
      tone(kaiutin, 50,30);
          delay(530);
          
      tone(kaiutin, 50,30);
          delay(30);
      tone(kaiutin, 196,400); 
          delay(400);
      tone(kaiutin, 220,200); 
          delay(200);
      tone(kaiutin, 246,400);
          delay(400);
      tone(kaiutin, 50,30);
          delay(30);
      tone(kaiutin, 246,300); 
          delay(300);
      tone(kaiutin, 50,30);
          delay(30);
      tone(kaiutin, 220,200); 
          delay(200);
      tone(kaiutin, 196,200); 
          delay(200);
      tone(kaiutin, 220,700);
          delay(700);
      tone(kaiutin, 196,800);
          delay(800);
      tone(kaiutin, 50,30);
          delay(30);
      tone(kaiutin, 196,200); 
          delay(200);          
      tone(kaiutin, 220,400); 
          delay(400);
      tone(kaiutin, 246,400); 
          delay(400);
      tone(kaiutin, 50,30);
          delay(30);
      tone(kaiutin, 246,1000);
          delay(1500);
          
      tone(kaiutin, 50,30); 
          delay(30);
      tone(kaiutin, 196,400);
          delay(400);
      tone(kaiutin, 220,200);
          delay(200);
      tone(kaiutin, 246,400);
          delay(400);
      tone(kaiutin, 50,30);
          delay(30);
      tone(kaiutin, 246,300);
          delay(300);
      tone(kaiutin, 50,30);
          delay(30);         
      tone(kaiutin, 220,200); 
          delay(200);
      tone(kaiutin, 196,200); 
          delay(200);
      tone(kaiutin, 220,700); 
          delay(700);
      tone(kaiutin, 196,800); 
          delay(800);
      tone(kaiutin, 50,30); 
          delay(30);
      tone(kaiutin, 196,200);
          delay(700);
          
      tone(kaiutin, 50,30);
          delay(30);
      tone(kaiutin, 196,500);
          delay(250);
      tone(kaiutin, 220,400);
          delay(400);
      tone(kaiutin, 50,30);
          delay(30);
      tone(kaiutin, 220,1000);
          delay(1000);
      tone(kaiutin, 50,30);
          delay(530);
          
      tone(kaiutin, 50,30); 
          delay(30);
      tone(kaiutin, 196,600);
          delay(600);
      tone(kaiutin, 220,300);
          delay(300);
      tone(kaiutin, 50,30);
          delay(30);
      tone(kaiutin, 220,300);
          delay(300);
      tone(kaiutin, 220,800);
          delay(1300);
          
      tone(kaiutin, 50,30);
          delay(30);
      tone(kaiutin, 196,2000); 
          delay(2500);
          
      tone(kaiutin, 50,30);
          delay(30);
      tone(kaiutin, 190,10);
          delay(10);
      tone(kaiutin, 196,1500);
          delay(2000);
          
      tone(kaiutin, 258,200);
          delay(200);
      tone(kaiutin, 50,30);
          delay(30);
      tone(kaiutin, 261,400);
          delay(400);
      tone(kaiutin, 50,30);
          delay(30);
      tone(kaiutin, 261,400);
          delay(400);          
      tone(kaiutin, 50,30);
          delay(30);
      tone(kaiutin, 261,400);
          delay(900);
          
      tone(kaiutin, 50,30); 
          delay(30);
      tone(kaiutin, 293,700); 
          delay(1200);
          
      tone(kaiutin, 329,500); 
          delay(500);
      tone(kaiutin, 293,200);
          delay(200);
      tone(kaiutin, 329,500);
          delay(1000);
          
      tone(kaiutin, 258,200); 
          delay(200);
      tone(kaiutin, 50,30); 
          delay(30);
      tone(kaiutin, 261,400);
          delay(400);
      tone(kaiutin, 50,30); 
          delay(30);
      tone(kaiutin, 261,400);
          delay(400);
      tone(kaiutin, 50,30); 
          delay(30);
      tone(kaiutin, 261,400);
          delay(900);
          
      tone(kaiutin, 50,30); 
          delay(30);
      tone(kaiutin, 293,700); 
          delay(1200);
          
      tone(kaiutin, 329,500); 
          delay(500);
      tone(kaiutin, 293,200);
          delay(200);
      tone(kaiutin, 329,500);
          delay(1000);
          
      tone(kaiutin, 50,30); 
          delay(30);
      tone(kaiutin, 196,600); 
          delay(600);
      tone(kaiutin, 220,300); 
          delay(300);
      tone(kaiutin, 50,30); 
          delay(30);
      tone(kaiutin, 220,300); 
          delay(300);
      tone(kaiutin, 220,800); 
          delay(1300);
          
      tone(kaiutin, 50,30); 
          delay(30);
      tone(kaiutin, 196,2000); 
          delay(2500);
          
      tone(kaiutin, 50,30); 
          delay(30);
      tone(kaiutin, 190,10); 
          delay(10);
      tone(kaiutin, 196,1500); 
          delay(1500);
      return 0;
    }
void checkMessages(){
  Serial.read();
  
  if (modem.available() > 0) {
    String textMessage = modem.readString();
    Serial.println("Incoming:");
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
      delay(1000);
      tone(kaiutin, 300, 1000);
      delay (3000);
      //textMessage = "";
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
    }
    if (textMessage.indexOf("NO CARRIER") >= 0) {
         String message = "Puhelu katkaistu";
      sendSMS(message);
      }
    
    if (textMessage.indexOf("Matka") >=0) {
      String message;
      char a[4];
      Serial.println("Matka: Mitataan");
      mittaus();
      Serial.println("Matka: Mitattu");
      itoa(distanceCm, a, 10);
      message.concat(a);
      message.concat("\r\n");
      sendSMS(message); 
      if (distanceCm < 10){
        CharlieBrown();
      }
     else if (distanceCm <50){
      Metallica();
     }
    }
    if  (textMessage.indexOf("Mix") >= 0) {
      Serial.println ("Toimii");
      tone(kaiutin, 1600, 1500);
      delay(1500);
      tone(kaiutin, 1900, 1500);
      delay(1500);
      tone(kaiutin, 2100, 1500);
      delay(1500);
      Serial.println ("Toimii2");
      textMessage = "";
      String message = "Arsyttaako?";
      sendSMS(message);
    }
    if  (textMessage.indexOf("Musiikki") >= 0) {
      Metallica();   
    }
    if  (textMessage.indexOf("Music") >= 0) {
      CharlieBrown();
    } 
    

 }
}
