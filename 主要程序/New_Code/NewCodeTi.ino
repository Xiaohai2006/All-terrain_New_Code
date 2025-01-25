void NewCodeTi() {


  /////
  /////
  /////
  /////
  /////           //开车第人称一视角
  /////           myservo1.write(角度); //值大向上 值小向下       //前面的舵机 1900是进管道抬起
  /////           myservo3.write(角度); //中间的舵机 小舵机 ////无
  /////           myservo4.write(角度); //值大向下 值小向上 //后面的舵机
  /////
  /////
  /////


  myservo1.write(1200);  //设置舵机1转动的初始角度  //值大向上 值小向下 //初始化
  delay(700);


  Move(Forward, 75, 70);

  myservo4.write(1780);  //值大向下 值小向上 //后面的舵机 //上楼梯时候 向下顶起后轮

  delay(2000);
  Move(Stop,255,255);
  delay(10);
  myservo1.write(1900);  //值大向下 值小向上 //后面的舵机
  delay(300);
  Move(Forward,75,75);
  delay(700);
  Move(Stop,255,255);
  //myservo3.write(1280);///////////////良帅 //废弃 已更换为多线程
  //二次废弃因性能不足使用主要线程运行
  int x1 = 1580;
  int x2 = x1;
  int aq1 = 1650;
  for (int i = 0; i<= aq1 - x2  ; i++) {
    myservo3.write(x1);  //
    x1 -= 1;
    delay(10);

  }
  delay(20);



  Move(Forward,70,70);
  
  delay(400);
  myservo4.write(1480);



  delay(1000);
  Move(Stop,255,255);
  delay(200);
  Move(Forward,65,65);
  myservo1.write(1080);
  myservo4.write(1780);
  delay(1200);


  myservo4.write(1580);
  delay(500);
  myservo4.write(1080);
  delay(1000);

  Move(Stop,255,255);

  delay(200);

  myservo4.write(1700);
  
  delay(200);
  Move(Forward,70,70);

  delay(1100);

  Move(Stop,255,255);

  x1 = 1580;
  x2 = x1;
  aq1 = 1650;
  for (int i = 0; i<= aq1 - x2; i++) {
    myservo3.write(x1);  //
    x1 += 1;
    delay(10);

  }
  
  
  myservo1.write(980);
  delay(300);

  myservo4.write(1500);

  delay(200);
  Move(Forward, 65, 65);
  delay(1200);

  Move(Stop,255,255);

  int a = 980;
  int c = a;
  int b = 1420;

  for(int i = 0; i <= b - c; i++) {
    
    myservo1.write(a);

    a += 1;
    delay(6);



  }

  Move(Forward, 80,70);
  delay(888);
  
  myservo1.write(980);

  delay(200);
  Move(Stop,255,255);
  delay(2);
  int d = 1500;
  int e = d;
  int f = 1100;

  for (int i =0; i <= e - f; i++) {

    myservo4.write(d);

    d -= 1;
    delay(6);

  }
  delay(10);
  Move(Forward, 83,70);/////下第二个台架了 往前冲
  delay(988);
  Move(Stop,255,255);
  myservo4.write(1650);

  delay(500);

  a = 980;
  c = a;
  b = 1420;

  for(int i = 0; i <= b - c; i++) {
    
    myservo1.write(a);

    a += 1;
    delay(6);

  }

  Move(Forward,83,70);
  delay(888);
  Move(Stop,255,255);


  d = 1650;
  e = d;
  f = 1100;

  for (int i =0; i <= e - f; i++) {

    myservo4.write(d);

    d -= 1;
    delay(6);

  }

  Move(Forward, 120, 100);
  delay(788);
  Move(Stop,255,255);
  delay(10);
  ////准备进入管道
  //废弃以下注释
  // int a1 = 1420;//前面舵机原有的值
  // int a2 =1100;//后面舵机原有的值3

  // int ca1 = a1;//储存原值
  // int ca2 = a2;//储存原值
  
  // int ab1 = 1900;//要达到的舵机值
  // int ab2 = 1700;//要达到的舵机值
  // int cda = 0;//执行次数

  myservo4.write(900);//1700
  myservo1.write(1700);//

  

  delay(300);
  int l = 1480;
  int ll = l;
  int lll= 1750;
  for (int i = 0; i <= lll - l; i++) {
    myservo3.write(l);//准备进入//值低时倒的 往下倒 1535 平的
    l += 1;
    delay(3);

  }
  delay(500);
  


  //切换 后脚抬起灰度检测
  Gray_Aoto_Mode = 1;
  //切换 无记录111 检测
  Get_Stats = 1;
  //准备完毕
  //等待7秒 恢复 111 检测
  //非阻塞 延迟执行
  waitAndExecute(7000, []() {
    //等待 7秒后恢复
    Get_Stats = 0;
  });


}
