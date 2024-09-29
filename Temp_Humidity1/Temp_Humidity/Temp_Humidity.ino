#include <DHT.h>  // Ensure the DHT library is installed

#define DHTPIN 2         // Pin connected to DHT11 sensor
#define DHTTYPE DHT11    // DHT 11 sensor type

// Create an instance of the DHT sensor object
DHT dht(DHTPIN, DHTTYPE);

// Define temperature thresholds
#define TEMP_LOW 20
#define TEMP_HIGH 30

// Define LED pins
#define GREEN_LED 3
#define YELLOW_LED 4
#define RED_LED 5

void setup() {
  // Initialize serial monitor
  Serial.begin(9600);

  // Initialize the DHT sensor
  dht.begin();

  // Initialize the LED pins as outputs
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  // Small delay to allow sensor to stabilize
  delay(1000);
}

void loop() {
  // Read temperature and humidity
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check if the readings are valid
  if (isnan(temp) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(2000); // Wait before retrying
    return;
  }

  // Print temperature and humidity to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" °C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Determine which LED to light up based on the temperature
  if (temp < TEMP_LOW) {
    lightUp(GREEN_LED);
  } else if (temp <= TEMP_HIGH) {
    lightUp(YELLOW_LED);
  } else {
    lightUp(RED_LED);
  }

  // Delay for a while to allow sensor readings to settle
  delay(2000);
}

// Function to light up one LED and turn off the others
void lightUp(int ledPin) {
  digitalWrite(GREEN_LED, LOW);  // Turn off all LEDs
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);

  digitalWrite(ledPin, HIGH);    // Turn on the selected LED
}
