int redLED = 9;    // Pin for the red LED
int yellowLED = 8; // Pin for the yellow LED
int greenLED = 7;  // Pin for the green LED

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
}

void loop() {
  // Red light on
  digitalWrite(redLED, HIGH);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);
  delay(5000); // Red light on for 5 seconds

  // Green light on
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, HIGH);
  delay(5000); // Green light on for 5 seconds

  // Yellow light on
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, HIGH);
  digitalWrite(greenLED, LOW);
  delay(2000); // Yellow light on for 2 seconds
}
