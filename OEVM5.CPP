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
	oldvect = _dos_getvect (0x09);
	_dos_setvect (0x09, mykeyboardint);

	printf("Get ready\n\r");


	getch();
	getch();
	_dos_setvect (0x09, oldvect);
	return 0;
}