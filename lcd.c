#include "lcd.h"

#define LCD_REG (*((volatile unsigned short *) 0x6F000000))
#define LCD_RAM (*((volatile unsigned short *) 0x6F010000))

__INLINE void lcd_write_index(uint16_t idx){
	
	LCD_REG = idx;
}

__INLINE void lcd_write_data(uint16_t val){
	
	LCD_RAM = val;
}

__INLINE uint16_t lcd_read_data(void){
	
	return LCD_RAM;
}

__INLINE void lcd_write_reg(uint16_t reg, uint16_t val){
	
	lcd_write_index(reg);
	lcd_write_data(val);
}

__INLINE uint16_t lcd_read_reg(uint16_t reg){
	
	lcd_write_index(reg);
	
	return lcd_read_data();
}

static void lcd_line_init(void){
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOG, ENABLE);
	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);
	
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource4, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_FSMC);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource2 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource7 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource8 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource10 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource12 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource14 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource15 , GPIO_AF_FSMC);
	
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_2 | GPIO_Pin_7 | GPIO_Pin_8  | GPIO_Pin_9  | GPIO_Pin_10 | GPIO_Pin_11| GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource5 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource12 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource13 , GPIO_AF_FSMC);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_13 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOG, &GPIO_InitStructure);
}

static void lcd_fsmc_initialize(void){
	
	FSMC_NORSRAMInitTypeDef FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef FSMC_NORSRAMTimingInitStructure;
	
	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
	FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &FSMC_NORSRAMTimingInitStructure;
	//FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 
	/* FSMC Write Timing */
	FSMC_NORSRAMTimingInitStructure.FSMC_AddressSetupTime = 15;   /* Address Setup Time */
	FSMC_NORSRAMTimingInitStructure.FSMC_AddressHoldTime = 0;
	FSMC_NORSRAMTimingInitStructure.FSMC_DataSetupTime = 15;	     /* Data Setup Time */
	FSMC_NORSRAMTimingInitStructure.FSMC_BusTurnAroundDuration = 0x00;
	FSMC_NORSRAMTimingInitStructure.FSMC_CLKDivision = 0x00;
	FSMC_NORSRAMTimingInitStructure.FSMC_DataLatency = 0x00;
	FSMC_NORSRAMTimingInitStructure.FSMC_AccessMode = FSMC_AccessMode_A;	/* FSMC Access Mode */
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &FSMC_NORSRAMTimingInitStructure;
	
	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);
	
	/* Enable FSMC Bank4_SRAM Bank */
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);
}

static void lcd_delay(uint16_t time){
	
	uint16_t i,j;
	
	for(i=0;i<time;i++)
		for(j=0;j<1141;j++);
}

static void lcd_set_cursor(uint16_t x, uint16_t y){
	
	uint16_t temp;
	temp = y;
	y = x;
	x = MAX_Y - 1 - temp;
	
	lcd_write_reg(0x0020, x);
	lcd_write_reg(0x0021, y);
	lcd_write_index(0x0022);
}

void lcd_initialize(void){
	
	uint32_t i = 0x1fffff;
	
	lcd_line_init();
	
	lcd_fsmc_initialize();
	
	while(i--);
	
	lcd_write_reg(0x00e7,0x0010);
	lcd_write_reg(0x0000,0x0001);
	
	lcd_write_reg(0x0001,(0<<10)|(1<<8));
	
	lcd_write_reg(0x0002,0x0700);
	lcd_write_reg(0x0003,(1<<12)|(1<<5)|(0<<4)|(1<<3));
	lcd_write_reg(0x0004,0x0000);
	lcd_write_reg(0x0008,0x0207);
	lcd_write_reg(0x0009,0x0000);
	lcd_write_reg(0x000a,0x0000);
	lcd_write_reg(0x000c,0x0001);
	lcd_write_reg(0x000d,0x0000);
	lcd_write_reg(0x000f,0x0000);
	lcd_write_reg(0x0010,0x0000);
	lcd_write_reg(0x0011,0x0007);
	lcd_write_reg(0x0012,0x0000);
	lcd_write_reg(0x0013,0x0000);
	lcd_delay(50);
	lcd_write_reg(0x0010,0x1590);
	lcd_write_reg(0x0011,0x0227);
	lcd_delay(50);
	lcd_write_reg(0x0012,0x009c);
	lcd_delay(50);
	lcd_write_reg(0x0013,0x1900);
	lcd_write_reg(0x0029,0x0023);
	lcd_write_reg(0x002b,0x000e);
	lcd_delay(50);
	lcd_delay(50);
	lcd_write_reg(0x0030,0x0007);
	lcd_write_reg(0x0031,0x0707);
	lcd_write_reg(0x0032,0x0006);
	lcd_write_reg(0x0035,0x0704);
	lcd_write_reg(0x0036,0x1f04);
	lcd_write_reg(0x0037,0x0004);
	lcd_write_reg(0x0038,0x0000);
	lcd_write_reg(0x0039,0x0706);
	lcd_write_reg(0x003c,0x0701);
	lcd_write_reg(0x003d,0x000f);
	lcd_delay(50);
	lcd_write_reg(0x0050,0x0000);
	lcd_write_reg(0x0051,0x00ef);
	lcd_write_reg(0x0052,0x0000);
	lcd_write_reg(0x0053,0x013f);
	lcd_write_reg(0x0060,0xa700);
	lcd_write_reg(0x0061,0x0001);
	lcd_write_reg(0x006a,0x0000);
	lcd_write_reg(0x0080,0x0000);
	lcd_write_reg(0x0081,0x0000);
	lcd_write_reg(0x0082,0x0000);
	lcd_write_reg(0x0083,0x0000);
	lcd_write_reg(0x0084,0x0000);
	lcd_write_reg(0x0085,0x0000);
	lcd_write_reg(0x0090,0x0010);
	lcd_write_reg(0x0092,0x0600);
	lcd_write_reg(0x0093,0x0003);
	lcd_write_reg(0x0095,0x0110);
	lcd_write_reg(0x0097,0x0000);
	lcd_write_reg(0x0098,0x0000);
	lcd_write_reg(0x0007,0x0133);
}

void lcd_clear(uint16_t bg){
	
	uint32_t i;
	
	lcd_set_cursor(0,0);
	
	for(i=0;i<MAX_X*MAX_Y;i++){
		lcd_write_data(bg);
	}
}

void lcd_set_point(uint16_t x, uint16_t y, uint16_t color){
	
	if( (x >= MAX_X) || (y >= MAX_Y)){
		return;
	}
	
	lcd_set_cursor(x, y);
	lcd_write_reg(0x0022,color);
}

void lcd_draw_vertical_line(uint16_t x, uint16_t y, uint16_t height, uint16_t color){
	
	uint16_t max_y = y + height;
	if(max_y > MAX_Y)
		max_y = MAX_Y;
	
	do{
		lcd_set_point(x,y,color);
		y++;
	}while(y <= max_y);
}

void lcd_draw_horizontal_line(uint16_t x, uint16_t y, uint16_t width, uint16_t color){
	
	uint16_t max_x = x + width;
	if(max_x > MAX_X)
		max_x = MAX_X;
	
	do{
		lcd_set_point(x,y,color);
		x++;
	}while(x <= max_x);
}

void lcd_draw_line(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color){
	
	short dx, dy;
	short tmp;
	
	if(sx > ex){
		tmp = ex;
		ex = sx;
		sx = tmp;
	}
	
	if(sy > ey){
		tmp = ey;
		ey = sy;
		sy = tmp;
	}
	
	dx = ex - sx;
	dy = ey - sy;
	
	if(dx == 0){
		do{
			lcd_set_point(sx,sy, color);
			sy++;
		}while(ey >= sy);
		
		return;
	}
	
	if(dy == 0){
		do{
			lcd_set_point(sx,sy,color);
			sx++;
		}while(ex >= sx);
		
		return;
	}
	
	if(dx > dy){
		tmp = 2 * dy - dx;
		while(sx != ex){
			lcd_set_point(sx, sy, color);
			sx++;
			if(tmp > 0){
				sy++;
				tmp += 2 * dy - 2 * dx;
			}
			else{
				tmp += 2 * dy;
			}
		}
		
		lcd_set_point(sx,sy,color);
	}
	else{
		tmp = 2 * dx - dy;
		while( sy != ey ){
			lcd_set_point(sx,sy,color);
			sy++;
			if(tmp > 0){
				sx++;
				tmp += 2 * dy - 2 * dx;
			}
			else{
				tmp += 2 * dy;
			}
		}
		
		lcd_set_point(sx,sy,color);
	}
}

void lcd_draw_circle(uint16_t x, uint16_t y, uint16_t rad,  uint16_t color, uint8_t fill){
	
	int16_t a,b,p;
	a = 0;
	b = rad;
	p = 1 - rad;
	
	do{
		if(fill){
			lcd_draw_line(x-a, y+b, x+a, y+b, color);
			lcd_draw_line(x-a, y-b, x+a, y-b, color);
			lcd_draw_line(x-b, y+a, x+b, y+a, color);
			lcd_draw_line(x-b, y-a, x+b, y-a, color);
		}
		else{
			lcd_set_point(a+x, b+y, color);
			lcd_set_point(b+x, a+y, color);
			lcd_set_point(x-a, b+y, color);
			lcd_set_point(x-b, a+y, color);
			lcd_set_point(b+x, y-a, color);
			lcd_set_point(a+x, y-b, color);
			lcd_set_point(x-a, y-b, color);
			lcd_set_point(x-b, y-a, color);
		}
		
		if(p < 0){
			p += 3 + 2 * a++;
		}
		else{
			p += 5 + 2 * (a++ - b--);
		}
	}while(a<=b);
}

void lcd_draw_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color, uint8_t fill){
	
	uint16_t s = x;
	
	if(fill){
		for(;x <= (s+width);x++){
			lcd_draw_vertical_line(x,y,height,color);
		}
	}
	else{
		lcd_draw_horizontal_line(x,y,width,color);
		lcd_draw_vertical_line(x,y,height,color);
		lcd_draw_horizontal_line(x,y+height,width,color);
		lcd_draw_vertical_line(x+width,y,height,color);
	}
}
