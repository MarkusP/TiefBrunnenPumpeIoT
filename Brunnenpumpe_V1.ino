// 2020-03-02 Brunnenpumpe V1
// (c) Markus Pohle @Creative Commons BY-NC-SA
// https://en.wikipedia.org/wiki/File:Cc-by-nc-sa_icon.svg
// 
// Brunnenpumpen Steuerung mittels Schwimmschalter

const int relayPin = 23;
const int upperWaterLevelSwitch = 22; 
int upperWaterLevelSwitchState = 0;
const int lowerWaterLevelSwitch = 21;
int lowerWaterLevelSwitchState = 0;
int pumpActive = 0;


void setup() {
  // Wir definieren einige Aus- und Eingabe Pins
  // die Eingabe Pins definieren wir als PULLDOWN!
  pinMode(relayPin, OUTPUT);
  pinMode(upperWaterLevelSwitch, INPUT_PULLDOWN);
  pinMode(lowerWaterLevelSwitch, INPUT_PULLDOWN);
}

void loop() {
  // hier lesen wir die Zustände der Schwimmschalter ein
  upperWaterLevelSwitchState = digitalRead(upperWaterLevelSwitch);
  lowerWaterLevelSwitchState = digitalRead(lowerWaterLevelSwitch);

  // wir prüfen die Zustände der Schwimmschalter
  // sind beide Schalter "unten", dann muss die Pumpe starten
  // das "Pumpe aktiv" Flag geht auf 1
  if (lowerWaterLevelSwitchState && upperWaterLevelSwitchState) {
    pumpActive = 1;    
  }

  if (!upperWaterLevelSwitchState) {
    pumpActive = 0;
  }

  if (!lowerWaterLevelSwitchState && upperWaterLevelSwitchState && pumpActive) {
    pumpActive = 1;
  }
  
  
  if (pumpActive) {
    digitalWrite(relayPin, HIGH);
  } else {
    digitalWrite(relayPin, LOW);
  }

}
