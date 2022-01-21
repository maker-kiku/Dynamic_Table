#include <SoftwareSerial.h>
SoftwareSerial AXSerial(0,5); // Rx, Tx핀 설정

void setup() {
  AXSerial.begin(57600); // 다이나믹셀 통신 속도 설정

  // 다이나믹셀 내장LED : ON
  AXSerial.write(0xFF); // Header1
  AXSerial.write(0xFF); // Header2
  AXSerial.write(0x01); // Packet ID
  AXSerial.write(0x04); // Length
  AXSerial.write(0x03); // Instruction
  AXSerial.write(0x19); // Param 1
  AXSerial.write(0x01); // Param 2
  AXSerial.write(0xDD); // Checksum
  delay(1000);

  // 다이나믹셀 내장LED OFF
  AXSerial.write(0xFF); // Header1
  AXSerial.write(0xFF); // Header2
  AXSerial.write(0x01); // Packet ID
  AXSerial.write(0x04); // Length
  AXSerial.write(0x03); // Instruction
  AXSerial.write(0x19); // Param 1
  AXSerial.write(char(0x00)); // Param 2 
  AXSerial.write(0xDE); // Checksum
  delay(1000);
}

void loop() {
  
}
