#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the library with the I2C address and the LCD size (e.g., 16x2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    lcd.begin(16, 2);  // Initialize the LCD with 16 columns and 2 rows
    lcd.backlight();   // Turn on the backlight
}

void loop() {
    lcd.clear();               // Clear the display
    lcd.setCursor(0, 0);       // Set cursor to first row, first column
    lcd.print("Asim Mo"); // Display text
    delay(1000);               // Wait for a second

  //   int sensor = analogRead(A0); // Read the analog value from the sensor

  // if (sensor < 100){  // If the sensor value is less than 100
  //   lcd.println("Low"); // Print "Low" to the Serial Monitor
  // } 
  // else if (sensor >= 100 && sensor <= 200){ // If the sensor value is between 100 and 200
  //   lcd.println("Medium"); // Print "Medium" to the Serial Monitor
  // } 
  // else if (sensor > 200){ // If the sensor value is greater than 200
  //   lcd.println("High"); // Print "High" to the Serial Monitor
  // }
  //     delay(1000); 
}
