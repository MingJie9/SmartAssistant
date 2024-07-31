#ifndef _AUDIO_H
#define _AUDIO_H

#include <Arduino.h>   //Arduino 基础库
#include "base64.h"    //Base64 编码
#include "I2S.h"       //I2S 音频接口
#include <WiFi.h>      //WiFi 和 JSON 处理库
#include <ArduinoJson.h>

// 16bit, monoral, 16000Hz,  linear PCM
class Audio1
{
  I2S *i2s;
  static const int headerSize = 44; //分别表示 WAV 头部大小
  //和 I2S 缓冲区大小。
  static const int i2sBufferSize = 5120;
  char i2sBuffer[i2sBufferSize];    //存储音频数据的缓冲区。
  const int DATA_JSON_SIZE = 512;   //DATA_JSON_SIZE 和 data_json：用于存储 JSON 数据的缓冲区大小和缓冲区。
  char data_json[512];
  String Question = "";             //存储音频转文本后的问题字符串
  //client 和 _client：用于 WiFi 网络连接的客户端。
  WiFiClient client; // @suppress("Abstract class cannot be instantiated")
  // WiFiClientSecure clientsecure; // @suppress("Abstract class cannot be instantiated")
  WiFiClient *_client = nullptr;
  //header_format 和 footer_format：用于构建 JSON 请求的字符串格式。
  const char *header_format = "{"
                              "\"format\":\"pcm\","
                              "\"rate\":8000,"
                              "\"dev_pid\":1537,"
                              "\"channel\":1,"
                              "\"cuid\":\"\","
                              "\"token\":\"\","
                              "\"speech\":\"";

  const char *footer_format = "\",\"len\":";
  //CreateWavHeader：生成 WAV 文件头部。
  void CreateWavHeader(byte *header, int waveDataSize);
  //parseJSON：解析 JSON 响应。
  String parseJSON(const char *jsonResponse);
  //calculateRMS：计算音频数据的均方根（RMS）值。
  float calculateRMS(uint8_t *buffer, int bufferSize);

public:
//wavDataSize 和 dividedWavDataSize：常量，分别表示 WAV 数据大小和分割的 WAV 数据大小。
  static const int wavDataSize = 30000; // It must be multiple of dividedWavDataSize. Recording time is about 1.9 second.
  static const int dividedWavDataSize = i2sBufferSize / 4;
  //wavData：指向分割的 WAV 数据的指针数组。
  char **wavData;                          // It's divided. Because large continuous memory area can't be allocated in esp32.
  //paddedHeader：存储填充后的 WAV 头部，用于 Base64 编码。
  byte paddedHeader[headerSize + 4] = {0}; // The size must be multiple of 3 for Base64 encoding. Additional byte size must be even because wave data is 16bit.

  Audio1();
  ~Audio1();
  //Record：录制音频。
  //clear：清除数据。
  //init：初始化音频接口和其他资源
  void Record();
  void clear();
  void init();
};

#endif // _AUDIO_H
