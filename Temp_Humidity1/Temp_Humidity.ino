// #include <Adafruit_Sensor.h>
// #include <DHT.h>
// #include <DHT_U.h>

// // Define the pin connected to the DHT11 data pin
// #define DHTPIN 2    

// // Define the DHT type (DHT11 or DHT22)
// #define DHTTYPE DHT11  

// // Initialize the DHT sensor
// DHT dht(DHTPIN, DHTTYPE);

// void setup() {
//   Serial.begin(9600);  // Initialize serial communication
//   dht.begin();         // Start the DHT sensor
// }

// void loop() {
//   // Read humidity
//   float humidity = dht.readHumidity();

//   // Read temperature in Celsius
//   float temperature = dht.readTemperature();

//   // Check if any reads failed
//   if (isnan(humidity) || isnan(temperature)) {
//     Serial.println("Failed to read from DHT sensor!");
//     return;
//   }

//   // Print the results to the Serial Monitor
//   Serial.print("Humidity (%): ");
//   Serial.println(humidity, 2);

//   Serial.print("Temperature (C): ");
//   Serial.println(temperature, 2);

//   delay(2000);  // Wait 2 seconds before the next reading
// }



#include <dht.h>

dht DHT;

#define DHT11_PIN 2

void setup() {
  Serial.begin(9600);  
}

void loop() {
  int chk = DHT.read11(DHT11_PIN);
  
 
  Serial.print("Temp: ");
  Serial.print(DHT.temperature);
  Serial.print((char)223); 
  Serial.println("C");


  Serial.print("Humidity: ");
  Serial.print(DHT.humidity);
  Serial.println("%");


  delay(1000);  
}

// #include <dht.h>
// #include <Wire.h>  // Include Wire library for I2C
// #include <LiquidCrystal_I2C.h>  // Include library for I2C LCD

// // Initialize the I2C LCD (address 0x27) with 16 columns and 2 rows
// LiquidCrystal_I2C lcd(0x27, 16, 2);

// dht DHT;

// #define DHT11_PIN 7

// void setup() {
//   lcd.init();        // Initialize the LCD
//   lcd.backlight();   // Turn on the LCD backlight
// }

// void loop() {
//   int chk = DHT.read11(DHT11_PIN);
  
//   lcd.setCursor(0, 0); 
//   lcd.print("Temp: ");
//   lcd.print(DHT.temperature);
//   lcd.print((char)223);  // Degree symbol
//   lcd.print("C");

//   lcd.setCursor(0, 1);
//   lcd.print("Humidity: ");
//   lcd.print(DHT.humidity);
//   lcd.print("%");

//   delay(100);
// }