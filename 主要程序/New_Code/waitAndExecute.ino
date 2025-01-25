
void waitAndExecute(unsigned long interval, void (*command)()) {
  unsigned long currentMillis = millis();
  
  // 检查是否达到了等待的间隔
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    // 执行传入的函数指针
    command();
  }
}









void xunji(unsigned long runDuration) {
  /*
  计算经过的时间：使用unsigned long elapsedTime = millis() - startTime;来计算自开始以来已经过去的时间。这种方式确保了时间计算的准确性，并且每次迭代都在更新。
  在每次循环中计算自程序开始以来的时间，而不是在特定时间点才进行计算。
  设置条件：通过设置条件while (elapsedTime < runDuration)来控制循环，使得程序只在指定的运行时间内执行，而不多也不少。条件的判断是在每次迭代中进行的，确保了时间的准确控制。
  */
  
  unsigned long startTimew = millis();  // 记录开始时间
  unsigned long elapsedTimea = 0;        // 记录已经经过的时间

  // 当经过的时间小于指定的运行时间时持续循环
  while (elapsedTimea < runDuration) {
    Automatic_Tracking_analogRead();  // 进行自动循迹读取
    
    // 计算已经经过的时间
    elapsedTimea = millis() - startTimew;

    // 打印当前运行时间（秒）
    Serial.print("当前运行时间: ");
    Serial.print(elapsedTimea / 1000);  // 将毫秒转换为秒并打印
    Serial.println(" 秒");

    

    delay(100); // 加入短暂延迟，以避免串口输出过快（可选）
  }

  // 时间到达，停止小车
  Move(Stop, 0, 0);  
}
