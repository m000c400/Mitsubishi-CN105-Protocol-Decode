#ifndef MELCLOUDDECODER_h
#define MELCLOUDDECODER_h

#include <stdint.h>
#include <time.h>
#include <string.h>
#include "EcodanDecoder.h"  // To get some of the definitions

typedef struct _MelCloudMessgeStruct {
  uint8_t SyncByte;
  uint8_t PacketType;
  uint8_t Preamble[4];
  uint8_t PayloadSize;
  uint8_t Payload[MAXDATABLOCKSIZE];
  uint8_t Checksum;
} MelCloudMessgeStruct;

typedef struct _MelCloudStatus {
  uint8_t ReplyNow, ActiveMessage, Write_To_Melcloud_OK;
  uint8_t ConnectRequest, MELRequest1, MELRequest2, MEL_HB_Request;
  bool A2ADevice, A2WDevice;
  bool MEL_Online = false;
} MelCloudStatus;


class MELCLOUDDECODER {
public:
  MELCLOUDDECODER(void);
  uint8_t Process(uint8_t c);

  void CreateBlankTxMessage(uint8_t PacketType, uint8_t PayloadSize);
  void SetPayloadByte(uint8_t Data, uint8_t Location);
  uint8_t PrepareTxCommand(uint8_t *Buffer);
  void SetTypeA2W(void);
  void SetTypeA2A(void);

  MelCloudStatus Status;
protected:

private:
  MessageStruct RxMessage;
  MessageStruct TxMessage;


  void WriteTypeA2W(MelCloudStatus *Status);
  void WriteTypeA2A(MelCloudStatus *Status);

  uint8_t Preamble[4];

  uint8_t CheckForSyncMsg1(MessageStruct *Message, uint8_t c);
  uint8_t CheckForSyncMsg2(MessageStruct *Message, uint8_t c);
  uint8_t BuildRxMessage(MessageStruct *Message, uint8_t c, MelCloudStatus *Status);

  void CreateBlankMessageTemplate(MessageStruct *Message, uint8_t PacketType, uint8_t PayloadSize, MelCloudStatus *Status);
  uint8_t PrepareCommand(MessageStruct *Message, uint8_t *Buffer, MelCloudStatus *Status);

  uint8_t CheckSum(uint8_t *Buffer, uint8_t len);

  void Process0x5A(uint8_t *Payload, MelCloudStatus *Status);
  void Process0xFF(uint8_t *Payload, MelCloudStatus *Status, uint8_t type);
  void ProcessAC0x01(uint8_t *Payload, MelCloudStatus *Status);
  void ProcessAC0x07(uint8_t *Payload, MelCloudStatus *Status);
  void ProcessAC0x30(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x01(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x02(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x03(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x04(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x05(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x06(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x07(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x08(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x09(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x0B(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x0C(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x0D(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x0E(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x0F(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x10(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x11(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x13(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x14(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x15(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x16(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x17(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x18(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x19(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x1a(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x1b(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x1c(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x1d(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x1e(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x1f(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x20(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x26(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x27(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x28(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x29(uint8_t *Payload, MelCloudStatus *Status);
  void Process0xA1(uint8_t *Payload, MelCloudStatus *Status);
  void Process0xA2(uint8_t *Payload, MelCloudStatus *Status);
  void Process0xA3(uint8_t *Payload, MelCloudStatus *Status);
  void Process0xC9(uint8_t *Payload, MelCloudStatus *Status);
  void Process0xCD(uint8_t *Payload, MelCloudStatus *Status);
  void Process0xCE(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x32(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x33(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x34(uint8_t *Payload, MelCloudStatus *Status);
  void Process0x35(uint8_t *Payload, MelCloudStatus *Status);
  //void ProcessUnkWrite(uint8_t *Payload, MelCloudStatus *Status);

  void WriteOK(uint8_t *Payload, MelCloudStatus *Status);
};

#endif
