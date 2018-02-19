#ifndef PAYLOADMOTOR_H
#define PAYLOADMOTOR_H

/* Arduino pin definition */
#define PHASES    2
#define STEP      3
#define DIRECTION 4
#define CLK       5
#define INHIBIT   8
#define BUSY      9
#define HOME      10

/* Motor constants */
#define STEPS           20                //number of steps per motor rotation (without gearbox)
#define GEAR_RATIO      16                //16:1 ratio on the gearbox
#define TOTAL_STEPS     STEPS*GEAR_RATIO  //amount of steps required for the output shaft to go through one full rotation
#define ROTATION_PERIOD 16                //time in seconds required to complete one full rotation (4s for 90deg)
#define CLK_PERIOD      ROTATION_PERIOD/TOTAL_STEPS

/* Constants for motor control */
#define ON      0 //for use with setState()
#define OFF     1 //for use with setState()
#define CCW     0 //for use with setDir()
#define CW      1 //for use with setDir()
#define TWO_PH  0 //for use with setPhase()
#define ONE_PH  1 //for use with setPhase()

class PayloadMotor{
  public:
    void    setState(uint8_t);
    void    setDir(uint8_t dir);
    void    setPhase(uint8_t phase);
    uint8_t getBusyState();
    uint8_t getHomeState();
    void    rotate();
    void    rotate90();
};

void    setState(uint8_t);
void    setDir(uint8_t dir);
void    setPhase(uint8_t phase);
uint8_t getBusyState();
uint8_t getHomeState();
void    rotate();
void    rotate90();

//FUNCTIONS
void PayloadMotor(){
  pinMode(INHIBIT,  OUTPUT);
  setState(OFF);
  pinMode(PHASES,   OUTPUT);
  setPhase(TWO_PH);
  pinMode(STEP,     OUTPUT);
  pinMode(DIRECTION,OUTPUT);
  setDir(CW);
  pinMode(CLK,      OUTPUT);
  digitalWrite(CLK,0);
  pinMode(BUSY,     INPUT);
  pinMode(HOME,     INPUT);
}
void setState(uint8_t state){
  digitalWrite(INHIBIT,state);
}
void setDir(uint8_t dir){
  digitalWrite(DIRECTION,dir);
}
void setPhase(uint8_t phase){
  digitalWrite(PHASES,phase);
}
uint8_t getBusyState(){
  return digitalRead(BUSY);
}
uint8_t getHomeState(){
  return digitalRead(HOME);
}
void rotate(){
  digitalWrite(CLK,1);
  delay(CLK_PERIOD/2);
  digitalWrite(CLK,0);
  delay(CLK_PERIOD/2);
}
void rotate90(){
  for(uint8_t i = 0; i < TOTAL_STEPS/4; i++){
    rotate();
  }
}
#endif
