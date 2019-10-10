#include "setup.h"

#define IH_NMLEN		32	/* Image Name Length		*/
#define uint32_t unsigned long
#define uint8_t unsigned char

extern void uart0_init(void);
extern void puts(char * str);
extern void nand_read(unsigned int addr, unsigned char * buf, unsigned int len);
extern void nand_read0(unsigned int addr, unsigned char *buf, unsigned int len);

extern void puthex(unsigned int val);
static struct tag *params;

/*
 * all data in network byte order (aka natural aka bigendian)
 */

typedef struct image_header {
	uint32_t	ih_magic;	/* Image Header Magic Number	*/
	uint32_t	ih_hcrc;	/* Image Header CRC Checksum	*/
	uint32_t	ih_time;	/* Image Creation Timestamp	*/
	uint32_t	ih_size;	/* Image Data Size		*/
	uint32_t	ih_load;	/* Data	 Load  Address		(内核运行所需的加载地址)*/
	uint32_t	ih_ep;		/* Entry Point Address(启动内核的函数地址)		*/
	uint32_t	ih_dcrc;	/* Image Data CRC Checksum	*/
	uint8_t		ih_os;		/* Operating System		*/
	uint8_t		ih_arch;	/* CPU architecture		*/
	uint8_t		ih_type;	/* Image Type			*/
	uint8_t		ih_comp;	/* Compression Type		*/
	uint8_t		ih_name[IH_NMLEN];	/* Image Name		*/
} image_header_t;



void setup_start_tag (void)
{
#define ATAG_CORE	0x54410001

	// 让tag指针指向启动参数约定地址
	params = (struct tag *) 0x30000100;

	params->hdr.tag = ATAG_CORE;
	params->hdr.size = tag_size (tag_core);

	params->u.core.flags = 0;
	params->u.core.pagesize = 0;
	params->u.core.rootdev = 0;

	params = tag_next (params);

}

void setup_memory_tags (void)
{

#define PHYS_SDRAM_1		0x30000000 /* SDRAM Bank #1 */
#define PHYS_SDRAM_1_SIZE	0x04000000 /* 64 MB */

	params->hdr.tag = ATAG_MEM;
	params->hdr.size = tag_size (tag_mem32);
	
	params->u.mem.start = PHYS_SDRAM_1;
	params->u.mem.size = PHYS_SDRAM_1_SIZE;
	
	params = tag_next (params);

}

int strlen(char * str)
{
	int i = 0;
	while(str[i]!='\0')
	{
		i++;
	}

	return i;
}

void strcpy(char * dest, char * src )
{
	while ((*dest++=*src++)!='\0'); //[4]

}


void setup_commandline_tag (void)
{

	
#define CONFIG_BOOTARGS    	"noinitrd root=/dev/mtdblock3 init=/linuxrc console=ttySAC0"
	char bootargs[] = CONFIG_BOOTARGS;
	char *p = bootargs;

	/* eat leading white space */
	for (; *p == ' '; p++);

	/* skip non-existent command lines so the kernel will still
	 * use its default command line.
	 */
	if (*p == '\0')
		return;

	params->hdr.tag = ATAG_CMDLINE;
	params->hdr.size =
		(sizeof (struct tag_header) + strlen (p) + 1 + 3) >> 2;

	strcpy (params->u.cmdline.cmdline, p);

	params = tag_next (params);

}

void setup_end_tag (void)
{
	params->hdr.tag = ATAG_NONE;
	params->hdr.size = 0;

}



int main(void)
{
#define MACH_TYPE_S3C2440              362
	void (*theKernel)(int zero, int arch, unsigned int params);
	image_header_t *hdr = (image_header_t *)0x30007FC0;
	unsigned char * ptr_8;

	unsigned long entry_point;
	volatile unsigned int *p = (unsigned int *)0x30008000;


	/*0.设置串口：内核启动时会从串口打印信息，但是内核一开始没有初始化串口*/
	uart0_init();

	puts("Copy kernel form nand\n\r");

	/*1. 从Nand FLASH里把内核读入内存*/
	nand_read0(0x60000, (unsigned char *)0x30007FC0, 0x200000);



	
	ptr_8 = (unsigned char *)(&(hdr->ih_ep));
	entry_point = 0;
	entry_point += (((unsigned long)(ptr_8[0])) << 24);
	entry_point += (((unsigned long)(ptr_8[1])) << 16);
	entry_point += (((unsigned long)(ptr_8[2])) << 8);
	entry_point += (((unsigned long)(ptr_8[3])) << 0);

	puthex(entry_point);

	puts("\n\r");

	/*2. 设置启动参数*/
	puts("Set Boot param\n\r");
	setup_start_tag ();

	setup_memory_tags ();

	setup_commandline_tag ();

	setup_end_tag ();

 
	/*3. 跳转执行*/
	puts("Boot Kernel\n\r");
	puts("Boot Kernel\n\r");
	puts("Boot Kernel\n\r");
	//theKernel = (void(*)(int, int, unsigned int))0x30008000;
	theKernel = (void(*)(int, int, unsigned int))entry_point;
	theKernel(0, MACH_TYPE_S3C2440, 0x30000100); /*mov pc #0x30008000*/

	puts("Boot Error\n\r");

	return 0;
}
