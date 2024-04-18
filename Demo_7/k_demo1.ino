void Demo1( ){
  int prevButtonPressed = buttonPressed;
  ReadButtons();

  switch( buttonPressed){
    case 3:
    case 1:
      tslIncrement = millis() - incrementTime;
      if( prevButtonPressed != buttonPressed || tslIncrement > 250 ){
        incrementTime = millis();
        if(buttonPressed  == 3 ){
          target ++;
        }
        else if(buttonPressed == 1){
          target --;
        }
        target = constrain(target, 0, 5);
        //Serial.print(F("Target num is: "));
        //Serial.println(target);
      }
    break;

    case 4:
    case 2:
      tslIncrement = millis() - incrementTime;
      if( prevButtonPressed != buttonPressed || tslIncrement > 250 ){
        incrementTime = millis();

        if(buttonPressed  == 4 ){
          headed --;
        }
        else if(buttonPressed == 2){
          headed ++;
        }
        headed = constrain(headed, 0, 2);
        //Serial.print(F("Headed is: "));
        //Serial.println(headed);
      }
    break;

    case 5:
      startMotion = 1;
      state = 1;
    break;

    case 0:
      MoveLauncher();
    break;

  }
}