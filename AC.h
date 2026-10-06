#ifndef AC_h
#define AC_h

#include <stdint.h>
#include <Arduino.h>
#include "ACDecoder.h"


class AC : public ACDECODER {
public:
  AC(void);
  void Process(void);
  void SetStream(Stream* ACStream);
  void TriggerStatusStateMachine(void);
  void StopStateMachine(void);
  void StatusStateMachine(void);
  void WriteStateMachine(void);
  uint8_t UpdateComplete(void);
  uint8_t SVCUpdateComplete(void);
  uint8_t HeatPumpConnected(void);
  uint8_t Lastmsbetweenmsg(void);

  int lookupByteMapIndex(const int valuesMap[], int len, int lookupValue);
  int lookupByteMapIndex(const char* valuesMap[], int len, const char* lookupValue);
  const char* lookupByteMapValue(const char* valuesMap[], const byte byteMap[], int len, byte byteValue);
  int lookupByteMapValue(const int valuesMap[], const byte byteMap[], int len, byte byteValue);

  void SetWideVane(const char* WideVane);
  void SetVane(const char* Vane);
  void SetFanSpeed(const char* Speed);
  void SetMode(const char* Mode);
  void SetTempSetpoint(float Setpoint, bool floatMode);
  void SetRemoteTemp(float Setpoint);
  void SetSystemPowerMode(bool OnOff);
  void WriteMELCloudCMD(uint8_t cmd);

  void Connect(void);
  void Disconnect(void);
  void GetVersion(uint8_t type);
  bool PauseStateMachine;
  bool PrevConnected;
  
  const uint8_t POWER[2] = { 0x00, 0x01 };
  const char* POWER_MAP[2] = { "OFF", "ON" };
  const uint8_t MODE[5] = { 0x01, 0x02, 0x03, 0x07, 0x08 };
  const char* MODE_MAP[5] = { "heat", "dry", "cool", "fan_only", "auto" };
  const char* MODE_HA_MAP[5] = { "heating", "drying", "cooling", "fan", "idle" };
  const uint8_t TEMP[16] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
  const int TEMP_MAP[16] = { 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16 };
  const uint8_t FAN[6] = { 0x00, 0x01, 0x02, 0x03, 0x05, 0x06 };
  const char* FAN_MAP[6] = { "AUTO", "QUIET", "1", "2", "3", "4" };
  const char* FAN_HA_MAP[6] = { "AUTO", "QUIET", "1", "2", "3", "4" };
  const uint8_t VANE[7] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x07 };
  const char* VANE_MAP[7] = { "AUTO", "1", "2", "3", "4", "5", "SWING" };
  const uint8_t WIDEVANE[7] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x08, 0x0c };
  const char* WIDEVANE_MAP[7] = { "<<", "<", "|", ">", ">>", "<>", "SWING" };
  const uint8_t ROOM_TEMP[32] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                                  0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f };
  const int ROOM_TEMP_MAP[32] = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
                                  26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41 };
  const uint8_t TIMER_MODE[4] = { 0x00, 0x01, 0x02, 0x03 };
  const char* TIMER_MODE_MAP[4] = { "NONE", "OFF", "ON", "BOTH" };


protected:

private:


  uint8_t CurrentMessage, CurrentSVCMessage;
  uint8_t CurrentCommand;

  uint8_t UpdateFlag, SVCUpdateFlag;
  bool ProcessFlag;
  uint8_t Connected;

  uint8_t msbetweenmsg;


  ACMessageStruct TXMessage;
  Stream* DeviceStream;
  void printCurrentTime(void);
  void printTransferMsg(int length);
};

#endif