//Transmitter Code

#include <Wire.h> //Include the Wire library
#include <RH_ASK.h> //Include the RH_ASK library

RH_ASK rf_driver; //create object
char* msg="100"; //Store the msg to be sent
void setup() {
  
  Serial.begin(9600); //For debugging
  
  Wire.begin();                      
  Wire.beginTransmission(0x68); //0x68 is I2C slave address of MPU6050      
  Wire.write(0x6B); //Accessing register 6B - Power Management(comes up in SLEEP mode upon power-up)             
  Wire.write(0x00); //Setting SLEEP register to 0                
  Wire.endTransmission(true); //true sends a stop msg

  if (!rf_driver.init()) //Check initialisation of object
      Serial.println("init failed");
}

void loop() {
    Wire.beginTransmission(0x68); //Starts transmission with I2C slave address of MPU6050
    Wire.write(0x3B); //Starting register for Accel Readings
    Wire.endTransmission();
    Wire.requestFrom(0x68, 6); //Request 6 Accel Registers(3B-40)
    
    //In 16 bit variables, Wire.read reads 8 bits from the starting register
    //We use bitwise left shift and bitwise OR to merge the value read from the next register
    //The merged values are divided by 163.84 which is Accel senstivity to get meaningful data
    int16_t accX = ((Wire.read()<<8)|Wire.read())/163.84;
    int16_t accY = ((Wire.read()<<8)|Wire.read())/163.84;
    int16_t accZ = ((Wire.read()<<8)|Wire.read())/163.84;
    Wire.endTransmission();
    

    //Print the accelerometer values on the serial monitor
    Serial.print(" a-x :");    
    Serial.print(accX);
    Serial.print(" a-Y :");
    Serial.print(accY);
    Serial.print(" a-Z :");
    Serial.println(accZ); 
    delay(500);

    //Using the accelerometer values to store instruction in msg
    if(accY>=20 && accY<=60)
     {
          msg="Backward";
          Serial.println("Backward"); //Prints on serial monitor
     }
     else if(accY<=-20 && accY>=-60)
     {
          msg = "Forward";
          Serial.println("Forward"); //Prints on serial monitor
     }
     else if(accX>=20 && accX<=60)
          
     {
          msg="Left";
          Serial.println("Left"); //Prints on serial monitor
     }
     else if(accX<=-20 && accX>=-60)
           
     {
          msg="Right";
          Serial.println("Right"); //Prints on serial monitor
     }
     else
     {
          Serial.println("Stop"); //Prints on serial monitor
          msg="Stop";
     }
     delay(200);

     rf_driver.send((uint8_t *)msg, strlen(msg));  // Transmits the msg to receiver
     rf_driver.waitPacketSent(); //Waits for the full msg to be sent
     delay(200);

}
