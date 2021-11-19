//DS= [D]ata [S]torage - data
//STCP= [ST]orage [C]lock [P]in latch
//SHCP= [SH]ift register [C]lock [P]in clock
// Define Connections to 74HC595
#include <EEPROM.h>
const int latchPin = 11; // STCP to 12 on Shift Register
const int clockPin = 10; // SHCP to 11 on Shift Register
const int dataPin = 12; // DS to 14 on Shift Register

/*  See that the array is declared as int
 *  The B in front is the binary representation of the int number
 *  Instead of B11111100, which displays 0, we can write 252
 */
int digitArray[16] = {
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
const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;
int displayDigits[] = {
  segD1, segD2, segD3, segD4
};
const int displayCount = 4;
int numbers[] = {0, 0, 0, 0};

volatile bool lockedIn = false;
volatile bool lastSwState = false;
volatile long long lastDebounce = 0;
const int debounceInterval = 200;
const int blinkSpeed = 500;
bool joyMovedX = false;
bool joyMovedY = false;
const int swPin = 2;

unsigned long lastIncrement = 0;
unsigned long delayCount = 50;
unsigned long number = 0;
int currentIndex = 0;

const int pinX = A0;
const int pinY = A2;
const int minThresh = 200;
const int maxThresh = 600;

void setup () {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(swPin, INPUT_PULLUP);
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
  for (int i = 0; i < displayCount; i++) {
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], LOW);
    numbers[i] = EEPROM.read(i);
  }
  attachInterrupt(digitalPinToInterrupt(2), updateSW, FALLING);
  Serial.begin(9600);
}


void loop() {
  byte dpState = updateDP();
  writeNumber(numbers, dpState);
  Serial.println(lockedIn);
  updateJoystick();
}

void writeReg(int digit) {
    // ST_CP LOW to keep LEDs from changing while reading serial data
    digitalWrite(latchPin, LOW);
    // Shift out the bits
    shiftOut(dataPin, clockPin, MSBFIRST, digit);
    /* ST_CP on Rising to move the data from shift register
     * to storage register, making the bits available for output.
     */
    digitalWrite(latchPin, HIGH);
}


void showDigit(int displayNumber) {
  // delay(1);
  // first, disable all the display digits
  for (int i = 0; i < displayCount; i++) {
    digitalWrite(displayDigits[i], HIGH);
  }
  digitalWrite(displayDigits[displayNumber], LOW);
  delay(5);
}

byte updateDP() {
  if (lockedIn == true) {
    return HIGH;
  } else {
    return (millis() % blinkSpeed) > (blinkSpeed / 2);
  }
}

void writeNumber(int numbers[], byte dpState) {
  int i = 0;
  int displayDigit = 0;
  int currentDigit;
  
  for (int i = 0; i < 4; i++) {
    // get the last digit of the number
    currentDigit = numbers[i];
    // send the number to the display
    if (i == currentIndex) {
      writeReg(digitArray[currentDigit] + dpState);
    }
    else {
      writeReg(digitArray[currentDigit]);
    }
    // enable only the display digit for that 
    showDigit(i);
    // delay(5);
    // eliminate the last digit of the number
  }
}
void updateJoystick() {
  int xValue = analogRead(pinX);
  int yValue = analogRead(pinY);
  if (lockedIn == false) {
    if (xValue < minThresh && joyMovedX == false) {
      if (currentIndex < 3) {
        currentIndex++;
      }
      else {
        currentIndex = 0;
      }
      joyMovedX = true;
    }
    if (xValue > maxThresh && joyMovedX == false) {
      if (currentIndex > 0) {
        currentIndex--;
      }
      else {
        currentIndex = 3;
      }
      joyMovedX = true;
    }
    if (xValue >= minThresh && xValue <= maxThresh) {
      joyMovedX = false;
    }
  }
  else {
    if (yValue < minThresh && joyMovedY == false) {
      if (numbers[currentIndex] < 9) {
        numbers[currentIndex]++;
      }
      else {
        numbers[currentIndex] = 0;
      }
      joyMovedY = true;
    }
    if (yValue > maxThresh && joyMovedY == false) {
      if (numbers[currentIndex] > 0) {
        numbers[currentIndex]--;
      }
      else {
        numbers[currentIndex] = 9;
      }
      joyMovedY = true;
    }
    if (yValue >= minThresh && yValue <= maxThresh) {
      joyMovedY = false;
    }
  }
}
void updateSW() {
  Serial.println("in");
  if (millis() - lastDebounce > debounceInterval) {
    lastSwState = lockedIn;
    lockedIn = !lockedIn;
    if (lastSwState == true && lockedIn == false) {
      saveToMemory();
    }
  }
  lastDebounce = millis();
}
void saveToMemory() {
  EEPROM.update(currentIndex, numbers[currentIndex]);
}
