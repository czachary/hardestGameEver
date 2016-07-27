typedef unsigned int u32;
typedef unsigned short u16;

#define REG_DISPCTL *(unsigned short *)0x4000000
#define MODE3 3
#define BG2_ENABLE (1<<10)

extern unsigned short *videoBuffer;
extern const unsigned char fontdata_6x8[12288];

#define COLOR(r,g,b) ((r) |  (g)<<5 |  (b)<<10)
#define RED COLOR(31,0,0)
#define BLUE COLOR(0,0,31)
#define GRAY COLOR(21,21,21)
#define BLACK 0

#define OFFSET(r,c,rowlen) ((r)*(rowlen) + (c))

// Buttons

#define BUTTON_A		(1<<0)
#define BUTTON_B		(1<<1)
#define BUTTON_SELECT	(1<<2)
#define BUTTON_START	(1<<3)
#define BUTTON_RIGHT	(1<<4)
#define BUTTON_LEFT		(1<<5)
#define BUTTON_UP		(1<<6)
#define BUTTON_DOWN		(1<<7)
#define BUTTON_R		(1<<8)
#define BUTTON_L		(1<<9)

#define KEY_DOWN_NOW(key)  (~(BUTTONS) & key)

#define BUTTONS *(volatile unsigned int *)0x4000130

#define SCANLINECOUNTER *(volatile short *)0x4000006

/* DMA */

typedef struct
{
	const volatile void *src;
	void *dst;
	unsigned int cnt;
} DMA_CONTROLLER;

#define DMA ((volatile DMA_CONTROLLER *) 0x040000B0)

#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)

#define DMA_ON (1 << 31)



// Prototype
void setPixel(int , int , unsigned short );
void drawRect(int row, int col, int height, int width, unsigned short color);
void waitForVblank();

void drawImage3(int r, int c, int width, int height, const u16* image);
void drawChar(int row, int col, char ch, u16 color);
void drawString(int row, int col, char *str, u16 color);
