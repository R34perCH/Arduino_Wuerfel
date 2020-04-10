// Const declaration
const byte LED1 = 11;
const byte LED2 = 6;
const byte LED3 = 10;
const byte LED4 =  9;
const byte LED5 =  5;
const byte LED6 =  3;
const byte LED7 =  12;
const byte BUTTON = 2;

// Global Variable declaration
byte allLeds [7] = {LED1, LED2, LED3, LED4, LED5, LED6, LED7};
byte rNumber;
String incoming;
int brightness = 0;
int sensorValue = 0;

// Function declaration
void showNumber(byte number);
bool checkButton();
bool checkSerial();
void wurf();
void allOff();
void error();
int getLdrValue();

// Setup
void setup()
{
  for (int i = 0; i < 7; i++) {
    pinMode(allLeds[i], OUTPUT);
  }
  pinMode(BUTTON, INPUT_PULLUP);  
  randomSeed(analogRead(A1));
  Serial.begin(9600); 
}

// Programm Loop
void loop()
{
  /*
  while (!checkS) {
    checkB = checkButton();
    brightness = getLdrValue();
    checkS = checkSerial();
    delay(10);
  };
  */
  brightness = getLdrValue();
  if (checkButton() || checkSerial()) {
    wurf();
  	rNumber = random(1,7);
  	showNumber(rNumber);
  	Serial.print("Wurfzahl: ");
  	Serial.print(rNumber);
  	Serial.println();
    Serial.print("Helligkeit: ");
  	Serial.print(brightness);
  	Serial.println();
  	delay(5000);
  	allOff();
  }
  delay(10);
}

// Functions definitions
void showNumber(byte number) {
  switch(number) {
    case 1:	 digitalWrite(LED7, HIGH);
    		 break;
    case 2:  analogWrite(LED1, brightness);
    		 analogWrite(LED4, brightness);
    		 break;
    case 3:  analogWrite(LED1, brightness);
    		 digitalWrite(LED7, HIGH);
    		 analogWrite(LED4, brightness);
    		 break;
    case 4:  for (int i = 0; i < 4; i++) {
      		  analogWrite(allLeds[i], brightness);
    		 }
    		 break;
    case 5:  for (int i = 0; i < 4; i++) {
      		  analogWrite(allLeds[i], brightness);
   			 }
    		 digitalWrite(LED7, HIGH);
    		 break;
    case 6:  for (int i = 0; i < 6; i++) {
      		  analogWrite(allLeds[i], brightness);
   			 }
    		 break;
    default: error();
    		 break;
  }
}

bool checkButton() {
  return digitalRead(BUTTON) == HIGH ? false : true;
}

bool checkSerial() {
  incoming = "";
  while (Serial.available() > 0) {
    incoming = Serial.readString();
    Serial.print("Empfangen: ");
    Serial.println(incoming);
  }
  return incoming == "s" ? true : false;
}

void wurf () {
  float rDelay = 100;
  for (int i = 0; i < 10; i++) { 
    rNumber = random(1,7);
    Serial.println(rNumber);
    showNumber(rNumber);
    delay(rDelay);
    allOff();
    delay(rDelay);
    rDelay *= 1.2;
  }
}

void allOff() {
  for (int i = 0; i < 7; i++) {
    digitalWrite(allLeds[i], LOW);
  }
}

void error() {
  for (int i = 0; i < 3; i++) {
    for (int y = 0; y < 7; y++) {
    digitalWrite(allLeds[y], HIGH);
  }
  delay(500);
  allOff();
  delay(500);
  }
}

int getLdrValue() {
  sensorValue = analogRead(A0);
  int value = 0;
  if (sensorValue >= 54 && sensorValue < 890) {
    value = 20;
    }
  else if (sensorValue >= 890 && sensorValue <942) {
    value = 95;
    }
  else if (sensorValue >= 942 && sensorValue < 965) {
    value = 190;
    }
  else {
    value = 255;
  }
  return value;
}

