#include "TimerCallBack.h"

TimerCallBack::TimerCallBack(uint32_t _Delay, void (*_CallBack)(void)) {
  Delay = _Delay;
  CallBack = _CallBack;
  TimeofNext = Delay;
}


void TimerCallBack::Process(void) {
  if ((int32_t)((uint32_t)millis() - TimeofNext) >= 0) {
    TimeofNext += Delay;
    CallBack();
  }
}

void TimerCallBack::SetDelay(uint32_t _Delay) {
  Delay = _Delay;
}
