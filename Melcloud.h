#ifndef MELCLOUD_h
#define MELCLOUD_h

#include <stdint.h>
#include <Arduino.h>
#include "MELCloudDecoder.h"
#include "proxy.h"


class MELCLOUD : public MELCLOUDDECODER {
public:
  MELCLOUD(void);
  void Process(void);
  void SetStream(Stream *MELCloudStream);
  void ConnectA2W(void);
  void ConnectA2A(void);
  void MELNegotiate1(bool A2A);
  void MELNegotiate2(void);
  void ReplyStatus(uint8_t TargetMessage);
  uint8_t UpdateComplete(void);
  uint8_t Lastmsbetweenmsg(void);
  unsigned long LastMELCloudMessage(void);
  uint8_t Connected;

protected:

private:
  uint8_t UpdateFlag;
  uint8_t msbetweenmsg;
  
  void printCurrentTime(void);

  MessageStruct TXMessage;
  Stream *DeviceStream;
};

#endif