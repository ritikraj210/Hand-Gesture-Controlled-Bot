
//Receiver Code

#include <RH_ASK.h> //Include the RH_ASK library

//Defining motor driver pins
int m1 = 2;
int m2 = 3;
int m3 = 4;
int m4 = 5;

RH_ASK rf_driver; //create object
String str; //To store the received msg

void setup()
{
  Serial.begin(9600); //For debugging 
  if (!rf_driver.init()) //Check initialisation of object
      Serial.println("init failed");

  //Configures the pins to behave as output
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
}

void loop()
{
    uint8_t buf[1]; //max size of the buffer
    uint8_t buflen = sizeof(buf); //Create a 1 byte char buffer

    if (rf_driver.recv(buf, &buflen))  //returns true if valid msg copied to buf
    {
        str=(char*)buf;  //stores the received msg
        Serial.println(str);  //Prints the msg on serial monitor
    }
    delay(200);
    
    if(str=="F")
    {
       //Writing the motor driver pins to move forward
       digitalWrite(m1,LOW);
       digitalWrite(m2,HIGH);
       digitalWrite(m3,HIGH);
       digitalWrite(m4,LOW);
       Serial.println("Forward"); //Prints on serial monitor
    }  
    else if(str=="B")
    {
       //Writing the motor driver pins to move backward
       digitalWrite(m1,HIGH);
       digitalWrite(m2,LOW);
       digitalWrite(m3,LOW);
       digitalWrite(m4,HIGH);
       Serial.println("Backward"); //Prints on serial monitor
    }
    else if(str=="L")
    {
       //Writing the motor driver pins to move left
       digitalWrite(m1,HIGH);
       digitalWrite(m2,LOW);
       digitalWrite(m3,LOW);
       digitalWrite(m4,LOW); 
       Serial.println("Left"); //Prints on serial monitor
    }
    else if(str=="R")
    {
       //Writing the motor driver pins to move right
       digitalWrite(m1,LOW);
       digitalWrite(m2,LOW);
       digitalWrite(m3,LOW);
       digitalWrite(m4,HIGH);
       Serial.println("Right"); //Prints on serial monitor
    }    
    else if(str=="S")
    {
      //Writing the motor driver pins to stop
      digitalWrite(m1,LOW);
      digitalWrite(m2,LOW);
      digitalWrite(m3,LOW);
      digitalWrite(m4,LOW);
      Serial.println("Stop"); //Prints on serial monitor
    }
}
