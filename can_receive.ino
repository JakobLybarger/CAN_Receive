#include <mcp_can_dfs.h>
#include <mcp_can.h>

const int but1 = 4;
const int but2 = 5;
const int but3 = 6;
int canPin = 3;

unsigned char len = 0;
unsigned char buf[4];
unsigned int recID = 0x55;
unsigned int checkID = 0x7A;

char gears[4]{'F', 'R', 'P', '0'};
//char drivers[7]{'1', '2', '3', '4', '5', '6', '7'};
String drivers[7]{"Jakob", "Gabe", "Bailey", "Daniel", "Josh", "Callahan", "Savannah"};

const int SPI_CS_PIN = 10;
MCP_CAN CAN(SPI_CS_PIN);

void setup() {
  Serial.begin(115200);
  pinMode(but1, OUTPUT);
  pinMode(but2, OUTPUT);
  pinMode(but3, OUTPUT);
  pinMode(canPin, INPUT_PULLUP);
  while (CAN_OK != CAN.begin(CAN_500KBPS)) {
    delay(100);
  }

  CAN.init_Mask(0,0,0x7ff);
  CAN.init_Filt(0,0,recID);
}

void canRead() {
  if (CAN_MSGAVAIL == CAN.checkReceive()) {
    CAN.readMsgBuf(&len, buf);
    if (CAN.getCanId() == recID && buf[2] == checkID) {
      Serial.println(DEC, buf[0]); // Print the Air Temp
      Serial.println(buf[1]); // Print the ASCII character
      digitalWrite(but1, (buf[3]&0b10000000)>>7); // Turn light on if but1 is pressed 
      digitalWrite(but2, (buf[3]&0b01000000)>>6); // Turn light on if but2 is pressed
      digitalWrite(but3, (buf[3]&0b00100000)>>5); // Turn on light if but3 is pressed

      unsigned int gear = (buf[3]&0b00011000)>>3;
      Serial.println(gears[gear]); // Print whether the car is in
                                   // Forward, Reverse, or Park
      unsigned int driver = (buf[3]&0b00000111);
      Serial.println(drivers[driver]); // Print the driver
    }
  }
}

void loop() {
  if (digitalRead(canPin)==LOW) {
    canRead();
  }
}
