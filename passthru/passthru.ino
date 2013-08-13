/*

*/


const int triggerPin = 4;

int outPin = 8;
int triggerVal = 0;
char inputVal = '0';

boolean wasTriggered = 0;

char triggerSequence[2048];
int triggerPosition = 0;

void setup() {
   pinMode(triggerPin, INPUT);

   // set pins as out
   pinMode(7, OUTPUT); // valve 0
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
   pinMode(41, OUTPUT); // valve 15
   
   // set valve 0 to on by default
   digitalWrite(7, HIGH);
   
   // clear all values in the trigger sequence
   memset(triggerSequence, '0', sizeof(triggerSequence));

   Serial.begin(9600);
 }

/* 
loop has two stages

1)  check for new serial input that indicates a series of states.
    This will be a string of hexidecimal characters, 0-9 or a-f
    These will be mapped to valve positions, 0-15.  Saved as a 
    character array in 'triggerSequence'.  Current valve is saved
    as an index called 'triggerPosition'
    
2)  Check the state of the triggerPin and pass thru it's state to
    the correct pin, and turn off valve 0.  This will continually 
    be set through each time in the loop, which is wasteful but no 
    big deal and makes signal generation easy.  Once high, mark 
    'wasTriggered' as true.
    
    If the pin is low, and wasTriggered is true, then we've transitioned
    out.  Turn on valve 0, turn off the current valve, and increment
    the triggerPosition.  
*/      
void loop(){
  // serial
  if (Serial.available()>0) {
    memset(triggerSequence, '0', sizeof(triggerSequence));
    triggerPosition = 0;

    Serial.readBytesUntil('\n', triggerSequence, 2048);
    
    updateThruPin();
    digitalWrite(7, HIGH); // reset so valve 0 is on
  }
  
  // pin logic
  triggerVal = digitalRead(triggerPin);
  if (triggerVal == HIGH) {
    // set valve 0 to off
    digitalWrite(7, LOW);
    digitalWrite(outPin, HIGH);
    //delay(10);
    wasTriggered = 1;
  } else {
    digitalWrite(outPin, LOW);
    digitalWrite(7,HIGH);
    //delay(10);
    if (wasTriggered) {
      triggerPosition += 1;
      updateThruPin();
      wasTriggered = 0;
    }
  }
}

// this code is to map serial character to the right pin for each valve
void updateThruPin() {
    inputVal = triggerSequence[triggerPosition];
    
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
      case '\0':  // string termination: valve 0
        outPin = 7;
        break;
      default: // anything weird:  valve 0
        outPin = 7;
        break;
    }
    Serial.print("Next pin: ");
    Serial.println(outPin);
    
    Serial.flush();
}
