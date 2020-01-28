#include "Puhelin.h"



void setup() { //Asetukset
  pinmode();
  Serial.begin(9600); //Alustetaan sarjaportti
  delay(500); //Viive
  clearBuffer(); //Suorittaa puskurin tyhjennys funktion
 


 }


void loop(){
  initModem();//Modeemin alustus
  Serial.println("Init modem OK");
  while(1){
    int x = digitalRead(Button);
    if (x == LOW) {
      Serial.println("ABC");
      String message = "Moi";
      sendSMS(message);
      delay(1500);      
    }
    mittaus();
    checkMessages();
  }
}
