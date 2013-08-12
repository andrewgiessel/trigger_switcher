const int triggerPin = 4;
const int ledPin = 6;

int triggerVal = 0;
char inputVal = '0';
int blinkVal = 5;

void setup() {
   pinMode(triggerPin, INPUT);
   pinMode(ledPin, OUTPUT);
   Serial.begin(9600);
 }

void loop(){
  if (Serial.available()>0) {
    inputVal = Serial.read();
    
    switch (inputVal) {
      case '0':
        blinkVal = 0;
        break;
      case '1':
        blinkVal = 1;
        break;
      case '2':
        blinkVal = 2;
        break;
      case '3':
        blinkVal = 3;
        break;
      case '4':
        blinkVal = 4;
        break;
      case '5':
        blinkVal = 5;
        break;
      case '6':
        blinkVal = 6;
        break;
      case '7':
        blinkVal = 7;
        break;
      case '8':
        blinkVal = 8;
        break;
      case '9':
        blinkVal = 9;
        break;
      case 'a':
        blinkVal = 10;
        break;
      case 'b':
        blinkVal = 11;
        break;
      case 'c':
        blinkVal = 12;
        break;
      case 'd':
        blinkVal = 13;
        break;
      case 'e':
        blinkVal = 14;
        break;
      case 'f':
        blinkVal = 15;
        break;
    }
    
    Serial.println(blinkVal);
  
  }
  
  triggerVal = digitalRead(triggerPin);
  if (triggerVal == HIGH) {
    doBlink(blinkVal, 250);
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
