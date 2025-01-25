//由于死机问题移除大量 多线程代码


//废弃
void taskonea() {
  int x1 = 1400;
  int x2 = x1;
  int aq1 = 1300;
  for (int i = 0; i<= x2 - aq1; i++) {
    myservo4.write(x1);  //
    x1 -= 1;
    delay(20);

  }
  taskoneaw.disable(); // 停止任务
}


void Taska() {

  elapsedTime += 500; // 每次调用增加500毫秒
  Serial.print("当前运行时间: ");
  Serial.print(elapsedTime / 1000); // 输出运行时间（秒）
  Serial.println(" 秒");

}


void Oled_Init() //oled屏幕初始化

{

  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);

  display.display();

  display.clearDisplay();

}

void buttonexe() {
  bool currentButtonState = digitalRead(button);  // 读取按钮当前状态

  // 按钮从未按下变为按下的状态
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    Gray_Three++;  // 按钮被按下时递增
    Gray_Aoto_Mode = 1;
    ////准备进入管道
    myservo4.write(900);
    myservo1.write(1700);  //
    myservo3.write(1650);  //准备进入//值低时倒的 往下倒 1535 平的
    delay(500);  // 防抖延迟，避免重复触发
  }

  lastButtonState = currentButtonState;  // 更新按钮状态
}


