#include <Stepper.h>

int i;
const int StepX = 2; //elbow joint
const int DirX = 5;
const int StepY = 3;//shoulder joint
const int DirY = 6;
const int StepZ = 4; //base joint
const int DirZ = 7;

float var = 1.8;
float direction;
float BaseLength = 3.229;
float ShoulderLength = 9.555;
float ElbowLength = 9.859;
float Hypot;
float x0 = 4;//Target end point TEST
float y0 = 3;//Target end point TEST
float z0 = 4;//Target end point TEST
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

  delay(2000);

  //from top right to bottom right
  digitalWrite(DirX,HIGH);
  for(int x = 0; x<100/var ; x++){
  digitalWrite(StepX,HIGH);
  delay(100);
  digitalWrite(StepX,LOW);
  }

  //from bottom right to bottom left
  digitalWrite(DirZ,HIGH);
  for(int x = 0; x<100/var ; x++){
  digitalWrite(StepZ,HIGH);
  delay(100);
  digitalWrite(StepZ,LOW);
  }
  
  //from bottom left to top left
  digitalWrite(DirX,LOW);
  for(int x = 0; x<100/var ; x++){
  digitalWrite(StepX,HIGH);
  delay(100);
  digitalWrite(StepX,LOW);
  }

  //from top left to top right
  digitalWrite(DirZ,LOW);
  for(int x = 0; x<100/var ; x++){
  digitalWrite(StepZ,HIGH);
  delay(100);
  digitalWrite(StepZ,LOW);
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
