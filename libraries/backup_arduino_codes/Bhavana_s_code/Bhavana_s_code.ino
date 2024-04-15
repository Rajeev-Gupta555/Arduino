int encPin[4] = {33, 2, 35, 3};
//int encPin[4] = {35, 3, 33, 2};
volatile int counterx = 0, countery = 0;
const double pi = 3.1415926535897932384626433832795;
double x = 0.0, y = 0.0;
float disx, disy, disx1, disy1;
void enc_read()
{
  disx = counterx * 5.8 * pi / 600.0;
  disy = countery * 5.8 * pi / 600.0;
  if(disx!=disx1 || disy!=disy1){
  Serial.print("disx = ");
  Serial.print(disx);
  Serial.print("disy = ");
  Serial.print(disy);
  Serial.println();
  }
  disx1=disx;
  disy1=disy;
 }

void ai0()
{
  if (digitalRead(encPin[0]) == LOW)
    counterx--;
  else
    counterx++;
}
void ai1()
{
  if (digitalRead(encPin[2]) == LOW)
    countery++;
  else
    countery--;
}
 
void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 4; i++)
    pinMode(encPin[i], INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encPin[1]), ai0, RISING);
  attachInterrupt(digitalPinToInterrupt(encPin[3]), ai1, RISING);
}

void loop(){
  enc_read();
}
