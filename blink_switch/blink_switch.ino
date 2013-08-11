const int triggerPin = 4;
const int ledPin = 6;

int triggerVal = 0;
int inputVal = 0;
int blinkVal = 5;

void setup() {
   pinMode(triggerPin, INPUT);
   pinMode(ledPin, OUTPUT);
   Serial.begin(9600);

}

void loop(){
  if (Serial.available()>0) {
    inputVal = Serial.read();
    Serial.println(char(inputVal));
    
    switch (inputVal) {
      case '0':
        blinkVal = 0;
      case '1':
        blinkVal = 1;
      case '2':
        blinkVal = 2;
      case '3':
        blinkVal = 3;
      case '4':
        blinkVal = 4;
      case '5':
        blinkVal = 5;
      case '6':
        blinkVal = 6;
      case '7':
        blinkVal = 7;
      case '8':
        blinkVal = 8;
      case '9':
        blinkVal = 9;
      case 'a':
        blinkVal = 10;
      case 'b':
        blinkVal = 11;
      case 'c':
        blinkVal = 12;
      case 'd':
        blinkVal = 13;
      case 'e':
        blinkVal = 14;
      case 'f':
        blinkVal = 15; 
    }
    //parseInt();
    Serial.flush();
  }
  
  triggerVal = digitalRead(triggerPin);
  if (triggerVal == HIGH) {
    doBlink(blinkVal, 250);
  triggerVal = LOW;
  }
}

void doBlink(int numTimes, int pause) {
  for (int i = 1; i <= numTimes; i++) { 
    digitalWrite(ledPin, HIGH);
    delay(pause);
    digitalWrite(ledPin, LOW);
    delay(pause); 
  }
}

