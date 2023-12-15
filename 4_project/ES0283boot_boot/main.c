#include "config.h"
unsigned char updatacmpflag;
unsigned char iapstate;

void iapfunc(void);

int main(void)
{
	__disable_irq();
//	if(updataflag == 1){
	if(*(unsigned char *)DATA_IAP_ADDR != 1){
		JumpFunc();	
	}
	
	
	valueinit();
	bspinit();
	__enable_irq();
	updatacmpflag = 0;
	iapstate = 0;
	
	TEST_L;
	flashAPPerase();
	while(1) {
//		if(updatacmpflag == 1){
//			JumpFunc();	
//		}else{
//			iapfunc();
//		}
    }
}

void iapfunc(void){
	switch(iapstate){
		case 0:	//app全擦除
			
			break;
		case 1:	//appdownload
			
			break;
		case 2:	//iap success
			updatacmpflag = 1;
			break;
		case 3:	//iap fail,restart
			iapstate = 0;
			break;
		default:
			
			break;
	}
}
