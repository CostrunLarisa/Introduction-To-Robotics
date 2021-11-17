// declare all the joystick pins
const int pinSW = 2; // digital pin connected to switch output
const int pinX = A0; // A0 - analog pin connected to X output
const int pinY = A1; // A1 - analog pin connected to Y output


const int dataPin = 12;
const int latchPin = 11;
const int clockPin = 10;

const int seg01 = 7;
const int seg02 = 6;
const int seg03 = 5;
const int seg04 = 4;

// The current digit from the current display
int lastDigit = 0;
// Save the number showed on the display
int displayLastDigit[] = {
    0, 0, 0, 0
};

// Save the number showed on the display with DP high/low/blinking
int displayByteDigits[] = {
  B11111100,
  B11111100,
  B11111100,
  B11111100,    
};
int displayDigits[] = {
  seg01, seg02, seg03, seg04
};

const int displayCount = 4;

// The index of the current DP
int indexDP = 0;
byte digitArray[16] = {
//A B C D E F G DP 
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
  B11101110, // A
  B00111110, // b
  B10011100, // C
  B01111010, // d
  B10011110, // E
  B10001110  // F
};

// dp on or off
bool dpState = LOW;
// states of the button press
bool swState = LOW;
volatile bool lastSwState = LOW;
int xValue = 0;
int yValue = 0;

bool joyMoved = false;
int minThreshold= 400;
int maxThreshold= 600;
int currentMillis;
int previousMillis = 0;
int interval = 1000;
volatile boolean isPushed = false;
const int segSize = 8;
const int noOfDigits = 10;

void setup() { 
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(pinSW, INPUT_PULLUP); 
  attachInterrupt(digitalPinToInterrupt(pinSW), signalDP, FALLING);
  for(int i =  0; i < displayCount; i++){
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], LOW);
  }
  Serial.begin(9600);
}

void loop() {
  // If we switch through digits (the joystick button wasn't pushed)
  if(isPushed == false) {
    firstState();
  }
  // Otherwise we block the digit and change the DP state
  else {
    changeStateDP(1);
    secondState();
  }
}

void firstState(){
 // On Ox axis, if the value is lower than a chosen min threshold, then
 // decrease by 1 the digit value.
  writeNumber();
  xValue = analogRead(pinX);
  currentMillis = millis();
  if (xValue < minThreshold && joyMoved == false) {
    if (indexDP < 3) {
        indexDP++;
    } else {
        indexDP = 3;
    }
    joyMoved = true;
  }
 // On Ox axis, if the value is bigger than a chosen max threshold, then
 // increase by 1 the digit value
  if (xValue > maxThreshold && joyMoved == false) {
    if (indexDP > 0) {
        indexDP--;
    } else {
        indexDP = 0;
    }
    joyMoved = true;
  }
  if (xValue >= minThreshold && xValue <= maxThreshold) {
	  joyMoved = false;
  }
  // Change the previous DP into LOW
  changeStateDP(0);
  // Save the last showed digit
  lastDigit = displayLastDigit[indexDP];
  // Make the current DP blink
  blinkingDP();
}

void secondState() {
  isPushed = false;
  swState = digitalRead(pinSW);
  if(swState == LOW && swState != lastSwState) {
    isPushed = true;
  } 
  // Check if the button wasn't pressed twice
  while(isPushed == false) { 
    // While we didn't pressed the button, increase/decrease the value   
    changeValue();
    // Change the digit showed on the display
    lastDigit = displayLastDigit[indexDP];
    // Change the DP of the new digit
    changeStateDP(1);    
    writeNumber();    
  }
  lastSwState = swState;
  isPushed = false;
  displayByteDigits[indexDP] = digitArray[lastDigit];  
}

void changeStateDP(bool stateDigit) {
  byte byteDigit = digitArray[lastDigit];
  bitWrite(byteDigit, 0, stateDigit);
  displayByteDigits[indexDP] = byteDigit;
  showDigit(indexDP);
  writeReg(byteDigit);
  //delay(2);

}
void signalDP() {
  isPushed = true;
  lastSwState = LOW;
}
void changeValue(){
  yValue = analogRead(pinY);
  if (yValue < minThreshold && joyMoved == false) {
    if (displayLastDigit[indexDP] < 9) {
          displayLastDigit[indexDP]++;
        } else {
          displayLastDigit[indexDP] = 9;
        }
        joyMoved = true;
      }
    // On Oy axis, if the value is bigger than a chosen max threshold, then
    // increase by 1 the digit value
  if (yValue > maxThreshold && joyMoved == false) {
    if (displayLastDigit[indexDP] > 0) {
          displayLastDigit[indexDP]--;
        } else {
          displayLastDigit[indexDP] = 0;
        }
        joyMoved = true;    
  }

    if (yValue >= minThreshold && yValue <= maxThreshold) {
      joyMoved = false;
    }
}
void blinkingDP(){
   // If we are on a display and we didn't move
  int byteDigit = displayByteDigits[lastDigit];
  if(currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    int lastNumber = byteDigit % 10;
    if(lastNumber == 1) {
      changeStateDP(0);
    } 
    else {
      changeStateDP(1);
    }
  }
}

void writeReg(int digit) { 
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);  
  digitalWrite(latchPin, HIGH);
}

void writeNumber(){
  for(int i = 0; i < displayCount; i++){   
    showDigit(i);
    writeReg(displayByteDigits[i]);
    delay(4);  
  }
}

void showDigit(int displayNumber){
  for( int i = 0; i < displayCount; i++){
    digitalWrite(displayDigits[i], HIGH);
  }
  digitalWrite(displayDigits[displayNumber], LOW);
}














