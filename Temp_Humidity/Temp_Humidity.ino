#include <dht.h>
#include <Wire.h>  // Include Wire library for I2C
#include <LiquidCrystal_I2C.h>  // Include library for I2C LCD

// Initialize the I2C LCD (address 0x27) with 16 columns and 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

dht DHT;

#define DHT11_PIN 7

void setup() {
  lcd.init();        // Initialize the LCD
  lcd.backlight();   // Turn on the LCD backlight
}

void loop() {
  int chk = DHT.read11(DHT11_PIN);
  
  lcd.setCursor(0, 0); 
  lcd.print("Temp: ");
  lcd.print(DHT.temperature);
  lcd.print((char)223);  // Degree symbol
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(DHT.humidity);
  lcd.print("%");

  delay(100);
}
