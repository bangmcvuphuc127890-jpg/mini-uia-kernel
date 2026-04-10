#include "headers/uia_std.h"

//[1] HE THONG GDT <--------------------++-----------------> || && & | ^ << >> § ^ v < 
//Yeu cau xay dung cai nay truoc :D
struct gdt_huhu {
	unsigned short gioi_han_thap;
	unsigned short co_so_thap;
	unsigned char  co_so_bt;
	unsigned char  truy_cap;
	unsigned char  chi_tiet;
	unsigned char  co_so_cao;
} __attribute__((packed)); //huhuhu T_T
struct con_tro_thoi
{
	unsigned short gioi_han;
	unsigned int co_so;
} __attribute__((packed));
//include:)
gdt_huhu gatos[6];
con_tro_thoi contro;
void gdt_set_gate(int conso, unsigned long coso, unsigned int gioihan, unsigned char truycap, unsigned char chiatiet)
{
	gatos[conso].co_so_thap = (coso & 0xFFFF); 
	gatos[conso].co_so_bt = (coso >> 16) & 0xFF; 
	gatos[conso].co_so_cao = (coso >> 24) & 0xFF;
	gatos[conso].gioi_han_thap = (gioihan & 0xFFFF);
	gatos[conso].chi_tiet = ((gioihan >> 16) & 0x0F);
	gatos[conso].chi_tiet |= (chiatiet & 0xF0);
	gatos[conso].truy_cap = truycap;
	//return conso + coso + gioihan + (int)truycap + (int)chiatiet <---------------------------------------------
}
extern "C" void gdt_aflush(unsigned int);
void gdt_install(con_tro_thoi ct = contro)
{
	ct.gioi_han = (sizeof(struct gdt_huhu) * 7) - 1;
	ct.co_so = (unsigned int)&gatos;
	//Una Uno Una UIA
	gdt_set_gate(0, 0, 0, 0, 0); // NULL - nullptr
	// El Ring 0 (Kernel) es setup:
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);// Loi phan dinh SEG1 ¯|
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);// Loi phan dinh SEG2 _|Ring 0 (Kernel)
	gdt_aflush((unsigned int)&ct);
	// El Ring 3 (Userland y Virtual RAM) es setup:
	gdt_set_gate(5, 0, 0xFFFFFFFF, 0xFA, 0xCF); // keo kiet khi cho 11 :(
	gdt_set_gate(6, 0, 0xFFFFFFFF, 0xF2, 0xCF); // XD
	
}

// [2] BANG NGAT (IDT)
// Toi ko muon bi vo cam dau, huhu :( - Kernel khi ko co no . . . . . . . . . . . . . . . . . . * * * * * * * * * * * * * * * * * * *
struct ngat_structure
{
	uint16_t co_so_thap;
	uint16_t asm_sel;
	uint8_t luonluon_s0;
	uint8_t co; //flags
	uint16_t co_so_cao;
} __attribute__((packed));
struct ngat_tro
{
	uint16_t gioi_han;
	uint32_t co_so;
} __attribute__((packed));

ngat_structure idt[256];
ngat_tro con_tro;

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
	idt[num].co_so_thap 	= base & 0xFFFF;
	idt[num].co_so_cao 	= (base >> 16) & 0xFFFF;
	idt[num].asm_sel 	= sel;
	idt[num].luonluon_s0 	= 0;
	idt[num].co 		= flags;
}
extern "C" {
	void idt_aflush(uint32_t);
	void isr14_pageFault(uint32_t);
	void isr1_timer();
	void isr0_divbyzero(uint32_t);
}
void idt_install_init()
{
	con_tro.gioi_han = (sizeof(struct ngat_structure) * 256) - 1;
	con_tro.co_so = (uint32_t)&idt;
	idt_aflush((uint32_t)&con_tro); // extern "C"?! . . . . . * * * * * ° ° ° ° ° o o o o o 0 0 0 0 0 • • • • • 
	asm volatile("lidt (%0)" : : "r" (&con_tro));
	//ta duoi kip nhau! :)
	idt_set_gate(0, (uint32_t)isr0_divbyzero, 0x08, 0x8E); // chia cho 0
	idt_set_gate(32, (uint32_t)isr1_timer, 0x08, 0x8E); // cap nhat gio lien tuc
	idt_set_gate(14, (uint32_t)isr14_pageFault, 0x08, 0x8E); //ko dc vao NULL

}
void pic_setup(int offset1, int offset2)
{
	uint8_t port1 = read_io(0x21), port2 = read_io(0xA1);
	//Start Constuctor
	ink_io(0x20, 0x11); 
	ink_io(0xA0, 0x11);
	//Setup offset
	ink_io(0x21, offset1); //master
	ink_io(0xA1, offset2); //slave
	// PIC LINKER
	ink_io(0x21, 4);
	ink_io(0xA1, 2);
	//8086 mde:
	ink_io(0x21, 0x01);
	ink_io(0xA1, 0x01);
	//rset
	ink_io(0x21, 0x0);
	ink_io(0xA1, 0x0);
}
//------------> TRINH XU LY <-----------
extern "C"
{
	void err_divbyzero()
	{
		uia_messenge("\n[!] Error: Division by zero is 1 unknown and prohibited act\n");
		uia_messenge("[!] dibbyzero->called_abort(1) = named()\n");
	}
	void err_pageFault()
	{
		uia_messenge("\n[!] Error: RPage not fault\n");
		uia_messenge("[?] unknown");
	}
}
//MAIN
extern "C" void main()
{
	unsigned short* vcard = (unsigned short*)0xB8000;
	gdt_install();
	idt_install_init();
	pic_setup(0x20, 0x28);
	asm volatile("sti");
	//RAM MGR:
	SETVAL_FOR_ROOTDIR();
	uia_setup_bitmap(); // Clear di!!!
	uia_setup_regmem(0, pAddress);
	uia_clear();
	//FILE:
	while(1);
}
