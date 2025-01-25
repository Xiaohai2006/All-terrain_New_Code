/*!
 * @file interrupt.ino
 * @brief DFRobot's Color Sensor
 * @n [Get the module here](http://wiki.dfrobot.com.cn/index.php?title=(SKU:SEN0212)Color_Sensor-TCS34725_%E9%A2%9C%E8%89%B2%E4%BC%A0%E6%84%9F%E5%99%A8)
 * @n This example set interrupt service routine, read the color value,simulation calculation according to the original value by the IIC bus
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
#include <DFRobot_TCS34725.h>


/* Initialise with specific int time and gain values */
DFRobot_TCS34725 tcs = DFRobot_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);
const int interruptPin = 2;
volatile boolean state = false;


//Interrupt Service Routine
void isr() 
{
  state = true;
}


/* tcs.getRGBC() does a delay(Integration_Time) after the sensor readout.
We don't need to wait for the next integration cycle because we receive an interrupt when the integration cycle is complete*/
void getRawData_noDelay(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c)
{
  *c = tcs.readRegWord(TCS34725_CDATAL);
  *r = tcs.readRegWord(TCS34725_RDATAL);
  *g = tcs.readRegWord(TCS34725_GDATAL);
  *b = tcs.readRegWord(TCS34725_BDATAL);
}


void setup() {
  pinMode(interruptPin, INPUT_PULLUP); //TCS interrupt output is Active-LOW and Open-Drain
  attachInterrupt(digitalPinToInterrupt(interruptPin), isr, FALLING);

  Serial.begin(115200);
  
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }
  
  // Set persistence filter to generate an interrupt for every RGB Cycle, regardless of the integration limits
  tcs.writeReg(TCS34725_PERS, TCS34725_PERS_NONE); 
  tcs.lock();
  
  Serial.flush();
}


void loop() {
  if (state) {
    uint16_t r, g, b, c, colorTemp, lux;
    getRawData_noDelay(&r, &g, &b, &c);
    colorTemp = tcs.calculateColorTemperature(r, g, b);
    lux = tcs.calculateLux(r, g, b);
    
    Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
    Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
    Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
    Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
    Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
    Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
    Serial.println(" ");
    Serial.flush();
    tcs.clear();
    state = false;
  }
}
