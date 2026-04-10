ENTRY(_start)
SECTIONS
{
	. = 0x100000;          
	.text : {
		*(.multiboot)
		*(.text)         
		ALIGN(4K)
	}
	.data : {
		*(.data)
		ALIGN(4K)
	}       
	.bss  : { 
		*(.bss)  
		ALIGN(4K)
	}  
}
_kernel_end = .;
