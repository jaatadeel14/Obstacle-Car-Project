#define in1 5  // L298n Motor Driver pins.
#define in2 4
#define in3 3
#define in4 2
#define ena 10 // Enable pin for the left motor
#define enb 9  // Enable pin for the right motor
#define LED 13
#define LDR A1

#define trigPinRight 12 // Trig pin for the left ultrasonic sensor
#define echoPinRight 13 // Echo pin for the left ultrasonic sensor
#define trigPinCenter 8 // Trig pin for the center ultrasonic sensor
#define echoPinCenter 11 // Echo pin for the center ultrasonic sensor
#define trigPinLeft 7 // Trig pin for the right ultrasonic sensor
#define echoPinLeft 6 // Echo pin for the right ultrasonic sensor

int command; // Int to store app command state.
int Speed = 180; // 0 - 255.
int Speedsec;
int buttonState = 0;
int lastButtonState = 0;
int Turnradius = 0; // Set the radius of a turn, 0 - 255 Note: the robot will malfunction if this is higher than int Speed.
int brakeTime = 45;
int brkonoff = 1; // 1 for the electronic braking system, 0 for normal.
bool manual = true;
int isik = 800;
bool karanlik = false;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(LED, OUTPUT); // Set the LED pin.
  
  pinMode(trigPinLeft, OUTPUT);
  pinMode(echoPinLeft, INPUT);
  pinMode(trigPinCenter, OUTPUT);
  pinMode(echoPinCenter, INPUT);
  pinMode(trigPinRight, OUTPUT);
  pinMode(echoPinRight, INPUT);

  Serial.begin(9600);  // Set the baud rate to your Bluetooth module.
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.read();
    switch (command) {
      case 'F':
        forward();
        break;
      case 'B':
        back();
        break;
      case 'L':
        left();
        break;
      case 'R':
        right();
        break;
      case 'G':
        forwardleft();
        break;
      case 'I':
        forwardright();
        break;
      case 'H':
        backleft();
        break;
      case 'J':
        backright();
        break;
      case '0':
        Speed = 100;
        break;
      case '1':
        Speed = 140;
        break;
      case '2':
        Speed = 153;
        break;
      case '3':
        Speed = 165;
        break;
      case '4':
        Speed = 178;
        break;
      case '5':
        Speed = 191;
        break;
      case '6':
        Speed = 204;
        break;
      case '7':
        Speed = 216;
        break;
      case '8':
        Speed = 229;
        break;
      case '9':
        Speed = 242;
        break;
      case 'q':
        Speed = 255;
        break;
      case 'P':
        Serial.println("Hello World!");
        break;
      case 'T':
        manual = false; // Toggle manual mode
        karanlik = false;
        break;
      case 'C':
        karanlik = false;
        break;
      case 'X':
        manual = true; // Toggle manual mode

        Stop();
        break;
    }
    Speedsec = Turnradius;
    if (brkonoff == 1) {
      brakeOn();
    } else {
      brakeOff();
    }
  }

  if (!manual) {
    automaticBehavior();
    isik = analogRead(LDR);
    if(isik < 290 && !karanlik){
        delay(5000);
        karanlik = true;
        //Serial.println("Karanlik");
      }
  }
}

void forward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(ena, Speed);
  analogWrite(enb, Speed);
}

void back() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(ena, Speed);
  analogWrite(enb, Speed);
}

void right() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(ena, Speed);
  analogWrite(enb, Speed);
}

void left() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(ena, Speed);
  analogWrite(enb, Speed);
}

void forwardleft() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(ena, Speedsec);
  analogWrite(enb, Speed);
}

void forwardright() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(ena, Speed);
  analogWrite(enb, Speedsec);
}

void backleft() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(ena, Speedsec);
  analogWrite(enb, Speed);
}

void backright() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(ena, Speed);
  analogWrite(enb, Speedsec);
}

void Stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(ena, 0);
  analogWrite(enb, 0);
}

void brakeOn() {
  buttonState = command;
  if (buttonState != lastButtonState) {
    if (buttonState == 'S') {
      if (lastButtonState != buttonState) {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, HIGH);
        delay(brakeTime);
        Stop();
      }
    }
    lastButtonState = buttonState;
  }
}

void brakeOff() {
  // Future implementation
}

void automaticBehavior1() {
  // Read distances from ultrasonic sensors
  int distanceLeft = readUltrasonic(trigPinLeft, echoPinLeft);
  int distanceCenter = readUltrasonic(trigPinCenter, echoPinCenter);
  int distanceRight = readUltrasonic(trigPinRight, echoPinRight);

  // Check for obstacles and adjust movement
  if (distanceCenter < 30) {
    Stop();
    if (distanceLeft > distanceRight) {
      left();
    } else {
      right();
    }
  } else {
    forward();
  }
}

void automaticBehavior() {
  // Read distances from ultrasonic sensors
  int distanceLeft = readUltrasonic(trigPinLeft, echoPinLeft);
  int distanceCenter = readUltrasonic(trigPinCenter, echoPinCenter);
  int distanceRight = readUltrasonic(trigPinRight, echoPinRight);

  // Check for obstacles and stop if needed
  if (distanceCenter < 20) {
    Stop();
    delay(500); // Small delay to ensure the stop is effective
    back();
    delay(100);
    // Reassess distances after stopping
    distanceLeft = readUltrasonic(trigPinLeft, echoPinLeft);
    distanceCenter = readUltrasonic(trigPinCenter, echoPinCenter);
    distanceRight = readUltrasonic(trigPinRight, echoPinRight);
    
    // Determine direction based on the distances
    
    if (distanceLeft > distanceRight) {
      left();
      delay(600); // Allow time for turning
      Stop();
    } else {
      right();
      delay(600); // Allow time for turning
      Stop();
    }
  }else{
    if(distanceLeft > 20 && distanceRight < 15){
        Stop();
        back();
        delay(300);
        left();
        delay(300);
      }else if(distanceRight > 20 && distanceLeft < 15){
        Stop();
        back();
        delay(300);
        right();
        delay(300);
      }else{
        forward();
    }
  }
}

int readUltrasonic(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  return distance;
}
