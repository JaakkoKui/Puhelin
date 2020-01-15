

#include <SoftwareSerial.h>
#define PIN_TX    8
#define PIN_RX    7
SoftwareSerial mySerial(PIN_RX,PIN_TX);



void setup() {
  // put your setup code here, to run once:
  mySerial.begin(9600);
  Serial.begin(9600);
  pinMode (3, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  mySerial.print("AT\r\n");
  for(int i=0;i<100;i++){
    if(mySerial.available()){
      Serial.write(mySerial.read());
       
  
    }
  }
  delay(1000);
  Serial.println("Uudestaan");
  digitalWrite (3, HIGH);
     }
