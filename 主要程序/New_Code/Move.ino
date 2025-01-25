//小车运动
void Move(int Mode, int LeftSpeed, int RightSpeed)
{
  switch (Mode)
  {
    case Forward: {//前进
        analogWrite(Car_DC_Motor_Pin[0], LeftSpeed);
        analogWrite(Car_DC_Motor_Pin[1], 0);
        analogWrite(Car_DC_Motor_Pin[2], RightSpeed);
        analogWrite(Car_DC_Motor_Pin[3], 0);
      } break;
    case Back:   {
        analogWrite(Car_DC_Motor_Pin[0], 0); //9
        analogWrite(Car_DC_Motor_Pin[1], LeftSpeed);//10
        analogWrite(Car_DC_Motor_Pin[2], 0); //5
        analogWrite(Car_DC_Motor_Pin[3], RightSpeed);//6
      } break;
    case Left:   {
        analogWrite(Car_DC_Motor_Pin[0], 0); //9
        analogWrite(Car_DC_Motor_Pin[1], LeftSpeed);//10
        analogWrite(Car_DC_Motor_Pin[2], RightSpeed);//5
        analogWrite(Car_DC_Motor_Pin[3], 0);//6
      } break;
    case Right:  {
        analogWrite(Car_DC_Motor_Pin[0], LeftSpeed);//9
        analogWrite(Car_DC_Motor_Pin[1], 0);   //10
        analogWrite(Car_DC_Motor_Pin[2], 0); //5
        analogWrite(Car_DC_Motor_Pin[3], RightSpeed);//6
      } break;
    case Stop:   {
        analogWrite(Car_DC_Motor_Pin[0], LeftSpeed);//9
        analogWrite(Car_DC_Motor_Pin[1], LeftSpeed);//10
        analogWrite(Car_DC_Motor_Pin[2], RightSpeed);//5
        analogWrite(Car_DC_Motor_Pin[3], RightSpeed);//6
      } break;
    default: break;
  }
}

