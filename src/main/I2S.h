#ifndef _I2S_H
#define _I2S_H
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2s.h"
#include "esp_system.h"
/*
Arduino.h：为 Arduino 平台提供基本功能的库。
freertos/FreeRTOS.h 和 freertos/task.h：FreeRTOS 相关的头文件，ESP32 使用 FreeRTOS 作为操作系统。
driver/i2s.h：ESP32 的 I2S 驱动程序头文件。
esp_system.h：ESP32 系统相关的函数和宏定义。
*/
enum MicType {
  ADMP441,
  ICS43434,
  M5GO,
  M5STACKFIRE
};

class I2S {
  i2s_bits_per_sample_t BITS_PER_SAMPLE;
public:
  I2S();
  int Read(char* data, int numData);
  int GetBitPerSample();
  void clear();
};

#endif // _I2S_H
