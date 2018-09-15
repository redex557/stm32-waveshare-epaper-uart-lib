#define CMD_SIZE 512

#define    FRAME_B                            0xA5
#define    FRAME_E0                           0xCC
#define    FRAME_E1                           0x33
#define    FRAME_E2                           0xC3
#define    FRAME_E3                           0x3C

#define    WHITE                              0x03
#define    GRAY                               0x02
#define    DARK_GRAY                          0x01
#define    BLACK                              0x00

#define    CMD_DRAW_PIXEL                     0x20
#define    CMD_DRAW_LINE                      0x22
#define    CMD_FILL_RECT                      0x24
#define    CMD_UPDATE                         0x0A
#define    CMD_DRAW_CIRCLE                    0x26
#define    CMD_CLEAR                          0x2E
#define    CMD_MEMORYMODE                     0x07

#define    CMD_SET_EN_FONT                    0x1E

#define    ASCII32                            0x01
#define    ASCII48                            0x02
#define    ASCII64                            0x03

#define    CMD_DRAW_STRING                    0x30
#define    CMD_DRAW_BITMAP                    0x70

#define    MEM_NAND                           0
#define    MEM_TF                             1

static unsigned char cmd_buff[CMD_SIZE];

void putchars(unsigned char *buffer, int size);
static unsigned char verify(const void * buffer, int size);

void epd_update(void);
void epd_clear(void);
void epd_draw_pixel(int, int);
void epd_draw_line(int x0, int y0, int x1, int y1);
void epd_fill_rect(int x0, int y0, int x1, int y1);
void epd_draw_circle(int x0, int y0, int r);
void epd_disp_string(const void * p, int x0, int y0);
void epd_disp_bitmap(const void * p, int x0, int y0);
void epd_set_en_font(unsigned char font);
void epd_init(void);
void epd_wakeup(void);
void epd_set_memory(unsigned char mode);

static const unsigned char _cmd_update[8] = {0xA5, 0x00, 0x09, CMD_UPDATE, 0xCC, 0x33, 0xC3, 0x3C};		//update sequence from datasheet
