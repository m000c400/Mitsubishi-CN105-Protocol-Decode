#ifndef TIMERCALLBACK_h
#define TIMERCALLBACK_h

#include <stdint.h>
#include <Arduino.h>


class TimerCallBack {
public:
  TimerCallBack(uint32_t _Delay, void (*_CallBack)(void));
  void Process(void);
  void SetDelay(uint32_t _Delay);

protected:

private:
  uint32_t Delay;
  uint32_t TimeofNext;
  void (*CallBack)(void);
};


#endif
