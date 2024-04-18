void TestMotor() {
  int prevButtonPressed = buttonPressed;
  ReadButtons();
  switch (buttonPressed) {
    case 3: //Up
    case 1:
      //NEW 2
      tslIncrement = millis() - incrementTime;
      if( (prevButtonPressed != buttonPressed) || (tslIncrement > 250)){
        incrementTime = millis();
        if(buttonPressed == 3){
          counts ++;
        }
        else{
          counts --;
        }
        Serial.print(F("Counts: "));
        Serial.println(counts);
      }
      //counts --;
      //Serial.println("Down button pressed");
      break;
    case 4:
      motorRight = 0;
      TurnMotorOn();
      //Serial.println("Left button pressed");
      break;
    case 2:
      motorRight = 1;
      TurnMotorOn();
      break;
    case 5:
    //NEW 3
      if( counts != 24){
        counts = 24;
        Serial.print("Counts: ");
        Serial.println(counts);
      }
      //Serial.println("Select button pressed");
      break;
    case 0:
      TurnMotorOff(10);
      //NEW 4
      if( userInput == 'g'){
        CountStripes();
      }
      //Serial.println("No buttons pressed");
      break;
    default:
      break;
      //Serial.println("Something went wrong
  }
  if (motorOn){
    switch (userInput){
    case 'd':
    PrintLeftRight();
    break;
    case 'e':
    PrintSensorValue();
    break;
    case 'f':
    PrintBlackWhite();
    break;
    case 'g':
    //NEW 5
    CountStripes();
    break;
    }
    
  }
}

void PrintLeftRight(){
  tslPrint = millis() - printTime;
  printInterval = 250;
  if (tslPrint > printInterval){
    printTime = millis();
    Serial.print(F("Launcher is moving"));
    if (motorRight){
    Serial.println(F(" Right"));
    }
    else{
    Serial.println(F(" Left"));
    }
  }
}

void PrintSensorValue(){
  irSensorValue = analogRead(irSensorPin);
  tslPrint = millis() - printTime;
  if (tslPrint > 50){
    printTime = millis();
    Serial.print(F("The IR sensor value is "));
    Serial.println(irSensorValue);
  }
}

void PrintBlackWhite(){
  bool prevBlack = black;
  black = GetEncoderBoolean();
if (black != prevBlack){
   if (black){
    Serial.println(F("Over Black"));
  }
  else{
    Serial.println(F("Over White"));
  }
}
}