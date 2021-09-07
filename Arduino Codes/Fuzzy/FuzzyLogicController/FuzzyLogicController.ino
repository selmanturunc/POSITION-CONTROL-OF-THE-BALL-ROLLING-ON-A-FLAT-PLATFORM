//--------------------------------------

//--------------------------------------
#include <Servo.h>
#include <Fuzzy.h>

const int pin1UL = 2;// Pin 1 at touchs screen (Upper Left)
const int pin2UR = 3;// Pin 2 at touchs screen (Upper Right)
const int pin4LR = 4;// Pin 4 at touchs screen (Lower Right)
const int pin5LL = 5;// Pin 5 at touchs screen (Lower Left) 
const int sense = A0; // Pin 3 at touchs screen (COMMON)
float SetpointX, InputX, Input2X, velX, OutputX ,Xoutput; //for X axis
float SetpointY, InputY, Input2Y, velY, OutputY ,Youtput; //for Y axis
Servo servoX; //X axis
Servo servoY; //Y axis

Fuzzy *fuzzy = new Fuzzy();

// FuzzyInput analog1
FuzzySet *verylow1          = new FuzzySet(-15, -15, -15, -7.5);
FuzzySet *low1          = new FuzzySet(-15, -7.5, -7.5,0);
FuzzySet *mid1          = new FuzzySet(-7.5, 0, 0, 7.5);
FuzzySet *high          = new FuzzySet(0, 7.5, 7.5, 15);
FuzzySet *veryhigh          = new FuzzySet(7.5, 15, 15, 15);

// FuzzyInput analog2
FuzzySet *back2          = new FuzzySet(-1.5,-1.5, -1.5, 0);
FuzzySet *middle          = new FuzzySet(-1.5, 0, 0, 1.5);
FuzzySet *forward2          = new FuzzySet(0, 1.5, 1.5, 1.5);

// FuzzyOutput
FuzzySet *verylowout1            = new FuzzySet(-30, -30, -30, -20);
FuzzySet *midlowout1             = new FuzzySet(-30, -20, -20, -10);
FuzzySet *lowout1                 = new FuzzySet(-20, -10, -10, 0);
FuzzySet *midout1                = new FuzzySet(-10, 0, 0, 10);
FuzzySet *highout1               = new FuzzySet(0, 10, 10, 20);
FuzzySet *midhighout1            = new FuzzySet(10, 20, 20, 30);
FuzzySet *veryhighout1           = new FuzzySet(20, 30, 30, 30);


void setup()
{
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

  //--------------------------------------
  // FuzzyInput
  FuzzyInput *analog1 = new FuzzyInput(1);

  analog1->addFuzzySet(verylow1);
  analog1->addFuzzySet(low1);
  analog1->addFuzzySet(mid1);
  analog1->addFuzzySet(high);
  analog1->addFuzzySet(veryhigh);
  fuzzy->addFuzzyInput(analog1);

  // FuzzyInput
  FuzzyInput *analog2 = new FuzzyInput(2);

  analog2->addFuzzySet(back2);
  analog2->addFuzzySet(middle);
  analog2->addFuzzySet(forward2);
  fuzzy->addFuzzyInput(analog2);

  // FuzzyOutput
  FuzzyOutput *led = new FuzzyOutput(1);

  led->addFuzzySet(verylowout1);
  led->addFuzzySet(midlowout1);
  led->addFuzzySet(lowout1);  
  led->addFuzzySet(midout1); 
  led->addFuzzySet(highout1);
  led->addFuzzySet(midhighout1);
  led->addFuzzySet(veryhighout1);
  fuzzy->addFuzzyOutput(led);
  //--------------------------------------

  // Building FuzzyRule////////////////////////////////////////////////////////////////// 1
  FuzzyRuleAntecedent *verylow1_back2 = new FuzzyRuleAntecedent();
  verylow1_back2->joinWithAND(verylow1, back2);

  FuzzyRuleConsequent *led_verylowout1 = new FuzzyRuleConsequent();
  led_verylowout1->addOutput(verylowout1);

  FuzzyRule *fuzzyRule1 = new FuzzyRule(1, verylow1_back2, led_verylowout1);
  fuzzy->addFuzzyRule(fuzzyRule1);

  // Building FuzzyRule////////////////////////////////////////////////////////////////// 2
  FuzzyRuleAntecedent *verylow1_middle = new FuzzyRuleAntecedent();
  verylow1_middle->joinWithAND(verylow1, middle);

  FuzzyRuleConsequent *led_midlowout1 = new FuzzyRuleConsequent();
  led_midlowout1->addOutput(midlowout1);

  FuzzyRule *fuzzyRule2 = new FuzzyRule(2, verylow1_middle, led_midlowout1);
  fuzzy->addFuzzyRule(fuzzyRule2);

  // Building FuzzyRule////////////////////////////////////////////////////////////////// 3
  FuzzyRuleAntecedent *verylow1_forward2 = new FuzzyRuleAntecedent();
  verylow1_forward2->joinWithAND(verylow1, forward2);

  FuzzyRuleConsequent *led_lowout1 = new FuzzyRuleConsequent();
  led_lowout1->addOutput(lowout1);

  FuzzyRule *fuzzyRule3 = new FuzzyRule(3, verylow1_forward2, led_lowout1);
  fuzzy->addFuzzyRule(fuzzyRule3);

  // Building FuzzyRule////////////////////////////////////////////////////////////////// 4
  FuzzyRuleAntecedent *low1_back2 = new FuzzyRuleAntecedent();
  low1_back2->joinWithAND(low1, back2);


  FuzzyRule *fuzzyRule4 = new FuzzyRule(4, low1_back2, led_midlowout1);
  fuzzy->addFuzzyRule(fuzzyRule4);

  // Building FuzzyRule////////////////////////////////////////////////////////////////// 5
  FuzzyRuleAntecedent *low1_middle = new FuzzyRuleAntecedent();
  low1_middle->joinWithAND(low1, middle);

  FuzzyRule *fuzzyRule5 = new FuzzyRule(5, low1_middle, led_lowout1);
  fuzzy->addFuzzyRule(fuzzyRule5);

  // Building FuzzyRule////////////////////////////////////////////////////////////////// 6
  FuzzyRuleAntecedent *low1_forward2 = new FuzzyRuleAntecedent();
  low1_forward2->joinWithAND(low1, forward2);

  FuzzyRuleConsequent *led_midout1 = new FuzzyRuleConsequent();
  led_midout1->addOutput(midout1);

  FuzzyRule *fuzzyRule6 = new FuzzyRule(6, low1_forward2, led_midout1);
  fuzzy->addFuzzyRule(fuzzyRule6);

  // Building FuzzyRule////////////////////////////////////////////////////////////////// 7
  FuzzyRuleAntecedent *mid1_back2 = new FuzzyRuleAntecedent();
  mid1_back2->joinWithAND(mid1, back2);

  FuzzyRule *fuzzyRule7 = new FuzzyRule(7, mid1_back2, led_lowout1);
  fuzzy->addFuzzyRule(fuzzyRule7);

  // Building FuzzyRule////////////////////////////////////////////////////////////////// 8
  FuzzyRuleAntecedent *mid1_middle = new FuzzyRuleAntecedent();
  mid1_middle->joinWithAND(mid1, middle);

  FuzzyRule *fuzzyRule8 = new FuzzyRule(8, mid1_middle, led_midout1);
  fuzzy->addFuzzyRule(fuzzyRule8);

  // Building FuzzyRule////////////////////////////////////////////////////////////////// 9
  FuzzyRuleAntecedent *mid1_forward2 = new FuzzyRuleAntecedent();
  mid1_forward2->joinWithAND(mid1, forward2);

  FuzzyRuleConsequent *led_highout1 = new FuzzyRuleConsequent();
  led_highout1->addOutput(highout1);

  FuzzyRule *fuzzyRule9 = new FuzzyRule(9, mid1_forward2, led_highout1);
  fuzzy->addFuzzyRule(fuzzyRule9);
  // Building FuzzyRule////////////////////////////////////////////////////////////////// 10
  FuzzyRuleAntecedent *high_back2 = new FuzzyRuleAntecedent();
  high_back2->joinWithAND(high, back2);

  FuzzyRule *fuzzyRule10 = new FuzzyRule(10, high_back2, led_midout1);
  fuzzy->addFuzzyRule(fuzzyRule10);
  
  // Building FuzzyRule////////////////////////////////////////////////////////////////// 11
  FuzzyRuleAntecedent *high_middle = new FuzzyRuleAntecedent();
  high_middle->joinWithAND(high, middle);

  FuzzyRule *fuzzyRule11 = new FuzzyRule(11, high_middle, led_highout1);
  fuzzy->addFuzzyRule(fuzzyRule11);

  // Building FuzzyRule////////////////////////////////////////////////////////////////// 12
  FuzzyRuleAntecedent *high_forward2 = new FuzzyRuleAntecedent();
  high_forward2->joinWithAND(high, forward2);

  FuzzyRuleConsequent *led_midhighout1 = new FuzzyRuleConsequent();
  led_midhighout1->addOutput(midhighout1);

  FuzzyRule *fuzzyRule12 = new FuzzyRule(12, high_forward2, led_midhighout1);
  fuzzy->addFuzzyRule(fuzzyRule12);

    // Building FuzzyRule////////////////////////////////////////////////////////////////// 13
  FuzzyRuleAntecedent *veryhigh_back2 = new FuzzyRuleAntecedent();
  veryhigh_back2->joinWithAND(veryhigh, back2);

  FuzzyRule *fuzzyRule13 = new FuzzyRule(13, veryhigh_back2, led_highout1);
  fuzzy->addFuzzyRule(fuzzyRule13);

    // Building FuzzyRule////////////////////////////////////////////////////////////////// 14
  FuzzyRuleAntecedent *veryhigh_middle = new FuzzyRuleAntecedent();
  veryhigh_middle->joinWithAND(veryhigh, middle);

  FuzzyRule *fuzzyRule14 = new FuzzyRule(14, veryhigh_middle, led_midhighout1);
  fuzzy->addFuzzyRule(fuzzyRule14);
  
    // Building FuzzyRule////////////////////////////////////////////////////////////////// 15
  FuzzyRuleAntecedent *veryhigh_forward2 = new FuzzyRuleAntecedent();
  veryhigh_forward2->joinWithAND(veryhigh, forward2);

  FuzzyRuleConsequent *led_veryhighout1 = new FuzzyRuleConsequent();
  led_veryhighout1->addOutput(veryhighout1);

  FuzzyRule *fuzzyRule15 = new FuzzyRule(15, veryhigh_forward2, led_veryhighout1);
  fuzzy->addFuzzyRule(fuzzyRule15);
  delay(100);
}


void loop()
{
  SetpointX=16;
  SetpointY=11;
  InputX= Xcoordinates(); // read and convert X coordinate
  InputY= Ycoordinates(); // read and convert Y coordinate
  Input2X= Xcoordinates(); // read and convert X coordinate
  Input2Y= Ycoordinates(); // read and convert Y coordinate
  velX=(Input2X-InputX)/0.615;
  velY=(Input2Y-InputY)/0.615;
if (velX<-1.5)
{
velX= -1.5;
}
if (velX>1.5)
{
  velX= 1.5;
}

if (velY<-1.5)
{
  velY= -1.5;
}

if (velY>1.5)
{
  velY= 1.5;
}


float in_analog1 =InputX-SetpointX;
float in_analog2 =velX;
  
  //--------------------------------------

  fuzzy->setInput(1, in_analog1);
  fuzzy->setInput(2, in_analog2);
  fuzzy->fuzzify();

  float out_X = fuzzy->defuzzify(1);
  float in_analog1y =InputY-SetpointY;
  float in_analog2y =velY;
   fuzzy->setInput(1, in_analog1y);
  fuzzy->setInput(2, in_analog2y);
  fuzzy->fuzzify();
float out_Y = fuzzy->defuzzify(1);
Xoutput=99-1*out_X;
Youtput=80-1*out_Y;

if(InputX > SetpointX + 0.1 && InputX < SetpointX - 0.1 && InputY > SetpointY + 0.1 && InputY < SetpointY - 0.1 )
{
servoX.write(99);//Balance position
servoY.write(80);//Balance position
delay(20);
}
else
{
servoX.write(Xoutput);//Controll position
servoY.write(Youtput);//Controll position
delay(20);
}

  //--------------------------------------
  Serial.print(' '); 
  Serial.print(in_analog1); 
   Serial.print(' '); 
  Serial.print(in_analog2);
  Serial.print(' '); 
  Serial.print(out_X);
  Serial.print(' ');
  Serial.print(in_analog1y); 
   Serial.print(' '); 
  Serial.print(in_analog2y);
  Serial.print(' '); 
  Serial.println(out_Y);
  
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
