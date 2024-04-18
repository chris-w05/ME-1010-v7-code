void TestReloader(){
  // int prevButtonPressed = buttonPressed;
  // ReadButtons();
  // switch( buttonPressed ){
  //   case 5://SELECT
  //     if( buttonPressed != prevButtonPressed ){
  //       if( state > 0){
  //         Serial.println("Previous reload is still in progress");
  //       }
  //       else{
  //         state = 1;
  //       }
  //     }
  //   break;
  // }

  // switch( state ){
  //   case 1: //command reload servo to dispense angle
  //     //command servo
  //     reloadServo.write(dispenseAngle);
  //     Serial.println("Dispensing");
  //     //change state, update time
  //     state = 2;
  //     stateChangeTime = millis();
  //   break;

  //   case 2: //delay, then commad servo to hold angle
  //     tslStateChange = millis() - stateChangeTime;
  //     if( tslStateChange > dispenseDuration){
  //       //command servo
  //       reloadServo.write(holdAngle);
  //       Serial.println("Holding");
  //       //change state
  //       state = 0;
  //     }
  //   break;

  // }
}