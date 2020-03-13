//-- myOTTO move position

// 參數：校正的位置 (要調整的角度)
int adj[]={ 0, 0, 0, 0 };

// 參數：起始位置
int pos[]={ 90,90,90,90 };  // 起始位置

// 參數：各伺服馬達移動的角度
int shift4[][4] = {
  { 90, 90, 90, 90 },
  { 80, 100, 90, 90 },
  { 70, 110, 90, 90 },
  { 60, 120, 90, 90 },
  { 50, 130, 90, 90 },
  { 40, 140, 90, 90 },
  { 50, 130, 90, 90 },
  { 60, 120, 90, 90 },
  { 70, 110, 90, 90 },
  { 80, 100, 90, 90 },
  { 90, 90, 90, 90 }
};

int shift_length; // 直接在程式中計算取得
int shift_delay = 121;


#include <Servo.h>
Servo S0, S1, S2, S3;

// 參數：各伺服馬達的腳位
#define PIN_RR 5
#define PIN_RL 4
#define PIN_YR 3
#define PIN_YL 2


void move_servo()
{
  S0.write(pos[0]+adj[0]);
  S1.write(pos[1]+adj[1]);
  S2.write(pos[2]+adj[2]);
  S3.write(pos[3]+adj[3]);
}


void setup()
{
  Serial.begin(9600);
 
  S0.attach(PIN_RR);
  S1.attach(PIN_RL);
  S2.attach(PIN_YR);
  S3.attach(PIN_YL);
    
  show_message();
  move_servo();
}


void loop()
{
  shift_length = sizeof(shift4) / sizeof(shift4[0]);
  
  for(int j=0; j<shift_length; j++)
  {
    pos[0] = shift4[j][0];
    pos[1] = shift4[j][1];
    pos[2] = shift4[j][2];
    pos[3] = shift4[j][3];
    
    move_servo();
    // show_message();
    delay(shift_delay);
  }
}


void show_message()
{
  Serial.println("HOME Position");
  
  Serial.print("Position: ");  
  Serial.print(pos[0]);
  Serial.print(",");
  Serial.print(pos[1]);
  Serial.print(",");
  Serial.print(pos[2]);
  Serial.print(",");
  Serial.print(pos[3]);
  Serial.println("");
  
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
