const int triggerPin = 4;
const int ledPin = 6;

int outPin = 8;
int triggerVal = 0;
char inputVal = '0';
int blinkVal = 5;
int triggerPosition = 0;

void setup() {
   pinMode(triggerPin, INPUT);
   pinMode(ledPin, OUTPUT);
   
   // set pins as out
   pinMode(7, OUTPUT);
   pinMode(8, OUTPUT);
   pinMode(9, OUTPUT);
   pinMode(10, OUTPUT);
   pinMode(11, OUTPUT);
   pinMode(12, OUTPUT);
   pinMode(13, OUTPUT);
   pinMode(14, OUTPUT);
   pinMode(15, OUTPUT);
   pinMode(16, OUTPUT);
   pinMode(17, OUTPUT);
   pinMode(45, OUTPUT);
   pinMode(44, OUTPUT);
   pinMode(43, OUTPUT);
   pinMode(42, OUTPUT);
   pinMode(41, OUTPUT);
   
   Serial.begin(9600);
 }

void loop(){
  if (Serial.available()>0) {
    inputVal = Serial.read();
    
    switch (inputVal) {
      case '0':
        outPin = 7;
        break;
      case '1':
        outPin = 8;
        break;
      case '2':
        outPin = 9;
        break;
      case '3':
        outPin = 10;
        break;
      case '4':
        outPin = 11;
        break;
      case '5':
        outPin = 12;
        break;
      case '6':
        outPin = 13;
        break;
      case '7':
        outPin = 14;
        break;
      case '8':
        outPin = 15;
        break;
      case '9':
        outPin = 16;
        break;
      case 'a':
        outPin = 17;
        break;
      case 'b':
        outPin = 45;
        break;
      case 'c':
        outPin = 44;
        break;
      case 'd':
        outPin = 43;
        break;
      case 'e':
        outPin = 42;
        break;
      case 'f':
        outPin = 41;
        break;
    }
    
    Serial.println(outPin);
  
  }
  
  triggerVal = digitalRead(triggerPin);
  if (triggerVal == HIGH) {
    digitalWrite(outPin, HIGH);
  } else {
    digitalWrite(outPin, LOW);
  }
}

