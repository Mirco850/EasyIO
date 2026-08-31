#include <EasyIO.h>

EasyIO Shield8 , Shield16;

void setup() {
  uint8_t Result8 = Shield8.begin(EASYIO_TYPE_8, 0x38);
  uint8_t Result16 = Shield16.begin(EASYIO_TYPE_16, 0x20);
  /* Result Number 
    0 = OK
    1 = BUFFER FULL
    2 = CHIP NOT FOUND
    3 = CHIP FOUND BUT REFUSED DATA
    4 = PISIC PROBLEM ON L2C LINE
    5 = TIMEOUT
    99 = TYPE OF SHIELD NOT VALID, USE EASYIO_TYPE_8 OR EASYIO_TYPE_16
  */

}

void loop() {

  /* EASYIO_TYPE_8*/

  uint8_t S8_Type = Shield8.getType(); //Read the type of module configured (0=None , 1=EASYIO_TYPE_8 , 2=EASYIO_TYPE_16)
  uint8_t S8_Addr = Shield8.getAddress(); //Read the address of configured module (0x38)

  bool S8_In_1 = Shield8.read(0); //Read input 1 from shield EASYIO_TYPE_8
  bool S8_In_2 = Shield8.read(1); //Read input 2 from shield EASYIO_TYPE_8
  bool S8_In_3 = Shield8.read(2); //Read input 3 from shield EASYIO_TYPE_8
  bool S8_In_4 = Shield8.read(3); //Read input 4 from shield EASYIO_TYPE_8

  uint16_t S8_In = Shield8.readBin(); //Read all inputs from shield EASYIO_TYPE_8

  Shield8.write(0,HIGH); //Switch ON Relay 1 from shield EASYIO_TYPE_8
  Shield8.write(1,LOW); //Switch OFF Relay 2 from shield EASYIO_TYPE_8
  Shield8.write(2,HIGH); //Switch ON Relay 3 from shield EASYIO_TYPE_8
  Shield8.write(3,LOW); //Switch OFF Relay 4 from shield EASYIO_TYPE_8
  Shield8.write(3,HIGH); //Switch ON Relay 4 from shield EASYIO_TYPE_8

  Shield8.writeBin(0xA); //Switch relay in combination of 0101 (R1=0 , R2=1 , R3=0 , R4=1) from shield EASYIO_TYPE_8


  /* EASYIO_TYPE_16*/

  uint8_t S16_Type = Shield16.getType(); //Read the type of module configured (0=None , 1=EASYIO_TYPE_8 , 2=EASYIO_TYPE_16)
  uint8_t S16_Addr = Shield16.getAddress(); //Read the address of configured module (0x20)

  bool S16_In_1 = Shield16.read(0); //Read input 1 from shield EASYIO_TYPE_16
  bool S16_In_2 = Shield16.read(1); //Read input 2 from shield EASYIO_TYPE_16
  bool S16_In_3 = Shield16.read(2); //Read input 3 from shield EASYIO_TYPE_16
  bool S16_In_4 = Shield16.read(3); //Read input 4 from shield EASYIO_TYPE_16
  bool S16_In_5 = Shield16.read(4); //Read input 5 from shield EASYIO_TYPE_16
  bool S16_In_6 = Shield16.read(5); //Read input 6 from shield EASYIO_TYPE_16
  bool S16_In_7 = Shield16.read(6); //Read input 7 from shield EASYIO_TYPE_16
  bool S16_In_8 = Shield16.read(7); //Read input 8 from shield EASYIO_TYPE_16

  uint16_t S16_In = Shield16.readBin(); //Read all inputs from shield EASYIO_TYPE_16

  Shield16.write(0,HIGH); //Switch ON Relay 1 from shield EASYIO_TYPE_16
  Shield16.write(1,LOW);  //Switch OFF Relay 2 from shield EASYIO_TYPE_16
  Shield16.write(2,HIGH); //Switch ON Relay 3 from shield EASYIO_TYPE_16
  Shield16.write(3,LOW);  //Switch OFF Relay 4 from shield EASYIO_TYPE_16
  Shield16.write(4,HIGH); //Switch ON Relay 5 from shield EASYIO_TYPE_16
  Shield16.write(5,HIGH); //Switch ON Relay 6 from shield EASYIO_TYPE_16
  Shield16.write(6,LOW);  //Switch OFF Relay 7 from shield EASYIO_TYPE_16
  Shield16.write(7,LOW);  //Switch OFF Relay 8 from shield EASYIO_TYPE_16

  Shield16.writeBin(0xCA); //Switch relay in combination of 01010011 (R1=0 , R2=1 , R3=0 , R4=1 , R5=0 , R6=0 , R7=1 , R8=1) from shield EASYIO_TYPE_16

}
