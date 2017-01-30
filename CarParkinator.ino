
// Car Parkinator 2.3

#include <EEPROM.h>

#define debug false

const int redLED = 5;         // Red LED, pin 5
const int greenLED = 6;        // Green LED, pin 7
const int yellowLED = 7;       // Yellow LED, pin 6
const int echoPin = 8;        // Echo, pin 8
const int triggerPin = 9;     // Trigger, pin 9
const int buttonPin = 11;       // Button, pin 11 (blue wire)

int stop = 24;                 // Default stop distance of 24 inches
int warning = 12;              // Define the warning distance
int buttonState = 0;           // Tracks the state of the button

long duration;         // Define duration and inches variables
int inches; // Define variable for inches

void setup() {
  
  if(debug) Serial.begin (9600); // Serial monitor for development
  
  // Define inputs and outputs
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buttonPin, INPUT);

  if (EEPROM.read(0) != 24) {
   stop = EEPROM.read(0);
  }

}

void getDistance() {
  digitalWrite(triggerPin, LOW); // Send a short LOW pulse to ensure a clean HIGH pulse
  delayMicroseconds(5);
  digitalWrite(triggerPin, HIGH); // Trigger the rangefinder
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW); 

  duration = pulseIn(echoPin, HIGH); // Measure the reply pulse from the rangefinder

  inches = (duration/2) / 74;   // Convert the time into a distance
}

void confirmSetting(){
   digitalWrite(greenLED, HIGH); // LEDs ON
   digitalWrite(yellowLED, HIGH);
   digitalWrite(redLED, HIGH);
   delay(250);
   digitalWrite(greenLED, LOW); // LEDs OFF
   digitalWrite(yellowLED, LOW);
   digitalWrite(redLED, LOW);
   delay(250);
}

void loop() {
  // Watch the button for a press, and set the distance
  
  buttonState = digitalRead(buttonPin); // Check the state of the botton and store it

  if (buttonState == HIGH) { // If the button is pressed, set the new stop distance
    getDistance();
    stop = inches; // Copy current distance to stop distance
    EEPROM.write(0,stop); // Save new setting to EEPROM
   
    confirmSetting(); // Blink the LEDs 3 times to confirm save
    confirmSetting();
    confirmSetting();
    
    // Serial monitor for development
    if(debug)
    {
      Serial.print("Button pressed! Now set to "); // Print to serial, so I can see what is happening
      Serial.print(inches);
      Serial.print(" inches.");
      Serial.println();

      Serial.print("Read from EEPROM is "); // Print to serial, so I can see what is happening
      Serial.print(EEPROM.read(0));
      Serial.println();
    }
    
    
  }

  else { // If the button isn't pressed, check the distance
  
    getDistance();
  
    // Serial monitor for development
    if(debug)
    {
    Serial.print(inches);
    Serial.print(" inches");
    Serial.println();
    }
 
  
    // Logic to decide which LED to light.
    
    if (inches <= stop) {
        digitalWrite(greenLED, LOW); 
        digitalWrite(yellowLED, LOW);
        digitalWrite(redLED, HIGH);   // Red LED ON
    }
  
    if ((inches > stop) && (inches <= stop + warning)) {
        digitalWrite(greenLED, LOW);
        digitalWrite(yellowLED, HIGH); // Yellow LED ON
        digitalWrite(redLED, LOW);
    }
  
    if (inches > stop + warning) {
        digitalWrite(greenLED, HIGH); // Green LED ON
        digitalWrite(yellowLED, LOW);
        digitalWrite(redLED, LOW);
    }

  }

  delay(250); // Short delay to keep the LED from bouncing around

}
