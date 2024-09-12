void setup() {
  // Begin serial communication
  Serial.begin(9600);
}

void loop() {
  // Read data from the analog pin and store it in the 'value' variable
  int sensor = analogRead(A0);  
  

//Serial.println(sensor); 
  
  if (sensor <= 50) { 
    Serial.println("Water level: 0mm - Empty!"); 
}
else if (sensor > 50 && sensor <= 100) { 
    Serial.println("Water level: 0mm to 5mm"); 
}
else if (sensor > 100 && sensor <= 150) { 
    Serial.println("Water level: 5mm to 10mm"); 
}
else if (sensor > 150 && sensor <= 200) { 
    Serial.println("Water level: 10mm to 15mm"); 
}
else if (sensor > 200 && sensor <= 250) { 
    Serial.println("Water level: 15mm to 20mm"); 
}
else if (sensor > 250 && sensor <= 300) { 
    Serial.println("Water level: 20mm to 30mm"); 
}
else if (sensor > 300 && sensor <= 350) { 
    Serial.println("Water level: 30mm to 40mm"); 
}
  
  /*if (sensor < 100){  // If the sensor value is less than 100
    Serial.println("Low"); // Print "Low" to the Serial Monitor
  } 
  else if (sensor >= 100 && sensor <= 200){ // If the sensor value is between 100 and 200
    Serial.println("Medium"); // Print "Medium" to the Serial Monitor
  } 
  else if (sensor > 200){ // If the sensor value is greater than 200
    Serial.println("High"); // Print "High" to the Serial Monitor
  }*/

  delay(2000); // Check for new value every 5 seconds
  }