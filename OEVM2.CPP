#include <dos.h>
#include <conio.h>
#include <stdio.h>

void scroll (int direction, char size, char x1, char y1, char x2, char y2, char colors)
{ 
	union REGS r;
	if (direction){ r.h.al=size; r.h.ah=direction; }
	else { r.h.al=0; r.h.ah=6; }
	r.h.ch = y1; r.h.cl = x1; 
	r.h.dh = y2; r.h.dl = x2; 
	r.h.bh = colors; 
	int86(0x10,&r,&r);
}


int main() {
	double d;
	double* d_ptr = &d;
	unsigned long long int d_0 = 9223372036854775808;
	char c;
	char* c_ptr = &c;
	int c_0 = 128;
	clrscr();
	printf("Enter char\n");
	scanf("%c",&c);

	printf("Enter double\n");
	scanf("%lf",&d);
	printf("\n");


	const char * colorName[] = { "BLACK", "BLUE", "GREEN", "CYAN", "RED", "MAGENTA", "BROWN", "LIGHTGRAY", "DARKGRAY", "LIGHTBLUE", "LIGHTGREEN", "LIGHTCYAN", "LIGHTRED", "LIGHTMAGENTA", "YELLOW", "WHITE" };
	enum DIRECTIONS { UP = 0x07, DOWN = 0x06};
	int X1=15, Y1=5, X2=70, Y2=15, T=400, S=2;
	clrscr();
	window(X1, Y1, X2, Y2);
	int middle = (S % 2 == 0) ? S / 2 : S / 2 + 1;	
	for (int i=0; i<8;++i) {
		textbackground(i);
		for (int j=0;j<16;++j) {
			textcolor(j);
			scroll(DOWN, S, X1-1, Y1-1, X2, Y2, i);
			gotoxy(1, middle);
			// char
			cprintf("char %c = %d: ", c, (short int)c);
			c_0 = 128;
			while (c_0 > 0)
			{
				if (c & c_0)
					cprintf("1");
				else
					cprintf("0");
				c_0 >>= 1;
			}

			cprintf("\n\r");
			// double
			cprintf("double %lf: ",d);

			for (size_t b = 0; b < sizeof(double);++b){
				c_0 = 128;
				while (c_0 > 0)
				{
					if (*((char*)d_ptr+b) & c_0)
						cprintf("1");
					else
						cprintf("0");
					c_0 >>= 1;
				}
			}
			
			cprintf("\n\r");
			

			cprintf("Background: %s, font: %s\r\n", colorName[i], colorName[j]);
			delay(100);
		}
	}
	getch();
	return 0;
}
