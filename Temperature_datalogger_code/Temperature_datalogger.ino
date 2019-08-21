/* 
 * Temperature datalogger
 * 
 * by Mike Dijkstra, for the Hanze Racing Division
 * 
  */

#include <SD.h>
#include <SPI.h>

int sensorPin = A0; //This is the Arduino Pin that will read the sensor output
int pinCS = 10;
int sensorInput;    //The variable we will use to store the sensor input
double temp;        //The variable we will use to store temperature in degrees
File file

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pinCS, OUTPUT);

  // Initialization SD Card
  if (SD.begin()){
      Serial.println("Ready for use");
    }
   else{
      Serial.println("Failed to open SD card, terminating progam...");
      return;
    }
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorInput = analogRead(A0); //read the analog sensor and store it
  temp = (double)sensorInput / 1024;   //find percentage of input reading
  temp = temp * 5;                     //multiply by 5V to get voltage
  temp = temp - 0.5;                   //Subtract the offset (gives a temp range of -50 to 125) 
  temp = temp * 100;                   //Convert to degrees 

  Serial.print("Current Temperature: "); 
  Serial.println(temp);

  file = SD.open("temperature_data.txt", FILE_WRITE);
  if(file){
    file.print(temp);
    file.print(","); // makes reading the file in excel easier
    file.close();
    }
   //If the file didn't open print error
   else{
    Serial.println("error opening temperature_data.txt")
    }
  delay(10000); // Delay of 10 seconds.

}
