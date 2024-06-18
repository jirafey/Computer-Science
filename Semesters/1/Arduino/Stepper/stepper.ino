int pin[]{8,9,10,11};

unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
int rows = 8;
int cols = 4;
int step = 0;

int steps_matrix[8][4] = {
    {0, 0, 0, 1},
    {0, 0, 1, 1}, 
    {0, 0, 1, 0}, 
    {0, 1, 1, 0}, 
    {0, 1, 0, 0}, 
    {1, 1, 0, 0},
    {1, 0, 0, 0}, 
    {1, 0, 0, 1} 
};


void rotate(int choice, float interval) {
  currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    switch (choice) {
        case 0:
            digitalWrite(pin[0], steps_matrix[(step%4)*2][0]);
            digitalWrite(pin[1], steps_matrix[(step%4)*2][1]);
            digitalWrite(pin[2], steps_matrix[(step%4)*2][2]);
            digitalWrite(pin[3], steps_matrix[(step%4)*2][3]);
            break;        
        case 1:
            digitalWrite(pin[0], steps_matrix[(step%4)*2+1][0]);
            digitalWrite(pin[1], steps_matrix[(step%4)*2+1][1]);
            digitalWrite(pin[2], steps_matrix[(step%4)*2+1][2]);
            digitalWrite(pin[3], steps_matrix[(step%4)*2+1][3]);
            break;
        case 2:
            digitalWrite(pin[0], steps_matrix[step%8][0]);
            digitalWrite(pin[1], steps_matrix[step%8][1]);
            digitalWrite(pin[2], steps_matrix[step%8][2]);
            digitalWrite(pin[3], steps_matrix[step%8][3]);
            break;
      }step++;
  }
 }
  void setup() {
    for (int i=0; i<4; i++){
        pinMode(pin[i], OUTPUT);
    }

  }
  
  void loop() {
          
        rotate(1, 2.5);

    }
