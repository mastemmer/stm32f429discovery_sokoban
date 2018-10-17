/************************************************
 * mprintf: Small printing functions similar to printf
 * Copyright (C) 2018 Marcos Augusto Stemmer <mastemmer@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 **************************************************
 * mprintf prints formated output like printf to any character device
 * The first parameter is a pointer to the function that print a character
 * The second parameter is the format string similar to printf
 * Ther may be additional parameters corresponding to each field in the format string
 * The format codes are similar to those of printf with some differences:
The modifier '-' means left alignment.
The modifier '0' fills with zeros to the left (instead of space character)
[fieldwith]	this is in place of a number that spcfies the field width
	[frac]	Number of digits of the fracional part.
	%[fieldwidth]d or i	Signed decimal integer
	%[fieldwidth]u		Unsigned decimal integer
	%[fieldwidth]x or X	Hexadecimal integer
	%[fieldwidth]o or q	Octal integer (o is the lower case letter 'o')
	%[fieldwidth]c		Write as an ASCII character
	%[fieldwidth]s		Write string
	%[fieldwidth].[frac]f	Similar to %lf of standard printf
	%[fieldwidth].[frac]e	Similar to %le of standard printf
	%[fieldwidth].[frac]g	Similar to %lg
notacao cientifica se o valor for maior que 1e10 ou menor que a precisao.
	The modifiers h, l, L, hh and ll are ignored.
The function mprintf returns the number of characters that were written.
These functions are hardwere independent
*/
#include <stdarg.h>
#include <ctype.h>
#define edigito(c) ((c)>='0' && (c)<='9')
/* If only integer formats are used, generated code size may be reduced commenting
 * the definition of FPSUPPORT */
//#define DEBUG
//#define FPSUPPORT
/* Local Function prototypes */
int u2str(char *buf, unsigned int num, int base);
int matoi(char *str);
int mprintf(void (*putc)(int), const char *formato, ... );
int va_printf(void (*putc)(int), const char *formato, va_list va);
void sputchar(int c);
int sprintf(char *buf, const char *formato, ... );

/* internal use only: Write a number backwards (least significant first) */
int u2str(char *buf, unsigned int num, int base)
{
int nd=0, c;
do	{
	c = (num % base) + '0';
	if(c > '9') c+=7;
	buf[nd++] = c;
	num /= base;
	} while(num);
return nd;
}

/* matoi: similar to standard atoi */

int ngscanf;


int matoi(char *str)
{
int x, d, s;
x=s=0;
while(!edigito(*str)) { s |= (*str++ == '-'); ngscanf++; }
do	{
	d = *str++;
	if(!edigito(d)) break;
	x = x*10 + d - '0';
	ngscanf++;
	} while(1);
return s? -x: x;
}

int padchar;

#ifdef FPSUPPORT
/* Convert string to a double */
double atod(char *str)
{
double x, p;
int d, s;
p=1.0;
x=0.0; s=0;
while(*str == ' ') str++;
if(*str == '-') { s=1; str++; }
do	{
	d = *str++;
	if(d=='.') { d = *str++; s |= 2; }
	if(d < '0' || d > '9') break;
	x = x*10 + d - '0';
	if(s & 2) p *=10.;
	} while(1);
if(d=='e' || d=='E'){
	if(*str == '-') { str++; s |= 4; }
	if(*str == '+') str++;
	d=0;
	while(edigito(*str)) d = 10*d + (*str++) - '0';
	if(s & 4) while(d--) p *= 10.0;
	else while(d--) x *= 10.0;
	}
if(s & 1) x = -x;
return x/p;
}

/**** dprint Write a number of type double ******
x		Number to be written
fieldwidth	Total field width
frac	Number of digits of the fractional part
putc	Name of the function that writes a character to the output device 
Returns the number of characters that were written  */
int dprint(double x, int fieldwidth, int frac, void (*putc)(int))
{
int dig, k, signal=0, npr=1;
double ar;
if(x < 0) { signal=1; x=-x; fieldwidth--; }
for(ar=0.5, k=0; k<frac; k++) ar/=10.0;
x += ar;
k=0;
fieldwidth -= (frac+1);
while(x >= 1.0) { x/=10.0; k++; fieldwidth--; }
if(!k) { k=1; fieldwidth--; x/=10.0; }
frac += k;
if(padchar == 0x130 && signal) {
	putc('-'); npr++;
	}
while(fieldwidth-- > 0) { putc(padchar); npr++; }
if(padchar == 0x120 && signal) {
	putc('-'); npr++;
	}
npr += frac;
while(frac--) {
	x *= 10;
	dig = x;
	x -= dig;
	putc(dig+'0');
	if(!(--k)) { putc('.'); k=800; }
	}
return npr;
}
#endif

int va_printf(void (*putc)(int), const char *format, va_list va)
{
char buf[16];
char *s, *ps;
int c,  frac, n, signal, base, nprinted;
int fieldwidth;
#ifdef FPSUPPORT
double x, y;
#endif
s=(char *)format;
nprinted=fieldwidth=0;
while((c=*s++)) {
	if(c != '%') { putc(c); nprinted++; continue;} 
	c=*s++;
	signal=frac=fieldwidth=0;
	padchar = ((c=='0')? '0' + 0x100:' ' + 0x100);
	if(c=='-') { padchar =' '; c=*s++; }
	while(edigito(c)) { fieldwidth=10*fieldwidth+c-'0'; c=*s++; }
	if(c=='.') {
		c=*s++;
		while(edigito(c)) { frac=10*frac+c-'0'; c=*s++; }
		}
	while(c=='l' || c=='L' || c=='h') c=*s++;
	base=10;
	if(c >= 'A' && c <= 'Z') c ^= 0x20;
	switch(c){
		case 'o': case 'q': base=8; goto lbl_u;
		case 'x': base=16;
		case 'u':
		lbl_u:
			n = u2str(buf, va_arg(va, unsigned int), base);
		lbl_escrevei:
		nprinted += n;
		fieldwidth -= (n+signal);
		if(fieldwidth < 0) fieldwidth=0;
		nprinted +=fieldwidth;
			if(padchar & 0x100) while(fieldwidth--) putc(padchar & 0xff);
			if(signal) putc('-');
			while(n--) putc(buf[n]);
			break;
		case 'd': case 'i':
			base=va_arg(va, int);
			if(base < 0) { signal=1; base=-base; }
			n = u2str(buf, base, 10);
			goto lbl_escrevei;
		case 'c':
			if(fieldwidth < 0) fieldwidth=0;
			nprinted +=fieldwidth;
			if(padchar & 0x100) while(fieldwidth--) putc(padchar);
			putc(va_arg(va, int)); nprinted++; break;
		case 's':
			ps = va_arg(va, char *);
			for(n=0; ps[n]; n++);
			nprinted += n;
			fieldwidth -= n;
			if(fieldwidth < 0) fieldwidth=0;
			nprinted +=fieldwidth;
			if(padchar & 0x100) while(fieldwidth--) putc(padchar);
			while(*ps) { putc(*ps); ps++; }
			break;
#ifdef FPSUPPORT
		case 'e': case 'f': case 'g':
			n=0;
			x=y=va_arg(va, double);
			if(x<0) { x=-x; signal=1; }
			while((x > 1.0)) { x /= 10.0; n++; }
			if(x) while((x < 1.0)) { x *= 10.0; n--; }
			if(c=='e' || ((c=='g') && 
				((n > 9) || ((-n >= frac)&& frac)))){
				y = (signal ? -x: x);
				signal = 2;
				fieldwidth -=4;
				if(frac<2) frac=2;
				}
			c = dprint(y, (padchar & 0x100)?fieldwidth:0, frac, putc);
			fieldwidth -=c;
			nprinted +=c;
			if(signal & 2){
				putc('E');
				if(n < 0) { putc('-'); n=-n; }
				else putc('+');
				if(n>99) { putc((n/100) + '0'); n %= 100; }
				putc((n / 10) + '0');
				putc((n % 10) + '0');
				}
			break;
#endif
		case '%': putc(c); nprinted++; break;
		}
	if(fieldwidth < 0) fieldwidth=0;
	nprinted +=fieldwidth;
	if(!(padchar & 0x100)) while(fieldwidth--) putc(padchar);
	}
return nprinted;
}

/*
The first parameter is the name of the function that write a character.
Other parameters are like in printf
*/
int mprintf(void (*putc)(int), const char *format, ... )
{
va_list va;
va_start(va,format);
return va_printf(putc, format, va);
}

char *gp_buf;
void sputchar(int c) { *gp_buf++=c; }

/* This is similar to the standard function with this name */
int sprintf(char *buf, const char *format, ... )
{
va_list va;
int n;
va_start(va,format);
gp_buf=buf;
n=va_printf(sputchar, format, va);
*gp_buf='\0';
return n;
}
