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
  delay(500); //Viive
  clearBuffer(); //Suorittaa puskurin tyhjennys funktion
}

bool cmdToModem(char* str) {
  Serial.print("Kom: ");
  Serial.println(str);
  modem.print(str);
  while(modem.available()<1){delay(2);}//Odotetaan vastausta
  String ans;
  char c;
  int i=0;
  c=modem.read();
  while(c != -1){
    i++;
    ans.concat(c);//Miksi?
    c=modem.read();
    delay(3);
    if(i == 500){
      return true;//Joku vika
    }
  }
  Serial.println(ans);
  Serial.println(i);
    
  return false;
}

 
void loop(){
/*  
  if(cmdToModem("AT+CMGD=2,4\r\n")){
    Serial.println("Timeout");
    while(1);
  }
  clearBuffer();
  delay(500);  
*/
  if(cmdToModem("AT\n")){
    Serial.println("Timeout");
    delay(1000);
    while(1);
  }
  clearBuffer();
  delay(500);
  if(cmdToModem("AT+CMGF=1\r\n")){
    Serial.println("Timeout");
    while(1);
  }
  clearBuffer();
  delay(500);
  if(cmdToModem("AT+CPMS=\"MT\",\"MT\",\"MT\"\r\n")){
    Serial.println("Timeout");
    while(1);
  }
  clearBuffer();
  delay(500);
  if(cmdToModem("AT+CMGL=\"REC READ\",0\r\n")){
    Serial.println("Timeout");
    while(1);
  }
  clearBuffer();
  delay(500);
  if(cmdToModem("AT+CMGR=3,0\r\n")){
    Serial.println("Timeout");
    while(1);
  }
  clearBuffer();
  delay(1000);
  Serial.println("Loppu");
  while(1);

  
}
  
