#include <Stepper.h>

int i;
const int StepX = 2; //elbow joint
const int DirX = 5;
const int StepY = 3;//shoulder joint
const int DirY = 6;
const int StepZ = 4; //base joint
const int DirZ = 7;

float var = 1.8;
float n = 2; // repitions to grid pattern (back & forth)
float direction;
float BaseLength = 3.229;
float ShoulderLength = 9.555;
float ElbowLength = 9.859;
float Hypot;
float x0 = 4; //initial x coordinate
float y0 = -8; //initial y coordinate
float z0 = 10; //initial z coordinate
float A, B, C,
      Theta,
      Alpha,
	  Alpha_temp,
	  Alpha_i,
	  Beta_temp,
      Beta;

//Function will be added here to aquire actual desired target points

void setup()
{

  calculation();
  Serial.begin(115200);
  pinMode(StepX,OUTPUT);
  pinMode(DirX,OUTPUT);
  pinMode(StepY,OUTPUT);
  pinMode(DirY,OUTPUT);
  pinMode(StepZ,OUTPUT);
  pinMode(DirZ,OUTPUT);

  //HIGH for clockwise and LOW for anticlockwise
  if(Beta<0) direction = LOW;
  else direction = HIGH;
  digitalWrite(DirX,direction); 
 
  if(Alpha<0) direction = LOW;
  else direction = HIGH;
  digitalWrite(DirY,direction);
  
  if(Theta>0) direction = LOW;
  else direction = HIGH;
  digitalWrite(DirZ,direction);

  //Move until target steps
  for(int x = 0; x<Theta/var ; x++){
  digitalWrite(StepZ,HIGH);
  delay(100);
  digitalWrite(StepZ,LOW);
  }
  for(int x = 0; x<Alpha/var ; x++){
  digitalWrite(StepY,HIGH);
  delay(100);
  digitalWrite(StepY,LOW);
  }
  for(int x = 0; x<Beta/var ; x++){
  digitalWrite(StepX,HIGH);
  delay(100);
  digitalWrite(StepX,LOW);
  }

  delay(5000);// wait 5 seconds
  for(int y = 0; y<=n ; y++){
  grid();// call upon grid function n times
  }

//end setup.
}

void loop(){
  
  Serial.println("set");
  Serial.println(Theta);
  Serial.println(Alpha);
  Serial.println(Beta);

}

void calculation() {
  
  Hypot = sqrt(sq(x0) + sq(z0));
  A = ElbowLength;
  B = Hypot;
  C = ShoulderLength;

  Theta = atan(y0/x0)* (180 / PI);

  Alpha_temp = acos((sq(B) + sq(C) - sq(A)) / (2 * B * C)) * (180 / PI);
  Alpha_i = 90 - Alpha_temp + atan(z0/x0)*(180 / PI);
  Alpha = 90 - Alpha_i;

  Beta_temp =  acos((sq(C) + sq(A) - sq(B)) / (2 * A * C)) * (180 / PI);
  Beta = 180 -(Alpha_i + Beta_temp);


}//end calc

void grid(){
  
  //from left to right
  digitalWrite(DirZ,LOW);
  for(int x = 0; x<150 ; x = x + 15){
  digitalWrite(StepZ,HIGH);
  delay(100);
  digitalWrite(StepZ,LOW);
  delay(4000);
  }
  //move to next line
  digitalWrite(DirX,HIGH);
  for(int x = 0; x<10 ; x = x++){
  digitalWrite(StepX,HIGH);
  delay(100);
  digitalWrite(StepX,LOW);
  delay(4000);
  }
  //from right to left
  digitalWrite(DirZ,HIGH);
  for(int x = 0; x<150 ; x+15){
  digitalWrite(StepZ,HIGH);
  delay(100);
  digitalWrite(StepZ,LOW);
  delay(4000);
  }
  //move to next line
  digitalWrite(DirX,HIGH);
  for(int x = 0; x<10 ; x = x++){
  digitalWrite(StepX,HIGH);
  delay(100);
  digitalWrite(StepX,LOW);
  delay(4000);
  }

}// end grid