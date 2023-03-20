//-- myOTTO

int N_SERVOS = 4; // 伺服馬達的個數

// 參數：校正的位置 (要調整的角度)
int adj[]={ 0, 0, 0, 0 };

// 參數：起始位置
int pos[]={ 90,90,90,90 };  // 起始位置

// TEMPO: 120 BPM ==> 0.5sec/beat
int beat_time = 500;

#define INTERVALTIME 10.0 

// 硬體設定
#include <Servo.h>
Servo S0, S1, S2, S3;

// 參數：各伺服馬達的腳位
#define PIN_RR 5
#define PIN_RL 4
#define PIN_YR 3
#define PIN_YL 2


void move_servo() {
  S0.write(pos[0]+adj[0]);
  S1.write(pos[1]+adj[1]);
  S2.write(pos[2]+adj[2]);
  S3.write(pos[3]+adj[3]);
}


void tempo_servo(int stime, int pos_new[]) {
  float increment[N_SERVOS];
  unsigned long final_time;
  unsigned long interval_time;
  int iteration = 1; 
  int oneTime;
  int pos_old[] = { 0, 0, 0, 0 };

  for(int i=0; i<N_SERVOS; i++) {
    pos_old[i] = pos[i];
    increment[i] = ((pos_new[i])-pos[i])/(stime/INTERVALTIME);
  }
  
  final_time =  millis() + stime; 
  
  iteration = 1; 
  while(millis() < final_time) {
      interval_time = millis()+INTERVALTIME;  
      
      oneTime=0;      
      while(millis()<interval_time) {
          if(oneTime<1) {
              for(int i=0;i<N_SERVOS;i++) {
                  pos[i] = pos_old[i] + (iteration * increment[i]);
              }
              move_servo();
              iteration++;
              oneTime++;
          }
      }     
  }   

  for(int i=0;i<N_SERVOS;i++) {
    pos[i] = pos_new[i];
  }
}


void setup(void) {
  Serial.begin(115200);
 
  S0.attach(PIN_RR);
  S1.attach(PIN_RL);
  S2.attach(PIN_YR);
  S3.attach(PIN_YL);
  
  move_servo();
}


void loop() {
  int move0[] = { 90, 90, 90, 90 };
  int move1[] = { 60, 90, 90, 90 };
  int move2[] = { 120, 90, 90, 90 };

  float t = beat_time;
  
  tempo_servo(t, move2);
  tempo_servo(t, move0);
  tempo_servo(t, move2);
  tempo_servo(t, move0);
  
  tempo_servo(t, move2);
  tempo_servo(t, move0);
  tempo_servo(t, move2);
  tempo_servo(t, move0);
  
  tempo_servo(t*2, move1);
  tempo_servo(t*2, move0);
  tempo_servo(t*2, move1);
  tempo_servo(t*2, move0); 
}
