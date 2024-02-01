const int BUTTON_PIN = 2;            // Choose a pin that supports interrupts (interrupt 0)
const int LED_PIN = 3;                // the number of the LED pin
const int LIGHT_SENSOR_PIN = A0;      // the number of the light sensor pin

volatile int buttonState = HIGH;      // variable for reading the pushbutton status
volatile int lightSensorValue = 0;    // variable for reading the light sensor value
volatile bool ledState = LOW;         // variable to store the LED state

void handleInterrupt() {
  // Read the state of the pushbutton value
  buttonState = digitalRead(BUTTON_PIN);

  // Read the light sensor value
  lightSensorValue = analogRead(LIGHT_SENSOR_PIN);

  // Control LED according to the state of button and light sensor
  if (buttonState == LOW) {
    // If the button is pressed, toggle the LED state
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
    Serial.println(ledState ? "LED turned on" : "LED turned off");

    if (ledState == HIGH && lightSensorValue > 500) {
      ledState = LOW;
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED turned on after button press in low light");
    }
  } else {
    // If the button is not pressed, maintain LED state if light is low
    if (ledState == HIGH && lightSensorValue < 500) {
      digitalWrite(LED_PIN, HIGH);
    }
  }
}

void setup() {
  // Initialize the LED pin as an output
  pinMode(LED_PIN, OUTPUT);

  // Initialize the pushbutton pin as an input with pull-up resistor
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Initialize the light sensor pin as an input
  pinMode(LIGHT_SENSOR_PIN, INPUT);

  // Initialize serial communication
  Serial.begin(9600);

  // Attach the interrupt to the handleInterrupt function
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleInterrupt, CHANGE);
}

void loop() {
  // The loop is empty as the functionality is handled in the interrupt service routine
}
