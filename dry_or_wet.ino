#include <Servo.h>

Servo myServo;

const int trigPin = 9;
const int echoPin = 10;
const int moisturePin = A0;

long duration;
int distance;
int moistureValue;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  myServo.attach(6);
  myServo.write(90);
}

void loop() {

  // Ultrasonic Sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance < 15) {

    Serial.println("Object Detected...");
    delay(500); 

    // Check if object is still there
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;

    if (distance < 15) {

      moistureValue = analogRead(moisturePin);

      Serial.print("Moisture Value: ");
      Serial.println(moistureValue);

      if (moistureValue < 1000) {

        Serial.println("Wet Waste");
        myServo.write(0);
        delay(3000);

      } else {

        Serial.println("Dry Waste");
        myServo.write(180);
        delay(3000);

      }

      myServo.write(90);
      delay(1000);
    }
  }

  delay(500);
}
