#include <dos.h>
#include <conio.h>
#include <stdio.h>

char mygetch() {
	union REGS r;
	r.h.ah = 7; 
	int86(0x21, &r, &r);
	return r.h.al;
}

int main() {
	int LEFT = 75, RIGHT = 77;
	int X1=15, Y1=5, X2=65, Y2=15;
	clrscr();

	printf("Type 1 to use function getch() from stdio.h, 2 to use my mygetch()\n");
	char mode;
	do {
		mode = getch();
	}
	while ((mode != '1') && (mode != '2'));
	int mode1 = mode - '1';

	clrscr();
	printf("ESC to exit\n");

	window(X1, Y1, X2, Y2);
	int x = X1, y = Y1;
	putch('*');
	putch('\n');
	putch('\r');
	char c;
	while (c = (mode1?getch():mygetch()) != 27) {
		c = (mode1?getch():mygetch());
		if (c == LEFT || c == RIGHT)
		{
			if (c == LEFT) {
				if (x == X1)
					continue;
			}
			if (c == RIGHT) {
				if (x == X2)
					continue;
			}
			int dx = (c==LEFT)?(-1):1;
			// копируем вправо или влево кусок экрана из трёх текселей — пустого, со звёдочкой и пустого,
			// чтобы пустыми перекрывать старую звёздочку, где бы она ни была
			movetext(x-1,y,x+1,y,x-1+dx,y);
			x += dx;
		}
	}
	// getch();
}