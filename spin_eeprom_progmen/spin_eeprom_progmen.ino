// write binary to FV-1, using atmega328 (or what not)

#include <Wire.h>    
 
#define disk1 0x50    //eeprom address
 
extern prog_uchar PROGMEM image[]; // binary data

unsigned int address = 0;

void setup(void)
{
  Serial.begin(9600);
  Wire.begin();  
  //while (!Serial) {;} 
}
 
void loop()
{
  while (address < 4096) {
    
    Serial.print(address);
    Serial.print("  -- " );
    unsigned char tmp = pgm_read_byte_near(image + address);
    Serial.print(tmp);
    Serial.print("  --> " );
    writeEEPROM(disk1, address, tmp);
    Serial.println(readEEPROM(disk1, address), DEC);
    address++;
  };
}
 
void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data ) 
{
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.write(data);
  Wire.endTransmission();
 
  delay(5);
}
 
byte readEEPROM(int deviceaddress, unsigned int eeaddress ) 
{
  byte rdata = 0xFF;
 
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.endTransmission();
 
  Wire.requestFrom(deviceaddress,1);
  if (Wire.available()) rdata = Wire.read();
  return rdata;
}


