void MoveLauncher(){
  //DebugPrint("Calling MoveLauncher function; startMotion = ", startMotion);
  //Serial.print("Calling MoveLauncher function; startMotion = ");
  if(driveTo[target] > reloadStripe)){
    targetBeyondReloader = true;
  }
  else{
    targetBeyondReloader = false;
  }

  if(motorOn){
    Moving();

    if( !stuffComputed && firstHome){
      Serial.println("Computing Stuff");
      ComputeStuff();
    }
  }
  else{
    if(startMotion){
      PreparingToMove();
    }
    else{
      NotMoving();
    }
  }

  //dispensing while moving  
  if( ((counts > reloadStripe  && motorRight) || rightSwitchState) && !reloadComplete ){
    //reloadServo.write(dispenseAngle);
    AtReloader();
  }
  else if( !motorRight){// && reloadTime > dispenseDuration){
    reloadServo.write(holdAngle);
  }



  


}

void PreparingToMove(){
  //set desiredPosition
  if( userInput == 'k' || userInput == 'v'){
    switch( headed){
      case 0:
        leftSwitchState = digitalRead(leftSwitchPin);
        if(leftSwitchState){
          //Serial.println(F("Already Home!"));
          counts = 5;
          desiredPosition = 5;
          startMotion = 0;
          headed = 1;
        }
        else{
          //Serial.println(F("Headed home"));
          desiredPosition = -50;
        }
      break;

      case 1:
        desiredPosition = driveTo[target];
      break;

      case 2:
        desiredPosition = 100;
      break;
    }
  }

  // set motorRight
  if( desiredPosition > counts ){
    motorRight = 1; //need to move right
  }
  else{
    motorRight = 0; //need to move left
  }
  // turn motor on
  if( counts != desiredPosition){
    TurnMotorOn();
    startMotion = 0;
  }
}

void Moving(){
  // count stripes
  CountStripes();
  // stop at target

  //old code
  // if( counts == desiredPosition){ 
  //   TurnMotorOff(10);
  //   CountStripes();
  //   Serial.print("Launcher at stripe ");
  //   Serial.println(counts);
  // }

  

  if( counts == desiredPosition ){
    //if the target is one that requires turning around
    //if ( target != 0 && target != 5 ){ 
      TurnMotorOff(10);
    //}
    AtTarget();
    CountStripes();
    /*
    Serial.print("Launcher at stripe ");
    Serial.println(counts);*/

  }


  //change angle while moving
  if( target == 0 && counts < driveTo[0]){
    desiredServoAngle = writeToServo[0];
    launcherServo.write(desiredServoAngle);
  }
  else if (!motorRight){
    desiredServoAngle = writeToServo[target];
    launcherServo.write(desiredServoAngle);
  }

  // read switches
  leftSwitchState = digitalRead(leftSwitchPin);
  rightSwitchState = digitalRead(rightSwitchPin);
  // stop at home (moving left, left switch tripped)
  if( !motorRight && leftSwitchState == 1){
    TurnMotorOff(10);
    CountStripes();
    counts = 5;
    Serial.println("Launcher at home, counts set to 5");
  }
  // stop at reloader (moving right, right switch tripped)
  if( !reloadComplete && motorRight && (rightSwitchState == 1 || counts > reloadStripe)){
    TurnMotorOff(10);
    CountStripes();
    //counts = 43;
    //Serial.println("Launcher at reloader, counts set to 43");
  }
}