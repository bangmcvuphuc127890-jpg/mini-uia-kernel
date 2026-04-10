#ifndef UIA_STD_H
#define UIA_STD_H
#include "uia_typedef.h"
extern "C" {
	void __cxa_pure_virtual() { while (1); }
	int __cxa_guard_acquire(long *g) { return !*(char *)(g); }
	void __cxa_guard_release(long *g) { *(char *)g = 1; }
	void __cxa_guard_abort(long *g) {}
	void* __gxx_personality_v0 = 0;
	void _Unwind_Resume(void* p) { while(1); }
}
void quay_cop(char* i1, char* i2)
{
	unsigned int i = 0;
	while (i2[i]) {
		i1[i] = i2[i];
		i++;
	}
	i1[i] = 0;

}
int k_COMPARE(char*, const char*);

static inline auto read_io = [](uint16_t p) -> uint8_t
{
	uint8_t r;
	asm volatile ("inb %1, %0" : "=a"(r) : "Nd"(p));
	return r;
};
static inline auto read_dio = [](uint16_t p) -> uint16_t
{
	uint16_t re;
	asm volatile ("inw %1, %0" : "=a"(re) : "Nd"(p));
	return re;
};

inline void ink_io(uint16_t p, uint8_t v) {
	    asm volatile ("outb %0, %1" : : "a"(v), "Nd"(p));
};
inline void ink_dio(uint16_t p, uint16_t v) {
	    asm volatile ("outw %0, %1" : : "a"(v), "Nd"(p));
};

struct process_task
{
	const char* process_name;
	uint32_t process_id;
	uint32_t ESP, EBP, EIP;
	uint32_t* virtual_ram;
	process_task* next;
};
extern "C" {uint32_t _kernel_end;}
uint32_t pAddress = (uint32_t)&_kernel_end;
uint32_t uia_kmalloc(uint32_t kich_co, int CauCaVanCan)
{
	if (CauCaVanCan == 1 && (pAddress & 0xFFFFF000))
	{
		pAddress &= 0xFFFFF000;
		pAddress += 0x1000;
	}
	uint32_t t = pAddress;
	pAddress += kich_co;
	return t;
}
static uint32_t* ram_bitmap = (uint32_t*)uia_kmalloc(32768 * 4, 1);
static uint32_t bitos = 0;
void uia_setup_bitmap() {	
	for (int i = 0; i < 32768; i++) {ram_bitmap[i] = 0;}
}
void uia_setup_regmem(uint32_t start, uint32_t size)
{
	uint32_t number1 = start / 4096;
	uint32_t numbersz = size / 4096;
	for (int i = number1; i < (number1 + numbersz); i++) {
		ram_bitmap[i / 32] |= (1 << (i % 32));
	}
}
void uia_kfree(void* ptr)
{
	if (!ptr) {return;}
	uint32_t* h = (uint32_t*)((uint8_t*)ptr - 4);
	uint32_t s = *h;
	uint32_t p = (uint32_t)h;    
	uint32_t n = (s + 4 + 4095) / 4096; 
	uint32_t start = p / 4096;
	for (uint32_t k = 0; k < n; k++) 
	{
		uint32_t cur = start + k;
		ram_bitmap[cur / 32] &= ~(1 << (cur % 32));
	}
}
uint32_t uia_palloc()
{
	for (uint32_t i = 0; i < 32768; i++)
	{
		if (ram_bitmap[i] != 0xFFFFFFFF)
		{
			for (int j = 0; j < 32; j++)
			{
				bitos = (1 << j);
				if (!(ram_bitmap[i] & bitos))
				{
					ram_bitmap[i] |= bitos;
					return (i * 32 + j) << 12;
				}
			}
		}
	}
	return 0;
}

uint32_t _SYS_TICK = 0;
extern "C" 
{
	void utime() {
		_SYS_TICK++;
		ink_io(0x20, 0x20);
	}
}
struct _kTIMER
{	
	int _CONV(unsigned char bcd) {ink_io(0x70, 0x04); /*tron bac bao ve bootloader ¬¬*/return ((bcd / 16) * 10) + (bcd % 16);}
	unsigned char seconds() {return _CONV(read_io(0x00));}
	unsigned char min() {return _CONV(read_io(0x02));} 
	unsigned char hour() {return _CONV(read_io(0x04));}
	unsigned char day() {return _CONV(read_io(0x07));}
	unsigned char month() {return _CONV(read_io(0x08));}
	unsigned char year() {return _CONV(read_io(0x09));}
	void sleep_for(int ms) 
	{
		uint32_t tg = _SYS_TICK + ms;
		do {asm volatile("hlt");} while (_SYS_TICK < tg); 
	}
};
_kTIMER *uia_time;

//[4] File
void uia_await_ready() {while(read_io(ATA_STATUS) & 0x80) {}; while(!(read_io(ATA_STATUS) & 0x08)) {}; return;}
void uia_aread_sector(uint32_t lam, uint16_t* buffer)
{
	ink_io(ATA_DRIVE_SEL, 0xE0 | ((lam >> 24) & 0x0F));
	// send 1 in sector
	ink_io(ATA_SECTOR_COUNT, 1);
	//send lambda LBA
	ink_io(ATA_LBA_LOW, (uint8_t)lam); 
	ink_io(ATA_LBA_MID, (uint8_t)(lam >> 8)); 
	ink_io(ATA_LBA_HIGH, (uint8_t)(lam >> 16));
	//doc du lieu sectors
	ink_io(ATA_COMMAND, 0x20);

	uia_await_ready();
	for (int i = 0; i < 256; i++) {
		buffer[i] = read_dio(ATA_DATA);
	}
};
void uia_aink_sector(uint32_t lam, uint16_t* buffer)
{
	ink_io(ATA_DRIVE_SEL, 0xE0 | ((lam >> 24) & 0x0F));
	// send 1 in sector
	ink_io(ATA_SECTOR_COUNT, 1);
	//send lambda LBA
	ink_io(ATA_LBA_LOW, (uint8_t)lam); 
	ink_io(ATA_LBA_MID, (uint8_t)(lam >> 8)); 
	ink_io(ATA_LBA_HIGH, (uint8_t)(lam >> 16));
	//doc du lieu sectors
	ink_io(ATA_COMMAND, 0x30);

	uia_await_ready();
	for (int i = 0; i < 256; i++) {
		ink_dio(ATA_DATA, buffer[i]);
	}
};

static int _j = 0;
void uia_messenge(const char* print, unsigned short color = 0xF, int slpt = 0, bool is_slpt = false)
{
	unsigned short* ivcard = (unsigned short*)0xB8000;
	if (is_slpt)
	{
		for (int i = 0; i < slpt; i++, _j++)
		{
			if (print[i] == '\n') {_j = (_j / 80 + 1) * 80;}
			//else if (print[i] == '\t') {print[i] = '	';}
			else {ivcard[_j] = (color << 8) | print[i];}
		}
	}
	else
	{
		for (int i = 0; print[i] != '\0'; i++, _j++)
		{
			if (print[i] == '\n') {_j = (_j / 80 + 1) * 80;}
			//else if (print[i] == '\t') {print[i] = '	';}
			else {ivcard[_j] = (color << 8) | print[i];}
		}

	}
}
extern "C" void* memcpy(void* dest, const void* src, size_t n) {
	char* d = (char*)dest;
	const char* s = (const char*)src;
	while (n--) {*d++ = *s++;}
	return dest;
}
char* uia_input(char* messenge, bool is_fspace = true, bool is_ENTER = true, const char* typos = "\n") //o shell: uia_input(command, false, true, "\n")
{
	int _i = 0; _i = _j;
	static bool is_shift = false;
	uint8_t CLICKBAT = 0; // 0->false, else {true}
	const char keyboard[128] = { 0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 0, 0, 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 /*83-96...*/ };
	while(1)
	{
		if (read_io(0x64) & 0x01) 
		{
		
			uint8_t sc = read_io(K_PORT);	
			if ((is_ENTER && sc == K_ENTER))
			{
				messenge[_i] = '\0';
				uia_messenge(typos);
				break;
			}
			else if (sc & 0x80)
			{
				if (sc == K_LSHIFT_PRESS || sc == K_RSHIFT_PRESS) {is_shift = true;}
				else if (sc == K_LSHIFT_NPRESS || sc == K_RSHIFT_NPRESS) {is_shift = true;}
			}
			else if ((is_fspace && sc == K_SPACE))
			{
				messenge[_i] = '\0';
				break;
			}
			else if (sc == K_BACKSPACE)
			{
				if (_i > 0)
				{
					_i--;
					_j--;
					unsigned short* ivcard = (unsigned short*)0xB8000;
					ivcard[_j] = (0xF << 8) | ' ';
				}
				continue; //ko biet co chuyen gi . . .
			}
			else if (sc < 210)
			{
				char symbol = keyboard[sc];
				if (is_shift && symbol >= 'a' && symbol <= 'z') {symbol -= 32;}
				if (symbol > 0)
				{
					char string[2] = {symbol, '\0'};
					uia_messenge(string);
					messenge[_i] = symbol;
				}
			}
			_i++;
		}
	}
	return messenge;
}
int k_COMPARE(char* s1, const char* s2) 
{
	int i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i]) {return 0;} // Không khớp!
		i++;
	}
	return 1; // Khớp hoàn toàn!
}
template <typename A, typename B>
struct type_is {constexpr static const bool ans = false;};
//so sanh U voi U -> true (U == U; A luon bang (true operator==) A) 
template <typename U>
struct type_is<U, U> {constexpr static const bool ans = true;};


template <typename T>
const char* uia_convmess(T con_so, int so_lcs = 6, unsigned long long luot_cs = 1000000, char typos = '.')
	{
		if (type_is<T, const char*>::value) {return con_so;}
		else if (type_is<T, int>::value || type_is<T, unsigned int>::value|| type_is<T, short>::value || type_is<T, unsigned short>::value || type_is<T, long>::value || type_is<T, unsigned long>::value || type_is<T, long long>::value || type_is<T, unsigned long long>::value || type_is<T, signed char>::value || type_is<T, ssize_t>::value || type_is<T, size_t>::value || type_is<T, unsigned char>::value) // so nguyen
		{
			static char buffer[40];
			int thu_tu = 38; bool hiha = false;
			buffer[39] = '\0';
			if (con_so == 0) {return "0";} // xu ly lam gi cho mat chat xam!
			if (con_so < 0) {hiha = true; con_so = -con_so;}
			while(con_so > 0)
			{
				buffer[thu_tu--] = (con_so % 10) + 48;
				con_so /= 10;
			}
			if (hiha) {buffer[--thu_tu] = '-';}
			return &buffer[thu_tu + 1];
		}
		else if (type_is<T, float>::value || type_is<T, double>::value || type_is<T, long double>::value)
		{
			static char buffer[42];
			int i = 40; bool ma = false;
			buffer[1] = '\0';
			if (con_so == 0 || con_so == 0.0) {return (typos == ',') ? "0,0" : "0.0";}
			if (con_so < 0.0 || con_so < 0) {ma = true; con_so = -con_so;}
			// setup dan INT:
			long long nguyen = (long long)con_so;
			long long luon = static_cast<long long>((con_so - (T)nguyen) * luot_cs + 0.5);
			for (int j = 0; j < so_lcs; j++)
			{
				buffer[i--] = (luon % 10) + '0';
				luon /= 10;
			}
			buffer[--i] = typos;
			if (nguyen == 0) {buffer[--i] = '0';}
			else
			{
				while(nguyen > 0)
				{
					buffer[i--] = (nguyen % 10) + '0';
					nguyen /= 10;
				}
			}
			if (ma) {buffer[--i] = '-';}
			return &buffer[i + 1];
		}
		else {return "[?]unk";}
	}
template <typename T>
T uia_messconv(const char* s, char type = '.') 
{
	T result = 0;
	T factor = 1;
	int i = 0;
	if (s[0] == '-') 
	{
		factor = -1;
		i = 1;
	}
	for (; s[i] != '\0' && s[i] != type; i++) 
	{
		if (s[i] >= '0' && s[i] <= '9') {
			result = result * 10 + (s[i] - '0');
		}
	}

	if (s[i] == type) {
		i++;
		T weight = 0.1;
		for (; s[i] != '\0'; i++) {
			if (s[i] >= '0' && s[i] <= '9') {								result += (s[i] - '0') * weight;
				weight /= 10;
			}
										            		}
	}
	return result * factor;
}
void uia_dpixel(int x, int y, int colors)
{
	uint8_t* video = (uint8_t*)0xA0000;
	video[y * 320 + x] = colors;
}
#endif	
