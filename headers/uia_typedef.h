										#ifndef UIA_TYPEDEF_H
										#define UIA_TYPEDEF_H
//define
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef unsigned int size_t;
typedef signed int ssize_t;
//ban phim && nhap lieu
#define K_ENTER 0x1C
#define K_PORT 0x60
#define K_SPACE 0x39
#define K_BACKSPACE 0x0E
#define K_LSHIFT_PRESS 0x2A
#define K_LSHIFT_NPRESS 0xAA
#define K_RSHIFT_PRESS 0x36 //32 Thanh hoa
#define K_RSHIFT_NPRESS 0xB6
//con tro && bieu thuc con tro
#define NULL 0
//tep tin
#define F_FILE (8826 >> 1)
#define F_FOLDER (8826 >> 2)
//Sac dep tham tuoi - colors
#define C_WHITE 0xF
#define C_BLACK 0X0
#define C_BLACKS 0X00
#define C_BLUE 0x1
#define C_GREEN 0x2
#define C_CYAN 0x3
#define C_RED 0x4
#define C_YELLOW 0XE
//Rac roi dia ATA va PATA
#define ATA_DATA 	 0x1F0  // Cong du lieu (16-bit)
#define ATA_FEATURES     0x1F1  // Cong dac tinh
#define ATA_SECTOR_COUNT 0x1F2  // So luong sector muon doc/ghi
#define ATA_LBA_LOW      0x1F3  // Dia chi LBA thap
#define ATA_LBA_MID      0x1F4  // Dia chi LBA trung binh
#define ATA_LBA_HIGH     0x1F5  // Dia chi LBA cao
#define ATA_DRIVE_SEL    0x1F6  // Chon o dia (Master/Slave)
#define ATA_COMMAND      0x1F7  // Cong gui lenh
#define ATA_STATUS       0x1F7  // Cong
										#endif
