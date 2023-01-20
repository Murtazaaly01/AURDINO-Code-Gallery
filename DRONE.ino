#include <Servo.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

// Remote control pins
#define THROTTLE_PIN 9
#define YAW_PIN 6
#define PITCH_PIN 5
#define ROLL_PIN 3

// Motor pins
#define MOTOR_1_PIN 10
#define MOTOR_2_PIN 11
#define MOTOR_3_PIN 6
#define MOTOR_4_PIN 5

// Sensor
Adafruit_BNO055 bno = Adafruit_BNO055();

// Remote control variables
int throttle, yaw, pitch, roll;

// Motor variables
int motor1Speed, motor2Speed, motor3Speed, motor4Speed;

// Servo objects
Servo motor1, motor2, motor3, motor4;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize sensor
  bno.begin();

  // Initialize remote control pins
  pinMode(THROTTLE_PIN, INPUT);
  pinMode(YAW_PIN, INPUT);
  pinMode(PITCH_PIN, INPUT);
  pinMode(ROLL_PIN, INPUT);

  // Initialize motor pins
  pinMode(MOTOR_1_PIN, OUTPUT);
  pinMode(MOTOR_2_PIN, OUTPUT);
  pinMode(MOTOR_3_PIN, OUTPUT);
  pinMode(MOTOR_4_PIN, OUTPUT);

  // Attach servo objects to motor pins
  motor1.attach(MOTOR_1_PIN);
  motor2.attach(MOTOR_2_PIN);
  motor3.attach(MOTOR_3_PIN);
  motor4.attach(MOTOR_4_PIN);
}

void loop() {
  // Read remote control values
  throttle = analogRead(THROTTLE_PIN);
  yaw = analogRead(YAW_PIN);
  pitch = analogRead(PITCH_PIN);
  roll = analogRead(ROLL_PIN);

  // Read sensor values
  sensors_event_t event;
  bno.getEvent(&event);

  // Calculate motor speeds based on sensor and remote control values
  motor1Speed = throttle + yaw - pitch + roll;
  motor2Speed = throttle - yaw - pitch - roll;
  motor3Speed = throttle - yaw + pitch + roll;
  motor4Speed = throttle + yaw + pitch - roll;

  // Constrain motor speeds to be between 0 and 180
  motor1Speed = constrain(motor1Speed, 0, 180);
  motor2Speed = constrain(motor2Speed, 0, 180);
  motor3Speed = constrain(motor3Speed, 0, 180);
  motor4Speed = constrain(motor4Speed, 0, 180);

    // Set motor speeds
  motor1.write(motor1Speed);
  motor2.write(motor2Speed);
  motor3.write(motor3Speed);
  motor4.write(motor4Speed);
}
