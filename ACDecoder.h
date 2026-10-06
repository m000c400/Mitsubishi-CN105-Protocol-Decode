#ifndef ACDECODER_h
#define ACDECODER_h

#include <stdint.h>
#include <time.h>
#include <string.h>
#include "proxy.h"

#define PACKET_SYNC 0xFC
#define SET_REQUEST 0x41
#define SET_RESPONSE 0x61
#define GET_REQUEST 0x42
#define GET_RESPONSE 0x62
#define GET_ABOUT_RESPONSE 0x7B
#define CONNECT_REQUEST 0x5A
#define CONNECT_RESPONSE 0x7A
#define EXCONNECT_REQUEST 0x5B
#define EXCONNECT_RESPONSE 0x7B
#define CONNECT_MEL_REQUEST 0xFF

#define COMMANDSIZE 22  // 5 Byte Header + 16 Byte Payload  + 1 Byte Checksum
#define HEADERSIZE 5
#define MAXDATABLOCKSIZE 16

#define AC_PENDING_HOLD_MS 5000  // How long an optimistic write shields a field from stale read-backs

#define PREAMBLESIZE 2



static const int TIMER_INCREMENT_MINUTES = 10;



typedef struct _ACMessageStruct {
  uint8_t SyncByte;
  uint8_t PacketType;
  uint8_t Preamble[PREAMBLESIZE];
  uint8_t PayloadSize;
  uint8_t Payload[MAXDATABLOCKSIZE];
  uint8_t Checksum;
} ACMessageStruct;


typedef struct _ACStatus {

  // From Message 0x02
  uint8_t SystemPowerMode, fan, vane, remoteProhibit, wideVane, Buffer04;
  float Temperature;
  bool tempMode, isee;

  // Optimistic-write reconcile guard: last commanded values, held until the unit
  // reads them back or the hold window lapses (see holdPending in ACDecoder.cpp).
  // Pending*Until == 0 means no hold is active for that field.
  uint8_t PendingPower = 0, PendingMode = 0, PendingFan = 0, PendingVane = 0, PendingWideVane = 0;
  float PendingTemperature = 0;
  unsigned long PendingPowerUntil = 0, PendingModeUntil = 0, PendingFanUntil = 0,
    PendingVaneUntil = 0, PendingWideVaneUntil = 0, PendingTempUntil = 0;

  // From Message 0x03
  float OAT, RoomTempFloat;
  bool RmtempMode;
  uint8_t RoomTemp, Runtime;

  // From Message 0x04
  uint8_t ErrCode1, ErrCode2, FltCode1, FltCode2;

  // From Message 0x05
  uint8_t Timermode, onMinutesSet, onMinutesRemaining, offMinutesSet, offMinutesRemaining;

  // From Message 0x06
  float InputPower, LifePower;
  uint8_t CompressorFrequency, Operating, InputPower1, InputPower2, LifePower1, LifePower2;

  // From Message 0x09
  uint8_t Status, FanActual, AutoMode;

  // From Message 0x61
  bool Write_To_Ecodan_OK;

  // From Messages C9, CD and CE
  bool CD, CE, C9;

  // From Message 0xC9
  bool SupportsHozVane, FanBitA, FanBitB, FanBitC;

  // AC Flag
  bool Is_AC;

} ACStatus;


class ACDECODER {
public:
  ACDECODER(void);
  uint8_t Process(uint8_t c);

  void CreateBlankTxMessage(uint8_t PacketType, uint8_t PayloadSize);
  void SetPayloadByte(uint8_t Data, uint8_t Location);
  uint8_t PrepareTxCommand(uint8_t *Buffer);
  void EncodePower(uint8_t setting);
  void EncodeSetpoint(uint8_t setting, bool floatMode);
  void EncodeSetMode(uint8_t setting);
  void EncodeFanSpeed(uint8_t setting);
  void EncodeVane(uint8_t setting);
  void EncodeWideVane(uint8_t setting);
  void EncodeRemoteTemperature(float setting);

  void EncodeVersion(uint8_t type);
  void EncodeMELCloud(uint8_t cmd);
  void PayloadWipe(void);
  void TransfertoBuffer(uint8_t msgtype, uint8_t bufferposition);
  uint8_t ReturnNextCommandType(uint8_t bufferposition);
  void EncodeNextCommand(uint8_t bufferposition);

  ACStatus Status;
protected:

private:
  ACMessageStruct RxMessage;
  ACMessageStruct TxMessage;


  bool IS_BIT_SET(uint8_t value, uint8_t bit);

  uint8_t Preamble[PREAMBLESIZE];

  uint8_t BuildRxMessage(ACMessageStruct *Message, uint8_t c);

  void CreateBlankMessageTemplate(ACMessageStruct *Message, uint8_t PacketType, uint8_t PayloadSize);
  uint8_t PrepareCommand(ACMessageStruct *Message, uint8_t *Buffer);


  uint8_t CheckSum(uint8_t *Buffer, uint8_t len);

  void Process0x02(uint8_t *Payload, ACStatus *Status);
  void Process0x03(uint8_t *Payload, ACStatus *Status);
  void Process0x04(uint8_t *Payload, ACStatus *Status);
  void Process0x05(uint8_t *Payload, ACStatus *Status);
  void Process0x06(uint8_t *Payload, ACStatus *Status);
  void Process0x09(uint8_t *Payload, ACStatus *Status);
  void Process0x15(uint8_t *Payload, ACStatus *Status);
  void Process0x16(uint8_t *Payload, ACStatus *Status);
  void Process0x17(uint8_t *Payload, ACStatus *Status);
  void Process0x18(uint8_t *Payload, ACStatus *Status);
  void Process0x19(uint8_t *Payload, ACStatus *Status);
  void Process0xC9(uint8_t *Payload, ACStatus *Status);
  void Process0xCD(uint8_t *Payload, ACStatus *Status);
  void Process0xCE(uint8_t *Payload, ACStatus *Status);

  void WriteOK(uint8_t *Payload, ACStatus *Status);
  uint16_t ExtractUInt16(uint8_t *Buffer, uint8_t Index);
};



#endif
