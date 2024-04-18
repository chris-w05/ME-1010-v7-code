void ComputeStuff(){
  Serial.println(F("performing target calculations"));
  float d[] = {0.0876, 0.1190};
  float H[] = {0.0866, 0.075, 0.106, 0.0250};
  TargetServoAngle(d, kappa, lambda, H, alpha, beta, thetaL0, xTargetVec);

  for( int i = 0; i < 6; i ++){
    Serial.print(F("To hit a target at "));
    Serial.print(xTargetVec[i]);
    Serial.print(F(" m, command the servo to "));
    Serial.print(writeToServo[i]);
    Serial.println(F(" deg"));
  }
  target = 0;
  stuffComputed = true;
  firstHome = false;
}

float Deg2Rad( float angleDeg){
  return angleDeg * M_PI/180;
}

float Rad2Deg( float angleRad){
  return angleRad * 180/M_PI;
}


float Quadratic( float a, float b, float c, int plusOrMinus){
  plusOrMinus /= abs(plusOrMinus);
  return (-1 * b + plusOrMinus * sqrt(b*b - 4 * a * c))/(2 * a);
}

float LandingDistance( float d[], float kappa, float lambda, float theta){
  const float g = 9.81; // m/s^2
  float d1 = d[0];
  float d2 = d[1];
  float v0 = kappa + lambda * theta;
  theta = Deg2Rad(theta); // from now on theta is in radians
  float x0 = cos(theta) * d2;
  float y0 = d1 + sin(theta) * d2; 
  float v0x = v0 * cos(theta);
  float v0y = v0 * sin(theta);
  float landingTime = Quadratic(-.5*g, v0y, y0, -1);
  float landingDistance = x0 + v0x * landingTime; 
  //Serial.println(landingDistance);
  return landingDistance; 
}


//ignore this

//finds angle that produces longest shot
float RangeAngle(float d[], float kappa, float lambda){ //returns angle in deg
//   float d1 = d[0];
//   float d2 = d[1];
//   const float stepSize = 0.05;
//   float lastDistance = 0;
//   float launchAngle = 45;
//   float distance = LandingDistance(d, kappa, lambda, launchAngle);
//   launchAngle += stepSize;
//   //set variable distance in the condition of the while statement to minimize number of times LandingDistance is called.
//   //otherwise the program will call LandingDistance for values of launchAngle that are already known.
//   // while( (lastDistance < (distance = LandingDistance(d, kappa, lambda, launchAngle))) && launchAngle <= 90 ){
//   //   lastDistance = distance;
//   //   launchAngle += stepSize;
//   // }


// // Serial.println(launchAngle);
//   return launchAngle;


  
//   //Serial.println(launchAngle);
//   //return launchAngle;
  return 39.8;
}

//finds steeper of two angles to hit specified distance
//returns nan if shot is outside the range of the cannon
float LaunchAngle(float d[], float kappa, float lambda, float targetDistance) {
  float d1 = d[0];
  float d2 = d[1];
  float rangeAngle = RangeAngle(d, kappa, lambda);
  float maxRange = LandingDistance(d, kappa, lambda, rangeAngle);
  if (targetDistance > maxRange) {
      //Serial.print("out of range");
      return NAN;
  }
  
  const float stepSize = 0.5; 
  float low = rangeAngle;
  float high = 90; // Maximum launch angle
  float launchAngle = low;
  float distance = maxRange;

  //optimized to O(logn)
  while (low <= high) {
      float mid = (low + high) / 2;
      distance = LandingDistance(d, kappa, lambda, mid);
      if (distance > targetDistance) {
          low = mid + stepSize; // Update lower bound
          launchAngle = mid; // Update launch angle
      } else {
          high = mid - stepSize; // Update upper bound
      }
      //Serial.println("in loop");
  }
  return launchAngle;
}


float ThetaServo(float H[], float thetaL, float alpha, float beta, float thetaL0){
  thetaL = Deg2Rad(thetaL);
  alpha = Deg2Rad(alpha);
  thetaL0 = Deg2Rad(thetaL0);
  //Compute K vals
  float k1 = H[0]/H[1];
  float k2 = H[0]/H[3];
  float k3 = ( H[0]*H[0] + H[1]*H[1] - H[2]*H[2] + H[3]*H[3] )/( 2*H[1]*H[3] );
  //Compute theta2
  float theta2 = thetaL + thetaL0;
  //compute a, b, c coeffecients for quadratic
  float a = cos(theta2) - k1 - k2*cos(theta2) + k3;
  float b = -2*sin(theta2);
  float c = k1 - ( k2 + 1 )*cos(theta2) + k3;
  //compute theta4
  float theta4 = 2 * atan((-b - sqrt( b*b - 4*a*c))/(2*a));
  //compute thetaS
  float thetaS = (theta4 + alpha)/(1 - beta);
  return Rad2Deg(thetaS);
}

void TargetServoAngle(float d[], float kappa, float lambda, float H[], float alpha, float beta, float thetaL0, float xTargetVec[]){
  float launchAngles[6];
  float servoAngles[6];
  for( int i = 0; i < 6; i ++){
    Serial.print(F("Computing target "));
    Serial.println(i);
    launchAngles[i] = LaunchAngle(d, kappa, lambda, xTargetVec[i]);
    servoAngles[i] = ThetaServo(H, launchAngles[i], alpha, beta, thetaL0);
    writeToServo[i] = int(round(servoAngles[i]));

    // Serial.print("xTarget [m] = ");
    // Serial.print(xTargetVec[i]);
    // Serial.print("\tthetaL [deg] = ");
    // Serial.print(launchAngles[i]);
    // Serial.print("\tthetaS [deg] = ");
    // Serial.print(servoAngles[i]);
    // Serial.print("\trounded thetaS [deg] = ");
    // Serial.println(writeToServo[i]);
  }

}