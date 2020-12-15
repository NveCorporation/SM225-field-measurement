/*********************************************************************************  
Reads magnetic field from an SM22x smart sensor with an Arduino. 
Sensor to Arduino connections: 
Sensor VDD to 3.3V; GND to GND; SS=pin 10; MOSI=pin 11; MISO=pin 12; SCLK=pin 13.
Demo at: https://youtu.be/PDNVEmkQcs0
www.nve.com * www.YouTube.com/NveCorporation * sensor-apps@nve.com * Rev. 12/14/20
*********************************************************************************/
#include <SPI.h>
int field; //Sensor magnetic field data
void setup() {
Serial.begin(57600); //Initialize the serial port
SPI.begin ();
SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0)); //Initialize SPI 
pinMode(10, OUTPUT); //SS (Sensor Select; low true)
digitalWrite(10, LOW); //Enable the sensor
}
void loop() {
field = (SPI.transfer (0))<<8; //Send 0 for address MSB; receive sensor MSB
delayMicroseconds (3); //Allow 3 us between address bytes
field |= SPI.transfer (0); //2nd address byte (0 for read); receive LSB
Serial.print(float(field)/100); //Read, scale, and print sensor output
Serial.print(" mT  \r" );
delay(100); //10 samples/second
}
