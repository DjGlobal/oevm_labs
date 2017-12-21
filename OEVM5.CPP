#include <dos.h>
#include <conio.h>
#include <stdio.h>

void interrupt (far *oldvect)(...);
void interrupt far mykeyboardint(...)
{
	printf("Key pressed\n\r");
	_chain_intr (oldvect);
}

int main() {
	oldvect = getvect (0x09);
	setvect (0x09, mykeyboardint);
	printf("Vect set\n\r");
	getch();
	getch();
	setvect (0x09, oldvect);
	return 0;
}