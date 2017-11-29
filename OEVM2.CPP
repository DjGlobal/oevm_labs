#include <dos.h>
#include <conio.h>
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
	const char * colorName[] = { "BLACK", "BLUE", "GREEN", "CYAN", "RED", "MAGENTA", "BROWN", "LIGHTGRAY", "DARKGRAY", "LIGHTBLUE", "LIGHTGREEN", "LIGHTCYAN", "LIGHTRED", "LIGHTMAGENTA", "YELLOW", "WHITE" };
	enum DIRECTIONS { UP = 0x07, DOWN = 0x06};
	int X1=10, Y1=12, X2=70, Y2=23, T=500, S=1;
	clrscr();
	window(X1, Y1, X2, Y2);
	int middle = (S % 2 == 0) ? S / 2 : S / 2 + 1;	
	for (int i=0; i<8;++i) {
		textbackground(i);
		for (int j=0;j<16;++j) {
			scroll(UP, S, X1-1, Y1-1, X2, Y2, i);
			textcolor(j);
			gotoxy(1, middle);
			cprintf("Background: %s, font: %s\r\n", colorName[i], colorName[j]);
			delay(T);
			// delay(20);
		}
	}
	getch();
	return 0;
}