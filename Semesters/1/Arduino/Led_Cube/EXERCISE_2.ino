int led[]        = { 2, 3, 4, 5, 6, 7, 8, 9, 10};
int pin[]        = { 11,12,13};
int fast = 200;
int normal = 1000;
// the setup function runs once when you press reset or power the board
void setup() {
for( int i=0; i<9; i++ )pinMode(led[i], OUTPUT);	
}

void loop() {
for( int j=0; j<3; j++){
	pinMode(pin[j], OUTPUT);
	for( int i=0; i<9; i++ ){
		digitalWrite(led[i], HIGH);
		delay(fast);
		digitalWrite(led[i], LOW);
		}
	pinMode(pin[j], INPUT);

	}		
}



