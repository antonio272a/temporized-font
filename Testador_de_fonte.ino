#define RELAY_OUT 2
#define RELAY_IN 3
#define LED_OUT 4
#define ON_SWITCH 5
#define RESET_BUTTON 6
#define ON_LED 7
#define POWER_OFF_CHECK_BUTTON 8
#define POWER_OFF_CHECK_LED 9

bool isWorking = true;
bool isOn = false;
bool reset = false;

void setup() {
  pinMode(RELAY_OUT, OUTPUT);
  pinMode(RELAY_IN, INPUT_PULLUP);
  pinMode(LED_OUT, OUTPUT);
  pinMode(ON_SWITCH, INPUT_PULLUP);
  pinMode(RESET_BUTTON, INPUT_PULLUP);
  pinMode(ON_LED, OUTPUT);
  pinMode(POWER_OFF_CHECK_BUTTON, INPUT_PULLUP);
  pinMode(POWER_OFF_CHECK_LED, OUTPUT);
  digitalWrite(RELAY_OUT, HIGH);
}

void fireEvent() {
  digitalWrite(RELAY_OUT, LOW);
  delay(1000);
  digitalWrite(RELAY_OUT, HIGH);
}

bool checkInput(){
  return digitalRead(RELAY_IN) == LOW;
}

void turnErrorLed() {
  digitalWrite(LED_OUT, HIGH);
}

void resetLedWarning() {
  digitalWrite(LED_OUT, LOW);
  delay(200);
  digitalWrite(LED_OUT, HIGH);
  delay(200);
  digitalWrite(LED_OUT, LOW);
  delay(200);
  digitalWrite(LED_OUT, HIGH);
  delay(200);
  digitalWrite(LED_OUT, LOW);
}

void resetTest(){
  isWorking = true;
  resetLedWarning();
}
 
void loop() {
  isOn = digitalRead(ON_SWITCH) == LOW;
  reset = digitalRead(RESET_BUTTON) == LOW;
  if (!digitalRead(POWER_OFF_CHECK_BUTTON)) {
    digitalWrite(POWER_OFF_CHECK_LED, HIGH);
    }
  digitalWrite(ON_LED, !digitalRead(ON_SWITCH));
  if (reset && !isWorking) {
    resetTest();
   }
    
  if(isOn && isWorking){
    fireEvent();
    isWorking = checkInput();
    if(!isWorking){
      turnErrorLed();
      } else {
        delay(10000);
        }
    }
} 
