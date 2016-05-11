#include<stdio.h>
#include<string.h>
#define DXL_BUS_SERIAL1 1  //Dynamixel on Serial1(USART1)  <-OpenCM9.04
#define DXL_BUS_SERIAL2 2  //Dynamixel on Serial2(USART2)  <-LN101,BT210
#define DXL_BUS_SERIAL3 3  //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#define STEP_DEGREE 0.29296875
#define ID1  100 //left servo holder
#define ID3 10  // left wheel
#define ID2 40  // right wheel
#define ID4 30  // right servo holder
#define ID5 2   // cam mount
#define LOAD 41
Dynamixel Dxl(DXL_BUS_SERIAL1); 

int left_pressure;
int right_pressure;
int capture=0;
int motpostest=80;
char str1[10];
char str2[10];
char str3[20];

void setup() 
{
  
  Dxl.begin(3);  
  Dxl.setPacketType(DXL_PACKET_TYPE2);
  SerialUSB.attachInterrupt(MOTOR_POS); 
  
  Dxl.wheelMode(ID2);
  delay(20);
  Dxl.goalSpeed(ID2, 0);  
  
  Dxl.wheelMode(ID1);
  delay(20);
  Dxl.goalSpeed(ID1, 50);  
  delay(20);
  Dxl.maxTorque(ID1,1020); 
  delay(20);
  Dxl.jointMode(ID1);
  
  Dxl.wheelMode(ID3);
  delay(20);
  Dxl.goalSpeed(ID3, 0);
  
  Dxl.wheelMode(ID4);
  delay(20);
  Dxl.goalSpeed(ID4, 50);  
  delay(20);
  Dxl.maxTorque(ID4,1020); 
  delay(20);
  Dxl.jointMode(ID4);

  Dxl.wheelMode(ID5);
  delay(20);
  Dxl.goalSpeed(ID5, 50);  
  delay(20);
  Dxl.maxTorque(ID5,1020); 
  delay(20);
  Dxl.jointMode(ID5);
}

void loop() 
{
  left_pressure = Dxl.readWord(ID1, LOAD);
  right_pressure = Dxl.readWord(ID4, LOAD);
//  SerialUSB.println(left_pressure);
//  SerialUSB.println(right_pressure);
  snprintf(str1, 10, "%d", left_pressure);
  snprintf(str2, 10, "%d", right_pressure);
  strcat(str1,str2);
  SerialUSB.println(str3);
  delay(100);
}
void MOTOR_POS(byte* buffer, byte nCount)
{
  Dxl.goalSpeed(ID1, 50); 
  Dxl.goalSpeed(ID4, 50); 
  Dxl.goalSpeed(ID5, 50); 
  int Key1 = (buffer[0]-48);
  int Key2 = (buffer[6]-48);
  int Key3 = (buffer[13]-48);
  int Key4 = (buffer[20]-48);
  int Key5 = (buffer[26]-48);
  int M1 = (((buffer[2]-48)*100)+((buffer[3]-48)*10)+(buffer[4]-48));
  int M2 = (((buffer[8]-48)*1000)+((buffer[9]-48)*100)+((buffer[10]-48)*10)+(buffer[11]-48));
  int M3 = (((buffer[15]-48)*1000)+((buffer[16]-48)*100)+((buffer[17]-48)*10)+(buffer[18]-48));
  int M4 = (((buffer[22]-48)*100)+((buffer[23]-48)*10)+(buffer[24]-48));
  int M5 = (((buffer[28]-48)*100)+((buffer[29]-48)*10)+(buffer[30]-48));
  Dxl.goalPosition(ID1, (M1/STEP_DEGREE));
  Dxl.goalSpeed(ID2, M2);
  Dxl.goalSpeed(ID3, M3);  
  Dxl.goalPosition(ID4, (M4/STEP_DEGREE));
  Dxl.goalPosition(ID5, (M5/STEP_DEGREE));  
  SerialUSB.println("Start");
  SerialUSB.println(Key1);
  SerialUSB.println(M1);
  SerialUSB.println(Key2);
  SerialUSB.println(M2);
  SerialUSB.println(Key3);
  SerialUSB.println(M3);
  SerialUSB.println(Key4);
  SerialUSB.println(M4);
  SerialUSB.println(Key5);
  SerialUSB.println(M5);
  SerialUSB.println("End");
}

