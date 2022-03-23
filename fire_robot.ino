/*
  mec_fire_robot
  multisensor:MQ-2、CO、fire_5、alarm、pusher、servo 
  Used in arduino mega 
  Created by Ju Yuting
*/
#include <Arduino.h>
#include <Servo.h>

#define smogSensor_AO 12   //烟雾传感器引脚
#define smogSensor_DO 13   
#define COSensor_AO 30     //一氧化碳CO传感器引脚
#define COSensor_DO 31

Servo myservo_1,myservo_2;  
float pos = 0;    //该变量存储舵机角度位置

int alarming_pusher = 2;  //报警器+电推杆引脚
int fire_sensor1 = A11;    //5个火焰传感器引脚
int fire_sensor2 = A12;
int fire_sensor3 = A13;
int fire_sensor4 = A14;
int fire_sensor5 = A15;
unsigned int smogsensorValue = 0;  //烟雾传感器值
unsigned int cosensorValue = 0;    //CO传感器值
unsigned int firesensorValue3 = 0;  

void setup()
{
  pinMode(smogSensor_DO, INPUT);
  pinMode(smogSensor_AO, INPUT);
  pinMode(COSensor_DO, INPUT);
  pinMode(COSensor_AO, INPUT);
  
  //火焰传感器5个引脚+电推杆+警报器
  pinMode(fire_sensor1,INPUT);  
  pinMode(fire_sensor2,INPUT); 
  pinMode(fire_sensor3,INPUT); 
  pinMode(fire_sensor4,INPUT); 
  pinMode(fire_sensor5,INPUT); 
  pinMode(alarming_pusher,OUTPUT);
  
  myservo_1.attach(9);   //该舵机由arduino第9脚控制
  myservo_2.attach(10);
  Serial.begin(9600);
}

void loop()
{   
  // MQ-2烟雾传感器，检测值大于11，触发后警报器响灯闪
  smogsensorValue = analogRead(smogSensor_AO);
  Serial.print("MQ-2 smogSensor_AO Value = ");
  Serial.println(smogsensorValue);
  delay(1000);  
  // CO一氧化碳传感器，检测到数值，触发后警报器响灯闪
  cosensorValue = analogRead(COSensor_AO);
  Serial.print("COSensor_AO Value = ");
  Serial.println(cosensorValue);
  delay(1000); 

  // 火焰传感器，检测到火焰，触发后警报器响+电推杆打开+舵机转动
  firesensorValue3 = analogRead(fire_sensor3);
  Serial.print("fireSensor Value3 = ");
  Serial.println(firesensorValue3);
  onAlarmPush();
  onServo();
  
  if (firesensorValue3>100)
  { 
  Serial.print("now fireSensor Value3 = ");
  Serial.println(firesensorValue3);
  onAlarmPush();
  onServo();
  }
  
  else 
  {
    digitalWrite(alarming_pusher,LOW); 
    delay(2000);
  }
  
}

// 触发报警器的函数
void onAlarmPush()
{
  digitalWrite(alarming_pusher,HIGH);
  delay(2000);
  Serial.print("The alarming and pusher has opened!\n");
}

// 触发舵机操作
void onServo()
{
  for(pos=0;pos<=120;pos+=1)   // 从0度到180度运动,每次步进一度
  {
    myservo_1.write(pos);
    myservo_2.write(pos/2);
    delay(15);             //等待15ms让舵机到达指定位置
  }
  for(pos=120;pos>=1;pos-=1)  // 从180度到0度运动,每次步进一度  
  {
    myservo_1.write(pos);
    myservo_2.write(pos/2);
    delay(15);            //等待15ms让舵机到达指定位置
  }
}
