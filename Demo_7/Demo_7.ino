/****************************************************************
Author Names: Christopher Wall, Blake Martin
Lab section: 15
Team number: 1
Date:  3/15/2024
Sketch Description:  Lab 6 testing sketch

Button Usage: Up/Down    -  
              Left/Right -  
              Select     -  

Pin Usage:    Pin type/number     Hardware 
              13                  IR LED                 
              11                  right switch
              12                  left switch
              A7                  buttons
              9                   Angle servo
              10                  Reload servo
              6                   Solenoid
*******************************************************************/
 
/****************************
 ** #defines and #includes **
 ****************************/ 
 #include <Servo.h>



/***********************
 ** Global Variables ***
 ***********************/

// *** Declare & Initialize Pins ***
int ledPin = 13;
int debugLedPin = 13;
int leftSwitchPin = 11;
int rightSwitchPin = 12;
int buttonPin = A7;
int motorDirPin = 4;
int motorPowPin = 5;
int irSensorPin = A5;
int launcherServoPin = 9;
int solenoidPowPin = 6;
int reloadServoPin = 10;




// *** Create Servo Objects ***
Servo launcherServo;
Servo reloadServo;



// *** Declare & Initialize Program Variables ***
//LED test variables
int ledOnDuration = 1000;
int ledOffDuration = 2000;
unsigned long blinkTime = 0;
unsigned long tslBlink = 0;
bool ledOn = 0;

//Switch test variables
int leftSwitchState = 0;
int rightSwitchState = 0;
unsigned long printTime = 0;
unsigned long tslPrint = 0;
int printInterval = 2000;
unsigned long leftSwitchChangeTime = 0;
unsigned long rightSwitchChangeTime = 0;
unsigned long tslLeftSwitchChange = 0;
unsigned long tslRightSwitchChange = 0;
int switchDebounceInterval = 20;

//Debug variables
unsigned long tslDebugPrint = 0;
unsigned long tslDebugBlink = 0;
unsigned long debugPrintTime = 0;
unsigned long debugBlinkTime = 0;
unsigned long debugPrintInterval = 220;
bool debugLedHiLo;

//Button test variables
int buttonNumber = 0;
unsigned long cibn = 0;
int buttonPressed = 0;

char userInput = 'z';

bool newUserInput = 1; //1 means user just entered a number, 0 means user did not enter a number

// Motor Test variables
bool motorOn = 0;
bool motorRight = 0;
const int motorPower = 255;

// Sensor Variables
int irSensorValue;

//Boolean Variables
bool black = 1;

//Encoder variables
unsigned long stripeChangeTime = 0;
unsigned long tslStripeChange = 0;
int counts = 24;

unsigned long incrementTime = 0;
unsigned long tslIncrement = 0;

//Moving motor to position vars
bool startMotion = 0;
int desiredPosition = 24;

//LAB 8
int desiredServoAngle = 80;
int servoAngleIncrement = 5;
int state = 0;
unsigned long stateChangeTime = 0;
unsigned long tslStateChange = 0;
int solenoidActivationTime = 31; //ms previously 31
int holdAngle = 30;
int dispenseAngle = 0;
int dispenseDuration = 230;//ms //230
int launcherReloadAngle = 132;

/* DEMO variables */

int target = 0;
int headed = 0;
int driveTo[] = {19, 35, 33, 31, 32, 34};
float xTargetVec[] = {0.5, 0.6, 0.7, 0.8, 0.9, 1.0};

int writeToServo[] = {140, 110, 130, 90, 120, 80};
float alpha = 5.5932;
float beta = 0.083;
float thetaL0 = 28.0968;
float kappa = 3.0445; // previously 2.9945
float lambda = -0.00135; //previously -0.0013

//unsigned long reloadTime = 0;
int reloadStripe = 36;
bool stuffComputed = false;
bool firstHome = false;
/********************
 ** Setup Function **
 ********************/  
void setup(void){
  // PUT YOUR SETUP CODE HERE, TO RUN ONCE:

  // *** Initialize Serial Communication ***
  Serial.begin(9600);
  // *** Configure Digital Pins & Attach Servos ***
  pinMode(ledPin, OUTPUT);
  pinMode(leftSwitchPin, INPUT_PULLUP);
  pinMode(rightSwitchPin, INPUT_PULLUP);
  pinMode(motorDirPin, OUTPUT);
  pinMode(motorPowPin, OUTPUT);
  launcherServo.attach(launcherServoPin);
  pinMode(solenoidPowPin, OUTPUT);
  reloadServo.attach(reloadServoPin);
  // *** Take Initial Readings ***
  GetEncoderBoolean();
  // *** Move Hardware to Desired Initial Positions *

  reloadServo.write(holdAngle);
}// end setup() function
