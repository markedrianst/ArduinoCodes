#include <dht.h>

// DHT11 setup
#define DHT11_PIN 2
dht DHT;

#define LED_1 5 // Red LED
#define LED_2 4 // Yellow LED
#define LED_3 3// Green LED

// Pin assignments
#define WATER_SENSOR_PIN A2      // Water sensor on A2
#define POTENTIOMETER_PIN A1     // Potentiometer on A1 for mode selection
#define SOUND_SENSOR_PIN A0      // Sound sensor on A0

void setup() {
  // Set pin modes
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  
  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Read the potentiometer value to determine which mode to operate in
  int potValue = analogRead(POTENTIOMETER_PIN);
  
  if (potValue < 341) {
    // DHT11 Mode (Temperature and Humidity)
    dht11Mode();
  } else if (potValue < 682) {
    // Water Sensor Mode
    waterMode();
  } else {
    // Sound Sensor Mode
    soundMode();
  }
  
  delay(2000); // Wait 1 second before repeating
}

// DHT11 Mode: Read temperature and humidity
void dht11Mode() {
  int chk = DHT.read11(DHT11_PIN);
  float temperature = DHT.temperature;
  float humidity = DHT.humidity;

  // Print temperature and humidity to the Serial Monitor
  Serial.println("Mode: DHT11 (Temperature and Humidity)");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print((char)223); // Degree symbol
  Serial.println("C");

  Serial.print("Humidity: ");
  Serial.println(humidity);

  // Control LEDs based on temperature
  if (temperature < 20) {
    setLED(LED_1); // Low temperature
  } else if (temperature <= 30) {
    setLED(LED_2); // Medium temperature
  } else {
    setLED(LED_); // High temperature
  }
}

// Water Sensor Mode: Read water level from the water sensor
void waterMode() {
  int waterSensorVal = analogRead(WATER_SENSOR_PIN);

  // Print water sensor value to the Serial Monitor
  Serial.println("Mode: Water Sensor");
  Serial.print("Water Sensor Value: ");
  Serial.println(waterSensorVal);

  // Control LEDs based on water level
  if (waterSensorVal <= 125) {
    setLED(LED_1); // Low water level
    Serial.println("Water Level: Low");
  } else if (waterSensorVal <= 250) {
    setLED(LED_2); // Medium water level
    Serial.println("Water Level: Medium");
  } else {
    setLED(LED_3); // High water level
    Serial.println("Water Level: High");
  }
}

// Sound Sensor Mode: Read sound level from the sound sensor
void soundMode() {
  int soundSensorVal = analogRead(SOUND_SENSOR_PIN);

  // Print sound sensor value to the Serial Monitor
  Serial.println("Mode: Sound Sensor");
  Serial.print("Sound Level: ");
  Serial.println(soundSensorVal);

  // Control LEDs based on sound level
  if (soundSensorVal < 496) {
    setLED(LED_1); // Low sound level
    Serial.println("Sound Level: Low");
  } else if (soundSensorVal < 505) {
    setLED(LED_2); // Medium sound level
    Serial.println("Sound Level: Medium");
  } else {
    setLED(LED_3); // High sound level
    Serial.println("Sound Level: High");
  }
}

// Function to set the appropriate LED and turn others off
void setLED(int ledPin) {
  digitalWrite(LED_1, ledPin == LED_1);
  digitalWrite(LED_2, ledPin == LED_2);
  digitalWrite(LED_3, ledPin == LED_3);
}
