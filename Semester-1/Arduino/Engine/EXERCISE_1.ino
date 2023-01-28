#define IN1 8 
#define IN2 9 
#define IN3 10 
#define IN4 11

unsigned long previousMillis;
unsigned long currentMillis = 0;
unsigned long interval = 300;
// zmienić z delay na millis
const int lengthSeq = 4;
int Step = 0;
//void roll(int work_type){
//
//  if (work_type == 0){
//    for (Step = 0; Step<4;Step++){
//      digitalWrite(IN1, stepsMatrix_wave[Step][0]);
//      digitalWrite(IN2, stepsMatrix_wave[Step][1]);
//      digitalWrite(IN3, stepsMatrix_wave[Step][2]);
//      digitalWrite(IN4, stepsMatrix_wave[Step][3]);
//      delay(10);
//      }
//    }
//  else if (work_type == 1){
//    for (Step = 0; Step<4;Step++){
//      digitalWrite(IN1, stepsMatrix_full_step[Step][0]);
//      digitalWrite(IN2, stepsMatrix_full_step[Step][1]);
//      digitalWrite(IN3, stepsMatrix_full_step[Step][2]);
//      digitalWrite(IN4, stepsMatrix_full_step[Step][3]);
//      delay(10);
//      }
//    }
//  else if (work_type == 2){
//    for (Step = 0; Step<4;Step++){
//      digitalWrite(IN1, stepsMatrix_half_step[Step][0]);
//      digitalWrite(IN2, stepsMatrix_half_step[Step][1]);
//      digitalWrite(IN3, stepsMatrix_half_step[Step][2]);
//      digitalWrite(IN4, stepsMatrix_half_step[Step][3]);
//      delay(10);
//    }
//  }
//}

int stepsMatrix_wave[lengthSeq][4] ={
  {0,0,0,1},
  {0,0,1,0},
  {0,1,0,0},
  {1,0,0,0}
 
};

int stepsMatrix_full_step[lengthSeq][4] ={
  {0,0,1,1},
  {0,1,1,0},
  {1,1,0,0},
  {1,0,0,1}
 
};
int stepsMatrix_half_step[lengthSeq*2][4] ={
  {0,0,0,1},
  {0,0,1,1},
  {0,0,1,0},
  {0,1,1,0},
  {0,1,0,0},
  {1,1,0,0},
  {1,0,0,0},
  {1,0,0,1}
 
};

void setup(){
//  void roll(int work_type){
//  if (work_type == 0){
//  stepsMatrix = stepsMatrix_wave;
//    for (Step = 0; Step<4;Step++){
//    
//      digitalWrite(IN1, stepsMatrix[Step][0]);
//      digitalWrite(IN2, stepsMatrix[Step][1]);
//      digitalWrite(IN3, stepsMatrix[Step][2]);
//      digitalWrite(IN4, stepsMatrix[Step][3]);
//      delay(10);
//      }
//    }
//  else if (work_type == 1){
//    stepsMatrix = stepsMatrix_full_step;
//
//    for (Step = 0; Step<4;Step++){
//      digitalWrite(IN1, stepsMatrix_[Step][0]);
//      digitalWrite(IN2, stepsMatrix_[Step][1]);
//      digitalWrite(IN3, stepsMatrix_[Step][2]);
//      digitalWrite(IN4, stepsMatrix_[Step][3]);
//      delay(10);
//      }
//    }
//  else if (work_type == 2){
//    stepsMatrix = stepsMatrix_half_step;
//    for (Step = 0; Step<4;Step++){
//      digitalWrite(IN1, stepsMatrix_[Step][0]);
//      digitalWrite(IN2, stepsMatrix_[Step][1]);
//      digitalWrite(IN3, stepsMatrix_[Step][2]);
//      digitalWrite(IN4, stepsMatrix_[Step][3]);
//      delay(10);
//    }
//  }
//}

//  Serial.begin(9600);
//  Serial.println()
//  function_name(2,3);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop(){
currentMillis = millis();
//    for (Step = 0; Step<4;Step++){
//      digitalWrite(IN1, stepsMatrix_wave[Step][0]);
//      digitalWrite(IN2, stepsMatrix_wave[Step][1]);
//      digitalWrite(IN3, stepsMatrix_wave[Step][2]);
//      digitalWrite(IN4, stepsMatrix_wave[Step][3]);
//      delay(2);
////    }
//        for (Step = 0; Step<4;Step++){
//      digitalWrite(IN1, stepsMatrix_full_step[Step][0]);
//      digitalWrite(IN2, stepsMatrix_full_step[Step][1]);
//      digitalWrite(IN3, stepsMatrix_full_step[Step][2]);
//      digitalWrite(IN4, stepsMatrix_full_step[Step][3]);
//      delay(10);
//      }
while(currentMillis - previousMillis <= interval)
    {
    previousMillis = millis();
          for (Step = 0; Step<8;Step++){
      digitalWrite(IN1, stepsMatrix_half_step[Step][0]);
      digitalWrite(IN2, stepsMatrix_half_step[Step][1]);
      digitalWrite(IN3, stepsMatrix_half_step[Step][2]);
      digitalWrite(IN4, stepsMatrix_half_step[Step][3]);
      digitalWrite(IN1, stepsMatrix_half_step[Step][4]);
      digitalWrite(IN2, stepsMatrix_half_step[Step][5]);
      digitalWrite(IN3, stepsMatrix_half_step[Step][6]);
      digitalWrite(IN4, stepsMatrix_half_step[Step][7]);
//     delay(2);
    }
}
}