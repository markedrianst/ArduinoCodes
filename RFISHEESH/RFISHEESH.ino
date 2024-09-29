#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>  // Include the Servo library

// Define LCD address and create object
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Set up the Servo object
Servo myServo;  

// Define the rows and columns for the keypad
const byte ROWS = 4; 
const byte COLS = 3;  // Now the keypad has 3 columns

// Define the keymap
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

// Connect to the row and column pinouts of the keypad (pins 2 to 8)
byte rowPins[ROWS] = {5, 4, 3, 2};  // Rows are connected to pins 2, 3, 4, and 5
byte colPins[COLS] = {8, 7, 6};     // Columns are connected to pins 6, 7, and 8

// Create an object of the Keypad class
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String password = "1234";  // Set your password
String input = "";         // Store the input password

// Define pin numbers for buzzer and LED
const int buzzerPin = 10;  
const int ledPin = 11;

int invalidAttempts = 0;   // Counter for invalid attempts

void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();

  lcd.setCursor(1, 0);
  lcd.print("Enter Password:");

  myServo.attach(A1);  // Attach the servo on analog pin A1 to the servo object
  myServo.write(0);    // Set the servo to 0 degrees (locked position)

  pinMode(buzzerPin, OUTPUT);  // Set buzzer pin as output
  pinMode(ledPin, OUTPUT);     // Set LED pin as output
  digitalWrite(ledPin, LOW);   // Turn off LED by default (initial state)

  Serial.begin(9600);
}

void loop() {
  char key = keypad.getKey();  // Read the key

  // If a key is pressed
  if (key) {
    Serial.print("Key Pressed: ");
    Serial.println(key);
    
    if (key == '#') {  // Check if the entered key is '#'
      if (input == password) {  // Check if the input matches the password
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Access Granted");

        digitalWrite(ledPin, HIGH);  // Turn on LED for correct password
        tone(buzzerPin, 1000);       // Play buzzer sound at 1000 Hz
        myServo.write(90);           // Unlock the door (rotate the servo to 90 degrees)

        delay(5000);                 // Keep the door unlocked for 5 seconds

        myServo.write(0);            // Lock the door again (rotate the servo back to 0 degrees)
        digitalWrite(ledPin, LOW);   // Turn off LED after the door locks
        noTone(buzzerPin);           // Stop buzzer sound

        invalidAttempts = 0;         // Reset invalid attempts on successful access
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Enter Password:");
      } else {
        invalidAttempts++;           // Increment the invalid attempts counter
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Access Denied");

        tone(buzzerPin, 500);        // Play a lower tone for denied access

        delay(2000);                 // Display "Access Denied" for 2 seconds
        noTone(buzzerPin);           // Stop buzzer

        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Enter Password:");

        // If 4 invalid attempts are reached
        if (invalidAttempts >= 4) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Too Many Tries");
          lcd.setCursor(0, 1);
          lcd.print("Buzzer Active!");

          // Activate buzzer continuously
          while (invalidAttempts >= 4) {
            tone(buzzerPin, 1000);  // Continuous buzzer sound
            delay(3000);            // Keep buzzer on for 3 seconds
            noTone(buzzerPin);      // Stop buzzer
            delay(1000);            // 1-second pause between buzzers
          }
        }
      }
      input = "";  // Clear the input
    } else if (key == '*') {
      // Clear the input if '*' is pressed
      input = "";
      lcd.setCursor(0, 1);
      lcd.print("                "); // Clear the second line on the LCD
    } else {
      // Append the key to the input string
      input += key;
      lcd.setCursor(0, 1);
      lcd.print(input);  // Display the input on the LCD
    }
  }
}
