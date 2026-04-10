#ifndef UIA_MATHS_H
#define UIA_MATHS_H
#include "uia_std.h"
#include "uia_typedef.h"
	class throwerr
	{
	private:
		const char* errmess;
		const char* id;
		int errcode;
	public:
		throwerr(const char* e, int c, const char* i):errmess(e), errcode(c), id(i) {}
		throwerr() : errmess("unk"), errcode(0), id("unk") {}
		const char* called() const {return errmess;}
		int code() const {return errcode;}
		const char* name() const {return id;}
		const char* what() const {return called();}
	};
	throwerr runtime_err("This application has requested the Runtime to terminate it in an unusual way", -1, "runtime_err");
	throwerr divbyzero("Integer division by zero - Floating point exception (core dumped)", 3221225477, "divbyzero");
	throwerr ioexpect("Error accessing stream or file", 3221225478, "ioexpect");
	throwerr access_NULL("Unknown of you accessed", 0, "access_NULL");
	throwerr bad_alloc("Allocation of memory is invalid", 32767, "bad_alloc");
	throwerr invalid_arg("Invalid Argument of input", sizeof(int), "invalid_arg");
	throwerr logicerr("What logic is this?", 568, "logicerr");
	throwerr converr("Convert to dataType not fault", 572, "converr");
	throwerr fatal_unknown("Something went wrong but I don't know why!", sizeof(unsigned short), "unk");
	throwerr file_err("Cannot interaction to file/folder!", 9009, "file_err");

	namespace maths
	{
		//... con kien chay con kien co uia
		float infinite = 1.0F / 0.0F;
		float nan = 0.0F / 0.0F;
		double epsilon = 1e-9;
		double epsilon18 = 1e-18;
		double epsilon5 = 1e-5;
		
		double sqrt_of(double x, double c);
		const long double constant(char* name)
		{
			if (k_COMPARE(name, "pi")) return 3.14159265358979323846264338327950288L;
			else if (k_COMPARE(name, "e")) return 2.71828182845904523536028747135266249L;
			else if (k_COMPARE(name, "phi")) return 1.61803398874989484820458683436563811L;
			else if (k_COMPARE(name, "tau")) return (3.14159265358979323846264338327950288L) * 2.0L;
			else if (k_COMPARE(name, "sqrt2")) return 1.41421356237309504880168872420969808L;
			else if (k_COMPARE(name, "sqrt3")) return 1.73205080756887729352744634150587236L;
			else if (k_COMPARE(name, "sqrt5")) return 2.23606797749978969640917366873127623L;
			else if (k_COMPARE(name, "ln2")) return 0.69314718055994530941723212145817657L;
			else if (k_COMPARE(name, "ln10")) return 2.30258509299404568401799145468436421L;
			else if (k_COMPARE(name, "log2")) return 1.44269504088896340735992468100189213L;
			else if (k_COMPARE(name, "log10")) return 0.43429448190325182765112891891660508L;
			else if (k_COMPARE(name, "bern")) return 0.2801694954L;
			else if (k_COMPARE(name, "omega")) return 0.56714329040978387299996866221035555L;
			else if (k_COMPARE(name, "sqrt2pi") || k_COMPARE(name, "sqrttau")) return (const long double)sqrt_of(3.14159265358979323846, 2);
			//Vat ly MC kieu :)
			else if (k_COMPARE(name, "R") || k_COMPARE(name, "r")) return 8.31446261815324L;
			else if (k_COMPARE(name, "h")) return 6.62607015e-34L;
			else if (k_COMPARE(name, "silver")) return 2.4142135623730950488L;
			else if (k_COMPARE(name, "fibonacci")) return 0.4350523081L;
			else if (k_COMPARE(name, "a")) return 0.0072973525693L;
			else if (k_COMPARE(name, "G")) return 6.67430e-11L;
			else if (k_COMPARE(name, "egamma")) return 0.57721566490153286060651209008240243L;
			else if (k_COMPARE(name, "apery")) return 1.20205690315959428539973816151144999L;
			else if (k_COMPARE(name, "catalan")) return 0.91596559417721901505460351493238411L;
			else if (k_COMPARE(name, "k0") || k_COMPARE(name, "khinchin")) return 2.68545200106530644530971483548179569L;
			else if (k_COMPARE(name, "g") || k_COMPARE(name, "gtttr")) return 9.80665L;
			else if (k_COMPARE(name, "c-m/s") || k_COMPARE(name , "tdas-m/s")) return 299792458.0L;
			else if (k_COMPARE(name, "kb-j/k")) return 1.380649e-23L;
			else if (k_COMPARE(name, "Na:mol-1")) return 6.02214076e23L;
			else if (k_COMPARE(name, "F-C/mol")) return 96485.33212L;
			else return -1;
		}

		ssize_t totals_of(ssize_t a, ssize_t b, char type = 's' , ssize_t start = 0)
		{
			ssize_t kq = start;
			ssize_t kqt = 1;
			if (type == 's'){
				for (ssize_t i = a; i <= b; i++) {kq += i;}
				return kq;
			}
			else if (type == 'p'){
				for (ssize_t i = a; i <= b; i++) {kqt *= i;} 
				return kqt;
			}
			else {return 0;}
		}
		size_t fact(size_t x)
		{
			size_t kq = 1;
			for (auto i = 1; i <= x; i++) {kq *= i;}
			return kq;
		}
		double mod_of(double a, double b)
		{
			if (b == 0) return 0L;
			 int kqt = (int)a / (int)b;
			double kq = (double)a - (double)kqt * (double)b;
			return kq;
		}
		double ln(double x);
		double log_n(double a, double b) {return ln(b) / ln(a);}
		double log10(double x) {return log_n(10, x) ;}
		double euler_x(double x)
		{
			double kq = 1.0, ke_thua = 1.0;
			for (int i = 1; i < 50; i++) {
				ke_thua *= x/i;
				kq += ke_thua;
			}
			return kq;
		}
		double expon(double cs, double ms)
		{
			//... ;)
			return (ms == 0) ? 1 : euler_x(ms * ln(cs));
		}
		double ln(double x) 
		{
			if (x <= 0) return -1;
			double tam = (x - 1.0) / (x + 1.0);
			double du = 0.0;
			double luy_thua_tam = tam;       
			double tam_binh_phuong = tam * tam; 				 
			for (int i = 0; i < 90; i++) 
			{
							 
				double huhu = (1.0 / (2 * i + 1)) * luy_thua_tam;
				du += huhu;
				luy_thua_tam *= tam_binh_phuong; 
			}
			return 2.0 * du;
		}
		double round_of(double x)
		{
			if (x >= 0) return (int)(x + 0.5);
			else return (int)(x - 0.5);
		}
		double sqrt_of(double x, double c)
		{
			double kq = expon(x, 1.0/c);
			return kq;
		}
			
		//cut di! (-)
		double abs_of(double x) {return (x < 0) ? -x : x;}
		ssize_t trunc(double x) {return (ssize_t)x;}
		ssize_t floor(double x) {return (ssize_t)x;}
		ssize_t ceil(double x) {return floor(x + 1);}
		size_t Combine(size_t n, size_t k) {return fact(n) / fact(k) * fact((n - k));}
		size_t Pcombie(size_t n, size_t k) {return fact(n) / fact(n - k);}
		size_t fibonacci(int x)
		{
			if (x <= 1) return -1;
			size_t kq = 0;
			size_t sh1 = 0, sh2 = 0;
			for (int i = 02; i <= x; i++) 
			{
				kq = sh1 + sh2;
				sh1 = sh2;
				sh2 = kq;
			}
			return sh2;
		}
		size_t tribonacci(int x)
		{
			if (x == 0 || x == 1) return 0;
			else if (x == 2) return 1;
			else if (x <= -1) return -1;
			size_t k1 = 0, k2 = 0, k3 = 0, kq;
			for (int i = 3; i <= x; i++) 
			{kq = k1 + k2 + k3; k1 = k2; k2 = k3; k3 = kq;}
		
			return k3;
		}
		template <typename ...Arg>
		double tbc(Arg ...arg) {return (double)(... + arg) / sizeof...(arg);}
		//uon luon nhu do thi ham sin...
		double sin(double x, int start_to = 15)
		{
			long double kq = x, ke_thua = x;
			for (int i = 1; i <= start_to; i++) {
				ke_thua *= -(x * x) / ((2 * i) * (2 * i + 1));
				kq += ke_thua;
			}
			return kq;

		}
		double cos(double x, int start_to = 15)
		{
			long double kq = 1.0, ke_thua = 1.0;
			for (int i = 1; i <= start_to; i++) {
				ke_thua *= -(x * x) / ((2 * i) * (2 * i - 1));
				kq += ke_thua;
			}
			return kq;
		}
		double tan(double x, int start_to = 15)
		{
			double du = mod_of(x, (double)constant("tau"));
			if (du < 0) du += (double)constant("tau");
			if (abs_of(du - (double)constant("pi") / 2) < 0.000001 || abs_of(du - 270.0) < 0.000001) {return -1;}
			
			long double kq = sin(x) / cos(x);
			return kq;
		}
		
		double arctan(double x, int ss = 31) 
		{
			//double ke_thua = x, kq = x;
			auto taylor = [&] (double y) -> double
			{
				double kq1 = 0, ke_thua1 = y;
				for (int i = 1; i <= ss; i += 2) 
				{	
					if ((i / 2) % 2 == 0) {kq1 += ke_thua1 / i;}
					else {kq1 -= ke_thua1 / i;}
					ke_thua1 *= (y * y);
				}
				return kq1;
			};
			if (abs_of(x) <= 1) return taylor(x);
			else
			{
				if (x > 1) return (3.1415926535 / 2.0) - taylor(1.0 / x);
				else return -(3.1415926535 / 2.0) - taylor(1.0 / x);
			}
		}
		double sinh(double x) {return (euler_x(x) - euler_x(-x)) / 2.0;}
		double cosh(double x) {return (euler_x(x) + euler_x(-x)) / 2.0;}
		double tanh(double x) {return sinh(x) / cosh(x);}
		double arcsin(double x)
		{
			if (x < -1 || x > 1) return -1;
			double kq = arctan(x / sqrt_of(1 - (x * x), 2));
			return kq;
		}
		double gamma_of(double x, int t = 7)
		{
			auto lancoz = [&](double y) -> double
			{
				const static double nhieu[9] { 0.99999999999980993, 676.5203681218851, -1259.1392167224028, 771.32342877765313, -176.61502916214059, 12.507343278686905, -0.13857109526572012, 9.9843695780195716e-6, 1.5056327351493116e-7};
				if (y < 0.5) {return static_cast<double>(constant("pi")) / sin(static_cast<double>(constant("pi")) * y);} 
				y--;
				double out = nhieu[0];
				for (int i = 0; i < 9; i++) {out += nhieu[i] / (y + i);}
				return sqrt_of(2 * (double)constant("pi"), 2) * expon(x + t + 0.5, x + 0.5) * euler_x(-(x + t + 0.5)) * out;
			};
			double kq = 1.0;
			while (x > 1.0)
			{
				kq *= (x - 1);
				x--;
				if (x <= 1) {return lancoz(x);}
			}
		}
		double beta_of(double x, double y) {return (gamma_of(x) * gamma_of(y)) / gamma_of(x + y);}
		double lngamma_of(double x) {return ln(abs_of(gamma_of(x)));}
		template <typename T>
		class complex_num
		{
		private:
			T real_;
			T imag_;
		public:
			complex_num(T rl, T ig): real_(rl), imag_(ig) {}
			complex_num() {}
			T real() {return real_;}
			T imag() {return imag_;}

			//1 chut ma-gen-ta la ma_gen_ta
			complex_num<T> operator+(const complex_num<T> &t) {
				return complex_num<T>(this->real_ + t.real_, this->imag_ + t.imag_);
			}
			complex_num<T> operator-(const complex_num<T> &a) {
				return complex_num<T>(this->real_ - a.real_, this->imag_ + a.imag_);
			}
			complex_num<T> operator*(const complex_num<T> &m) {
				return complex_num<T>(this->real_ * m.real_ - this->imag_ * m.imag_, this->real_ * m.imag_ + this->imag_ * m.real_);
			}
			complex_num<T> operator/(const complex_num<T> &h) {
				T thuc_te = (this->real_ * h.real_ + this->imag_ * h.imag_);
				T cay_choi = (this->imag_ * h.real_ - this->real_ * h.imag_);
				T ao_tung_chao = (h.real_ * h.real_) + (h.imag_ * h.imag_);
				complex_num<T> ve(thuc_te / ao_tung_chao, cay_choi / ao_tung_chao);
				return ve;
			}
			complex_num<T> conj() {return complex_num<T>(this->real_, this->imag_);}
			bool operator==(const complex_num<T> &a)
			{
				if (a.real_ == this->real_ && a.imag_ == this->imag_) return true;
				else return false;
			}
			bool operator!=(const complex_num<T> &a)
			{
				if (a.real_ != this->real_ && a.imag_ != this->imag_) return true;
				else return false;
			}

		};
		template <typename T>
		double abs_of(complex_num<T> &abc) {return sqrt_of(abc.real() * abc.read() + abc.imag() * abc.imag(), 2);}
		template <typename T>
		complex_num<T> ceil(complex_num<T> &z) {return complex_num<T>(ceil(z.real()), ceil(x.imag());}
		template <typename T>
		complex_num<T> floor(complex_num<T> &z) {return complex_num<T>(floor(z.real()), floor(x.imag());}
		template <typename T>
		T gcd_of(T a, T b)
		{
			if (a < 0) a = -a;
			if (b < 0) b = -b;
			while (b != 0)
			{
				T c = b;
				b = mod_of(a, b);
				a = c;
			}
			return a;
		}
		template <typename T>
		T lcm_of(T a, T b) {return (a == 0 || b == 0) ? 0 : (a / gcd_of<T>(a, b)) * b;}
		template <typename T>
		class fract
		{
		private:
			T _numer, _deno; long long _mixed;
		public:
			fract(T n, T d): _numer(n), _deno(d) {}
			fract() {_numer = 0; _deno = 1;}
			fract(const fract<T> &a) : _numer(a._numer), _deno(a._deno) {};
			fract(T n) : _numer(n), _deno(1) {}
			fract(T n, T d, long long m) : _mixed(m), _numer(n), _deno(d) {}
			T numer() {return _numer;}
			T deno() {return _deno;}
			long long mixed() {return _mixed;}
			double value() {return (double)_numer / (double)_deno;}

			//Cong, Tru, Nhan, Chia (+-*/) cho Phan So
			fract<T> operator+(const fract<T> &tam)
			{
				if (tam._deno != _deno) 
				{
					this->_deno *= tam._deno; 
					tam._deno *= this->_deno;
					this->_numer *= tam._deno;
					tam._numer *= this->_deno;
				}
				fract<T> ve(tam._numer + this->_numer, tam._deno);
				return ve;
			}
			fract<T> operator-(const fract<T> &tam)
			{
				if (tam._deno != _deno) 
				{
					this->_deno *= tam._deno; 
					tam._deno *= this->_deno;
					this->_numer *= tam._deno;
					tam._numer *= this->_deno;
				}
				fract<T> ve(tam._numer - this->_numer, tam._deno);
				return ve;
			}
			fract<T> operator*(const fract<T> &tam)
			{
				fract<T> ve(tam._numer * this->_numer, tam._deno * this->_deno);
				return ve;
			}
			fract<T> operator/(const fract<T> &tam)
			{
				if (tam._deno == 0 || this->_deno == 0) return fract<T>(1, 1);
				fract<T> ve(this->_deno * tam._numer, this->_numer * tam._deno);
				return ve;
			}

			//Cong Tru Nhan Chia (+-*/) cho so
			fract<T> operator+(T tam)
			{
				fract<T> well(tam, 1);
				if (well.deno() != this->_deno)
				{
					this->_deno *= well._deno; 
					well._deno *= this->_deno;
					this->_numer *= well._deno;
					well._numer *= this->_deno;
				}
				fract<T> ve(this->_numer + well.numer(), well.deno());
				return ve;
			}
			fract<T> operator-(T a)
			{
				fract<T> tam(a, 1);
				if (tam._deno != _deno) 
				{
					this->_deno *= tam._deno; 
					tam._deno *= this->_deno;
					this->_numer *= tam._numer;
					tam._numer *= this->_numer;
				}
				fract<T> ve(tam._numer - this->_numer, tam._deno);
				return ve;
			}
			fract<T> operator*(T a)
			{
				fract<T> ve(a * this->_numer, this->_deno);
				return ve;
			}
			fract<T> operator/(T a)
			{
				fract<T> ve(this->_numer, (a == 0) ? this->_deno * a : this->_deno);
				return ve;
			}
			void simple() 
			{
				if (_deno == 0) return;
				T nhan_tu_chung = gcd_of<T>(_numer < 0 ? -_numer : _numer, _deno < 0 ? -_deno : _deno);
				_numer /= nhan_tu_chung;
				_deno /= nhan_tu_chung;
				//cu lat keo abs:
				if (_deno < 0) {_numer = -_numer; _deno = -_deno;}
			}
			fract<T> inverse() {
				_numer = _deno;
				if (_numer == 0) {throw divbyzero;}
				_deno = _numer;
				return fract<T>(_numer, _deno);
			}
			fract<T> to_mixed()
			{
				if (_numer > _deno) return fract<T>(0, 1, 1);
				if (mod_of(_numer, _deno) == 0.0) return fract<T>(0, 1, _numer / _deno);
				_mixed = _numer / _deno;
				_numer = mod_of(_numer, _deno);
				return fract<T>(_numer, _deno, _mixed);
			}
			fract<T> to_fract() {return fract<T>(_mixed * _deno + _numer, _deno);}
		};
	};


#endif
