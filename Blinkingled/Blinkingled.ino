/*int brightness = 0;
int fadeAmount = 10; 
void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop() {


// analogWrite(9, brightness);
  
//    brightness = brightness + fadeAmount;
    
//    if (brightness == 0 || brightness == 255) {
//       fadeAmount = -fadeAmount ;
      
//    }
analogWrite(9, brightness);

// Change the brightness for next time through the loop:
brightness = brightness + fadeAmount;

// Check if the brightness has reached the limits:
if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
    
    // Turn off the LED when brightness reaches a limit
   
}

// Reduce the delay time for a faster transition
delay(30);
   
  
  //  delay(5000);
  //  
   //delay(300);


  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
}*/

int redLED = 9;   // Pin for the red LED
int blueLED = 10; // Pin for the blue LED
int greenLED = 11; // Pin for the green LED

int fadeAmount = 70; // Step size for fading
int brightness = 0;  // Initial brightness
int currentLED = 0;  // Start with the blue LED

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
}

void loop() {
  // Turn on the current LED and turn off the others
  if (currentLED == 0) { // Blue LED
    analogWrite(blueLED, brightness);
    analogWrite(redLED, 0);
    analogWrite(greenLED, 0);
  } else if (currentLED == 1) { // Red LED
    analogWrite(redLED, brightness);
    analogWrite(blueLED, 0);
    analogWrite(greenLED, 0);
  } else if (currentLED == 2) { // Green LED
    analogWrite(greenLED, brightness);
    analogWrite(redLED, 0);
    analogWrite(blueLED, 0);
  }

  // Change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // Reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
    currentLED = (currentLED + 1) % 3; // Cycle through 0, 1, 2 (blue, red, green)
  }

  // Adjust the delay for the speed of the effect
  delay(20); // Decrease this value for a faster effect
}


