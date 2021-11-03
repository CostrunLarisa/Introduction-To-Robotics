const int pushButton = 2;
const int ledPinPassengerRed = 3;
const int ledPinPassengerGreen = 5;
const int ledPinCarRed = 11;
const int ledPinCarYellow = 10;
const int ledPinCarGreen = 9;
const int buzzerPin = 6;

bool buttonState = LOW;
bool ledStatePassengerRed = HIGH;
bool ledStatePassengerGreen = LOW;

bool ledStateCarGreen = HIGH;
bool ledStateCarYellow = LOW;
bool ledStateCarRed = LOW;
bool lastButtonState = LOW;
bool lastLedStateCar = HIGH;
bool lastLedStatePassenger = LOW;

bool reading = LOW;
bool lastReading = LOW;

int lastDebounceTimer = 0;
const int debounceInterval = 50;

// The interval we begin the cycle after pushing the button
// It is 7000 due to those 3 seconds of waiting to change each color of the car semaphore
const int firstStateInterval = 10000;
const long interval = 10000;
const long intervalSemaphore = 3000;
unsigned long previousMillis = 0;
unsigned long previousMillisPassenger = 0;
unsigned long previousMillisPushedButton = 0;
unsigned long previousMillisBlinked = 0;

// Shows if the button was pushed
bool isPushed = LOW;
// Shows if the cycle reached the first state or not
int firstState = 0;

unsigned long currentMillis;
unsigned long currentMillisPassenger;
unsigned long currentStartingMillis;
unsigned int lastDebounceTime = 0;
unsigned int debounceDelay = 50;
int buzzerTone = 1000;

void setup() {
  // put your setup code here, to run once:
  pinMode(pushButton, INPUT_PULLUP);
  pinMode(ledPinPassengerGreen, OUTPUT);
  pinMode(ledPinPassengerRed, OUTPUT);
  pinMode(ledPinCarRed, OUTPUT);
  pinMode(ledPinCarGreen, OUTPUT);
  pinMode(ledPinCarYellow, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  currentMillis = millis();
  reading = digitalRead(pushButton);
  showLeds();
  if (isPushed == HIGH){
    if(ledStateCarRed == HIGH && ledStatePassengerRed == HIGH){
        ledStatePassengerRed = LOW;
        ledStatePassengerGreen = HIGH;
        previousMillisPassenger = currentMillis;
        showLeds();
        tone(buzzerPin, buzzerTone, interval);
    }
    else if(ledStateCarRed == HIGH){
      semaphorePassengers();
      }
    else {
      semaphore();
      }        
  }
  if(reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if((millis() - lastDebounceTime) > debounceDelay){
      if(reading != buttonState) {
        buttonState = reading;
        // If it is not already in a cycle, then generate a new cycle
        if(buttonState == LOW && isPushed == LOW) {
          isPushed = HIGH;
          firstState = 1;
          currentStartingMillis = millis();
          }
      }
  }
  lastButtonState = reading;  
}

void semaphore(){
  if(firstState == 1 && currentMillis - currentStartingMillis >= firstStateInterval){
    firstState = 0;
    previousMillis = currentMillis;
    changeSemaphoreCar();
  }
  else if (firstState == 0 && currentMillis - previousMillis >= intervalSemaphore){
    previousMillis = currentMillis;
    changeSemaphoreCar();
  }
}

void semaphorePassengers(){
  //The total interval for state 3 + state 4 = 15 seconds
  if (currentMillis - previousMillisPassenger >= 3*interval/2){
    previousMillis = currentMillis;
    ledStatePassengerRed = HIGH;
    ledStatePassengerGreen = LOW;
    ledStateCarRed = LOW;
    ledStateCarGreen = HIGH;
    isPushed = LOW;
    noTone(buzzerPin);
    showLeds();
  }else if (currentMillis - previousMillisPassenger >= interval){
    // If state 3 has passed then cycle starts state 4
    if(currentMillis - previousMillisBlinked >= 500){
      if (buzzerTone <= 0) buzzerTone +=1000;
      else buzzerTone -=1000;
      previousMillisBlinked = currentMillis;
      tone(buzzerPin, buzzerTone, interval);
      ledStatePassengerGreen = !ledStatePassengerGreen;
    }
  }  
}
void showLeds(){
  digitalWrite(ledPinCarYellow, ledStateCarYellow);  
  digitalWrite(ledPinCarRed, ledStateCarRed);   
  digitalWrite(ledPinCarGreen, ledStateCarGreen);   
  digitalWrite(ledPinPassengerRed, ledStatePassengerRed);   
  digitalWrite(ledPinPassengerGreen, ledStatePassengerGreen); 
}

void changeSemaphoreCar(){
  if(ledStateCarGreen == HIGH)
  {
    ledStateCarGreen = LOW;
    ledStateCarYellow = HIGH;
  }
  else if (ledStateCarYellow == HIGH) {
    ledStateCarYellow = LOW;
    ledStateCarRed = HIGH;
  }
  else if (ledStateCarRed == HIGH) {
    ledStateCarRed = LOW;
    ledStateCarGreen = HIGH;
  }
}
