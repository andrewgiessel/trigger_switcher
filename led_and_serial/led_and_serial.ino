


int ledPin = 6;
int delayAmount = 1000;

void setup(){
// Do stuff once
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600); // USB is always 12 Mbit/sec

}

void loop(){
// Do stuff repeatedly
   if(Serial.available()>0) // if there is data to read
   {
    delayAmount = Serial.parseInt(); // read data
    Serial.flush();
   }
   digitalWrite(ledPin, HIGH);
   Serial.println("high");
   delay(delayAmount);
   digitalWrite(ledPin, LOW);
   Serial.println("low");
   delay(delayAmount);
}
