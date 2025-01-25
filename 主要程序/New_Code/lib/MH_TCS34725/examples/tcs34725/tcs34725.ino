/*!
 * @file tcs34725.ino
 * @brief DFRobot's Color Sensor
 * @n [Get the module here](http://wiki.dfrobot.com.cn/index.php?title=(SKU:SEN0212)Color_Sensor-TCS34725_%E9%A2%9C%E8%89%B2%E4%BC%A0%E6%84%9F%E5%99%A8)
 * @n This example read the color value by the IIC bus
 * @n [Connection and Diagram](http://wiki.dfrobot.com.cn/index.php?title=(SKU:SEN0212)Color_Sensor-TCS34725_%E9%A2%9C%E8%89%B2%E4%BC%A0%E6%84%9F%E5%99%A8)
 *
 * @copyright	[DFRobot](http://www.dfrobot.com), 2016
 * @copyright	GNU Lesser General Public License
 *
 * @author [carl](carl.xu@dfrobot.com)
 * @version  V1.0
 * @date  2016-07-12
 */
#include <Wire.h>
#include "DFRobot_TCS34725.h"

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// DFRobot_TCS34725 tcs = DFRobot_TCS34725();

/* Initialise with specific int time and gain values */
DFRobot_TCS34725 tcs = DFRobot_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

void setup(void) {
  Serial.begin(115200);
  
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }
  
  // Now we're ready to get readings!
}

void loop(void) {
  uint16_t r, g, b, c, colorTemp, lux;
  
  tcs.getRGBC(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature(r, g, b);
  lux = tcs.calculateLux(r, g, b);
  
  Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");
}
