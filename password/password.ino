#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>  // Include the Servo library

// Define LCD address and create object
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Set up the Servo object
Servo myServo;  

// Define the rows and columns for the keypad
const byte ROWS = 4; 
const byte COLS = 4; 

// Define the keymap
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Connect to the row and column pinouts of the keypad
byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

// Create an object of the Keypad class
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String password = "1234";  // Set your password
String input = "";         // Store the input password

void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();

  lcd.setCursor(1, 0);
  lcd.print("Enter Password:");

  myServo.attach(10);  // Attach the servo on pin 10 to the servo object
  myServo.write(0);    // Set the servo to 0 degrees (locked position)

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
        myServo.write(90);  // Unlock the door (rotate the servo to 90 degrees)
        delay(5000);        // Keep the door unlocked for 5 seconds
        myServo.write(0);   // Lock the door again (rotate the servo back to 0 degrees)
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Enter Password:");
      } else {
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Access Denied");
        delay(2000);        // Display "Access Denied" for 2 seconds
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Enter Password:");
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
