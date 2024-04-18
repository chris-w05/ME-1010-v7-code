

void NotMoving(){
  leftSwitchState = digitalRead(leftSwitchPin);
  rightSwitchState = digitalRead(rightSwitchPin);

  //at home
  if(leftSwitchState){
    AtHome();
  }
  //at reloader
   else if(rightSwitchState || counts > reloadStripe){
     AtReloader();
   }
  //at target
  else if(desiredPosition == counts){
    AtTarget();
  }
}


void AtReloader(){
  switch( state){
    case 1://dispense ball
      //command the servo
      reloadServo.write(dispenseAngle);
      //Serial.println(F("dispensing"));
      //change state, update time
      reloadComplete = false;
      state = 2;
      stateChangeTime = millis();
      //reloadTime = stateChangeTime;
    break;

    case 2: //delay then stop dispensing
       tslStateChange = millis() - stateChangeTime;
      if( tslStateChange > dispenseDuration){
        //command servo
        reloadComplete = true;
        reloadServo.write(holdAngle);
        //Serial.println("Holding");
        //change state, update time
        state = 3;
        stateChangeTime = millis();
      }
    break;

    case 3: //delay then set motion variables
      tslStateChange = millis() - stateChangeTime;
      if(tslStateChange > 10){
        //set motion variables
        startMotion = 1;
        headed = 1;
        target ++;
        //Serial.println(F("ball reloaded - setting motion variables"));
        //change the state
        state = 1;
      }
    break;
  }
}

void AtHome(){
  switch(state){
    case 1: //turn LED on 
      digitalWrite( ledPin , HIGH);
      Serial.println(F("Starting timer - LED on"));
      //change state, update time
      state = 2;
      stateChangeTime = millis();
    break;

    case 2: //delay then turn LED off
      tslStateChange = millis() - stateChangeTime;
      if(tslStateChange > 1000){                          //LED DELAY TIME AT START
        //turn LED off
        digitalWrite( ledPin , LOW);
        Serial.println(F("Triggering timer, LED off"));
        //change state
        state = 3;
      }
    break;

    case 3: //set motion variables
      //Serial.println(F("Setting motion variables"));
      if( target < 5){
        if( target == 0 && userInput == 'v'){
          //Serial.println(F("Calling ComputeStuff()"));
          ComputeStuff();
          firstHome = true;
        }
        startMotion = 1;
        headed = 1;
        //change state
        state = 1;
        //sets launcher angle to angle to shoot at target
        
      }
      else{
        target = 0;
        state = 0;
        Serial.println(F("All done."));
        userInput = 'x';
        if( userInput == 'v'){
          Serial.println(F("Done"));
        }

      }
    break;
  }
}

void AtTarget(){
  int waitToShoot = 75;

  switch( state ){
    case 1: //command launcher servo to firing angle
      //command launcher servo
      desiredServoAngle = writeToServo[target];
      launcherServo.write(desiredServoAngle);
      //Serial.print(F("Commanding Launcher servo to "));
      //Serial.print(desiredServoAngle);
      //Serial.print(F(" for target "));
      //Serial.println(target);
      //change state, update time
      state = 2;
      stateChangeTime = millis();
    break;

    case 2: //delay then turn solenoid on
      tslStateChange = millis() - stateChangeTime;
      if(tslStateChange > waitToShoot){
        //turn solenoid on 
        digitalWrite(solenoidPowPin, HIGH);
        ////Serial.println(F("Firing!"));
        //change state, update time
        state = 3;
        stateChangeTime = millis();
    }
    break;

    case 3: //delay then turn solenoid off
      tslStateChange = millis() - stateChangeTime;
      if(tslStateChange > solenoidActivationTime){
        //turn solenoid off
        digitalWrite(solenoidPowPin, LOW);
        ////Serial.println(F("Done firing"));
        //change state, update time
        state = 4;
        stateChangeTime = millis();
        reloadComplete = false;
        Serial.println("Current target is:" + String(target));
      }
    break;

    case 4: //delay then command launcher servo to reload angle
      tslStateChange = millis() - stateChangeTime;
      if(tslStateChange > 1){
        //commmand launcher servo
        launcherServo.write(launcherReloadAngle);
        ////Serial.println(F("Commanding launcher servo to reload angle"));
        //change state
        state = 5;
      }
    break;

    case 5: //set the motion variables
      ////Serial.println(F("Target actions complete - setting motion variables"));
      startMotion = 1;
      if( target < 5){
        headed = 2;
      }
      else{
        headed = 0;
      }
      //change state
      state = 1;
  }
}
