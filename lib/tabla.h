#include <stdio.h>
#include <conio.h>
#include "gotoxy.h"

void imprimirParedes(int coordenadaY){
	int posicion[5] = {0, 11, 21, 71, 79}, i;
	for(i = 0; i < 5; i++){
		gotoxy(posicion[i], coordenadaY);
		printf("%c", 179);
	}
	return;
}

int imprimirRenglon(char cadena[], int coordenadaY, int coordenadaX, int tipo){
	int j, desplazamiento, x[4];
	if(tipo == 1){ //Ayuda a indicar si se trata de una columna tipo 1 (de 50 espacios) o de una tipo 0 (de 10 espacios)
		x[0] = 49;
		x[1] = 98;
		x[2] = 147;
		x[3] = 196;
		if(strlen(cadena) < 50) desplazamiento = 0;
	}
	else{
		x[0] = 9;
		x[1] = 19;
		x[2] = 29;
		x[3] = 39;
		if(strlen(cadena) < 10) desplazamiento = 0;
	}
	for(j = 0; j < strlen(cadena); j++){ //Mini algoritmo para la impresión de la descripción completa
		if(j == x[0] || j == x[1] || j == x[2] || j == x[3]){
			imprimirParedes(coordenadaY);
			if(j == x[0]){
				imprimirParedes(coordenadaY + 1);
				gotoxy(coordenadaX, coordenadaY + 1);
				printf("%c", cadena[j]);
				desplazamiento = 1;
			}
			if(j == x[1]){
				imprimirParedes(coordenadaY + 2);
				gotoxy(coordenadaX, coordenadaY + 2);
				printf("%c", cadena[j]);
				desplazamiento = 2;
			}
			if(j == x[2]){
				imprimirParedes(coordenadaY + 3);
				gotoxy(coordenadaX, coordenadaY + 3);
				printf("%c", cadena[j]);
				desplazamiento = 3;
			}
			if(j == x[3]){
				imprimirParedes(coordenadaY + 4);
				gotoxy(coordenadaX, coordenadaY + 4);
				printf("%c", cadena[j]);
				desplazamiento = 4;
			}
		}
		else{
			printf("%c", cadena[j]);
		}
	}
	return desplazamiento;
}
void imprimirDatos(cola *nombre, cola *id, cola *actividad, cola *tiempo, int anchoColumna, int desplazamiento, int numeroItem, int y){
	int i, j, desplazamientoNombre, desplazamientoId, desplazamientoActividad;
	elemento e1;
					//┌    |	-	  ┐	  ┘    └
	char tabla[6] = {218, 179, 196, 191, 217, 192};
	gotoxy(0, y + desplazamiento); 
	putchar(tabla[1]);
	gotoxy(1, y + desplazamiento);
	e1 = Element(nombre, numeroItem);
	desplazamientoNombre = imprimirRenglon(e1.array, y + desplazamiento, 1, 0);
	gotoxy(11, y + desplazamiento);
	putchar(tabla[1]);
	e1 = Element(id, numeroItem);
	desplazamientoId = imprimirRenglon(e1.array, y + desplazamiento, 12, 0);
	gotoxy(21, y + desplazamiento);
	putchar(tabla[1]);
	e1 = Element(actividad, numeroItem);
	desplazamientoActividad = imprimirRenglon(e1.array, y + desplazamiento, 22, 1);
	gotoxy(71, y + desplazamiento);
	printf("%c",tabla[1]);
	e1 = Element(tiempo, numeroItem);
	gotoxy(72, y + desplazamiento);
	printf("%ds", e1.n);
	gotoxy(79, y + desplazamiento);
	putchar(tabla[1]);
	if(desplazamientoActividad >= desplazamientoNombre && desplazamientoActividad >= desplazamientoId){
		desplazamiento = desplazamiento + desplazamientoActividad;
	}
	else{
		if(desplazamientoNombre >= desplazamientoActividad && desplazamientoNombre >= desplazamientoId){
			desplazamiento = desplazamiento + desplazamientoNombre;
		}
		else desplazamiento = desplazamiento + desplazamientoId;
	}
	gotoxy(0, y + 1 + desplazamiento);
	putchar(tabla[5]);
	gotoxy(79, y + 1 + desplazamiento);
	putchar(tabla[4]);
	gotoxy(1, y + 1 + desplazamiento);
	for(i = 0; i < 78; i++) printf("-");
}

void dibujarEncabezados(int y, char titulo[]){
	int i;
					//┌    |	-	  ┐	  ┘    └
	char tabla[6] = {218, 179, 196, 191, 217, 192};

	gotoxy((80-(strlen("Cola de") + strlen(titulo)))/2, y);
	printf("Cola de %s", titulo);
	gotoxy(0, y + 1);
	putchar(tabla[0]);
	for(i = 0; i < 78; i++) printf("-");
	gotoxy(79, y + 1);
	putchar(tabla[3]);
	gotoxy(0, y + 2);
	putchar(tabla[1]);
	gotoxy(3, y + 2);
	printf("Nombre");
	gotoxy(11, y + 2);
	putchar(tabla[1]);
	gotoxy(15, y + 2);
	printf("ID");
	gotoxy(21, y + 2);
	putchar(tabla[1]);
	gotoxy(40, y + 2);
	printf("Descripcion");
	gotoxy(71, y + 2);
	putchar(tabla[1]);
	gotoxy(73, y + 2);
	printf("Tiempo");
	gotoxy(79, y + 2);
	putchar(tabla[1]);
	gotoxy(0, y + 3);
	putchar(tabla[5]);
	gotoxy(79, y + 3);
	putchar(tabla[4]);
	gotoxy(1, y + 3);
	for(i = 0; i < 78; i++) printf("-");
	return;
}

void dibujarTabla(int anchoColumnas[], cola *nombre, cola *id, cola *actividad, cola *tiempo, int y, char titulo[], int tam){
	int desplazamiento = 0, i, j;
	elemento e1;
	dibujarEncabezados(y - 4, titulo);
	for(i = 0; i < tam; i++){
		imprimirDatos(nombre, id, actividad, tiempo, anchoColumnas[i], desplazamiento, i + 1, y);
		desplazamiento = desplazamiento + anchoColumnas[i] + 1;
	} 
	return;
}
