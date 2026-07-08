#include <Arduino.h>

// pins
// left motor
const int MOTOR_LEFT_PWM  = 4;  // Speed control
const int MOTOR_LEFT_IN1  = 5;  // Direction pin 1
const int MOTOR_LEFT_IN2  = 6;  // Direction pin 2

// right motor
const int MOTOR_RIGHT_PWM = 7;  // Speed control
const int MOTOR_RIGHT_IN1 = 8;  // Direction pin 1
const int MOTOR_RIGHT_IN2 = 9;  // Direction pin 2

// ultrasonic
const int TRIG_LEFT   = 10;
const int ECHO_LEFT   = 11;
const int TRIG_MID    = 12;
const int ECHO_MID    = 13;
const int TRIG_RIGHT  = 14;
const int ECHO_RIGHT  = 15;

unsigned long lastTelemetryTime = 0;
const unsigned long TELEMETRY_INTERVAL = 50; // Send sensor data every 50ms (20Hz)

// hold incoming command
String inputString = "";

float readDistance(int trigPin, int echoPin);
void setMotorSpeed(int pwmPin, int in1, int in2, int targetSpeed);
void parseLaptopCommand(String command);

void setup() {
    Serial.begin(115200);
    inputString.reserve(64);

    pinMode(MOTOR_LEFT_PWM, OUTPUT);
    pinMode(MOTOR_LEFT_IN1, OUTPUT);
    pinMode(MOTOR_LEFT_IN2, OUTPUT);
    pinMode(MOTOR_RIGHT_PWM, OUTPUT);
    pinMode(MOTOR_RIGHT_IN1, OUTPUT);
    pinMode(MOTOR_RIGHT_IN2, OUTPUT);

    pinMode(TRIG_LEFT, OUTPUT);
    pinMode(ECHO_LEFT, INPUT);
    pinMode(TRIG_MID, OUTPUT);
    pinMode(ECHO_MID, INPUT);
    pinMode(TRIG_RIGHT, OUTPUT);
    pinMode(ECHO_RIGHT, INPUT);

    // stop
    setMotorSpeed(MOTOR_LEFT_PWM, MOTOR_LEFT_IN1, MOTOR_LEFT_IN2, 0);
    setMotorSpeed(MOTOR_RIGHT_PWM, MOTOR_RIGHT_IN1, MOTOR_RIGHT_IN2, 0);
}

void loop() {
    unsigned long currentTime = millis();

    // send telemetry
    if (currentTime - lastTelemetryTime >= TELEMETRY_INTERVAL) {
        lastTelemetryTime = currentTime;

        float distLeft  = readDistance(TRIG_LEFT, ECHO_LEFT);
        float distMid   = readDistance(TRIG_MID, ECHO_MID);
        float distRight = readDistance(TRIG_RIGHT, ECHO_RIGHT);

        // usb format S,left,mid,right
        Serial.print("S,");
        Serial.print(distLeft, 1);
        Serial.print(",");
        Serial.print(distMid, 1);
        Serial.print(",");
        Serial.println(distRight, 1);
    }

    // interp command
    while (Serial.available()) {
        char inChar = (char)Serial.read();
        if (inChar == '\n') {
            parseLaptopCommand(inputString);
            inputString = ""; // done
        } else {
            inputString += inChar;
        }
    }
}


float readDistance(int trigPin, int echoPin) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH, 20000);

    if (duration == 0) return 400.0; // no echo
    return (duration * 0.0343) / 2.0; // cm
}


void setMotorSpeed(int pwmPin, int in1, int in2, int targetSpeed) {
    targetSpeed = constrain(targetSpeed, -255, 255);

    if (targetSpeed > 0) {
        //fwd
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        analogWrite(pwmPin, targetSpeed);
    } else if (targetSpeed < 0) {
        //back
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        analogWrite(pwmPin, abs(targetSpeed));
    } else {
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        analogWrite(pwmPin, 0);
    }
}

// M,leftSpeed,rightSpeed
void parseLaptopCommand(String command) {
    command.trim();
    if (command.length() == 0) return;

    if (command.charAt(0) == 'M') {
        int firstComma = command.indexOf(',');
        int secondComma = command.indexOf(',', firstComma + 1);

        if (firstComma != -1 && secondComma != -1) {
            String leftStr = command.substring(firstComma + 1, secondComma);
            String rightStr = command.substring(secondComma + 1);

            int leftSpeed = leftStr.toInt();
            int rightSpeed = rightStr.toInt();

            setMotorSpeed(MOTOR_LEFT_PWM, MOTOR_LEFT_IN1, MOTOR_LEFT_IN2, leftSpeed);
            setMotorSpeed(MOTOR_RIGHT_PWM, MOTOR_RIGHT_IN1, MOTOR_RIGHT_IN2, rightSpeed);
        }
    }
}
