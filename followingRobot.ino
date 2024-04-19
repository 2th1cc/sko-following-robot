  
  #include <Servo.h>

  int leftMotorPin = 3;
  int rightMotorPin = 2;

  long durationForward;
  long distanceForward;

  long durationLeft;
  long distanceLeft;

  long durationRight;
  long distanceRight;

  long minDistance;

  unsigned long prevUltrasonicMillis = 0; // Stores the last time the ultrasonic was triggered
  unsigned long ultrasonicInterval = 50; // Interval at which to take ultrasonic measurements (2 seconds)

  const int trigPinForward = 10;
  const int echoPinForward = 11;

  const int trigPinLeft = 6;
  const int echoPinLeft = 7;

  const int trigPinRight = 8;
  const int echoPinRight = 9;

  Servo leftMotor;
  Servo rightMotor;

  void ultrasonicForward(){
    // Ultrasonic
    digitalWrite(trigPinForward, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinForward, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinForward, LOW);
    durationForward = pulseIn(echoPinForward, HIGH);
    distanceForward = durationForward * 0.034 / 2;
    Serial.print ("DISTANCE Forward: ");
    Serial.println (distanceForward);
  }
  void ultrasonicLeft(){
    // Ultrasonic
    digitalWrite(trigPinLeft, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPinLeft, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigPinLeft, LOW);
    durationLeft = pulseIn(echoPinLeft, HIGH);
    distanceLeft = durationLeft * 0.034 / 2 + 7;

    Serial.print ("DISTANCE Left: ");
    Serial.println (distanceLeft);
  }
  void ultrasonicRight(){
    // Ultrasonic
    digitalWrite(trigPinRight, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPinRight, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigPinRight, LOW);
    durationRight = pulseIn(echoPinRight, HIGH);
    distanceRight = durationRight * 0.034 / 2 + 7;

    Serial.print ("DISTANCE Right: ");
    Serial.println (distanceRight);
  }
  void setup() {
    // Attach the motors to their respective pins
    leftMotor.attach(leftMotorPin);
    rightMotor.attach(rightMotorPin);
    // Ulttrasonic
    pinMode(trigPinForward, OUTPUT);
    pinMode(echoPinForward, INPUT);

    pinMode(trigPinLeft, OUTPUT);
    pinMode(echoPinLeft, INPUT);

    pinMode(trigPinRight, OUTPUT);
    pinMode(echoPinRight, INPUT);

    Serial.begin(115200);
  }
  void loop() {
    unsigned long currentMillis = millis();
    minDistance = min(distanceRight,min(distanceForward, distanceLeft));

    if(minDistance <= 45 && minDistance > 15){
      if(distanceRight==distanceLeft || distanceLeft == distanceForward || distanceRight==distanceForward){
        leftMotorControl(50);
        rightMotorControl(50);
      }
      if(minDistance==distanceForward){
        leftMotorControl(100);
        rightMotorControl(100);
      }
      if(minDistance==distanceLeft){
        leftMotorControl(0);
        rightMotorControl(50);
      }
      if(minDistance==distanceRight){
        leftMotorControl(50);
        rightMotorControl(0);
      }
      } else if(minDistance <= 15){
        leftMotorControl(0);
        rightMotorControl(0);
    }
    else {
      leftMotorControl(0);
      rightMotorControl(50); }

    // Ultrasonic measurement with non-blocking delay
    if (currentMillis - prevUltrasonicMillis >= ultrasonicInterval) {
      prevUltrasonicMillis = currentMillis; // Save the last time you triggered the ultrasonic sensor
      ultrasonicForward(); // Trigger ultrasonic measurement
      ultrasonicLeft();
      ultrasonicRight();
    }
  }

  void leftMotorControl(int value) {
    // Map the input value to the corresponding pulse width and control the motor
    leftMotor.writeMicroseconds(map(value, -100, 100, 1000, 2000));
  }

  void rightMotorControl(int value) {
    // Map the input value to the corresponding pulse width and control the motor
    rightMotor.writeMicroseconds(map(value, -100, 100, 1000, 2000));
  }