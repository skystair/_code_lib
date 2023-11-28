#include "config.h"


USBD_HandleTypeDef USBD_Device;

void GetPointerData(unsigned char *pbuf);

void GetPointerData(unsigned char *pbuf)
{
  static int8_t cnt = 0;
  int8_t  x = 0, y = 0 ;
  
  if(cnt++ > 0)
  {
    x = CURSOR_STEP;
  }
  else
  {
    x = -CURSOR_STEP;
  }
	y = x;

  pbuf[0] = 0;
  pbuf[1] = x;
  pbuf[2] = y;
  pbuf[3] = 0;
}

