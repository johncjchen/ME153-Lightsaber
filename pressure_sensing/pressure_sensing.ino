// This example shows how to read temperature/pressure

#include <Adafruit_DPS310.h>
#include <Servo.h> 
#include <SparkFun_TB6612.h>

Servo myservo;
//Adafruit_DPS310 dps;

// --------------------------Motor Variables
#define AIN1 4
#define PWMA 6
#define AIN2 5
#define STBY 7

const int motorControl = A1;
float motorValue = 1;
float motorInput = 0;

const int offsetA = 1;
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
// ---------------------Pressure Variables 
#define DPS310_CS 10
float currentPressure; 
float base_pressure = 1015;
float extension_pressure = 1150;
//float deflation_pressure = 0;
//----------------------------------Buttons 
#define e_button_pin 2
#define r_button_pin 3
int e_button_state = 0;
int r_button_state = 0;
bool extended = false; 
bool retracted = false; 

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  Serial.println("DPS310");
  if (! dps.begin_I2C()) {             // Can pass in I2C address here
  //if (! dps.begin_SPI(DPS310_CS)) {  // If you want to use SPI
    Serial.println("Failed to find DPS");
    while (1) yield();
  }
  Serial.println("DPS OK!");

  dps.configurePressure(DPS310_64HZ, DPS310_64SAMPLES);
  dps.configureTemperature(DPS310_64HZ, DPS310_64SAMPLES);

  myservo.attach(9);
  pinMode(e_button_pin, INPUT);
  pinMode(r_button_pin, INPUT);
}

void loop() {
  sensors_event_t temp_event, pressure_event;
  while (!dps.temperatureAvailable() || !dps.pressureAvailable()) {
    return; // wait until there's something to read
  }

  dps.getEvents(&temp_event,&pressure_event);
  Serial.print(pressure_event.pressure);
  //Serial.println(" hPa"); 

  Serial.println();
  currentPressure = pressure_event.pressure;         // reads the value of the potentiometer (value between 0 and 1023)
  //currentPressure = map(currentPressure, 1015, 1150, 0, 180);     // scale it for use with the servo (value between 0 and 180)
  if(currentPressure > basePressure && currentPressure < extendedpressure){
    // myservo.write(150);                  // sets the servo position according to the scaled value
    // delay(15);
    Serial.println("hello");
  }
  else{}
  // motor1.drive(250);
  // delay(5000);
  // motor1.drive(-250);
  // delay(5000);
  // motor1.brake();
  e_button_state = digitalRead(e_button_pin);
  if(e_button_state ==HIGH)
  {
    myservo.write(60);
  }
  else{
    myservo.write(0);
  }
  Serial.println(e_button_state);

//---------------- Motor Control Code
  motorInput = analogRead(motorControl);
  //Serial.println(motorInput);

//---------------- Forwards/backwards based on value from potentiometer
  if (-1 <= motorInput && motorInput<= 399){
    motorValue = 1*(motorInput/400)*255;
    motor1.drive(-255, 100); //-255 if potentiometer is within first 1/3
   // Serial.println(motorValue);
  }

  else if (400 <= motorInput && motorInput <= 624){
    motor1.brake(); //stops motor when poteniometer is at middle
   // Serial.println("Brake");
  }

  else if (625 <= motorInput && motorInput <= 1025){
    motorValue = 1*(motorInput-624)/400*255;
    motor1.drive(255, 100); //255 if potentiometer is within last 1/3
    //Serial.println(motorValue);
  }

}
