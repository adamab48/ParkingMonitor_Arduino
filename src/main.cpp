#include <Arduino.h>
#include <Servo.h>
#include <ArduinoJson.h>
Servo myservo;
int pos = 0;
void setup() {
   myservo.attach(10); //servo at 0
   myservo.write(90);
   pinMode(A0,INPUT);
   pinMode(A1,INPUT);
   pinMode(A2,INPUT);
  
   Serial.begin(9600);
}

void loop() {
  int cap1_status =0;
  int cap2_status = 0;
  int cap_door = analogRead(A0);
 int cap1 = analogRead(A1);
 int cap2 = analogRead(A2);

  if (cap1 > 900) cap1_status = 0 ; // FREE
  else cap1_status = 1; // Occupied
  if (cap2 > 800) cap2_status = 0;
  else cap2_status = 1;

  if (cap_door>900) {
    myservo.write(90);
    delay(2000);
    

    }
  else {
    delay(1000);
    myservo.write(180);
    
  }
 
 
  
  String message = "";
 bool messageR =false;
  while(Serial.available()) {  
    message = Serial.readString();
    messageR = true;
  }

 if (messageR) {

DynamicJsonDocument doc(1024);
DeserializationError err = deserializeJson(doc,message);
if (err) {
  Serial.print("Failed");
  Serial.println(err.c_str());
  messageR = false;
  return;
}
if (doc["type"] == "request") {
  doc["type"] = "response";
  doc["Cap 1"] = cap1_status ;
  doc["Cap 2"] = cap2_status;
  serializeJson(doc,Serial);
}
messageR = false;
 }  
  delay(200); 

}