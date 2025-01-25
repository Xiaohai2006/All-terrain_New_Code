//检测和循迹  灰度传感器A0,A2,A3 用来小车巡线时，返回传感器数值；

int Detection_tracking_analogRead() //灰度传感器A0，A2,A3 用来小车巡线时，返回传感器数值；
{
  int num = 0;
  int analogRead_data[3] = {0, 0, 0};
  for (int i = 0; i < Car_Head_Gray_SensorPin_Num; i++)
  {
    analogRead_data[i] = analogRead(Gray_SensorPin[i]); //A3,A2,A0
    switch(Gray_Aoto_Mode) {
      case 0:{
        //没起来的时候
        
        if( analogRead_data[0] <= 480){analogRead_data[0] = 1;} else{analogRead_data[0] = 0;}//17 右
        if( analogRead_data[1] <= 505){analogRead_data[1] = 1;} else{analogRead_data[1] = 0;}//16 中
        if( analogRead_data[2] <= 445){analogRead_data[2] = 1;} else{analogRead_data[2] = 0;} //14 左

        break;
      }
      case 1:{
         //起来的时候 (废弃注释）
         //管道灰度
        
        if( analogRead_data[0] <= 300){analogRead_data[0] = 1;} else{analogRead_data[0] = 0;}//17 右
        if( analogRead_data[1] <= 355){analogRead_data[1] = 1;} else{analogRead_data[1] = 0;}//16 中
        if( analogRead_data[2] <= 325){analogRead_data[2] = 1;} else{analogRead_data[2] = 0;} //14 左

        break;
      }

      default: break;

      
    }
        
    /*
    统一灰度 如果需要精准的灰度 则废弃
    if ( analogRead_data[i] <= 240 ) {
      analogRead_data[i] = 1;
    } else {
      analogRead_data[i] = 0;
    }*/
    num |= ( (analogRead_data[i]) << i);


  }
  
  // Serial.println(num);
  return num;
}




