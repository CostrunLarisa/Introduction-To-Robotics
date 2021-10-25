const int ledPinRed = 11;
const int ledPinBlue = 10;
const int ledPinGreen = 9;

const int potPinRed = A0;
const int potPinBlue = A1;
const int potPinGreen = A2;

const int maxPot = 1023;
const int maxLed = 255;

// Initial values for potentiometers
int potValueRed = 0;
int potValueBlue = 0;
int potValueGreen = 0;

// Setting the initial intensity of Led's colors to 0
int intensityRed = 0;
int intensityBlue = 0;
int intensityGreen = 0;

void setup() {

  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinBlue, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);

  pinMode(potPinRed, INPUT);
  pinMode(potPinBlue, INPUT);
  pinMode(potPinGreen, INPUT);
}

void loop() {

  potValueRed = analogRead(potPinRed);
  potValueBlue = analogRead(potPinBlue);
  potValueGreen = analogRead(potPinGreen);

  intensityRed = map(potValueRed, 0, maxPot, 0, maxLed);
  intensityBlue = map(potValueBlue, 0, maxPot, 0, maxLed);
  intensityGreen = map(potValueGreen, 0, maxPot, 0, maxLed);

  setColor(intensityRed, intensityGreen, intensityBlue);
}

void setColor(int red, int green, int blue) {
  analogWrite(ledPinRed, red);
  analogWrite(ledPinGreen, green);
  analogWrite(ledPinBlue, blue);
}
