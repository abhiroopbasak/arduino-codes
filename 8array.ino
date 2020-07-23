const int motorRPin1 = 2; // signal pin 1 for the right motor, connect to IN1
const int motorRPin2 = 4;  // signal pin 2 for the right motor, connect to IN2
const int motorREnable = 3; // enable pin for the right motor (PWM enabled)

const int motorLPin1 = 7; // signal pin 1 for the left motor, connect to IN3
const int motorLPin2 = 5; // signal pin 2 for the left motor, connect to IN4
const int motorLEnable = 6; // enable pin for the left motor (PWM enabled)

const int trig = 10;
const int echo = 11;

const int led =13;

const int irPins[8] = {12, A0, A2, A3, A4, A5 , 9 , 8};
int irSensorDigital[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int i, j = 0;
int d = 1000;
int duration=0,distance=0;

int irSensors = B00000000;

int motorLSpeed = 100;
int motorRSpeed = 100;
int error = 30; // 145 best 200  //  normal 255  // mad 0
int errorm = 60;
void setup() 
{

  Serial.begin(9600);


  pinMode(motorLPin1, OUTPUT);
  pinMode(motorLPin2, OUTPUT);
  pinMode(motorLEnable, OUTPUT);

  pinMode(motorRPin1, OUTPUT);
  pinMode(motorRPin2, OUTPUT);
  pinMode(motorREnable, OUTPUT);

  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);

  pinMode(led,OUTPUT);

  /* Set-up IR sensor pins as input */
  for (int i = 0; i <= 7; i++)
  {
    pinMode(irPins[i], INPUT);
  }


}

void loop() {
  scanD();
  check();
  sonar();
}

void check( )
{
  switch (irSensors) {

    
    /*case B00000000: // on white paper
      stopme();
      break;*/

    case B01111111: // leftmost sensor on the line
      rightR();
      break;

    case B10111111:
      rightS();
      break;

    case B11011111:
      rightG();
      break;


    case B11101111:
      go();
      break;

    case B11110111:
      go();
      break;

    case B11111011:
      leftG();
      break;

    case B11111101:
      leftS();
      break;

    case B11111110:
      leftR();
      break;

    case B00111111:
      rightR();
      break;

    case B10011111:
      rightS();
      break;

    case B11001111:
      rightG();
      break;

    case B11100111:
      go();
      break;

    case B11110011:
      leftG();
      break;

    case B11111001:
      leftS();
      break;

    case B11111100:
      leftR();
      break;

    case B00011111:
      rightR();
      break;

    case B10001111:
      rightS();
      break;

    case B11000111:
      go();
      break;

    case B11100011:
      go();
      break;

    case B11110001:
      leftS();
      break;

    case B11111000:
      leftR();
      break;

    case B00001111:
      rightR();
      break;

    case B10000111:
      rightS();
      break;

    case B11000011:
      go();
      break;

    case B11100001:
      leftS();
      break;

    case B11110000:
      leftR();
      break;

    case B00000111:
      rightR();
      break;

    case B10000011:
      rightS();
      break;

    case B11000001:
      leftS();
      break;

    case B11100000:
      leftR();
      break;

    case B00000011:
      rightS();
      break;

    case B10000001:
      go();
      break;

    case B11000000:
      leftS();
      break;


    case B00000001:
      rightG();
      break;

    case B10000000:
      leftG();
      break;

    case B11111111:
      stopme();
      break;

    case B00000000:
    {
    go();
    delay(20);
      break;
    }

    default:

      Serial.print("Unhandled case: ");

  }

}


void rightR()

{
  Serial.println("                         right motor forward (spin) sharp");
  analogWrite(motorREnable, motorRSpeed -errorm);
  digitalWrite(motorRPin1, LOW);
  digitalWrite(motorRPin2, HIGH);

  analogWrite(motorLEnable, motorLSpeed +error);
  digitalWrite(motorLPin1, LOW);
  digitalWrite(motorLPin2, HIGH);

}


void rightS()

{
  Serial.println("                         right motor forward (spin) slow");
  analogWrite(motorREnable, motorRSpeed - error);
  digitalWrite(motorRPin1, LOW);
  digitalWrite(motorRPin2, HIGH);

  analogWrite(motorLEnable, motorLSpeed +error);
  digitalWrite(motorLPin1, LOW);
  digitalWrite(motorLPin2, HIGH);

}


void rightG()

{
  Serial.println("                         right motor forward (spin) gentle");
  analogWrite(motorREnable, motorRSpeed - error);
  digitalWrite(motorRPin1, LOW);
  digitalWrite(motorRPin2, HIGH);

  analogWrite(motorLEnable, motorLSpeed+error);
  digitalWrite(motorLPin1, LOW);
  digitalWrite(motorLPin2, HIGH);

}



void leftR()  //turn left
{
  Serial.println("                         left  motor forward (spin) sharp");
  analogWrite(motorREnable, motorRSpeed +errorm);
  digitalWrite(motorRPin1, HIGH);
  digitalWrite(motorRPin2, LOW);

  analogWrite(motorLEnable, motorLSpeed - error);
  digitalWrite(motorLPin1, HIGH);
  digitalWrite(motorLPin2, LOW);

}


void leftS()  //turn left
{
  Serial.println("                         left  motor forward (spin) slow");
  analogWrite(motorREnable, motorRSpeed+error);
  digitalWrite(motorRPin1, HIGH);
  digitalWrite(motorRPin2, LOW);

  analogWrite(motorLEnable, motorLSpeed - error);
  digitalWrite(motorLPin1, HIGH);
  digitalWrite(motorLPin2, LOW);

}



void leftG()  //turn left
{
  Serial.println("                         left  motor forward (spin) gentle");
  analogWrite(motorREnable, motorRSpeed +error);
  digitalWrite(motorRPin1, HIGH);
  digitalWrite(motorRPin2, LOW);

  analogWrite(motorLEnable, motorLSpeed - error);
  digitalWrite(motorLPin1, HIGH);
  digitalWrite(motorLPin2, LOW);

}
void go()
{
  Serial.println("                         forward ");
  analogWrite(motorREnable, motorRSpeed);
  digitalWrite(motorRPin1, HIGH);
  digitalWrite(motorRPin2, LOW);

  analogWrite(motorLEnable, motorLSpeed);
  digitalWrite(motorLPin1, LOW);
  digitalWrite(motorLPin2, HIGH);

}

void stopme()
{
  Serial.println("                         stop");
  analogWrite(motorREnable, motorRSpeed);
  digitalWrite(motorRPin1, LOW);
  digitalWrite(motorRPin2, LOW);

  analogWrite(motorLEnable, motorLSpeed);
  digitalWrite(motorLPin1, LOW);
  digitalWrite(motorLPin2, LOW);

}




void scanD()
{
  for ( byte count = 0; count < 8; count++ )
  {
    bitWrite(irSensors, count, !digitalRead( irPins[count] ));
  }
  Serial.println(irSensors, BIN);
 
}

void sonar()
{
   digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  duration=pulseIn(echo,HIGH);
  distance=(duration/58.2);
  delay(10);
  if(distance<18)
  {
    digitalWrite(led,HIGH);
  }
}
