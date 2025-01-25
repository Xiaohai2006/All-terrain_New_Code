void Automatic_Tracking_analogRead() //小车前方两个灰度传感器用来寻迹（即小车巡线）。
{
  int Get_Data = 0;
  Get_Data = Detection_tracking_analogRead();////灰度传感器A0,A2,A3,用来小车巡线时，返回传感器数值；(序号值）
  // Serial.println(Get_Data);
  switch (Get_Stats) {
    case 0:
    {
        switch (Get_Data)
        {

          case 0x00: Move(Forward, Forward_Left_Speed, Forward_Right_Speed); break; //(0,0, 0, 1); //forward  前进
          case 0x01: Move(Right,  Right_Left_Speed,  Right_Right_Speed  ); break; //(0,0, 1, 1);//RIGHT   右转
          case 0x02: Move(Forward, Forward_Left_Speed, Forward_Right_Speed); break; //(0,1, 0, 1);//forward  前进
          case 0x03: Move(Right,  Right_Left_Speed,  Right_Right_Speed  ); break; //(0,1, 1, 1);//right  右转
          case 0x04: Move(Left,   Left_Left_Speed,   Left_Right_Speed   ); break; //(1,0, 0, 1);//left   左转
          case 0x06: Move(Left,   Left_Left_Speed,   Left_Right_Speed   ); break; //（1,1, 0, 1）;//LEFT  左转
          case 0x07:
            {

              Move(Forward, Forward_Left_Speed, Forward_Right_Speed);
              Gray_Three ++;//记录三个灰度传感器同时触发的次数(记录小车经过特殊路口的次数)
              
              Move(Forward, Forward_Left_Speed, Forward_Right_Speed);
              if (Gray_Three == 3) 
              {
                road_three();
              }
              if (Gray_Three == 2)
              {
                road_two();
              }
              if (Gray_Three == 1)
              {
                road_one();
              }
            }
            break;
          default: break;
        }
        break;
    }
    case 1:
    {
        switch (Get_Data)
        {

          case 0x00: Move(Forward, Forward_Left_Speed, Forward_Right_Speed); break; //(0,0, 0, 1); //forward  前进
          case 0x01: Move(Right,  Right_Left_Speed,  Right_Right_Speed  ); break; //(0,0, 1, 1);//RIGHT   右转
          case 0x02: Move(Forward, Forward_Left_Speed, Forward_Right_Speed); break; //(0,1, 0, 1);//forward  前进
          case 0x03: Move(Right,  Right_Left_Speed,  Right_Right_Speed  ); break; //(0,1, 1, 1);//right  右转
          case 0x04: Move(Left,   Left_Left_Speed,   Left_Right_Speed   ); break; //(1,0, 0, 1);//left   左转
          case 0x06: Move(Left,   Left_Left_Speed,   Left_Right_Speed   ); break; //（1,1, 0, 1）;//LEFT  左转
          case 0x07: Move(Forward, Forward_Left_Speed, Forward_Right_Speed); break;
          default: break;
        }
        break;

    }
    case 2:
    {
      switch (Get_Data) 
      {

          case 0x00: Move(Forward, Forward_Left_Speed, Forward_Right_Speed); break; //(0,0, 0, 1); //forward  前进
          case 0x01: Move(Right,  Right_Left_Speed,  Right_Right_Speed); break; //(0,0, 1, 1);//RIGHT   右转
          case 0x02: Move(Forward, Forward_Left_Speed, Forward_Right_Speed); break; //(0,1, 0, 1);//forward  前进
          case 0x03: Move(Right,  Right_Left_Speed,  Right_Right_Speed  ); break; //(0,1, 1, 1);//right  右转
          case 0x04: Move(Left,   Left_Left_Speed,   Left_Right_Speed   ); break; //(1,0, 0, 1);//left   左转
          case 0x06: Move(Left,   Left_Left_Speed,   Left_Right_Speed   ); break; //（1,1, 0, 1）;//LEFT  左转
          case 0x07: 
            Move(Forward, 240, 240);
            delay(2000);
            Move(Stop,0,0);

            while(1);

            break;
          default: break;
      }
    }
    case 3:
    {
      switch (Get_Data) 
      {
          case 0x00: Move(Forward, Forward_Left_Speed, Forward_Right_Speed); break; //(0,0, 0, 1); //forward  前进
          case 0x01: Move(Right,  Right_Left_Speed,  Right_Right_Speed); break; //(0,0, 1, 1);//RIGHT   右转
          case 0x02: Move(Forward, Forward_Left_Speed, Forward_Right_Speed); break; //(0,1, 0, 1);//forward  前进
          case 0x03: Move(Right,  Right_Left_Speed,  Right_Right_Speed  ); break; //(0,1, 1, 1);//right  右转
          case 0x04: Move(Left,   Left_Left_Speed,   Left_Right_Speed   ); break; //(1,0, 0, 1);//left   左转
          case 0x06: Move(Left,   Left_Left_Speed,   Left_Right_Speed   ); break; //（1,1, 0, 1）;//LEFT  左转
          case 0x07: 
            break;
          default: break;
      }
    }

    default: break;
  }

}

//初始化灰度和电机引脚初始化
void Motor_Sensor_Init()
{
  for (int i = 0; i < Car_Head_Gray_SensorPin_Num; i++) { //初始化灰度传感器
    pinMode(Gray_SensorPin[i], INPUT);
    delay(20);
  }
  for (int i = 0; i < motor_num; i++) { //初始化 电机引脚
    pinMode(Car_DC_Motor_Pin[i], OUTPUT);
    delay(20);
  }
}