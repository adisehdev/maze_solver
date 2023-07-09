#define TRIG_PIN_1 6
#define ECHO_PIN_1 2
#define TRIG_PIN_2 12
#define ECHO_PIN_2 11
#define TRIG_PIN_3 10
#define ECHO_PIN_3 13



// Motor A
// Motor A -> Wire Config
// Blue --> out1-->near castor wheel
// Orange -->out2 --> away from castor wheel
 
int enA = 9;
int in1 = 8;
int in2 = 7;
 
// Motor B
// Motor B -> Wire Config
// White --> out4-->near castor wheel
// Green -->out3 --> away from castor wheel
int enB = 3;
int in3 = 5;
int in4 = 4;


void straight(){
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);

  analogWrite(enA,255);

  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);

  analogWrite(enB,255);
}

void reverse(){

  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);

  analogWrite(enA,255);

  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);

  analogWrite(enB,255);
}


void turn_left(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);

  analogWrite(enA,255);

  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);

  analogWrite(enB,255);
}

void turn_right(){
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);

  analogWrite(enA,255);

  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);

  analogWrite(enB,255);
}


void stop(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);

  analogWrite(enA,0);

  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);

  analogWrite(enB,0);
}



float sonarDistance(int trig, int echo){
  float duration, distance;

  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;

  return distance;
}



void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN_1, OUTPUT);
  pinMode(ECHO_PIN_1, INPUT);
  pinMode(TRIG_PIN_2, OUTPUT);
  pinMode(ECHO_PIN_2, INPUT);
  pinMode(TRIG_PIN_3, OUTPUT);
  pinMode(ECHO_PIN_3, INPUT);

  //MOTOR DRIVER SETUP
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);


}

void loop() {
  float duration1, distance1;
  float duration2, distance2;
  float duration3, distance3;
  

distance1 = sonarDistance(TRIG_PIN_1,ECHO_PIN_1);
distance2 = sonarDistance(TRIG_PIN_2,ECHO_PIN_2);
distance3 = sonarDistance(TRIG_PIN_3,ECHO_PIN_3);

  
  // // Print the distance readings
  // Serial.print("Sensor 1: ");
  // Serial.print(distance1);
  // Serial.println(" cm");
  
  // Serial.print("Sensor 2: ");
  // Serial.print(distance2);
  // Serial.println(" cm");
  
  // Serial.print("Sensor 3: ");
  // Serial.print(distance3);
  // Serial.println(" cm");
  // Serial.println("--------------------------------------------------");
  // delay(100); // Delay between readings

//distance1 -> forward
//distance2 -> left
//distance3 -> right

// //For Turning
int max_distance = 5;

if(distance1>max_distance && distance2>max_distance && distance3>max_distance){   //No Walls
  straight();
}
else if(distance1<max_distance && distance2>max_distance && distance3>max_distance){  //Wall in front
  turn_right();
}
else if(distance1>max_distance && distance2<max_distance && distance3>max_distance){  //Wall in left
  straight();
}
else if(distance1>max_distance && distance2>max_distance && distance3<max_distance){ //wall in right
  straight();
}
else if(distance1<max_distance && distance2<max_distance && distance3>max_distance){  // wall in front and left
 turn_right();
}
else if(distance1<max_distance && distance2>max_distance && distance3<max_distance){  //wall in front and right
  turn_left();
}
else{
  stop();
}

}