#include <ServoTimer2.h>        //调用舵机库函数
//金鱼屏幕显示
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>  //调用oled屏幕库函数

//显示部分代码
#ifdef __AVR__
#include <avr/power.h>
#endif
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define button 12   //定义按钮针脚

#define Servo1_Pin 4   //定义舵机引脚号 前舵机

#define Servo2_Pin 11   //定义舵机引脚号 中舵机 大
#define Servo3_Pin 7  //定义舵机引脚号 中舵机 小  

#define Servo4_Pin 3   //定义舵机引脚号 后舵机

#define Angle_1 1400


#define Angle_2 1450   //设置舵机2 转动的初始角度   //小向左 值大向右 //开车第人称一视角 //900 向左转 正方向90°

#define Angle_3 1535  //1535//值低时倒的 往下倒 1535 

#define Angle_4 1500 //设置舵机4转动的初始角度  //值大向下 值小向上 //初始化


//灰度
ServoTimer2 myservo1;        //声明舵机对象 前

ServoTimer2 myservo2;       //声明舵机 中大

ServoTimer2 myservo3;       //声明舵机 中小

ServoTimer2 myservo4;        //声明舵机对象 后

bool lastButtonState = HIGH;  // 记录按钮的上一个状态
bool on = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(button,INPUT); //按钮传感器初始化
  pinMode(A0,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  
  myservo1.attach(Servo1_Pin);//设置舵机1引脚
  myservo2.attach(Servo2_Pin);
  myservo3.attach(Servo3_Pin);
  myservo4.attach(Servo4_Pin);
  Oled_Init();
}

void loop() {
  // put your main code here, to run repeatedly:
  int A01 = analogRead(A0);
  int A21 = analogRead(A2);
  int A31 = analogRead(A3);

  Serial.print("左:");
  Serial.print(A0);
  Serial.print("\t");
  Serial.print("中:");
  Serial.print(A2);
  Serial.print("\t");
  Serial.print("右:");
  Serial.print(A3);
  Serial.print("\n");


  String text = String(A01) + " " + String(A21) + " " + String(A31);
  display.clearDisplay();   // 清屏，防止显示内容叠加
  display.setTextSize(2);   // 修改字体大小
  display.setTextColor(WHITE); // 设置字体颜色
  display.setCursor(0, 3); // 设置字体位置
  display.println(text);    // 显示内容
  display.display();

  
  buttonexe();


}
void buttonexe() {
  bool currentButtonState = digitalRead(button);  // 读取按钮当前状态

  // 按钮从未按下变为按下的状态
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    if(on) {
      myservo1.write(Angle_1);


      myservo2.write(Angle_2);

      myservo3.write(Angle_3);
      myservo4.write(Angle_4);
      on = false;
    } else{
      myservo4.write(1700);
      myservo1.write(1900);  //
      myservo3.write(1650);  //准备进入//值低时倒的 往下倒 1535 平的
      on = true;
    }


  


  
    delay(500);  // 防抖延迟，避免重复触发
  }

  lastButtonState = currentButtonState;  // 更新按钮状态
}

void Oled_Init() //oled屏幕初始化

{

  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);   // initialize with the I2C addr 0x3C (for the 128x64)

  // init done
  display.display(); // show splashscreen

  display.clearDisplay();   // clears the screen and buffer  

}


//检测到 未检测到
//250 670 //
//270 920
// 180 590
//站起来的时候
//150 370
//190  590
//120  440