#include "stm32f1_epaper_display.h"
#include "main.h"
#include "stm32f1xx_hal.h"

static unsigned char verify(const void * buffer, int size)
{
	int i;
	unsigned char * p = (unsigned char *)buffer;
	unsigned char result;

	for(i = 0, result = 0; i < size; i++)
	{
		result ^= p[i];
	}

	return result;
}

void epd_update(void)
{
	memcpy(cmd_buff, _cmd_update, 8);
	cmd_buff[8] = verify(cmd_buff, 8);
	putchars(cmd_buff, 9);
}

void epd_draw_pixel(int x0, int y0) {

		cmd_buff[0] = FRAME_B;

		cmd_buff[1] = 0x00;
		cmd_buff[2] = 0x0D;

		cmd_buff[3] = CMD_DRAW_PIXEL;

		cmd_buff[4] = (x0 >> 8) & 0xFF;
		cmd_buff[5] = x0 & 0xFF;
		cmd_buff[6] = (y0 >> 8) & 0xFF;
		cmd_buff[7] = y0 & 0xFF;

		cmd_buff[8] = FRAME_E0;
		cmd_buff[9] = FRAME_E1;
		cmd_buff[10] = FRAME_E2;
		cmd_buff[11] = FRAME_E3;
		cmd_buff[12] = verify(cmd_buff, 12);

		putchars(cmd_buff,13);

}

void epd_draw_line(int x0, int y0, int x1, int y1)
{
	cmd_buff[0] = FRAME_B;

	cmd_buff[1] = 0x00;
	cmd_buff[2] = 0x11;

	cmd_buff[3] = CMD_DRAW_LINE;

	cmd_buff[4] = (x0 >> 8) & 0xFF;
	cmd_buff[5] = x0 & 0xFF;
	cmd_buff[6] = (y0 >> 8) & 0xFF;
	cmd_buff[7] = y0 & 0xFF;
	cmd_buff[8] = (x1 >> 8) & 0xFF;
	cmd_buff[9] = x1 & 0xFF;
	cmd_buff[10] = (y1 >> 8) & 0xFF;
	cmd_buff[11] = y1 & 0xFF;

	cmd_buff[12] = FRAME_E0;
	cmd_buff[13] = FRAME_E1;
	cmd_buff[14] = FRAME_E2;
	cmd_buff[15] = FRAME_E3;
	cmd_buff[16] = verify(cmd_buff, 16);

	putchars(cmd_buff, 17);
}

void epd_fill_rect(int x0, int y0, int x1, int y1)
{
	cmd_buff[0] = FRAME_B;

	cmd_buff[1] = 0x00;
	cmd_buff[2] = 0x11;

	cmd_buff[3] = CMD_FILL_RECT;

	cmd_buff[4] = (x0 >> 8) & 0xFF;
	cmd_buff[5] = x0 & 0xFF;
	cmd_buff[6] = (y0 >> 8) & 0xFF;
	cmd_buff[7] = y0 & 0xFF;
	cmd_buff[8] = (x1 >> 8) & 0xFF;
	cmd_buff[9] = x1 & 0xFF;
	cmd_buff[10] = (y1 >> 8) & 0xFF;
	cmd_buff[11] = y1 & 0xFF;

	cmd_buff[12] = FRAME_E0;
	cmd_buff[13] = FRAME_E1;
	cmd_buff[14] = FRAME_E2;
	cmd_buff[15] = FRAME_E3;
	cmd_buff[16] = verify(cmd_buff, 16);

	putchars(cmd_buff, 17);
}

void epd_draw_circle(int x0, int y0, int r)
{
	cmd_buff[0] = FRAME_B;

	cmd_buff[1] = 0x00;
	cmd_buff[2] = 0x0F;

	cmd_buff[3] = CMD_DRAW_CIRCLE;

	cmd_buff[4] = (x0 >> 8) & 0xFF;
	cmd_buff[5] = x0 & 0xFF;
	cmd_buff[6] = (y0 >> 8) & 0xFF;
	cmd_buff[7] = y0 & 0xFF;
	cmd_buff[8] = (r >> 8) & 0xFF;
	cmd_buff[9] = r & 0xFF;


	cmd_buff[10] = FRAME_E0;
	cmd_buff[11] = FRAME_E1;
	cmd_buff[12] = FRAME_E2;
	cmd_buff[13] = FRAME_E3;
	cmd_buff[14] = verify(cmd_buff, 14);

	putchars(cmd_buff, 15);
}

void epd_clear(void)
{
	cmd_buff[0] = FRAME_B;

	cmd_buff[1] = 0x00;
	cmd_buff[2] = 0x09;

	cmd_buff[3] = CMD_CLEAR;

	cmd_buff[4] = FRAME_E0;
	cmd_buff[5] = FRAME_E1;
	cmd_buff[6] = FRAME_E2;
	cmd_buff[7] = FRAME_E3;
	cmd_buff[8] = verify(cmd_buff, 8);

	putchars(cmd_buff, 9);
}

void epd_disp_string(const void * p, int x0, int y0)
{
	int string_size;
	unsigned char * ptr = (unsigned char *)p;


	string_size = strlen((const char *)ptr);
	string_size += 14;

	cmd_buff[0] = FRAME_B;

	cmd_buff[1] = (string_size >> 8) & 0xFF;
	cmd_buff[2] = string_size & 0xFF;

	cmd_buff[3] = CMD_DRAW_STRING;

	cmd_buff[4] = (x0 >> 8) & 0xFF;
	cmd_buff[5] = x0 & 0xFF;
	cmd_buff[6] = (y0 >> 8) & 0xFF;
	cmd_buff[7] = y0 & 0xFF;

	strcpy((char *)(&cmd_buff[8]), (const char *)ptr);

	string_size -= 5;

	cmd_buff[string_size] = FRAME_E0;
	cmd_buff[string_size + 1] = FRAME_E1;
	cmd_buff[string_size + 2] = FRAME_E2;
	cmd_buff[string_size + 3] = FRAME_E3;
	cmd_buff[string_size + 4] = verify(cmd_buff, string_size + 4);

	putchars(cmd_buff, string_size + 5);
}

void epd_disp_bitmap(const void * p, int x0, int y0)
{
	int string_size;
	unsigned char * ptr = (unsigned char *)p;

	string_size = strlen((const char *)ptr);
	string_size += 14;

	cmd_buff[0] = FRAME_B;

	cmd_buff[1] = (string_size >> 8) & 0xFF;
	cmd_buff[2] = string_size & 0xFF;

	cmd_buff[3] = CMD_DRAW_BITMAP;

	cmd_buff[4] = (x0 >> 8) & 0xFF;
	cmd_buff[5] = x0 & 0xFF;
	cmd_buff[6] = (y0 >> 8) & 0xFF;
	cmd_buff[7] = y0 & 0xFF;

	strcpy((char *)(&cmd_buff[8]), (const char *)ptr);

	string_size -= 5;

	cmd_buff[string_size] = FRAME_E0;
	cmd_buff[string_size + 1] = FRAME_E1;
	cmd_buff[string_size + 2] = FRAME_E2;
	cmd_buff[string_size + 3] = FRAME_E3;
	cmd_buff[string_size + 4] = verify(cmd_buff, string_size + 4);

	putchars(cmd_buff, string_size + 5);
}

void epd_set_en_font(unsigned char font)
{
	cmd_buff[0] = FRAME_B;

	cmd_buff[1] = 0x00;
	cmd_buff[2] = 0x0A;

	cmd_buff[3] = CMD_SET_EN_FONT;

	cmd_buff[4] = font;

	cmd_buff[5] = FRAME_E0;
	cmd_buff[6] = FRAME_E1;
	cmd_buff[7] = FRAME_E2;
	cmd_buff[8] = FRAME_E3;
	cmd_buff[9] = verify(cmd_buff, 9);

	putchars(cmd_buff, 10);
}

void epd_init(void) {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);		//Wakeup Pin Low
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);		//Reset Pin Low
}

void epd_wakeup(void) {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);		//Wakeup Pin Low
	HAL_Delay(10);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
	HAL_Delay(500);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_Delay(10);
}

void epd_set_memory(unsigned char mode)							//use 0x01 for sd card
{
	cmd_buff[0] = FRAME_B;

	cmd_buff[1] = 0x00;
	cmd_buff[2] = 0x0A;

	cmd_buff[3] = CMD_MEMORYMODE;

	cmd_buff[4] = mode;

	cmd_buff[5] = FRAME_E0;
	cmd_buff[6] = FRAME_E1;
	cmd_buff[7] = FRAME_E2;
	cmd_buff[8] = FRAME_E3;
	cmd_buff[9] = verify(cmd_buff, 9);

	putchars(cmd_buff, 10);
}
