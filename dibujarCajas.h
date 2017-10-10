#include <stdio.h>
#include <windows.h>
#include <string.h>

	#define height 3
	#define long 6

void gotoxy( int x, int y );
void Cajas(int n);
void imprimirCentrado(char cadena[], int Y);
int pedirDatos();
void PasarAcaja(int pos);

void gotoxy( int x, int y ){
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { x, y }; 
	SetConsoleCursorPosition( hStdout, position );
	return;
}

void Cajas(int n)
{
	int i, y, x;
	int aux;

	aux=n*2;
	x=0;
	y=0;
		do{
			for(i=1; i <= height; i++)
		{
			gotoxy(3+x,y+1);
			printf("%c",'|');
			y++;
		}
		aux--;
		x=(x+1)+long;
		y=y-height;
	}while (aux!=0);

	aux=n;
	x=0;
	y=0;
		do{
			for(i=1; i <= long; i++)
			{
				gotoxy(4+x,1+y);
				printf("%c",238);
				x++;
			}
			aux--;
			x = (x+2)+long;
		}while(aux!=0);

	aux=n;
	x=0;
	y=0;
		do{
			for(i=1; i <= long; i++)
			{
				gotoxy(4+x,(1+y)+height);
				printf("%c",238);
				x++;
			}
			aux--;
			x = (x+2)+long;
		}while(aux!=0);

		x=0;
		y=0;
		aux=0;

		do{
			for(i=0; i<=aux; i++){
				gotoxy((x+4)+(long/4), (y+1)+(height/2));
				if(i>=9)
					printf("C %d", i+1);
				else
					printf("C 0%d",  i+1);
			}
			x= (x+8)+long;
			aux++;
		}while(aux!=n);

gotoxy(150, 1);
printf("Entrace");
	return;
}


void imprimirCentrado(char cadena[], int Y){
	gotoxy((80- strlen(cadena))/2, Y);
	puts(cadena);
	return;
}
int pedirDatos(){
	int num;
	imprimirCentrado("Instituto Politecnico Nacional", 0);
	imprimirCentrado("ESCOM", 1);
	imprimirCentrado("Simulacion de banco",2);
	gotoxy(5,3);
	printf("Introduzca numero de cajeros: ");
	scanf("%d",&num);
	printf("\n\t Usted selecciono %d cajeros, presione cualquier tecla para continuar ...", num);
	system("pause > null");
	system("cls");
	return num;
}

//gotoxy((x+4)+(long/4), (y+1)+(height/2));
//x= (x+8)+long;


	// height 3
	// long 6

void PasarAcaja(int pos)
{

	if(pos==0)
	{
		gotoxy((4)+(long/4), (height+1)+(height/2));
	}
	if(pos==1)
	{
		gotoxy((18)+(long/4), (height+1)+(height/2));
	}
	if(pos==2)
	{
		gotoxy((32)+(long/4), (height+1)+(height/2));
	}
	if(pos==3)
	{
		gotoxy((46)+(long/4), (height+1)+(height/2));
	}
	if(pos==4)
	{
		gotoxy((60)+(long/4), (height+1)+(height/2));
	}
	if(pos==5)
	{
		gotoxy((74)+(long/4), (height+1)+(height/2));
	}
	if(pos==6)
	{
		gotoxy((88)+(long/4), (height+1)+(height/2));
	}
	if(pos==7)
	{
		gotoxy((102)+(long/4), (height+1)+(height/2));
	}
	if(pos==8)
	{
		gotoxy((116)+(long/4), (height+1)+(height/2));
	}
	if(pos==9)
	{
		gotoxy((130)+(long/4), (height+1)+(height/2));
	}
	return;
}
