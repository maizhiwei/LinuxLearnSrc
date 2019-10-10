/*NAND CONTROLLER register*/

#define NFCONF (*((volatile unsigned long *)0x4E000000))
#define NFCONT (*((volatile unsigned long *)0x4E000004))
#define NFCMMD (*((volatile unsigned char *)0x4E000008))
#define NFADDR (*((volatile unsigned char *)0x4E00000C))
#define NFDATA (*((volatile unsigned char *)0x4E000010))
#define NFSTAT (*((volatile unsigned char *)0x4E000020))

/* GPIO */
#define GPHCON              (*(volatile unsigned long *)0x56000070)
#define GPHUP               (*(volatile unsigned long *)0x56000078)

/* UART registers*/
#define ULCON0              (*(volatile unsigned long *)0x50000000)
#define UCON0               (*(volatile unsigned long *)0x50000004)
#define UFCON0              (*(volatile unsigned long *)0x50000008)
#define UMCON0              (*(volatile unsigned long *)0x5000000c)
#define UTRSTAT0            (*(volatile unsigned long *)0x50000010)
#define UTXH0               (*(volatile unsigned char *)0x50000020)
#define URXH0               (*(volatile unsigned char *)0x50000024)
#define UBRDIV0             (*(volatile unsigned long *)0x50000028)



#define TXD0READY   (1<<2)
#define RXD0READY   (1)
void nand_read(unsigned int addr, unsigned char * buf, unsigned int len);
void nand_read0(unsigned int addr, unsigned char *buf, unsigned int len);

int isBootFormNorFlash(void)
{
	volatile int *p = (volatile int *)0;
	int val;

	val = *p;
	*p = 0x12345678;
	if(*p ==  0x12345678)
	{
		/*写成功，是nand flash*/
		*p = val;
		return 0;
	}
	else
	{
		/*NOR不能像内存一样写*/
		return 1;
	}
}

int copy_code_to_sdram(unsigned char *src, unsigned char * dest, unsigned int len)
{
	int i = 0;
	
	/*如果是NOR启动*/
	if(isBootFormNorFlash())
	{
		while(i<len)
		{
			dest[i] = src[i];
			i++;
		}
	}
	else
	{
		//nand_init();
		nand_read((unsigned int)src, dest, len);
	}

	return 0;
}

void clean_bss(void)
{
	extern int __bss_start, __bss_end;
	int *p = &__bss_start;

	for(;p<&__bss_end;p++)
	{
		*p = 0;
	}
}

void nand_init(void)
{
#define TACLS   0
#define TWRPH0  1
#define TWRPH1  0

	/* 设置时序 */
	NFCONF = (TACLS<<12)|(TWRPH0<<8)|(TWRPH1<<4);
	/* 使能NAND Flash控制器, 初始化ECC, 禁止片选 */
	NFCONT = (1<<4)|(1<<1)|(1<<0);

}



void nand_select(void)
{
	NFCONT &= ~(1<<1);
}

void nand_unselect(void)
{
	NFCONT |= (1<<1);

}
void nand_cmd(unsigned char cmd)
{
	//volatile int i;
	int i;
	NFCMMD = cmd;

	for(i = 0; i < 10; i++);
}

void nand_addr(unsigned int addr)
{
	#define PAGE_SZE 2048;
	//volatile int i;
	int i;
	unsigned int col = addr % PAGE_SZE;
	unsigned int page = addr / PAGE_SZE;

	NFADDR = col & 0xff;
	for(i = 0; i < 10; i++);
	NFADDR = (col >> 8) & 0xff;
	for(i = 0; i < 10; i++);
	NFADDR = page & 0xff;
	for(i = 0; i < 10; i++);
	NFADDR = (page >> 8) & 0xff;
	for(i = 0; i < 10; i++);
	NFADDR = (page >> 16) & 0xff;
	for(i = 0; i < 10; i++);
}

void nand_wait_ready(void)
{
	while(!(NFSTAT & 0x01));
}

unsigned char nand_data(void)
{
	return NFDATA;
}





void nand_read(unsigned int addr, unsigned char * buf, unsigned int len)
{
	int i;
	int col;
	col = addr%2048;
	/*1.选中*/
	nand_select();

	i = 0;
	while(i<len)
	{


		/*2.发出读命令00h*/
		nand_cmd(0x00);

		/*3.发出地址（分5步发出）*/
		nand_addr(addr);

		/*4.发出page读命令30h*/
		nand_cmd(0x30);

		/*5.判断状态*/
		nand_wait_ready();

		/*6.读数据*/
		for(;(col < 2048) && (i<len); col ++)
		{	
			buf[i] = nand_data();
			i++;
			addr++;
		}
		
		col = 0;
	}

	/*7.取消选中*/
	nand_unselect();

}

void nand_page(unsigned int page)
{
	volatile int i;
	
	NFADDR  = page & 0xff;
	for (i = 0; i < 10; i++);
	NFADDR  = (page >> 8) & 0xff;
	for (i = 0; i < 10; i++);
	NFADDR  = (page >> 16) & 0xff;
	for (i = 0; i < 10; i++);	
}

void nand_col(unsigned int col)
{
	volatile int i;

	NFADDR = col & 0xff;
	for (i = 0; i < 10; i++);
	NFADDR = (col >> 8) & 0xff;
	for (i = 0; i < 10; i++);
}

// 一般坏块标志都是block内的第一个page的oob区，非0xFF则坏块
int nand_bad(unsigned int addr)
{
	unsigned int col  = 2048;
	unsigned int page = addr / 2048;
	unsigned char val;

	/* 1. 选中 */
	nand_select();
	
	/* 2. 发出读命令00h */
	nand_cmd(0x00);
	
	/* 3. 发出地址(分5步发出) */
	nand_col(col);
	nand_page(page);
	
	/* 4. 发出读命令30h */
	nand_cmd(0x30);
	
	/* 5. 判断状态 */
	nand_wait_ready();

	/* 6. 读数据 */
	val = nand_data();
	
	/* 7. 取消选中 */		
	nand_unselect();


	if (val != 0xff)
		return 1;  /* bad blcok */
	else
		return 0;
}

// 加入坏块检测的nand 读取
void nand_read0(unsigned int addr, unsigned char *buf, unsigned int len)
{
	int i;
	int col;
	col = addr%2048;
	///*1.选中*/
	//nand_select();

	i = 0;
	while(i<len)
	{

		if (!(addr & 0x1FFFF) && nand_bad(addr)) /* 一个block只判断一次 */
		{
			addr += (128*1024);  /* 跳过当前block */
			continue;
		}

		/* 1. 选中 */
		nand_select();

		/*2.发出读命令00h*/
		nand_cmd(0x00);

		/*3.发出地址（分5步发出）*/
		nand_addr(addr);

		/*4.发出page读命令30h*/
		nand_cmd(0x30);

		/*5.判断状态*/
		nand_wait_ready();

		/*6.读数据*/
		for(;(col < 2048) && (i<len); col ++)
		{	
			buf[i] = nand_data();
			i++;
			addr++;
		}
		
		col = 0;
		/*7.取消选中*/
		nand_unselect();
	}

	

}

#define PCLK            50000000    // init.c中的clock_init函数设置PCLK为50MHz
#define UART_CLK        PCLK        //  UART0的时钟源设为PCLK
#define UART_BAUD_RATE  115200      // 波特率
#define UART_BRD        ((UART_CLK  / (UART_BAUD_RATE * 16)) - 1)




/*
 * 初始化UART0
 * 115200,8N1,无流控
 */
void uart0_init(void)
{
    GPHCON  |= 0xa0;    // GPH2,GPH3用作TXD0,RXD0
    GPHUP   = 0x0c;     // GPH2,GPH3内部上拉

    ULCON0  = 0x03;     // 8N1(8个数据位，无较验，1个停止位)
    UCON0   = 0x05;     // 查询方式，UART时钟源为PCLK
    UFCON0  = 0x00;     // 不使用FIFO
    UMCON0  = 0x00;     // 不使用流控
    UBRDIV0 = UART_BRD; // 波特率为115200
}


/*
 * 发送一个字符
 */
void putc(unsigned char c)
{
    /* 等待，直到发送缓冲区中的数据已经全部发送出去 */
    while (!(UTRSTAT0 & TXD0READY));
    
    /* 向UTXH0寄存器中写入数据，UART即自动将它发送出去 */
    UTXH0 = c;
}

void puts(char * str)
{
	int i = 0;

	while(str[i]!='\0')
	{
		putc(str[i]);
		i++;
	}
}

void puthex(unsigned int val)
{
	/*0x1234abcd*/

	int i;
	int j;

	puts("0x");

	for(i = 0; i < 8; i++)
	{
		j = (val >> ((7-i)*4)) & 0xf;

		if((j>=0)&&(j<=9))
		{
			putc('0'+j);
		}
		else if((j>=0xA)&&(j<=0xF))
		{
			putc('A'+j-0xA);
		}
	}
}

 



