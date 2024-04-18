
/****************************
 ** User-Defined Functions **
 ****************************/
// create custom headers as necessary to clearly organize your sketch
// e.g., Button functions, DC Motor functions, Servo functions, etc.
void ReadButtons(){
  // Keep track of the previous button number
  int prevButtonNumber = buttonNumber;
  // Read the button value
  int buttonValue = analogRead(buttonPin);
  // Determine the button number that corresponds to the button value
  if( buttonValue < 5){
    buttonNumber = 1;
  }
  else if (buttonValue > 115 && buttonValue < 175 ){
    buttonNumber = 2;
  }
  else if (buttonValue > 305 && buttonValue < 365){
    buttonNumber = 3;
  }
  else if (buttonValue > 480 && buttonValue < 540){
    buttonNumber = 4;
  }
  else if (buttonValue > 715 && buttonValue < 775){
    buttonNumber = 5;
  }
  else if (buttonValue > 1015 ){
    buttonNumber = 0;
  }
  else{
    buttonNumber = -1;
  }

  // Determine if the button number is an actual button press or a bounce
  if( buttonNumber == prevButtonNumber){
    cibn ++;
    if(cibn > 100){
      buttonPressed = buttonNumber;
    }
  }
  else{
    cibn = 0;
  }

}


void TurnMotorOn(){
  // only worked if if statements are commented out
  if (motorOn == 0){
    digitalWrite(motorDirPin, motorRight);
    analogWrite(motorPowPin, motorPower);
    motorOn = 1;
  }
}


void TurnMotorOff( int reverseTime){
  if (motorOn == 1){
    analogWrite(motorPowPin, 0);
    delay(10);
    digitalWrite(motorDirPin, !motorRight);
    analogWrite(motorPowPin, motorPower);
    delay(reverseTime);
    analogWrite(motorPowPin, 0);
    motorOn = 0; 
  }
}


bool GetEncoderBoolean(){
  irSensorValue = analogRead(irSensorPin);
  if (black == 1 && irSensorValue < 55){
    return 0;
  }
  else if (black == 0 && irSensorValue > 660){
    return 1;
  }
  return black;
}


void CountStripes(){
  int prevBlack = black;
  black = GetEncoderBoolean();
  tslStripeChange = millis() - stripeChangeTime;
  if (black != prevBlack){
    stripeChangeTime = millis();
    if( motorRight == 1){
      counts ++;
    }
    else{
      counts --;
    }

    /*Serial.print(F("Stripe count: "));
    Serial.print(counts);
    Serial.print(F("\tTime since last stripe change: "));
    Serial.println(tslStripeChange);*/
  } 
}