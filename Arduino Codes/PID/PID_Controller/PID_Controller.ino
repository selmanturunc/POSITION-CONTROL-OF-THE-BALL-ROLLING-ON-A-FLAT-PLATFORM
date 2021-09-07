#include <Servo.h>
#include <PID_v1.h>
const int pin1UL = 2;// Pin 1 at touchs screen (Upper Left)// BEYAZ MOR KAHVERENGİ MAVİ SİYAH - SİYAHTAN SARIYA
const int pin2UR = 3;// Pin 2 at touchs screen (Upper Right)
const int pin4LR = 4;// Pin 4 at touchs screen (Lower Right)
const int pin5LL = 5;// Pin 5 at touchs screen (Lower Left) 
const int sense = A0; // Pin 3 at touchs screen (COMMON)
double SetpointX, InputX, OutputX; //for X axis
double SetpointY, InputY, OutputY; //for Y axis
Servo servoX; //X axis
Servo servoY; //Y axis
int Ts =25;//Time Sample
float KpX = 1.95;
float KiX = 0;
float KdX = 0.5;
float KpY = 1.95;
float KiY = 0;
float KdY = 0.5;
double Xoutput,Youtput;
PID PIDX(&InputX, &OutputX, &SetpointX, KpX, KiX, KdX, DIRECT);
PID PIDY(&InputY, &OutputY, &SetpointY,KpY,KiY,KdY, DIRECT);

void setup() {
SetpointX=16;
SetpointY=11;
servoX.attach(8);
servoY.attach(9);
servoX.write(99);//Balance position
servoY.write(80);//Balance position
pinMode(pin1UL,OUTPUT);
pinMode(pin2UR,OUTPUT);
pinMode(pin4LR,OUTPUT);
pinMode(pin5LL,OUTPUT);
Serial.begin(9600);
PIDX.SetMode(AUTOMATIC);
PIDX.SetOutputLimits(-60,30);//Değişecek.
PIDY.SetMode(AUTOMATIC);
PIDY.SetOutputLimits(-30, 30);//Değişecek.
PIDX.SetSampleTime(Ts);
PIDY.SetSampleTime(Ts);
delay(100);
}

void loop() {
SetpointX=16;
SetpointY=11;
InputX= Xcoordinates(); // read and convert X coordinate
InputY= Ycoordinates(); // read and convert Y coordinate
PIDX.Compute(); //action control X compute
PIDY.Compute(); // action control Y compute
Xoutput = 99 + OutputX;//Değişecek
Youtput = 80 + OutputY;//Değişecek
//Gereksiz Değişecek
Serial.print(InputX);
Serial.print("\t");
Serial.print(InputY);
Serial.print("\t");

Serial.print(OutputX);
Serial.print("\t");
Serial.println(OutputY);
Serial.print("\t");
if(InputX > SetpointX + 0.1 && InputX < SetpointX - 0.1 && InputY > SetpointY + 0.1 && InputY < SetpointY - 0.1 )
{
servoX.write(90);//Balance position
servoY.write(80);//Balance position
delay(20);
}
else
{
servoX.write(Xoutput);//Controll position
servoY.write(Youtput);//Controll position
delay(20);
}
}
double Xcoordinates()
{
double xVal;
digitalWrite(pin1UL,HIGH);
digitalWrite(pin2UR,LOW);
digitalWrite(pin4LR,LOW);
digitalWrite(pin5LL,HIGH);
delay(10);
xVal = analogRead(sense);


xVal = map(xVal,250,781,0,320);
xVal=xVal/10;//mm to cm 
return xVal;
}
double Ycoordinates()
{
double yVal;
digitalWrite(pin1UL,LOW);
digitalWrite(pin2UR,LOW);
digitalWrite(pin4LR,HIGH);
digitalWrite(pin5LL,HIGH);
delay(10);
yVal = analogRead(sense);


yVal = map(yVal,232,754,0,240);
yVal=yVal/10;//mm to cm
return yVal;
}
