/*
    Copyright (C) <2020>  <Mike Roberts>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "TimerCallBack.h"

TimerCallBack::TimerCallBack(uint32_t _Delay, void (*_CallBack)(void))
{
    Delay = _Delay;
    CallBack = _CallBack;
    TimeofNext = Delay;
}


void TimerCallBack::Process(void)
{
    if ( (int32_t)( (uint32_t)millis() -  TimeofNext ) >= 0 )
    {
        TimeofNext += Delay;
        CallBack();
    }
}

void TimerCallBack::SetDelay(uint32_t _Delay)
{
  Delay = _Delay;
}
