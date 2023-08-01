//Define CONSTANT variables to store pins connected to Button and LED
const uint8_t MOTION_PIN = 2;
const uint8_t LED_PIN = 13;

//Variable for reading the LED current status, initialized to LOW
uint8_t ledState = LOW;

//Initialize the program
void setup()
{
  //Initialize the pushbutton pin as an input
  pinMode(MOTION_PIN, INPUT);
  //Initialize the LED pin as an output
  pinMode(LED_PIN, OUTPUT);
  //Interupt to toggle the LED
  attachInterrupt(digitalPinToInterrupt(MOTION_PIN), motionCheck, CHANGE);
  //Initialize the Serial Monitor
  Serial.begin(9600);
}

//Function to toggle the LED when the button is pressed
void motionCheck()
{
  //Toggle the LED
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState);
  Serial.println("Motion Detected!");
  Serial.println(digitalRead(MOTION_PIN));
}

void loop()
{ }