/*

*/


const int triggerPin = 4;

int outPin = 7;
int triggerVal = 0;
char inputVal = '0';
int defaultPin = 7;

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
   digitalWrite(defaultPin, HIGH);
   
   // clear all values in the trigger sequence - default pin is 0 to start
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
    
    Alternatively, you can send a two character sequence 'X-' where the -
    is the new default valve (same convention as the sequence values).  
    This can be used to manually switch the valves. 
    
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
    memset(triggerSequence, pin2char(defaultPin), sizeof(triggerSequence));
    triggerPosition = 0;

    Serial.readBytesUntil('\n', triggerSequence, 2048);
    
    if (triggerSequence[0] == 'X') { // need to set the default pin to something else
      int newDefaultPin = char2pin(triggerSequence[1]);
      if (newDefaultPin != defaultPin) {
        digitalWrite(defaultPin, LOW);
        defaultPin = newDefaultPin;
        memset(triggerSequence, pin2char(defaultPin), sizeof(triggerSequence));
      }  
    } else {
      outPin = char2pin(triggerSequence[triggerPosition]);  
    }

    digitalWrite(defaultPin, HIGH); // reset so valve 0 is on
    
  }  
  // pin logic
  triggerVal = digitalRead(triggerPin);
  if (triggerVal == HIGH) {
    // set default pin off and out pin on
    if (outPin != defaultPin) {
      digitalWrite(outPin, HIGH);
      digitalWrite(defaultPin, LOW);
    }
    //delay(10);
    wasTriggered = 1;
  } else {
    // set outpin off and default pin on
     if (outPin != defaultPin) {
       digitalWrite(outPin, LOW);
       digitalWrite(defaultPin, HIGH);
     }
    //delay(10);
    if (wasTriggered) {
      triggerPosition += 1;
      outPin = char2pin(triggerSequence[triggerPosition]);  
      wasTriggered = 0;
    }
  }
}

// this code is to map serial character to the right pin for each valve
int char2pin(char inputVal) {
     int out;
    
    switch (inputVal) {
      case '0':
        out = 7;
        break;
      case '1':
        out = 8;
        break;
      case '2':
        out = 9;
        break;
      case '3':
        out = 10;
        break;
      case '4':
        out = 11;
        break;
      case '5':
        out = 12;
        break;
      case '6':
        out = 13;
        break;
      case '7':
        out = 14;
        break;
      case '8':
        out = 15;
        break;
      case '9':
        out = 16;
        break;
      case 'a':
        out = 17;
        break;
      case 'b':
        out = 45;
        break;
      case 'c':
        out = 44;
        break;
      case 'd':
        out = 43;
        break;
      case 'e':
        out = 42;
        break;
      case 'f':
        out = 41;
        break;
      case '\0':  // string termination: valve 0
        out = defaultPin;
        break;
      default: // anything weird:  valve 0
        out = defaultPin;
        break;
    }
    Serial.print("Next pin: ");
    Serial.println(out);
    
    Serial.flush();
    return out;
}

// this code does the reverse, it returns a valid serial character for a given pin number
char pin2char(int pinNumber) {
     char out;
    
    switch (pinNumber) {
      case 7:
        out = '0';
        break;
      case 8:
        out = '1';
        break;
      case 9:
        out = '2';
        break;
      case 10:
        out = '3';
        break;
      case 11:
        out = '4';
        break;
      case 12:
        out = '5';
        break;
      case 13:
        out = '6';
        break;
      case 14:
        out = '7';
        break;
      case 15:
        out = '8';
        break;
      case 16:
        out = '9';
        break;
      case 17:
        out = 'a';
        break;
      case 45:
        out = 'b';
        break;
      case 44:
        out = 'c';
        break;
      case 43:
        out = 'd';
        break;
      case 42:
        out = 'e';
        break;
      case 41:
        out = 'f';
        break;
      default: // anything weird:  valve 0
        out = '\0';
        break;
    }
    return out;
}
