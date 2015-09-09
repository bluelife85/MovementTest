#include "stm32f4xx.h"
#include "lcd.h"

uint32_t tick;
uint16_t x = 170;
uint16_t y = 120;

uint8_t vertical_direction = 0;
uint8_t horizontal_direction = 0;
uint32_t get_ticked = 0;

int main(void){
	
	lcd_initialize();
	SysTick_Config(SystemCoreClock/1000);
	
	lcd_clear(BLACK);
	lcd_draw_rect(x,y,30,30,WHITE,1);
	
	while(1){
		if(tick - get_ticked > 5){
			
			if(vertical_direction == 0){
				x++;
				if(x == (MAX_X - 30)){
					vertical_direction = 1;
				}
			}
			else{
				x--;
				if(x == 0){
					vertical_direction = 0;
				}
			}
			
			if(horizontal_direction == 0){
				y++;
				if(y == (MAX_Y - 30)){
					horizontal_direction = 1;
				}
			}
			else{
				y--;
				if(y == 0){
					horizontal_direction = 0;
				}
			}
			
			if(!vertical_direction){
				if(!horizontal_direction){
					lcd_draw_rect((x==0)? x : x-1,(y==0)? y : y-1,30,30,BLACK,0);
					lcd_draw_rect(x,y,30,30,WHITE,1);
				}
				else{
					lcd_draw_rect((x==0)? x : x-1,(y==MAX_Y)? y : y+1,30,30,BLACK,0);
					lcd_draw_rect(x,y,30,30,WHITE,1);
				}
			}
			else{
				if(!horizontal_direction){
					lcd_draw_rect((x==MAX_X)? x : x+1,(y==0)? y : y-1,30,30,BLACK,0);
					lcd_draw_rect(x,y,30,30,WHITE,1);
				}
				else{
					lcd_draw_rect((x==MAX_X)? x : x+1,(y==MAX_Y)? y : y+1,30,30,BLACK,0);
					lcd_draw_rect(x,y,30,30,WHITE,1);
				}
			}
			
			get_ticked = tick;
		}
	}
}

void SysTick_Handler(void){
	
	tick++;
}
