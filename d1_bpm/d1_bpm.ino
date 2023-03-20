/****************************************
myOTTO - tempo
by Shinjia Chen
Version: 1.1 (2023-03-20)
****************************************/

int N_SERVOS = 4; // 伺服馬達的個數

// 參數：校正的位置 (要調整的角度)
int adj[]={ 5, 3, 17, 10 };

// 參數：起始位置
int pos_home[]={ 90,90,90,90 };  // 起始位置
int pos[]={ 90,90,90,90 };  // 目前位置

// 參數：節拍設定 tempo: BPM (Beat per Minute)
int tempo = 120;

long millis_start = 0;
float beat_accumulation = 0.0;  // 起始必須為零
int base_interval_time = 10;  // 基礎間隔時間

bool debug_mode_servo = false;
bool debug_mode_tempo = false;
bool debug_mode_iteration = false;

// 硬體設定
#include <Servo.h>
Servo S0, S1, S2, S3;

// 參數：各伺服馬達的腳位
#define PIN_RR 5
#define PIN_RL 4
#define PIN_YR 3
#define PIN_YL 2


void servo_goto() {
  S0.write(pos[0]+adj[0]);
  S1.write(pos[1]+adj[1]);
  S2.write(pos[2]+adj[2]);
  S3.write(pos[3]+adj[3]);

  if(debug_mode_servo) {
    Serial.println();
    Serial.print("Servo goto: ");
    Serial.print(pos[0]);
    Serial.print("  ");
    Serial.print(pos[1]);
    Serial.print("  ");
    Serial.print(pos[2]);
    Serial.print("  ");
    Serial.print(pos[3]);
    Serial.print("  ");
  } 
}


void servo_tempo(float beat, int pos_new[]) {
  float increment[N_SERVOS];
  unsigned long final_time, final_time1, final_time2;
  unsigned long interval_time;
  int iteration = 1; 
  float stime;
  int segment = 0;
  int oneTime;
  int pos_old[] = { 0, 0, 0, 0 };

  if(beat_accumulation==0.0) {
    millis_start = millis();
  }
  beat_accumulation += beat;  // 累計拍子數
  
  stime = beat * (60000/tempo);
  segment = stime/base_interval_time;
  
  final_time1 = millis() + stime;
  final_time2 = millis_start + (beat_accumulation*(60000/tempo));
  
  for(int i=0; i<N_SERVOS; i++) {
    pos_old[i] = pos[i];
    increment[i] = (segment==0.0) ? 0.0 : ((float)(pos_new[i]-pos[i])/(float)segment);
  }

  if(debug_mode_tempo) {
    Serial.println();
    Serial.println("================");
    Serial.print("beat=");  
    Serial.print(beat);
    Serial.println();
    Serial.print("stime:");
    Serial.print(stime);
    Serial.println();
    Serial.print("segemnt:");
    Serial.print(stime/base_interval_time);
    Serial.println();
    Serial.print("Increment: ");
    Serial.print(increment[0]);
    Serial.println();
    Serial.print("final_time:");
    Serial.print(final_time1);
    Serial.print(", ");
    Serial.print(final_time2);
    Serial.println();
  }

  final_time = final_time2;
  iteration = 1; 
  while(millis() < final_time) {
    if(debug_mode_iteration) {
      Serial.println();
      Serial.print("iteration=");
      Serial.print(iteration);
      Serial.print("  ");
    }
    
    interval_time = millis()+base_interval_time;
      
    oneTime=0;      
    while(millis()<interval_time) {
      if(oneTime<1) { 
        for(int i=0;i<N_SERVOS;i++) {
          pos[i] = pos_old[i] + (iteration * increment[i]);
        }
        iteration++;
        oneTime++;
        servo_goto();
      }
      
      if(debug_mode_iteration) {
        Serial.print(".");
      }
    }     
  }

  for(int i=0;i<N_SERVOS;i++) {
    pos[i] = pos_new[i];
  }
  servo_goto();
}


void setup(void) {
  Serial.begin(115200);
 
  S0.attach(PIN_RR);
  S1.attach(PIN_RL);
  S2.attach(PIN_YR);
  S3.attach(PIN_YL);
  
  servo_goto();
}


void loop() {
  int pos0[] = {  0+90,   0+90, 90, 90 };
  int pos1[] = { 40+90,   0+90, 90, 90 };
  int pos2[] = {  0+90, -40+90, 90, 90 };
  int pos3[] = { 40+90, -40+90, 90, 90 };

  servo_tempo(0, pos0);

  
  servo_tempo(1, pos1);
  servo_tempo(1, pos3);
  servo_tempo(1, pos2);
  servo_tempo(1, pos0);
  
  
  /*
  servo_tempo(0, pos1);  servo_tempo(1, pos);
  servo_tempo(0, pos3);  servo_tempo(1, pos);
  servo_tempo(0, pos2);  servo_tempo(1, pos);
  servo_tempo(0, pos0);  servo_tempo(1, pos);
  */
  
  /*
  for(int k=0; k<2; k++)
  {
    servo_tempo(0, pos1);  servo_tempo(0.5, pos);
    servo_tempo(0, pos3);  servo_tempo(0.5, pos);
    servo_tempo(0, pos2);  servo_tempo(0.5, pos);
    servo_tempo(0, pos0);  servo_tempo(0.5, pos);
  }
  */

  /*
  for(int k=0; k<4; k++)
  {
    servo_tempo(0, pos1);  servo_tempo(0.25, pos);
    servo_tempo(0, pos3);  servo_tempo(0.25, pos);
    servo_tempo(0, pos2);  servo_tempo(0.25, pos);
    servo_tempo(0, pos0);  servo_tempo(0.25, pos);
  }
  */
}
