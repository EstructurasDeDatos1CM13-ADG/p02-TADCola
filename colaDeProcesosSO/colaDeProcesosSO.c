#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lib\gotoxy.h"
#include "lib\TADColaDin.h"
#include "lib\tabla.h"
void imprimir(char const *cadena, int y);
void letreros();
int otroProceso();
void colaDeProcesos();
void pedirProceso();

int main(){
	pedirProceso();
	getchar();
	return 0;
}

void imprimir(char const *cadena, int y){
	gotoxy((80-strlen(cadena))/2, y);
	puts(cadena);
	return;
}

void letreros(){
	imprimir("Instituto Politecnico Nacional", 1);
	imprimir("ESCOM", 2);
	imprimir("Cola de procesos de Sistema Operativo", 3);
	return;
}

int otroProceso(){
	char sn;
	printf("\nDesea introducir otro proceso(s|S,n|N)?: ");
	setbuf(stdin, NULL);
	scanf("%c", &sn);
	tolower(sn);
	return(sn == 's')?1:2;
}

void colaDeProcesos(int anchoColumnas[], cola *nombre, cola *id, cola *actividad, cola *tiempo){
	cola nombreFinalizado, idFinalizado, actividadFinalizado, tiempoFinalizado;
	elemento e1;
	int i, j, desplazamiento = 0;
	letreros();
	imprimir("COLA DE EJECUCION", 10);
	for(i = 0; i < Size(nombre); i++){
		dibujarEncabezados();
		imprimirDatos(nombre, id, actividad, tiempo, anchoColumnas[i], desplazamiento, 1);
		e1 = Element(tiempo, 1);
		for(i = e1.n; i >= 0; i--){
			gotoxy(72, 17 + desplazamiento);
			printf("%ds ", i);
			delay_ms(1000);
		}
		Dequeue(nombre);
		//Queue(&nombreFinalizado, e1);
		Dequeue(id);
		//Queue(&idFinalizado, e1);
		Dequeue(actividad);
		//Queue(&actividadFinalizado, e1);
		Dequeue(tiempo);
		//Queue(&tiempoFinalizado, e1);
		cleanScreen();
	}

	getchar();
	return;

}


/*
void pedirProceso()
Función que pide los datos del proceso, es decir, id, nombre, descripción y tiempo de
ejecución, y los va almacenando en colas con la misma etiqueta del dato (hay una cola
para nombres, otra para id´s, etc), 
*/
void pedirProceso(){
	int i = 5, j = 0, tam[10], tiempo;
	char id[32], nombre[32], actividad[200], temp[200];
	cola nombres, actividades, ids, tiempos;
	elemento e1;
	Initialize(&nombres);
	Initialize(&actividades);
	Initialize(&ids);
	Initialize(&tiempos);
	do{
		tam[j] = 1;
		setbuf(stdin, NULL);
		letreros();
		imprimir("A continuacion introduzca los parametros del proceso que se le solicitan: ", 4);
		gotoxy(5,6); 
		printf("Introduzca el nombre del proceso: ");
		gets(nombre);
		if(strlen(nombre) > 10) tam[j] = strlen(nombre)/10 + 1;
		gotoxy(5,7);
		printf("Introduzca el ID del proceso: ");
		gets(id);
		if(strlen(id) > 10) tam[j] = strlen(id)/10 + 1;
		gotoxy(5,8);
		printf("Introduzca la descripcion: ");
		gets(actividad);
		i = 9;
		if(strlen(actividad) > 48){
			i = i + (strlen(actividad) - 48)/80 + 1;
		}
		gotoxy(5,i);
		printf("Introduzca el tiempo de ejecucion: ");
		scanf("%d", &tiempo);
		if(i > 9){
			tam[j] = strlen(actividad)/50 + 1;
		}
		strcpy(e1.array, nombre);
		Queue(&nombres, e1);
		strcpy(e1.array, actividad);
		Queue(&actividades, e1);
		strcpy(e1.array, id);
		Queue(&ids, e1);
		e1.n = tiempo;
		Queue(&tiempos, e1);
		if(otroProceso() == 2) break;
		cleanScreen();
		j++;
	}while(1);
	dibujarTabla(tam, &nombres, &ids, &actividades, &tiempos);
	getchar();
	printf("\nPresione cualquier tecla para proceder a la inicializacion de la Cola de proceso");
	getchar();
	cleanScreen();
	delay_ms(500);
	colaDeProcesos(tam, &nombres, &ids, &actividades, &tiempos);
	return;
}


	