/*!
 * @file tcs34725autorange.ino
 * @brief DFRobot's Color Sensor
 * @n [Get the module here](http://wiki.dfrobot.com.cn/index.php?title=(SKU:SEN0212)Color_Sensor-TCS34725_%E9%A2%9C%E8%89%B2%E4%BC%A0%E6%84%9F%E5%99%A8)
 * @n This example retrieve color data from the sensor and do the calculations Gain Raw IR CPL Compensated Lux by the IIC bus
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

#define TCS34725_R_Coef 0.136 
#define TCS34725_G_Coef 1.000
#define TCS34725_B_Coef -0.444
#define TCS34725_GA 1.0
#define TCS34725_DF 310.0
#define TCS34725_CT_Coef 3810.0
#define TCS34725_CT_Offset 1391.0

// Autorange class for DFRobot_TCS34725
class tcs34725 {
public:
  tcs34725(void);

  boolean begin(void);
  void getData(void);  

  boolean isAvailable, isSaturated;
  uint16_t againx, atime, atime_ms;
  uint16_t r, g, b, c;
  uint16_t ir; 
  uint16_t r_comp, g_comp, b_comp, c_comp;
  uint16_t saturation, saturation75;
  float cratio, cpl, ct, lux, maxlux;
  
private:
  struct tcs_agc {
    tcs34725Gain_t ag;
    tcs34725IntegrationTime_t at;
    uint16_t mincnt;
    uint16_t maxcnt;
  };
  static const tcs_agc agc_lst[];
  uint16_t agc_cur;

  void setGainTime(void);  
  DFRobot_TCS34725 tcs;    
};
//
// Gain/time combinations to use and the min/max limits for hysteresis 
// that avoid saturation. They should be in order from dim to bright. 
//
// Also set the first min count and the last max count to 0 to indicate 
// the start and end of the list. 
//
const tcs34725::tcs_agc tcs34725::agc_lst[] = {
  { TCS34725_GAIN_60X, TCS34725_INTEGRATIONTIME_700MS,     0, 20000 },
  { TCS34725_GAIN_60X, TCS34725_INTEGRATIONTIME_154MS,  4990, 63000 },
  { TCS34725_GAIN_16X, TCS34725_INTEGRATIONTIME_154MS, 16790, 63000 },
  { TCS34725_GAIN_4X,  TCS34725_INTEGRATIONTIME_154MS, 15740, 63000 },
  { TCS34725_GAIN_1X,  TCS34725_INTEGRATIONTIME_154MS, 15740, 0 }
};
tcs34725::tcs34725() : agc_cur(0), isAvailable(0), isSaturated(0) {
}

// initialize the sensor
boolean tcs34725::begin(void) {
  tcs = DFRobot_TCS34725(agc_lst[agc_cur].at, agc_lst[agc_cur].ag);
  if ((isAvailable = tcs.begin())) 
    setGainTime();
  return(isAvailable);
}

// Set the gain and integration time
void tcs34725::setGainTime(void) {
  tcs.setGain(agc_lst[agc_cur].ag);
  tcs.setIntegrationTime(agc_lst[agc_cur].at);
  atime = int(agc_lst[agc_cur].at);
  atime_ms = ((256 - atime) * 2.4);  
  switch(agc_lst[agc_cur].ag) {
  case TCS34725_GAIN_1X: 
    againx = 1; 
    break;
  case TCS34725_GAIN_4X: 
    againx = 4; 
    break;
  case TCS34725_GAIN_16X: 
    againx = 16; 
    break;
  case TCS34725_GAIN_60X: 
    againx = 60; 
    break;
  }        
}

// Retrieve data from the sensor and do the calculations
void tcs34725::getData(void) {
  // read the sensor and autorange if necessary
  tcs.getRGBC(&r, &g, &b, &c);
  while(1) {
    if (agc_lst[agc_cur].maxcnt && c > agc_lst[agc_cur].maxcnt) 
      agc_cur++;
    else if (agc_lst[agc_cur].mincnt && c < agc_lst[agc_cur].mincnt)
      agc_cur--;
    else break;

    setGainTime(); 
    delay((256 - atime) * 2.4 * 2); // shock absorber
    tcs.getRGBC(&r, &g, &b, &c);
    break;    
  }

  // DN40 calculations
  ir = (r + g + b > c) ? (r + g + b - c) / 2 : 0;
  r_comp = r - ir;
  g_comp = g - ir;
  b_comp = b - ir;
  c_comp = c - ir;   
  cratio = float(ir) / float(c);

  saturation = ((256 - atime) > 63) ? 65535 : 1024 * (256 - atime);
  saturation75 = (atime_ms < 150) ? (saturation - saturation / 4) : saturation;
  isSaturated = (atime_ms < 150 && c > saturation75) ? 1 : 0;
  cpl = (atime_ms * againx) / (TCS34725_GA * TCS34725_DF); 
  maxlux = 65535 / (cpl * 3);

  lux = (TCS34725_R_Coef * float(r_comp) + TCS34725_G_Coef * float(g_comp) + TCS34725_B_Coef * float(b_comp)) / cpl;
  ct = TCS34725_CT_Coef * float(b_comp) / float(r_comp) + TCS34725_CT_Offset;
}

tcs34725 rgb_sensor;

void setup(void) {
  Serial.begin(115200);
  rgb_sensor.begin();
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW); // @gremlins Bright light, bright light!
}

void loop(void) {
  rgb_sensor.getData();
  Serial.print(F("Gain:")); 
  Serial.print(rgb_sensor.againx); 
  Serial.print(F("x "));
  Serial.print(F("Time:")); 
  Serial.print(rgb_sensor.atime_ms); 
  Serial.print(F("ms (0x")); 
  Serial.print(rgb_sensor.atime, HEX);   
  Serial.println(F(")"));
  
  Serial.print(F("Raw R:")); 
  Serial.print(rgb_sensor.r); 
  Serial.print(F(" G:")); 
  Serial.print(rgb_sensor.g); 
  Serial.print(F(" B:")); 
  Serial.print(rgb_sensor.b); 
  Serial.print(F(" C:")); 
  Serial.println(rgb_sensor.c); 

  Serial.print(F("IR:")); 
  Serial.print(rgb_sensor.ir); 
  Serial.print(F(" CRATIO:"));
  Serial.print(rgb_sensor.cratio); 
  Serial.print(F(" Sat:"));
  Serial.print(rgb_sensor.saturation); 
  Serial.print(F(" Sat75:"));
  Serial.print(rgb_sensor.saturation75); 
  Serial.print(F(" "));
  Serial.println(rgb_sensor.isSaturated ? "*SATURATED*" : "");

  Serial.print(F("CPL:")); 
  Serial.print(rgb_sensor.cpl);
  Serial.print(F(" Max lux:")); 
  Serial.println(rgb_sensor.maxlux);

  Serial.print(F("Compensated R:")); 
  Serial.print(rgb_sensor.r_comp); 
  Serial.print(F(" G:")); 
  Serial.print(rgb_sensor.g_comp); 
  Serial.print(F(" B:")); 
  Serial.print(rgb_sensor.b_comp); 
  Serial.print(F(" C:")); 
  Serial.println(rgb_sensor.c_comp); 
  
  Serial.print(F("Lux:")); 
  Serial.print(rgb_sensor.lux);
  Serial.print(F(" CT:")); 
  Serial.print(rgb_sensor.ct);
  Serial.println(F("K")); 
  
  Serial.println();
  
  delay(2000);
}
