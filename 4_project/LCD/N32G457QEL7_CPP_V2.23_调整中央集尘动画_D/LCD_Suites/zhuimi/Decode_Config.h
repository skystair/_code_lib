#ifndef _DECODE_CONF_H_
#define _DECODE_CONF_H_

/*************************************************************
*    The following are the areas that need to be configured  *
*     							用户配置区，按需要修改										 *
**************************************************************/
//屏幕宽度和高度
#define SCREEN_PIXEL_WIDTH					240
#define SCREEN_PIXEL_HEIGHT					240

//解码模块缓存大小，用于动态分配解码空间，建立解码树
#define DECODE_MODULE_BUFFER_SIZE		(4856*7)

//显存高度(单次图层叠加缓存高度)
#define DECODE_BUFFER_HEIGHT				10


//字库解码属性
#define ROLL_TEXT_STRING_MAX_LENGTH			100/*滚动文本支持的最长字符串长度*/
#define ROOL_SPEED											5/*文本滚动速度*/
#define ROOL_STRING_END_SPACE						3/*循环字符串结尾到新开始空格数量*/


/*********************配置区结束******************************/
//解码缓存宽度，单位：字节
#define SCREEN_BYTE_WIDTH			(SCREEN_PIXEL_WIDTH*2)

//显存容量，单位：字节
#define BLOCK_DECODED_SIZE		(DECODE_BUFFER_HEIGHT*SCREEN_BYTE_WIDTH)

//显示时的轮询刷新次数限制
#define SCREEN_REFRESH_LOOP		(SCREEN_PIXEL_HEIGHT/DECODE_BUFFER_HEIGHT)

#endif /*_DECODE_CONF_H_*/
