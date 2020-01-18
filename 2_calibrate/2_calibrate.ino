//-- myOTTO calibration
#include <Servo.h>

Servo S0, S1, S2, S3;

int pos[]={ 90,90,90,90 };  // 正中央的位置
int adj[]={ 0,0,0,0 };  // 要調整的角度 (此程式不可更改此值)

void help(void)
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

// process the user input char

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

// init all things

void setup(void)
{
  // Init Serial port
  Serial.begin(9600);
 
  S0.attach(5);
  S1.attach(4);
  S2.attach(3);
  S3.attach(2);
  
  help();
}

// see if the user wants anything

void loop()  // test comparing before & after function
{
  // get input from Serial port
  while(Serial.available() > 0)
  {
    processChar(Serial.read());
  }
  move_servo();
  
 // delay(4000);
}
