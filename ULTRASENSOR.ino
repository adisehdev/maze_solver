// Motor A
 
int enA = 9;
int in1 = 8;
int in2 = 7;
 
// Motor B
 
int enB = 3;
int in3 = 5;
int in4 = 4;


#define trigPin 10
#define echoPin 13


float duration, distance;
bool wall = false;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

    // Set all the motor control pins to outputs
 
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);


}

void straight()
{
  // Turn on motor A
  Serial.println("RUNNING");
 
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
 
  // Set speed to 200 out of possible range 0~255

  analogWrite(enA, 255);
 
  // Turn on motor B
 
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
 
  // Set speed to 200 out of possible range 0~255
 
  analogWrite(enB, 255);

}

void turn()
{
  
  Serial.println("TURNING");
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  delay(100);

  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);


  analogWrite(enB, 255);
  
}

void reverse(){
  // Turn on motor A
  Serial.println("REVERSE");
 
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
 
  // Set speed to 200 out of possible range 0~255

  analogWrite(enA, 255);
 
  // Turn on motor B
 
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
 

}

void loop() {
    // Write a pulse to the HC-SR04 Trigger Pin
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(200);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(200);
  digitalWrite(trigPin, LOW);

  // Measure the response from the HC-SR04 Echo Pin
 
  duration = pulseIn(echoPin, HIGH);
  
  // Determine distance from duration
  // Use 343 metres per second as speed of sound
  
  distance = (duration / 2) * 0.0343;
  
  // Send results to Serial Monitor
 
  Serial.print("Distance = ");
  if(distance<15){
    Serial.println("wall detected");
    if(!wall)
    {
      reverse();
      wall = true;
    }
  }
  else {
    if (wall)
    {
      straight();
      wall = false;
    }
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);

}