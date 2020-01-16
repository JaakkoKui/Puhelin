#include <SoftwareSerial.h> //Kirjasto 
#define PIN_RX    7 //Pinnit laitteiden väliseen keskusteluun
#define PIN_TX    8
SoftwareSerial modem(PIN_RX,PIN_TX); //Määritetään pinnit


void clearBuffer(){ //Puskurin tyhjennys funktio
  char c;
  while(c = modem.read() != -1){//Kun modeemin vastaus on muuta kun -1
    Serial.println(c); //Tämän pitäisi tulostaa mitä modeemista löytyy, ei toimi
  }
  Serial.println("Puskuri tyhjä"); //Se tulostaa 'puskuri tyhjä'
}

void setup() { //Asetukset
  modem.begin(9600); //Alustetaan modeemi
  Serial.begin(9600); //Alustetaan sarjaportti
  delay(5000); //Viive
  clearBuffer(); //Suorittaa puskurin tyhjennys funktion
}



bool cmdAT(){ //Funktio joka lähettää AT komennon
  modem.print("AT\r\n"); //Kirjoittaa AT modeemille
  while(modem.available()<1){delay(10);}//Odotetaan vastausta
  char c, i=0;
  c=modem.read();// Määritä c=modeemin luku
  while(c != -1){ //Kun modeemin vastaus on muuta kun -1
    Serial.print(c); //Tulosta sarjaporttiin modeemin vastaus
    c=modem.read(); //Lue modeemi
    delay(20); //Viive
    i++;
    if(i==255){ //Koittaa 255 kertaa
      return true;//TIMEOUT!
    }
  }
  return false;
}
bool listAT () {
  modem.print("AT+CMGL\r\n");
  while(modem.available()<1){delay(10);}//Odotetaan vastausta
  char c, i=0;
  c=modem.read();
  while(c != -1){
    Serial.print(c);
    c=modem.read();
    delay(20);
    i++;
    if(i==255){
      return true;//TIMEOUT!
    }
  }
  return false;
}

bool readAT() {
  modem.print("AT+CMGR=?\r\n");
  while(modem.available()<1){delay(10);}//Odotetaan vastausta
  char c, i=0;
  c=modem.read();
  while(c != -1){
    Serial.print(c);
    c=modem.read();
    delay(20);
    i++;
    if(i==255){
      return true;//TIMEOUT!
    }
  }
  return false;
}
 
void loop(){
  Serial.println(millis());
  if(cmdAT()){
    Serial.println("Timeout");
    while(1);
  }
  Serial.println("Alku");
  Serial.println(millis());
  if(listAT()){
    Serial.println("Timeout 2");
    while(1);
  }
  if(readAT()) {
    Serial.println ("Timeout 3");
    while(1);
    Serial.println(millis());
    
  }
  Serial.println(millis());
  delay(1000);
  Serial.println("Loppu");
  while(1);

  
}
  
