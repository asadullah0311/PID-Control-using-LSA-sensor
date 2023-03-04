const int Kp = 3;
const int Kd = 5;
const int setPoint = 35;
const int minspeed = 100;
const int maxspeed = 200;
int flag;
int lastError = 0, error, motorspeed, backlsa, leftlsa;
int goingl = 0; //flag for going left
int motor1DIR = 52;
int motor1PWM = 11;
int motor2DIR = 50;
int motor2PWM = 10;
int motor3DIR = 48;
int motor3PWM = 9;
int motor4DIR = 42;
int motor4PWM = 7;

int speed1, speed2, speed3, speed4;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);

  digitalWrite(motor1PWM, LOW);
  digitalWrite(motor2PWM, LOW);
  digitalWrite(motor3PWM, LOW);
  digitalWrite(motor4PWM, LOW);

}

void loop() {
  backlsa = Serial1.read();
  leftlsa = Serial2.read();

  Serial.print(backlsa);
  Serial.print("  ||  ");
  Serial.println( leftlsa);

  // If no line is detected, stay at the position
  if (backlsa == 255 && leftlsa == 255) {

    analogWrite(motor1PWM, 0);
    analogWrite(motor2PWM, 0);
    analogWrite(motor3PWM, 0);
    analogWrite(motor4PWM, 0);

    digitalWrite(motor1DIR, LOW);
    digitalWrite(motor2DIR, LOW);
    digitalWrite(motor3DIR, LOW);
    digitalWrite(motor4DIR, LOW);

    Serial.println("Stop, Stay calm");
  }
  else if (backlsa != 255 && leftlsa == 255) {
    //goingforward
    //goingl=0

    digitalWrite(motor1DIR, LOW);
    digitalWrite(motor2DIR, LOW);
    digitalWrite(motor3DIR, LOW);
    digitalWrite(motor4DIR, LOW);

    error = backlsa - setPoint;
    motorspeed = Kp * error + Kd * (error - lastError);
    lastError = error;

    // Adjust the motor speed based on calculated value
    speed1 = minspeed + motorspeed;
    speed2 = minspeed - motorspeed;
    speed3 = minspeed + motorspeed;
    speed4 = minspeed - motorspeed;

    if (speed1 > maxspeed) speed1 = maxspeed;
    if (speed2 > maxspeed) speed2 = maxspeed;
    if (speed3 > maxspeed) speed3 = maxspeed;
    if (speed4 > maxspeed) speed4 = maxspeed;

    if (speed1 < 0) speed1 = 0;
    if (speed2 < 0) speed2 = 0;
    if (speed3 < 0) speed3 = 0;
    if (speed4 < 0) speed4 = 0;

    // Writing the motor speed value as output to hardware motor
    analogWrite(motor1PWM, speed1);
    analogWrite(motor2PWM, speed2);
    analogWrite(motor3PWM, speed3);
    analogWrite(motor4PWM, speed4);
    //    Serial.println(speed1);
    //    Serial.println(speed2);
    //    Serial.println(speed3);
    //    Serial.println(speed4);
    goingl = 0 ;
    Serial.println("Forward");
  }

  else if (backlsa == 255 && 0<leftlsa < 70 ) {
    //going left
    //goingl=1 karro
    digitalWrite(motor1DIR, HIGH);
    digitalWrite(motor2DIR, HIGH);
    digitalWrite(motor3DIR, HIGH);
    digitalWrite(motor4DIR, HIGH);

    error = leftlsa - setPoint;
    motorspeed = Kp * error + Kd * (error - lastError);
    lastError = error;

    // Adjust the motor speed based on calculated value
    speed1 = minspeed + motorspeed;
    speed2 = minspeed - motorspeed;
    speed3 = minspeed + motorspeed;
    speed4 = minspeed - motorspeed;

    if (speed1 > maxspeed) speed1 = maxspeed;
    if (speed2 > maxspeed) speed2 = maxspeed;
    if (speed3 > maxspeed) speed3 = maxspeed;
    if (speed4 > maxspeed) speed4 = maxspeed;

    if (speed1 < 0) speed1 = 0;
    if (speed2 < 0) speed2 = 0;
    if (speed3 < 0) speed3 = 0;
    if (speed4 < 0) speed4 = 0;

    // Writing the motor speed value as output to hardware motor
    analogWrite(motor1PWM, speed1);
    analogWrite(motor2PWM, speed2);
    analogWrite(motor3PWM, speed3);
    analogWrite(motor4PWM, speed4);
    //    Serial.println(speed1);
    //    Serial.println(speed2);
    //    Serial.println(speed3);
    //    Serial.println(speed4);
    goingl = 1;
    Serial.println("Left");
  }

  else if (backlsa != 255 && leftlsa != 255) //junction detected
  {
    if (goingl == 0) {
      // going forward
      //tell to go left
      digitalWrite(motor1DIR, HIGH);
      digitalWrite(motor2DIR, HIGH);
      digitalWrite(motor3DIR, HIGH);
      digitalWrite(motor4DIR, HIGH);

      error = leftlsa - setPoint;
      motorspeed = Kp * error + Kd * (error - lastError);
      lastError = error;

      // Adjust the motor speed based on calculated value
      speed1 = minspeed + motorspeed;
      speed2 = minspeed - motorspeed;
      speed3 = minspeed + motorspeed;
      speed4 = minspeed - motorspeed;

      if (speed1 > maxspeed) speed1 = maxspeed;
      if (speed2 > maxspeed) speed2 = maxspeed;
      if (speed3 > maxspeed) speed3 = maxspeed;
      if (speed4 > maxspeed) speed4 = maxspeed;

      if (speed1 < 0) speed1 = 0;
      if (speed2 < 0) speed2 = 0;
      if (speed3 < 0) speed3 = 0;
      if (speed4 < 0) speed4 = 0;

      // Writing the motor speed value as output to hardware motor
      analogWrite(motor1PWM, speed1);
      analogWrite(motor2PWM, speed2);
      analogWrite(motor3PWM, speed3);
      analogWrite(motor4PWM, speed4);
      //      Serial.println(speed1);
      //      Serial.println(speed2);
      //      Serial.println(speed3);
      //      Serial.println(speed4);
      Serial.println("Left after Junction");
    }
    else if (goingl == 1) { // tell to go backward

      digitalWrite(motor1DIR, LOW);
      digitalWrite(motor2DIR, LOW);
      digitalWrite(motor3DIR, LOW);
      digitalWrite(motor4DIR, LOW);

      error = backlsa - setPoint;
      motorspeed = Kp * error + Kd * (error - lastError);
      lastError = error;

      // Adjust the motor speed based on calculated value
      speed1 = minspeed + motorspeed;
      speed2 = minspeed - motorspeed;
      speed3 = minspeed + motorspeed;
      speed4 = minspeed - motorspeed;

      if (speed1 > maxspeed) speed1 = maxspeed;
      if (speed2 > maxspeed) speed2 = maxspeed;
      if (speed3 > maxspeed) speed3 = maxspeed;
      if (speed4 > maxspeed) speed4 = maxspeed;

      if (speed1 < 0) speed1 = 0;
      if (speed2 < 0) speed2 = 0;
      if (speed3 < 0) speed3 = 0;
      if (speed4 < 0) speed4 = 0;

      // Writing the motor speed value as output to hardware motor
      analogWrite(motor1PWM, speed1);
      analogWrite(motor2PWM, speed2);
      analogWrite(motor3PWM, speed3);
      analogWrite(motor4PWM, speed4);
      //      Serial.println(speed1);
      //      Serial.println(speed2);
      //      Serial.println(speed3);
      //      Serial.println(speed4);
      Serial.println("Back After Junc.");
    }
  }
}
