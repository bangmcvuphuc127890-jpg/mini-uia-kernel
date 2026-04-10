section .multiboot
    dd 0x1BADB002   ; Magic: Multiboot 1
        dd 0x00         ; Flags
	    dd -0x1BADB002  ; Checksum (Magic + Flags + Checksum = 0)
section .text
[global _start]   ; Khai báo điểm bắt đầu bạo liệt
extern main       ; Gọi anh C/C++ từ bên ngoài
_start:
    mov esp, stack_top  ; Bế bổng 'esp' vào đỉnh ngăn xếp mướt rượt
        call main           ; Chính thức bước vào main
	    hlt                 ; Dừng CPU dập dồn nếu em thoát main

[global gdt_aflush]    ; Cho phép C++ gọi hàm này bảnh trai
gdt_aflush:
    	mov eax, [esp + 4] ; Lấy con trỏ 'contro' từ stack
    	lgdt [eax]         ; Nạp GDT vào pháo đài CPU!
	mov ax, 0x10      ; 0x10 là Data Segment (Cổng 2)
        mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:.flush   ; 0x08 là Code Segment (Cổng 1), nhảy xa để nạp CS
.flush:
	ret
[global idt_aflush]    ; Báo cho linker thấy hàm này để C++ gọi được
idt_aflush:
    mov eax, [esp + 4] ; Lấy địa chỉ idt_ptr (tham số đầu tiên) từ ngăn xếp
        lidt [eax]         ; NẠP IDT! Cú chạm định mệnh vào CPU!
	    ret                ; Quay lại với ASM!!!

[global isr0_divbyzero]
extern err_divbyzero ; Hàm C++

isr0_divbyzero:
    pushad            ; Cứu tất cả múi cơ thanh ghi (EAX, EBX...)
        call err_divbyzero ; Gọi hàm xử lý nồng nàn của Master
	popad             ; Phục hồi múi cơ
	iretd             ; Kết thúc ngắt, quay lại (nếu có thể)
section .bss
align 16          ; Căn lề 16-byte để các múi cơ CPU hoạt động mướt rượt
stack_bottom:
	resb 16384    ; Dự phòng 16KB (khoảng trống nồng nàn cho em trai)
stack_top:        ; Đỉnh ngăn xếp - nơi anh bế em bắt đầu

[global isr14_pageFault]
extern err_pageFault ; Hàm C++ sẽ viết sau
isr14_pageFault:
	pushad
	call err_pageFault
	popad
	iretd

[global isr1_timer]    ; Cho phép C++ nhìn thấy hàm này
extern utime   ; Khai báo hàm này nằm bên C++

isr1_timer:
    pushad             ; Cất hết 8 thanh ghi (EAX, ECX...) để bảo vệ dữ liệu
        call utime ; Gọi hàm C++ để làm việc chính
	    popad              ; Làm xong thì trả lại các thanh ghi như cũ
	        iretd              ; Lệnh kết thúc ngắt (khác với ret thường nhé!)
