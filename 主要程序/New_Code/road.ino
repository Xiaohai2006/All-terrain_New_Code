// 经过第一个路口
void road_one() {

  
  Move(Forward, 195, 170);
  

  waitAndExecute(300, []() {
  
    int a = 1400;//原来舵机的值
    int b = 1500;//原来舵机的值
    int e = 1535;//原来舵机的值
    int c = 0;//执行次数
    int d = 0;//执行次数
    bool f = false;//
    for (int i = 0; i <= 600; i++) {

      myservo4.write(b);
      if (c == 5) {
        b -= 1;
        c = 0;
      }
      c += 1;
      if (d <= 32 && !f) {
        if (d == 32) {

          e -= 5;
          myservo3.write(e);
          f = true;
        }

        d += 1;
      }

      if (d >= 0 && f) {
        if (d == 0) {
          e += 5;

          myservo3.write(e);
        }
        d -= 1;
      }

      myservo1.write(a);
      a += 1;
      delay(4);



    }
  });

  
  myservo1.write(1360); 

  delay(500);  

  
  myservo4.write(1400);

  myservo3.write(1650);

  for(int i = 1; i <= 6; i++) {
    Move(Forward,  70,65);
    delay(400); 
    Move(Stop, 255, 255);
    delay(400);

  }
  /*
  //陀螺仪控制 已废弃

  // while(1) {
    



  //   Wire.beginTransmission(MPU6050_ADDR);
  //     Wire.write(0x3B);  // 起始寄存器地址
  //     Wire.endTransmission(false);
  //     Wire.requestFrom(MPU6050_ADDR, 6, true);  // 读取6个字节数据

  //     if (Wire.available() == 6) {
  //       int16_t ax = Wire.read() << 8 | Wire.read();
  //       int16_t ay = Wire.read() << 8 | Wire.read();
  //       int16_t az = Wire.read() << 8 | Wire.read();

  //       // 输出陀螺仪加速度数据
  //       Serial.print("AX: "); Serial.print(ax);
  //       Serial.print(" AY: "); Serial.print(ay);
  //       Serial.print(" AZ: "); Serial.println(az);

  //       // 根据ax值控制动作
  //       if (ax >= 10 && ax <= 600) {
  //         Move(Forward, 65, 60);
  //       } else {
  //         Move(Back, 25, 25);
  //         delay(1200);  // 保持后退状态1200ms
  //         Move(Stop, 0, 0);  // 停止
  //         delay(500);  // 停止500ms
  //         break;  // 跳出循环
  //       }

  //     }
  




  // }

  */



  //Move(Back, 26, 26);    //开始下坡 //废弃
  //taskone.execute(); // 执行调度器 // 性能不足废弃

  Move(Forward, 65, 60);
  delay(2000);

  //切换 后脚抬起灰度检测
  Gray_Aoto_Mode = 1;
  //切换 无记录111 检测
  Get_Stats = 1;
  //准备完毕

  ////准备进入管道
  
  /*
  //废弃
  //servo4 原 1400 新 1700
  
  // myservo4.write(1700);

  // int my4a = 1400;
  // int myzwh = my4a;
  // int myqjy4b = 1700;

  // for (int i = 0; i <= myqjy4b - myzwh; i++) {

  //   my4a += 1;
  //   myservo4.write(my4a);

  //   delay(2);

  // }
  */
  
  myservo4.write(900);
  myservo1.write(1700);  //1900
  myservo3.write(1650);  //准备进入//值低时倒的 往下倒 1535 平的
  delay(200);
  //等待7秒 恢复 111 检测
  //非阻塞 延迟执行
  waitAndExecute(7000, []() {
    //等待 7秒后恢复
    Get_Stats = 0;
  });
  Forward_Left_Speed = 160;  //小车前进时左轮速度
  Forward_Right_Speed = 140;  //小车前进时右轮速度
  Left_Left_Speed = 160;     //小车左转时左轮速度
  Left_Right_Speed = 145;    //小车左转时右轮速度

}

// 经过第2个路口
void road_two() {

  //靠近楼梯
  Move(Forward, 0, 0);
  delay(100);
  
  Move(Right,200,200);
  delay(50);
  Move(Forward, 70, 65);
  delay(1000);
  Move(Forward, 0, 0);
  delay(1000);

  //到边缘了

  ///开始爬楼梯

  //NewCodeTi.ino

  NewCodeTi();
  Forward_Left_Speed = 160;  //小车前进时左轮速度
  Forward_Right_Speed = 150;  //小车前进时右轮速度
  Right_Left_Speed = 165;  //小车右转时左轮速度
  Right_Right_Speed = 140;   //小车右转时右轮速度
}


/*
  重写road_three()
  重写时间2024年11月28日18点36分

*/
void road_three() {
  //暂时停止
  Move(Stop, 255, 255);
  

  //myservo2.write(920);
  //
  //准备颜色识别的姿势
  myservo1.write(1400);
  delay(300);
  myservo2.write(1600);
  myservo4.write(1500);
  delay(666);
  
  Gray_Aoto_Mode = 0;

  //姿势准备完毕 准备识别卡片


  
  return_color_card();//识别目标卡片
  finish = true;
  finish_all = true;
  delay(500);
  
  airG = false;
  blockG = true;
  Move(Forward,70,65);
  delay(100);
  Forward_Left_Speed = 140;
  Forward_Right_Speed = 120;
  xunji(500);
  //先让程序陷入死循环

  

  while(1){
    HWd();

  }



}

//检测红外
int HWd() {
  bool endd = false;
  int stats = digitalRead(HW);
  

  if(!(stats == 1)){
    Automatic_Tracking_analogRead(); //继续进行循迹
    if(finish_all) {
      if (airG) {
        block = block + 1;
        
          
          Move(Stop,255,255);
          delay(100);
          return_color_ballon();//识别当前卡片是否符合目标卡片
        
        
          delay(100); 

          if ((color_detection_card == color_detection_ballon) && finish) {
            
            finish = false;
            Get_Stats = 2;//切换循迹模式
            if (air >= 3) {
              Get_Stats = 3;//切换循迹模式
              endd = true;
            }

            
            
            
          }
          

          airG = false;
          blockG = true;
          xunji(300);
        }
    } 


  } 
  else {
    
    Automatic_Tracking_analogRead(); //继续进行循迹
    if(finish_all) {
      if(blockG){
        air += 1;
        
        if (!finish) {
          Move(Stop,255,255);
          delay(100);
          dao();
          Forward_Left_Speed = 220;  //小车前进时左轮速度
          Forward_Right_Speed = 200;  //小车前进时右轮速度
          finish_all = false;
          if (endd) {
            end();
          }
          
            
          
        }
        
        airG = true;
        blockG = false;
        xunji(300);
      


      }
    }

  }
}

void end() {
  Move(Forward, 240, 240);
  delay(2000);
  Move(Stop, 0, 0);


  while(1);//陷入死循环程序运行结束


}
/*
  废弃 函数road_three()
  废弃时间 2024年11月28日18点36分 
  废弃原因： 重写红外方案

*/

/*
// 经过第3个路口
void road_three() {


  // return_color_card();//识别记录目标卡片
  // return_color_ballon();//识别目标卡片

  // Get_Stats = 2;

  //   if (finish_all) {
  //     Tracking_Automatic_Tracking(1448);//1424
  //     Move(Stop, Car_speed_stop, Car_speed_stop);
  //     delay(600);
  //     return_color_ballon();
  //     Move(Forward,90,100);
  //     delay(500);
  //     Move(Stop, Car_speed_stop, Car_speed_stop);

  //     if ((color_detection_card == color_detection_ballon) && finish) {
  //       dao();
  //       finish = false;
  //       finish_all = false;
  //       Get_Stats = 2;
  //     }  //识别判读按条件
  //   }


  Move(Stop, 0, 0);
  //myservo2.write(920);

  myservo1.write(1400);
  delay(300);
  myservo2.write(1600);
  myservo4.write(1500);
  delay(666);//888
  // int color = Get_Color_Data();

  return_color_card(); 识别目标卡片

  int colora;
  delay(100);//200
   
  xunji(620); //自动循迹

  delay(100);
  return_color_ballon();
  delay(100);

  //小车走到第一个卡牌区域，并判断卡牌颜色。
  if (color_detection_card == color_detection_ballon) {  //比较
    Move(Forward,90,110);
    delay(550);
    Move(Stop,0,0);
    delay(100);
    dao();
    finish = false;
    finish_all = false;
    Get_Stats = 2;

  }
  if (finish_all) {
    xunji(650);
    delay(100);
    return_color_ballon();
    delay(500);

    //小车走到第二个卡牌区域，并判断卡牌颜色。
    if ((color_detection_card == color_detection_ballon) && finish) {
      Move(Forward,90,110);
      delay(500);
      Move(Stop,0,0);
      delay(100);
      dao();
      finish = false;
      finish_all = false;
      Get_Stats = 2;
    }  
  }
  
  if (finish_all) {
    xunji(600);
    delay(100);
    return_color_ballon();
    delay(500);

    //小车走到第三个卡牌区域，并判断卡牌颜色。
    if ((color_detection_card == color_detection_ballon) && finish) {
      Move(Forward,90,110);
      delay(500);
      Move(Stop,0,0);
      delay(100);
      dao();
      finish = false;
      finish_all = false;
      Get_Stats = 2;
    }  
  }
  Get_Stats = 2;

}
*/
void dao() {
  int a = 1600;
  int b = a;
  int c = 950;
  for (int i = 0; i <= b - c; i++) {
    myservo2.write(a);
    a -= 1;
    delay(3);
  }
  delay(200);

  int a1 = 1535;
  int ca1 = a1;
  int b1 = 405;
  for(int i = 0; i <= ca1 - b1; i++) {
    myservo3.write(a1);
    a1 -= 1;
    delay(2);
  }
  
  delay(500);
  myservo2.write(1600);
  myservo3.write(1535);
  delay(500);

}
