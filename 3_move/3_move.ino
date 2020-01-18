//-- myOTTO home position

int pos[]={ 90,90,90,90 };  // 正中央的位置
int adj[]={ 0, 0, 0, 0 };  // 要調整的角度


int shift[] = {
  0,1,2,3,4,5,6,7,8,9,10,
  9,8,7,6,5,4,3,2,1,0,
  -1,-2,-3,-4,-5,-6,-7,-8,-9,-10,
  -9,-8,-7,-6,-5,-4,-3,-2,-1,0
};

int shift_delay = 10;
int shift_scale = 3;

#include <Servo.h>
Servo S0, S1, S2, S3;


void move_servo()
{
    S0.write(pos[0]+adj[0]);
    S1.write(pos[1]+adj[1]);
    S2.write(pos[2]+adj[2]);
    S3.write(pos[3]+adj[3]);
}

// init all things

void setup(void)
{
  // Init Serial port
  Serial.begin(9600);
 
  S0.attach(5);
  S1.attach(4);
  S2.attach(3);
  S3.attach(2);
  
  move_servo();
  
  int shift_length = sizeof(shift) / sizeof(int);
  Serial.println(shift_length);
}


void show_message()
{ 
  Serial.print("Posistion: ");  
  Serial.print(pos[0]);
  Serial.print(",");
  Serial.print(pos[1]);
  Serial.print(",");
  Serial.print(pos[2]);
  Serial.print(",");
  Serial.print(pos[3]);
  Serial.print(" | ");
  
  Serial.print(adj[0]);
  Serial.print(",");
  Serial.print(adj[1]);
  Serial.print(",");
  Serial.print(adj[2]);
  Serial.print(",");
  Serial.print(adj[3]);
  
  Serial.print(" | ");
  
  Serial.print(pos[0]-adj[0]);
  Serial.print(",");
  Serial.print(pos[1]-adj[1]);
  Serial.print(",");
  Serial.print(pos[2]-adj[2]);
  Serial.print(",");
  Serial.print(pos[3]-adj[3]);
  Serial.print(" | ");
  
  Serial.println("");
}


void loop()  // test comparing before & after function
{
  for(int i=0; i<4; i++)
  {
    int shift_length = sizeof(shift) / sizeof(int);
    for(int j=0; j<shift_length; j++)
    {
       pos[i] = 90 + shift[j]*shift_scale;
       move_servo();
       show_message();
       delay(shift_delay);
    }
  }
}
