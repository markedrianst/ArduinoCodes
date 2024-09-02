#include <Wire.h>               // Include Wire library for I2C communication
#include <LiquidCrystal_I2C.h>  // Include library for I2C LCD

int LED_1 = 2;  // Red LED connected to digital pin 2
int LED_2 = 3;  // Yellow LED connected to digital pin 3
int LED_3 = 4;  // Green LED connected to digital pin 4
#define sensorPin A0  // Sensor connected to analog pin A0

// Initialize I2C LCD with address 0x27, 16 columns, and 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);  

void setup() {
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(sensorPin, INPUT);

  lcd.init();  // Initialize the LCD
  lcd.backlight();   // Turn on the backlight

  Serial.begin(9600);  // Initialize serial communication at 9600 bps
}

void loop() {
  int sensorVal = analogRead(sensorPin);  // Read the sensor value
  Serial.println(sensorVal);  // Print the sensor value to the Serial Monitor

  // Display the sensor value on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sensor Value:");
  lcd.setCursor(0, 1);
  lcd.print(sensorVal);

  // Control LEDs based on sensor value
  if (sensorVal <=515) {  // Soft range
    digitalWrite(LED_1, LOW);  // Turn on Red LED
    digitalWrite(LED_2, LOW);   // Turn off Yellow LED
    digitalWrite(LED_3, HIGH);   // Turn off Green LED
  } else if (sensorVal >= 516 && sensorVal <= 517) {  // Medium range
    digitalWrite(LED_1, LOW);   // Turn off Red LED
    digitalWrite(LED_2, HIGH);  // Turn on Yellow LED
    digitalWrite(LED_3, HIGH);   // Turn off Green LED
  } 
  else {  // Rock range
    digitalWrite(LED_1, HIGH);   // Turn off Red LED
    digitalWrite(LED_2, HIGH);   // Turn off Yellow LED
    digitalWrite(LED_3, HIGH);  // Turn on Green LED
  }
  

  delay(500);  // Delay for 0.5 seconds
}
