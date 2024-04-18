/*******************
 ** Loop Function **
 *******************/
void loop(void) {
  //PUT YOUR MAIN CODE HERE, TO RUN REPEATEDLY

  if (Serial.available() >= 2) {
    userInput = Serial.read();
    // Serial.read();
    // Serial.print(F("user entered "));
    // Serial.println(userInput);
    newUserInput = 1;
  }

  switch (userInput) {
      // case 'a':
      //   if( newUserInput == 1){
      //     //action to happen oonce
      //     newUserInput = 0;
      //   }
      //   //action to happen repeatedly
      // break;

    case 'a':
      if (newUserInput == 1) {
        //action to happen oonce
        //Serial.println("Test a: Check that IR LED is blinking");
        newUserInput = 0;
      }
      //action to happen repeatedly
      TestIRLED();
      break;

    case 'b':
      if (newUserInput == 1) {
        //action to happen oonce
        newUserInput = 0;
        //Serial.println("Test b: Press the switches to test");
      }
      TestSwitches();
      //action to happen repeatedly
      break;

    case 'c':
      if (newUserInput == 1) {
        //action to happen oonce
        newUserInput = 0;
        //Serial.println("Test c: Press buttons to test");
      }
      //action to happen repeatedly
      TestButtons();
      break;

      case 'e':
      if (newUserInput == 1) {
        //action to happen oonce
        //Serial.println("Test e: Press the left and right buttons to test the motor and sensor.");
        newUserInput = 0;
      }
      //action to happen repeatedly
      TestMotor();
      break;

    case 'd':
      if (newUserInput == 1) {
        //action to happen oonce
        //Serial.println("Test d: Move motor with left or right buttons");
        newUserInput = 0;
      }
      //action to happen repeatedly
      TestMotor();
      break;

      case 'f':
      if (newUserInput == 1) {
        //action to happen oonce
        //Serial.println("Test f: Press the left and right buttons to test the motor and encoder.");
        newUserInput = 0;
      }
      //action to happen repeatedly
      TestMotor();
      break;

      case 'g':
      if (newUserInput == 1) {
        //action to happen oonce
        //Serial.println("Test g: Press the left and right buttons to count stripes");
        //Serial.println(" Press the up and down buttons to increment counts");
        //Serial.println(" Press the select button to set counts to 24");
        newUserInput = 0;
      }
      //action to happen repeatedly
      TestMotor();
      break;

      case 'h':
      if (newUserInput == 1) {
        //action to happen oonce
        startMotion = 0;
        newUserInput = 0;
        //Serial.println(F("Test h: Press the left and right buttons to increment desiredPosition"));
        //Serial.println(F(" Press the up and down buttons to increment counts."));
        //Serial.println(F(" Press the select button to send the launcher to the desired position."));
      }
      //action to happen repeatedly
      TestMoveLauncher();
      break;

      case 'i':
      if (newUserInput == 1) {
        //action to happen oonce
        //Serial.println(F("Test i: Press UP/DOWN/LEFT/RIGHT to increment desired servo angle"));
        //Serial.println(F(" Press select button to command the servo and fire the solenoid"));
        newUserInput = 0;
      }
      //action to happen repeatedly
      TestAimFire();
      break;

      case 'j':
      if (newUserInput == 1) {
        //action to happen oonce
        //Serial.println(F("Test j: Press select button to reload a ball"));
        newUserInput = 0;
      }
      //action to happen repeatedly
      TestReloader();
      break;

      case 'k':
      if (newUserInput == 1) {
        //action to happen oonce
        startMotion = 0;
        newUserInput = 0;
        //Serial.println(F("Test k: use left and right to increment headed"));
        //Serial.println(F(" Press the up and down buttons to increment target."));
        //Serial.println(F(" Press the select button to start demo 1."));
      }
      //action to happen repeatedly
      Demo1();
      break;

      case 'z':
      if (newUserInput == 1) {
        //action to happen oonce
        newUserInput = 0;
        PrintMenu();
      }
      break;

      case 's':
       GetDataFromMATLAB();
       userInput = 'x';
       //Serial.println(F("done"));
      break;

      case 't':
       GetDataFromMATLAB();
       ComputeStuff();
       userInput = 'x';
       //Serial.println(F("done"));
      break;

      case 'v':
      if (newUserInput == 1) {
        //action to happen once
        startMotion = 1;
        newUserInput = 0; //dont delete
        state = 1;
        firstHome = false;
        Serial.println(F("Running Demo 4/competition code"));
        GetDataFromMATLAB();
      }
      //action to happen repeatedly
      Demo1();
      break;

    default:
      if (newUserInput == 1) {
        //action to happen oonce
        newUserInput = 0;
        TurnMotorOff(5);
        //Serial.println(F("Aborting"));
        startMotion = 0;
        headed = 0;
        target = 0;
        state = 0;
        digitalWrite( solenoidPowPin, LOW); 
        //Serial.println(F("Waiting for a valid input"));
        //Serial.println(F("enter z to print menu"));
      }
      break;
  }

}  // end loop() function