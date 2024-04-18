void GetDataFromMATLAB(){
  Serial.println(F("Getting data from MATLAB"));
  Serial.println(F("ready for data"));
  Serial.readStringUntil('\n');
  for( target = 0; target < 6; target ++){
    String dataString1 = Serial.readStringUntil('\n');
    String dataString2 = Serial.readStringUntil('\n');
    int stripeNum = dataString1.toInt();
    //Serial.println("Str1 is " + dataString1);
    driveTo[target] = stripeNum;
    float distanceRead = dataString2.toFloat();
    //Serial.println("Str2 is " + dataString2);
    xTargetVec[target] = distanceRead;
    Serial.print(F("For target "));
    Serial.print(target);
    Serial.print(F(", drive to stripe "));
    Serial.print(driveTo[target]);
    Serial.print(F(" and aim for "));
    Serial.print(xTargetVec[target], 3);
    Serial.println(F("m"));
  }

  //Hardcoded offsets for targets 0 and 5 to shoot while moving
  //taken with an average time to target of 0.6s, multiplied by a 0.04m/s velocity 
  driveTo[0] = driveTo[0];// - 1;
  driveTo[5] = driveTo[5];// + 1;

  target = 0;
  
}