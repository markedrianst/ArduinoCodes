#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>
#include <avr/wdt.h>

// Define LCD address and create object
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Set up the Servo object
Servo myServo;

// Define RFID pins
#define RST_PIN 4    // Reset pin connected to analog pin 4
#define SS_PIN 10    // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

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

// Define the buzzer, green LED, and red LED pins
const int buzzerPin = A1; // Buzzer connected to analog pin A1
const int greenLedPin = A2; // Green LED connected to analog pin A2
const int redLedPin = A3; // Red LED connected to analog pin A3

// Track invalid attempts
int invalidAttempts;
const int maxAttempts = 4;
int holder ;

void setup()
{
 
    myServo.attach(A0);  // Attach the servo on analog pin A0 to the servo object
    myServo.write(0);    // Set the servo to 0 degrees (locked position)
   // wdt_enable(WDTO_1S);  
    pinMode(buzzerPin, OUTPUT); // Set the buzzer pin as output
    pinMode(greenLedPin, OUTPUT); // Set the green LED pin as output
    pinMode(redLedPin, OUTPUT); // Set the red LED pin as output

    // Turn on the red LED at idle
    digitalWrite(redLedPin, LOW);
      lcd.noBacklight();
    Serial.begin(9600);

    SPI.begin();                    // Initialize the SPI bus
    mfrc522.PCD_Init();             // Initialize the MFRC522
    delay(4);                       // Optional delay
}

void loop()
{

    if(invalidAttempts>=maxAttempts) {
        beepBuzzer();
        Serial.println(invalidAttempts);

    } else {

        if (checkRFIDCard()) {
            checkRFIDCard();
            

        } else if (handlePasswordEntry()) {
            handlePasswordEntry();
        }
    }

    Serial.println("Sheesh");
   
    delay(5);
}

bool checkRFIDCard()
{
    // Check if a new card is present
    if (mfrc522.PICC_IsNewCardPresent()) {
        // Check if card can be read
        if (mfrc522.PICC_ReadCardSerial()) {
            // Card detected and successfully read
            Serial.print("Card detected! UID: ");
            String cardUID = ""; // Variable to store the UID

            for (byte i = 0; i < mfrc522.uid.size; i++) {
                cardUID += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "") + String(mfrc522.uid.uidByte[i], HEX);
            }

            // Convert UID to uppercase for consistent comparison
            cardUID.toUpperCase();

            Serial.println(cardUID); // Print the UID

            // Check if the UID is valid or invalid
            if (cardUID == "82E6021E") {
                Serial.println("Valid card!");

                digitalWrite(buzzerPin, HIGH);
                delay(50);
                digitalWrite(buzzerPin, LOW);
                input="";
                int holder =0;
                invalidAttempts = holder;
                Serial.println("reset");
                delay(5);
                unlockDoor();

                return false;
            } else if (cardUID == "50B0881A") {
                Serial.println("Invalid card!");
                beepBuzzer();
                accessD();
                return false;

            } else {
                Serial.println("Unknown card!");

            }

            // Halt PICC (stop communication) and prepare for the next card
            mfrc522.PICC_HaltA();
            mfrc522.PCD_StopCrypto1();
        }

    }
    return false;
}

bool handlePasswordEntry()
{
    char key = keypad.getKey();  // Read the key

    // If a key is pressed
    if (key) {
        tone(buzzerPin, 1000, 100); // Play a short beep
        Serial.print("Key Pressed: ");
        Serial.println(key);
        
        

        if (key == '#') {  // Check if the entered key is '#'
            if (input == password) {  // Check if the input matches the password
                Serial.println("Access Granted!");
              
                unlockDoor(); // Unlock the door
                return false;
                // Reset state
                // Reset invalid attempts
                holder =0;
                invalidAttempts = holder;
            } else {
                Serial.println("Access Denied!");
                invalidAttempts++;
                digitalWrite(redLedPin, HIGH);
                
                delay(500);
                digitalWrite(redLedPin, LOW);
                return false;
            }
            input = "";  // Clear the input
        } else if (key == '*') {
            // Clear the input if '*' is pressed
            input = "";
        } else {
            // Add the pressed key to the input string
            input += key;
        }
    }
    return false;
}

bool beepBuzzer()
{
    const int beepCount = 5; // Number of beeps for the alarm
    const int beepDuration = 100; // Duration of each beep in milliseconds
    const int pauseDuration = 50; // Pause duration between beeps in milliseconds
    if (checkRFIDCard()) {
        stopBuzzer();
    } else {
        for (int i = 0; i < beepCount; i++) {
            digitalWrite(buzzerPin, HIGH); // Turn on the
            digitalWrite(redLedPin, HIGH);
            delay(beepDuration);             // Beep duration
            digitalWrite(buzzerPin, LOW);
            digitalWrite(redLedPin, LOW);  // Turn off the buzzer
            delay(pauseDuration);            // Wait before the next beep
        }
    }
}

void stopBuzzer()
{
    digitalWrite(buzzerPin, LOW); // Ensure you replace buzzerPin with the actual pin number for the buzzer.
}

void accessD(){

    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("Access Denied");
    delay(2000);
    lcd.noBacklight();
    
    wdt_enable(WDTO_1S);  // Enable Watchdog Timer for 1 second timeout

    while (2);


}
void unlockDoor()
{
    myServo.write(90);  // Unlock the door (rotate the servo to 90 degrees)
    digitalWrite(greenLedPin, HIGH); // Turn on the green LED
    digitalWrite(redLedPin, LOW);     // Turn off the red LED
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("Access Granted");
    delay(5000);        // Keep the door unlocked for 5 seconds
    myServo.write(0);   // Lock the door again (rotate the servo back to 0 degrees)
    digitalWrite(greenLedPin, LOW);  // Turn off the green LED
   
    wdt_enable(WDTO_1S);  // Enable Watchdog Timer for 1 second timeout

    while (1);

}