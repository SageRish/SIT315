#include <Adafruit_NeoPixel.h>


//Define CONSTANT variables to store pins connected to the Sensors, RGB LED and LED Strip
#define LED_COUNT 12
const uint8_t FORCE_SENSOR_PIN = 3;
const uint8_t MOTION_PIN = 2;
const uint8_t LIGHT_SENSOR_PIN = 11;
const uint8_t LED_PIN = 4;
const uint8_t LED_PIN_RED = 5;
const uint8_t LED_PIN_BLUE = 6;
const uint8_t LED_PIN_GREEN = 7;

//Declare the LED Strip
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

//Define CONSTANT variable to store the LED color
const uint32_t LED_COLOR = strip.Color(255, 0, 0);

//Variable for reading the LED current status, initialized to LOW
uint8_t ledState = LOW;

//VARIABLE to store current LED count
uint8_t CUR_LED_COUNT = 0;

//Initialize the program
void setup()
{
  //Prescalar = 256
  //Timer1 Overflow = 31250
  //Time Period = 0.5 second
  //Reset the Timer1 Control Registers
  TCCR1A = 0; // Reset entire TCCR1A to 0 
  TCCR1B = 0; // Reset entire TCCR1B to 0

  TCCR1B |= B00000100; //Set CS12 to 1 so we get prescalar 256
  TIMSK1 |= B00000010; //Enable Timer1 Compare A Match Interrupt

  OCR1A = 31250; //Set the Timer1 Compare A Register to 31250

  //Initialize the LED Strip
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  //Initialize the Motion Sensor pin as an input
  pinMode(MOTION_PIN, INPUT);
  pinMode(FORCE_SENSOR_PIN, INPUT);
  pinMode(LIGHT_SENSOR_PIN, INPUT);

  //Enable the Pin Change Interrupt for the Light Sensor
  PCICR |= B00000001;
  PCMSK0 |= B00001000;

  //Initialize the LED pin as an output
  pinMode(LED_PIN_RED, OUTPUT);
  pinMode(LED_PIN_BLUE, OUTPUT);
  pinMode(LED_PIN_GREEN, OUTPUT);
  //Interupt to toggle the LED
  attachInterrupt(digitalPinToInterrupt(MOTION_PIN), motionCheck, RISING);
  attachInterrupt(digitalPinToInterrupt(FORCE_SENSOR_PIN), forceCheck, RISING);
  //Initialize the Serial Monitor
  Serial.begin(9600);
}

//Function to toggle the LED when motion is detected
void motionCheck()
{
  //Toggle the LED to color green
  analogWrite(LED_PIN_RED,   0);
  analogWrite(LED_PIN_GREEN, 255);
  analogWrite(LED_PIN_BLUE,  0);
  Serial.println("Motion Detected!");
  Serial.println(digitalRead(MOTION_PIN)); //Print the signal from the motion sensor
  strip.clear(); //Clear the LED strip
  strip.show(); //Update the LED strip
  CUR_LED_COUNT = 0; //Reset the LED count to 0
  TCNT1 = 0; //Reset Timer1
  make_timer_faster(); //Make the timer faster when motion is detected
  Serial.println("Timer1 Reset");
}

//Function to toggle the LED when force is detected
void forceCheck()
{
  //Toggle the LED to color red
  analogWrite(LED_PIN_RED,   255);
  analogWrite(LED_PIN_GREEN, 0);
  analogWrite(LED_PIN_BLUE,  0);
  Serial.println("Force Detected!");
  Serial.println(digitalRead(FORCE_SENSOR_PIN)); //Print the signal from the force sensor
  strip.clear(); //Clear the LED strip
  strip.show(); //Update the LED strip
  CUR_LED_COUNT = 0; //Reset the LED count to 0
  TCNT1 = 0; //Reset Timer1
  Serial.println("Timer1 Reset");
}

//Function to toggle the LED when light is detected
ISR(PCINT0_vect)
{
  //Toggle the LED to color blue
  analogWrite(LED_PIN_RED,   0);
  analogWrite(LED_PIN_GREEN, 0);
  analogWrite(LED_PIN_BLUE,  255);
  Serial.println("Light Detected!");
  Serial.println(digitalRead(LIGHT_SENSOR_PIN)); //Print the signal from the light sensor
  strip.clear(); //Clear the LED strip
  strip.show(); //Update the LED strip
  CUR_LED_COUNT = 0; //Reset the LED count to 0
  TCNT1 = 0; //Reset Timer1
  Serial.println("Timer1 Reset"); //Notify that the timer has been reset
}

//Timer interrupt to increase the LED count when the timer overflows
ISR(TIMER1_COMPA_vect){
  CUR_LED_COUNT++; //Increment the LED count
  if(CUR_LED_COUNT > 12){
    CUR_LED_COUNT = 0; //Reset the LED count when it reaches 12
    reset_timer(); //Reset the timer to 0.5 seconds
    strip.clear(); //Clear the LED strip
  }
  else{
  	strip.fill(LED_COLOR, 0, CUR_LED_COUNT); //Fill the LED strip with the LED color for the current LED count
  }
  strip.show(); //Update the LED strip
  TCNT1  = 0; //Reset Timer1
  Serial.print("Timer1 Interrupt Fired. Current LED Count: "); //Print the current LED count and notify that the timer interrupt has fired
  Serial.println(CUR_LED_COUNT);
}

//Function to make the timer faster when motion is detected
void make_timer_faster(){
  cli(); //Disable Interrupts
  TCCR1A = 0; // Reset entire TCCR1A to 0 
  TCCR1B = 0; // Reset entire TCCR1B to 0

  TCCR1B |= B00000011; //Set CS12 and CS10 to 1 so we get prescalar 1024
  TIMSK1 |= B00000010; //Enable Timer1 Compare A Match Interrupt
  sei(); //Enable Interrupts
}

//Function to reset the timer to 0.5 seconds
void reset_timer(){
  cli(); //Disable Interrupts
  TCCR1A = 0; // Reset entire TCCR1A to 0 
  TCCR1B = 0; // Reset entire TCCR1B to 0

  TCCR1B |= B00000100; //Set CS12 to 1 so we get prescalar 256
  TIMSK1 |= B00000010; //Enable Timer1 Compare A Match Interrupt
  sei(); //Enable Interrupts
}

void loop()
{ }