// 2020-03-02 Brunnenpumpe V2
// (c) Markus Pohle @Creative Commons BY-NC-SA
// https://en.wikipedia.org/wiki/File:Cc-by-nc-sa_icon.svg
// 
// Brunnenpumpen Steuerung mittels Ultraschall-Sensor

const int relayPin = 23;
const int triggerPin = 22;
const int echoPin = 21;
const int barrelHeight = 98;
int pumpActive = 0;
float waterLevel = 0;


void setup() {
//  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);
  
  // PIN-Modes
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(triggerPin, HIGH);
}

float distance() {
  float d = 0;
  long t = 0;

  noInterrupts();
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(3);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  t = pulseIn(echoPin, HIGH);
  d = (t/2) * 0.03435;
  interrupts();
  return(d);
}

void loop() {
  
  waterLevel = (1-(distance()/barrelHeight))*100;

  if (!pumpActive && (waterLevel <= 15) ) {
    pumpActive = 1;
  }

  if (pumpActive && (waterLevel >= 92) ) {
    pumpActive = 0;
  }

  
//  Serial.println(waterLevel);

  // vor der nächsten Messung warten wir eine Sekunde
  delay (1000);
  
  if (pumpActive) {
    digitalWrite(relayPin, HIGH);
  } else {
    digitalWrite(relayPin, LOW);
  }

}
