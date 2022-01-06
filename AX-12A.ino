#include <SoftwareSerial.h>
SoftwareSerial AXSerial(0,5); // DigitalPin 5 (Rx / Tx)

void Packet_LED(unsigned char _id, unsigned char _ledStatus);
void Packet_MovingSpeed(unsigned char _id, unsigned int _movingSpeed);
void Packet_GoalPosition(unsigned char _id, unsigned int _goalPosition);

void setup()
{
  Serial.begin(9600);
  AXSerial.begin(57600);

  Serial.println("Serial begin...");
  delay(500);

  Serial.println("===== Start Led Test! =====");
  Packet_LED(0x01, 0x01);
  delay(1000);
  Packet_LED(0x01, 0x00);
  Serial.println("===== End Led Test! =====");

  delay(500);

  Serial.println("AX-12A Start!");
}

void loop(){
  JointModeExample();
}

void JointModeExample(){
  Packet_MovingSpeed(0x01,200);
  Packet_GoalPosition(0x01,200);
  delay(1000);
  Packet_MovingSpeed(0x01,400);
  Packet_GoalPosition(0x01,400);
  delay(1000);
}
void WheelModeExample(){
  Packet_MovingSpeed(0x01,200); // CCW
  delay(1000);
  Packet_MovingSpeed(0x01,1224); // CW
  delay(1000);
}


void Packet_LED(unsigned char _id, unsigned char _ledStatus){
  unsigned char Check_Sum;

  AXSerial.write(0xFF);  // Header1
  AXSerial.write(0xFF);  // Header2
  AXSerial.write(_id);   // ID
  AXSerial.write(0x04);  // Length = number of Parameters + 2
  AXSerial.write(0x03);  // instruction, 0x03 Write
  AXSerial.write(0x19);  // Adress, LED 25(Dec) > 0x19(Hex) // 10진수를 16진수로 변환
  AXSerial.write(_ledStatus);  // Value, 1 ON 0 OFF
  Check_Sum = ~( _id + 0x04 + 0x03 + 0x19 + _ledStatus); // Checksum = ~( ID + Length + Instruction + Parameter1 + … Parameter N )
  AXSerial.write(Check_Sum);
  delay(10);
}

void Packet_MovingSpeed(unsigned char _id, unsigned int _movingSupeed){
  unsigned char Check_Sum;

  AXSerial.write(0xFF);  // Header1
  AXSerial.write(0xFF);  // Header2
  AXSerial.write(_id);   // ID
  AXSerial.write(0x05);  // Length = number of Parameters + 2
  AXSerial.write(0x03);  // instruction, 0x03 Write
  AXSerial.write(0x20);  // Adress, MovingSpeed 32(Dec) > 0x20(Hex)
  AXSerial.write(_movingSpeed);     // Lower Bit Value, joint Mode 0~1023, wheel mode 0~1023(CCW)/1024~2047(CW)
  AXSerial.write(_movingSpeed>>8);  // Upper Bit Value, joint Mode 0~1023, wheel mode 0~1023(CCW)/1024~2047(CW)
  Check_Sum = ~( _id + 0x05 + 0x03 + 0x20 + _movingSpeed + (_movingSpeed>>8)); // Checksum = ~( ID + Length + Instruction + Parameter1 + … Parameter N )
  AXSerial.write(Check_Sum);
  delay(10);
}

void Packet_GoalPosition(unsigned char _id, unsigned int _goalPosition){
  unsigned char Check_Sum;

  AXSerial.write(0xFF);  // Header1
  AXSerial.write(0xFF);  // Header2
  AXSerial.write(_id);   // ID
  AXSerial.write(0x05);  // Length = number of Parameters + 2
  AXSerial.write(0x03);  // instruction, 0x03 Write
  AXSerial.write(0x1E);  // Adress, GoalPosition 30(Dec) > 0x1E(Hex)
  AXSerial.write(_goalPosition);     // Lower Bit Value, Angle 0~1023
  AXSerial.write(_goalPosition>>8);  // Upper Bit Value, Angle 0~1023 shift
  Check_Sum = ~( _id + 0x05 + 0x03 + 0x1E + _goalPosition + (_goalPosition>>8)); // Checksum = ~( ID + Length + Instruction + Parameter1 + … Parameter N )
  AXSerial.write(Check_Sum);
  delay(10);
}