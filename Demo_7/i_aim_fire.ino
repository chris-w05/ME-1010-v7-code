void TestAimFire(){
  // //UP and DQWn to move servo up and down 5 deg
  // //Lest anf RIGHT to move servo by 1 degrees
  // int prevButtonPressed = buttonPressed;
  // ReadButtons();
  // switch(buttonPressed){
  //   case 3: //UP
      
  //   case 1: //DOWN

  //   case 4:

  //   case 2:
  //   switch( buttonPressed ){
  //     case 3: //UP
  //       servoAngleIncrement = 5;
  //     break;
  //     case 1: //DOWN
  //       servoAngleIncrement = -5;
  //     break;
  //     case 4: //LEFT
  //       servoAngleIncrement = -1;
  //     break;
  //     case 2: //RIGHT
  //       servoAngleIncrement = 1;
  //     break;
  //   }
  //   tslIncrement = millis() - incrementTime;
  //   if( buttonPressed != prevButtonPressed || tslIncrement > 250){
  //     incrementTime = millis();
  //     desiredServoAngle += servoAngleIncrement;
  //     desiredServoAngle = constrain(desiredServoAngle, 0, 180);
  //     Serial.print(F("The servo angle is: "));
  //     Serial.println(desiredServoAngle);
  //   }
  //   break;

  //   case 5:
  //     if( buttonPressed != prevButtonPressed ){
  //         if(state > 0){
  //           Serial.println(F("Previous aim/fire sequence is still in progress"));
  //         }
  //         else{
  //           state = 1;
  //           stateChangeTime = millis();
  //         }
  //       }
  //   break;

  //   case 0:
  //   break;

  //   default:
  //   break;
  // }

  // int waitTime = 50;

  // switch(state){
  //   case 1:
  //     //delay, command servo
  //     tslStateChange = millis() - stateChangeTime;
  //     if(tslStateChange > waitTime){
  //       //command the servo
  //       launcherServo.write(desiredServoAngle);
  //       Serial.print(F("Launch servo commanded to: "));
  //       Serial.println(desiredServoAngle);
  //       //change state, update time
  //       state = 2;
  //       stateChangeTime = millis();
  //     }
  //   break;

  //   case 2:
  //     //delay, then turn solenoid on
  //     tslStateChange = millis() - stateChangeTime;
  //     if(tslStateChange > waitTime){
  //       //turn solenoid on
  //       digitalWrite( solenoidPowPin, HIGH);
  //       Serial.println("Firing!");
  //       //change state, update time
  //       state = 3;
  //       stateChangeTime = millis();
  //     }
  //   break;

  //   case 3:
  //     //delay then turn solenoid off
  //     tslStateChange = millis() - stateChangeTime;
  //     if(tslStateChange > solenoidActivationTime){
  //       //turn solenoid off
  //       digitalWrite( solenoidPowPin, LOW);
  //       Serial.println(F("Done firing"));
  //       //change the state
  //       state = 0;
  //     }
  //   break;
  // }
}