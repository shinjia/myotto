//-- myOTTO home position

int pos[]={ 90,90,90,90 };  // 正中央的位置
int adj[]={ 0, 0, 0, 0 };  // 要調整的角度

#include <Servo.h>
Servo S0, S1, S2, S3;

void move_servo()
{
    S0.write(pos[0]+adj[0]);
    S1.write(pos[1]+adj[1]);
    S2.write(pos[2]+adj[2]);
    S3.write(pos[3]+adj[3]);
}


void show_message()
{
  Serial.println("HOME Position");
  
  Serial.print("Adjusted: ");  
  Serial.print(adj[0]);
  Serial.print(",");
  Serial.print(adj[1]);
  Serial.print(",");
  Serial.print(adj[2]);
  Serial.print(",");
  Serial.print(adj[3]);
  Serial.println("");
}


void setup(void)
{
  // Init Serial port
  Serial.begin(9600);
 
  S0.attach(5);
  S1.attach(4);
  S2.attach(3);
  S3.attach(2);
  
  show_message();
  move_servo();
}


void loop()  // test comparing before & after function
{
}
