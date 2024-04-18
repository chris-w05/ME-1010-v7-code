void TestSwitches(){
  // // Keep track of previous switch states for comparison
  // int prevLeftSwitchState = leftSwitchState;
  // int prevRightSwitchState = rightSwitchState;

  // // Update the switch state variables
  // int tempLeftSwitchState = digitalRead(leftSwitchPin);
  // int tempRightSwitchState = digitalRead(rightSwitchPin);
  
  // //Left switch debounce code
  // if( tempLeftSwitchState != prevLeftSwitchState){
  //   tslLeftSwitchChange = millis() - leftSwitchChangeTime;
  //   if( tslLeftSwitchChange > switchDebounceInterval ){
  //     leftSwitchChangeTime = millis();
  //     leftSwitchState = tempLeftSwitchState;
  //   }
  // }
  // //Right switch debounce code
  // if( tempRightSwitchState != prevRightSwitchState){
  //   tslRightSwitchChange = millis() - rightSwitchChangeTime;
  //   if( tslRightSwitchChange > switchDebounceInterval ){
  //     rightSwitchChangeTime = millis();
  //     rightSwitchState = tempRightSwitchState;
  //   }
  // }


  // // If appropriate, print a new message
  // tslPrint = millis() - printTime;
  // if( ((prevLeftSwitchState != leftSwitchState) || 
  // (prevRightSwitchState != rightSwitchState) ) || 
  // (tslPrint > printInterval) ){
  //   printTime = millis();
  //   Serial.print(F("The left switch is "));
  //   Serial.print(leftSwitchState);
  //   Serial.print(F("\tThe right switch is "));
  //   Serial.println(rightSwitchState);
  // }
}