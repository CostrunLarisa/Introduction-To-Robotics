#define NUMREADINGS 15 
const int inPin = 5;             
const int pinRed1 = 2;         
const int pinRed2 = 3;
const int pinYellow1 = 6;   
const int pinYellow2 = 5;   
const int pinYellow3 = 4;   
const int pinGreen1 = 9;  
const int pinGreen2 = 8;
const int pinGreen3 = 7;
const int pinBuzzer = 10; 
bool ledStateRed1 = LOW;
bool ledStateRed2 = LOW;
bool ledStateYellow1 = LOW;
bool ledStateYellow2 = LOW;
bool ledStateYellow3 = LOW;
bool ledStateGreen1 = HIGH;
bool ledStateGreen2 = LOW;
bool ledStateGreen3 = LOW;
int readings[NUMREADINGS];                // the readings from the analog input
int index = 0;                            // the index of the current reading
int total = 0;                            // the running total
int average = 0;                          // average of the reading
int senseLimit = 15;
int val = 0;                 
int buzzerTone = 0;

void setup() {
 
  pinMode(pinRed1, OUTPUT);
  pinMode(pinRed2, OUTPUT);
  pinMode(pinYellow1, OUTPUT);
  pinMode(pinYellow2, OUTPUT);
  pinMode(pinYellow3, OUTPUT); 
  pinMode(pinGreen1, OUTPUT); 
  pinMode(pinGreen2, OUTPUT);
  pinMode(pinGreen3, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
  Serial.begin(9600);
 
}

void loop() {
  initialize();                               // leds come back to the  initial state after one reading
  val = analogRead(inPin);                    // reads the values from antenna
  if(val >= 1) {                
    val = constrain(val, 1, senseLimit);  
    val = map(val, 1, senseLimit, 1, 1023);  
    total -= readings[index];              
    readings[index] = val;                 
    total += readings[index];              
    index = (index + 1);                    
    if (index >= NUMREADINGS) {              
      index = 0;                            
    }
    average = total / NUMREADINGS;          
    if (average >  50) {                // if the average is over 50 
      ledStateGreen2 = HIGH;           // light the second Green LED
    }
    else {                        
      ledStateGreen2 = LOW;    
    }

    if (average > 250) {               
      ledStateGreen3 = HIGH;
    }
    else {
      ledStateGreen3 = LOW;
    }

    if (average > 350) {
      ledStateYellow1 = HIGH;
    }
    else {
      ledStateYellow1 = LOW;
    }

    if (average > 550) {
      ledStateYellow2 = HIGH;
      buzzerTone += 1000;
      noTone(pinBuzzer);
      tone(pinBuzzer, buzzerTone, 1000);
    }
    else {
      ledStateYellow2 = LOW;
    }

    if (average > 650) {
      ledStateYellow3 = HIGH;
      buzzerTone += 500;
      noTone(pinBuzzer);
      tone(pinBuzzer, buzzerTone, 1000);
    }
    else {
      ledStateYellow3 = LOW;
      buzzerTone -= 500;      
    }

    if (average > 850) {
      buzzerTone += 500;
      noTone(pinBuzzer);
      tone(pinBuzzer, buzzerTone, 100);      
      ledStateRed1 = HIGH;
    }
    else {
      buzzerTone -= 500;      
      ledStateRed1 = LOW;
    }

    if (average > 950) {
      buzzerTone += 500;
      noTone(pinBuzzer);
      tone(pinBuzzer, buzzerTone, 100);
      ledStateRed2 = HIGH;
    }
    else {
      buzzerTone -= 500;
      ledStateRed2 = LOW;
    }
  }
  showLeds();
}

void showLeds() {
  digitalWrite(pinRed1, ledStateRed1);
  digitalWrite(pinRed2, ledStateRed2);
  digitalWrite(pinYellow1, ledStateYellow1);
  digitalWrite(pinYellow2, ledStateYellow2);
  digitalWrite(pinYellow3, ledStateYellow3);
  digitalWrite(pinGreen1, ledStateGreen1);
  digitalWrite(pinGreen2, ledStateGreen2); 
  digitalWrite(pinGreen3, ledStateGreen3);           
}

void initialize() {
  buzzerTone = 0;
  ledStateGreen1 = HIGH;
  ledStateGreen2 = LOW;
  ledStateGreen3 = LOW;
  ledStateYellow1 = LOW;
  ledStateYellow2 = LOW;
  ledStateYellow3 = LOW;
  ledStateRed1 = LOW;
  ledStateRed2 = LOW;  
}