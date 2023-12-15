#ifndef __FLASHX_H__
#define __FLASHX_H__

#define START_MEMORY_ADDR	0
#define	MAX_MEMORY_ADDR		(0x00020000)



#define SECTOR_NUM			64
#define SECTOR_SIZE			(0x800)
#define PAGE_SIZE			(0x200)


//只能按划分好的sector操作	0~63
#define	 SECTOR_APP_POS		32
#define	 DATA_APP_ADDR		(SECTOR_APP_POS * SECTOR_SIZE)
#define	 SECTOR_APP_SIZE	4			//8KB /2 = 4

//last page: DATA_APP_ADDR - pagesize
#define  DATA_YUYAN_ADDR    (0xF800)
#define  DATA_HAIBA_ADDR    (0xF801)
#define	 DATA_IAP_ADDR		(0xF802)




void flashAPPerase(void);

#endif
