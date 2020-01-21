#include <SoftwareSerial.h> //Kirjasto 
#define PIN_RX    7 //Pinnit laitteiden väliseen keskusteluun
#define PIN_TX    8
#define kaiutin 13
#define Button 2
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
  pinMode (kaiutin, OUTPUT);
  pinMode (Button, INPUT_PULLUP);
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

void initModem(){

  if(cmdToModem("AT\n")){
    Serial.println("Timeout");
    while(1);
  }
  if(cmdToModem("AT+CMGF=1\r\n")){
    Serial.println("Timeout");
    while(1);
  }
  if(cmdToModem("AT+CPMS=\"MT\",\"MT\",\"MT\"\r\n")){
    Serial.println("Timeout");
    while(1);
  }
  if(cmdToModem("AT+CMGL=\"REC READ\",0\r\n")){
    Serial.println("Timeout");
    while(1);
  }
  if(cmdToModem("AT+CMGR=3,0\r\n")){
    Serial.println("Timeout");
    while(1);
  }
  if(cmdToModem("AT+CNMI=2,2,0,0,0\r\n")){
    Serial.println("Timeout");
    while(1);
  }
   if(cmdToModem("AT+CMEE=1\r\n")){
    Serial.println("Timeout");
    while(1);
   }
   if (cmdToModem("ATA\r\n")) {
    Serial.println ("Timeout");
    while(1);
   }


bool cmdToModem(String str) { //Komentojen pohja
  Serial.print("Kom: "); //Kirjoittaa sarjaporttiin "Kom:"
  Serial.println(str); //Kirjoittaa sarjaporttiin komennon nimen
  modem.print(str); //Kirjoittaa moodemille komennon
  while(modem.available()<1){delay(2);}//Odotetaan vastausta
  String msg;
  msg=modem.readString();
  Serial.println(msg);
    
  return false;
}


void loop(){
  initModem(); //Modeemin alustus
  
  

 
      
  while(1){
    
    if (modem.available() > 0) {
      String textMessage = modem.readString();
      Serial.print(textMessage);
      delay(10);
     
      if (textMessage.indexOf("Korkea") >= 0) {
        tone(kaiutin, 2000, 1000);
        textMessage = "";
        String message = "Arsyttaako?";
        sendSMS(message);
      }
      if (textMessage.indexOf("Delete") >= 0) {
        cmdToModem("AT+CMGD=2,4\r\n");
        textMessage = "";
        String message = "Tyhjennetty";
        sendSMS(message);
      }
       if (textMessage.indexOf("Matala") >= 0) {
        tone(kaiutin, 100, 1000);
        textMessage = "";
        String message = "Arsyttaako?";
        sendSMS(message);
       }
       int x = digitalRead(Button);
       if (x == LOW) {
        Serial.println("kakka");
        
      }
      if (textMessage.indexOf(".") >= 0) {
        String message = "Hävisit pelin";
        sendSMS(message);
        
      }
    }
  }
}
  
