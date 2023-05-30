// This example shows how to read temperature/pressure

#include <Adafruit_DPS310.h>
#include <Servo.h>
#include <SparkFun_TB6612.h>
#include <Wire.h>
#include <Adafruit_MS8607.h>
#include <Adafruit_Sensor.h>

Servo myservo;
//Adafruit_DPS310 dps;
Adafruit_MS8607 ms8607;
// --------------------------Motor Variables
#define BIN1 4
#define PWMB 5
#define BIN2 2
#define STBY 3

const int motorControl = B1;
float motorValue = 1;
float motorInput = 0;

const int offsetB = 1;
Motor motor1 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);
// ---------------------Pressure Variables
//#define DPS310_CS 10
//#define LED_pin 3
#define ON_LED_pin 9
float currentPressure;
float initialPressure = 0;
float extensionPressure = 0.05;

int on = 0;

//----------------------------------Buttons
#define button_pin 6
//#define r_button_pin 3
int button_state = 0;
bool extended = false;
bool retracted = true;

void setup() {
  Serial.begin(115200);
  // while (!Serial) delay(10);

  // Serial.println("Adafruit MS8607 test!");

  // // Try to initialize!
  // if (!ms8607.begin()) {
  //   Serial.println("Failed to find MS8607 chip");
  //   while (1) { delay(10); }
  // }
  // Serial.println("MS8607 Found!");

  // Serial.print("Pressure and Temperature resolution set to ");
  // switch (ms8607.getPressureResolution()) {
  //   case MS8607_PRESSURE_RESOLUTION_OSR_256: Serial.println("256"); break;
  //   case MS8607_PRESSURE_RESOLUTION_OSR_512: Serial.println("512"); break;
  //   case MS8607_PRESSURE_RESOLUTION_OSR_1024: Serial.println("1024"); break;
  //   case MS8607_PRESSURE_RESOLUTION_OSR_2048: Serial.println("2048"); break;
  //   case MS8607_PRESSURE_RESOLUTION_OSR_4096: Serial.println("4096"); break;
  //   case MS8607_PRESSURE_RESOLUTION_OSR_8192: Serial.println("8192"); break;
  // }
  // Serial.println("");
  // //myservo.attach(9);
   pinMode(button_pin, INPUT);
  // pinMode(LED_pin, OUTPUT);
  // pinMode(ON_LED_pin, OUTPUT);


  // sensors_event_t temp_event, pressure_event;
  // dps.getEvents(&temp_event,&pressure_event);
  // initialPressure = pressure_event.pressure;
}

void loop() {
  // sensors_event_t temp, pressure, humidity;
   button_state = digitalRead(button_pin);
  // ms8607.getEvent(&pressure, &temp, &humidity);
  // digitalWrite(ON_LED_pin, HIGH);

  // on = digitalRead(ON_LED_pin);
  // if(on == HIGH){
  //   Serial.println("on");
  // }
  // else{
  //   Serial.println("low");
  // }

  // Serial.print("Button State: ");
  // Serial.println(button_state);

  //------------------------------Motor Control Code
  //if (retracted) {
    // Serial.println("Retracted?: ");
    Serial.println(button_state);
    if (button_state == HIGH) {
      delay(100);
      while (button_state == HIGH) {
        button_state = digitalRead(button_pin);
        // Serial.println(":)");
        //Serial.print("button state: ");
        Serial.println(button_state);
        motor1.drive(255);
      }
      retracted = false;
      extended = true;
    } else {
      motor1.brake();
    }
  // } else {
  //   Serial.println("Extended?: ");
  //   if (button_state == HIGH) {
  //     delay(100);
  //     while (button_state == HIGH) {
  //       button_state = digitalRead(button_pin);
  //       motor1.drive(-255);
  //       //Serial.println("--------------");
  //     }
  //     extended = false;
  //     retracted = true;
  //   } else {
  //     motor1.brake();
  //   }
  // }
  // ---------------------------------------------- Pressure Sensing
  //dps.getEvents(&temp_event, &pressure_event);
  float psi_pressure = pressure.pressure * 0.0145 - 14.7;  //14.7 is atm
  Serial.print(pressure.pressure);
  Serial.print("   psi:");
  Serial.println(psi_pressure);


  // Serial.println();
  // currentPressure = psi_pressure;  // reads the value of the potentiometer (value between 0 and 1023)
  // //currentPressure = map(currentPressure, 1015, 1150, 0, 180);     // scale it for use with the servo (value between 0 and 180)
  // if (currentPressure > extensionPressure) {
  //   Serial.println("hello");
  //   digitalWrite(LED_pin, LOW);
  // } else {
  //   Serial.println("bye");
  //   digitalWrite(LED_pin, HIGH);
  // }
  // motor1.drive(250);
  // delay(5000);
  // motor1.drive(-250);
  // delay(5000);
  // motor1.brake();
  // e_button_state = digitalRead(e_button_pin);
  // if(e_button_state ==HIGH)
  // {
  //   myservo.write(60);
  // }
  // else{
  //   myservo.write(0);
  // }
  // Serial.println(e_button_state);*/
  /*
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
*/
}
