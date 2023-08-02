//Define CONSTANT variables to store pins connected to Motion Sensor, Force Sensor and RGB LED
const uint8_t FORCE_SENSOR_PIN = 3;
const uint8_t MOTION_PIN = 2;
const uint8_t LED_PIN_RED = 5;
const uint8_t LED_PIN_BLUE = 6;
const uint8_t LED_PIN_GREEN = 9;

//Variable for reading the LED current status, initialized to LOW
uint8_t ledState = LOW;

//Initialize the program
void setup()
{
  //Initialize the Motion Sensor pin as an input
  pinMode(MOTION_PIN, INPUT);
  //Initialize the RGB LED pin as an output
  pinMode(LED_PIN_RED, OUTPUT);
  pinMode(LED_PIN_BLUE, OUTPUT);
  pinMode(LED_PIN_GREEN, OUTPUT);
  //Interupt to toggle the LED when motion is detected
  attachInterrupt(digitalPinToInterrupt(MOTION_PIN), motionCheck, CHANGE);
  //Interupt to toggle the LED when force is detected
  attachInterrupt(digitalPinToInterrupt(FORCE_SENSOR_PIN), forceCheck, CHANGE);
  //Initialize the Serial Monitor
  Serial.begin(9600);
}

//Function to toggle the LED when motion is detected
void motionCheck()
{
  //Toggle the LED Green
  analogWrite(LED_PIN_RED,   0);
  analogWrite(LED_PIN_GREEN, 255);
  analogWrite(LED_PIN_BLUE,  0);
  Serial.println("Motion Detected!");
  Serial.println(digitalRead(MOTION_PIN));
}

//Function to toggle the LED when force is detected
void forceCheck()
{
  //Toggle the LED Red
  analogWrite(LED_PIN_RED,   255);
  analogWrite(LED_PIN_GREEN, 0);
  analogWrite(LED_PIN_BLUE,  0);
  Serial.println("Force Detected!");
  Serial.println(digitalRead(FORCE_SENSOR_PIN));
}

void loop()
{ }