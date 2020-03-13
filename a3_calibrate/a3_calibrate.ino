//-- myOTTO calibration

// 參數：校正的位置 (要調整的角度)
int adj[]={ 0, 0, 0, 0 };

// 參數：起始位置
int pos[]={ 90,90,90,90 };  // 起始位置


// 參數：各伺服馬達的腳位
#define PIN_RR 5
#define PIN_RL 4
#define PIN_YR 3
#define PIN_YL 2

#include <Servo.h>
Servo S0, S1, S2, S3;


void help()
{
  Serial.println("This is used to calibration the servos for 'Otto'");
  Serial.println("The interface uses single character controls");
  Serial.println("");
  Serial.println("'2' - add value of YL");
  Serial.println("'w' - minus value of YL");
  Serial.println("'1' - add value of YR");
  Serial.println("'q' - minus value of YL");
  Serial.println("'s' - add value of RL");
  Serial.println("'x' - minus value of RL");
  Serial.println("'a' - add value of RR");
  Serial.println("'z' - minus value of YL");
  Serial.println("");
}


void show_message()
{ 
  Serial.print("Adjust: "); 
  Serial.print(adj[0]);
  Serial.print(",");
  Serial.print(adj[1]);
  Serial.print(",");
  Serial.print(adj[2]);
  Serial.print(",");
  Serial.print(adj[3]);
  Serial.println("");
}


// 處理輸入的字元
void processChar(char c)
{
  // see if the first char is a number or a command char

  switch(c)
  {
    case 'h':
    case 'H':
      help();
      break;
      
    case '2':
      adj[3]++;
      break;
      
    case 'w':
    case 'W':
      adj[3]--;
      break;
      
    case '1':
      adj[2]++;
      break;
      
    case 'q':
    case 'Q':
      adj[2]--;
      break;
      
    case 's':
    case 'S':
      adj[1]++;
      break;
      
    case 'x':
    case 'X':
      adj[1]--;
      break;
      
    case 'a':
    case 'A':
      adj[0]++;
      break;
      
    case 'z':
    case 'Z':
      adj[0]--;
      break;
      
    case '\n':
    case '\r':
      break;
      
    default:
      Serial.print("Unknown command (");
      Serial.print(c);
      Serial.println(")");
      break;
  }
  show_message();
}


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
  
  help();
}


void loop()
{
  // 取得序列埠傳入的資料
  while(Serial.available() > 0)
  {
    processChar(Serial.read());
  }
  move_servo();
}
