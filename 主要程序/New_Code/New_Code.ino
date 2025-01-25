//多线程
#include <TaskScheduler.h>//多线程
#include <ServoTimer2.h>        //调用舵机库函数
//#include <Wire.h>         //调用IIC库函数
#include "MH_TCS34725.h"  //调用颜色识别传感器库函数
//金鱼屏幕显示
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>  //调用oled屏幕库函数
//显示部分代码
#ifdef __AVR__
#include <avr/power.h>
#endif
#define OLED_RESET 4


Scheduler scheduler;
Scheduler taskone;


void Taska();
void taskonea();


// 创建任务，每500毫秒调用一次 Task
Task runtime(500, TASK_FOREVER, &Taska);
//创建任务 
Task taskoneaw(1,TASK_FOREVER, &taskonea);

unsigned long elapsedTime = 0;


// 初始化 MPU6050 地址 废弃
// #define MPU6050_ADDR 0x68

//颜色识别的代码
int color_detection_card = 0; //记录颜色传感器识别到色卡的数值（红色为1，蓝色为2，绿色为3）
int color_detection_ballon = 0;//记录颜色传感器识别到要到弹珠的色卡的数值（红色为1，蓝色为2，绿色为3）


Adafruit_SSD1306 display(OLED_RESET);



MH_TCS34725 tcs = MH_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

int Forward_Left_Speed = 230;  //小车前进时左轮速度
int Forward_Right_Speed = 210;  //小车前进时右轮速度

#define Back_Left_Speed 160     //小车后退时左轮速度
#define Back_Right_Speed 110    //小车后退时右轮速度

int  Left_Left_Speed = 200;   //小车左转时左轮速度
int  Left_Right_Speed = 205;    //小车左转时右轮速度

int  Right_Left_Speed = 225;  
  //小车右转时左轮速度
int Right_Right_Speed = 200;   //小车右转时右轮速度



#define TrackingSensorNum 3     //小车寻迹时使用的灰度传感器数量

#define Servo1_Pin 4   //定义舵机引脚号 前舵机

#define Servo2_Pin 11   //定义舵机引脚号 中舵机 大
#define Servo3_Pin 7  //定义舵机引脚号 中舵机 小  

#define Servo4_Pin 3   //定义舵机引脚号 后舵机



//#define Angle_1 2000  //设置舵机1转动的初始角度  //值大向上 值小向下 //初始化
#define Angle_1 1400


#define Angle_2 1450   //设置舵机2 转动的初始角度   //小向左 值大向右 //开车第人称一视角 //900 向左转 正方向90°

#define Angle_3 1535  //1535//值低时倒的 往下倒 1535 

#define Angle_4 1500 //设置舵机4转动的初始角度  //值大向下 值小向上 //初始化

#define button 12   //定义按钮针脚
bool lastButtonState = HIGH;  // 记录按钮的上一个状态


//---近红外
//创建近红外
int HW = A1;//颜色识别使用检测前方是否有卡片

int air = 0; //识别空气次数
int block = 0;//识别到物体的次数
bool airG = false;
bool blockG =false;


//----



int Gray_Aoto_Mode = 0;
int Get_Stats = 0;

//
unsigned long previousMillis = 0;


//灰度
ServoTimer2 myservo1;        //声明舵机对象 前

ServoTimer2 myservo2;       //声明舵机 中大

ServoTimer2 myservo3;       //声明舵机 中小

ServoTimer2 myservo4;        //声明舵机对象 后


int Car_DC_Motor_Pin[4] = { 9, 10, 5, 6 }; //直流电机引脚
int Gray_SensorPin[3] = { A3, A2, A0 }; //寻迹、检测路口传感器


int motor_num = sizeof(Car_DC_Motor_Pin) / sizeof(Car_DC_Motor_Pin[0]);  //定义电机数量
int Car_Head_Gray_SensorPin_Num = 3;    //灰度传感器的数量

int Gray_Three = 0;  //记录三个灰度传感器同时触发的次数（即记录小车经过特殊路口的次数）

bool finish = true;
bool finish_all = true;  //判断小车是否结束比赛（true表示没有结束比赛，false表示结束比赛）

enum {
  Forward = 1,           //前进
  Back,                  //后退
  Left,                  //左转
  Right,                 //右转
  Stop,                  //停止
};  //跟踪自动
//小车各种模式状态


void setup() {
  Serial.begin(9600);   //打开串口并启用9600波特率  （和计算机进行通信的速率）
  
  /*
  陀螺仪 已废弃(陀螺仪 不稳定)

  // 初始化 I2C 总线
  // Wire.begin();
  // 初始化 MPU6050
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x6B); // 设置电源管理寄存器
  Wire.write(0);    // 唤醒 MPU6050
  if (Wire.endTransmission() == 0) {
    Serial.println("MPU6050 已上线!");
  } else {
    Serial.println("No MPU6050 Found!");
    while (1); // 停止运行
  }
  */
  

  pinMode(HW, INPUT); //初始化红外传感器
  pinMode(button,INPUT); //按钮传感器初始化


  scheduler.init();
  scheduler.addTask(runtime); // 将任务添加到调度器
  runtime.enable(); // 启用任务

  taskone.init();
  taskone.addTask(taskoneaw); // 将任务添加到调度器
  taskoneaw.enable(); // 启用任务


  
  Motor_Sensor_Init();  //电机及传感器引脚初始化

  Color_Init();        //颜色传感器引脚初始化


  myservo1.attach(Servo1_Pin);//设置舵机1引脚
  myservo2.attach(Servo2_Pin);
  myservo3.attach(Servo3_Pin);
  myservo4.attach(Servo4_Pin);

  myservo1.write(Angle_1);


  myservo2.write(Angle_2);

  myservo3.write(Angle_3);
  
  Oled_Init();

  myservo4.write(Angle_4);

  display.setTextSize(4); //修改字体大小

  display.setTextColor(WHITE); //修改字体颜色

  display.setCursor(35,3);   //修改字体位置  

  display.println("Win"); //显示内容

  display.display();


}
void loop() {

  buttonexe();
  scheduler.execute(); // 执行调度器
  Automatic_Tracking_analogRead();

    
}


