/************************************************************************
* PROGRAMA: coladeProcesosSO.c                                          *
* AUTOR: Alanís Ramírez Damián                                          *
* VERSIÓN: 1.2                                                          *
*                                                                       *
* DESCRIPCIÓN: Programa que simula la cola de procesos de un SO monopro-*
* cesador, en la cual existen procesos con su nombre, ID, descripción y *
* tiempo de ejecución.                                                  *
* Cada proceso entra en la cola de pendientes y el que este en el tope  *
* entrará en ejecución. Cada proceso terminado se encolará en la cola de*
* terminados y se mostrará al final sus datos, así como el tiempo total *
* en la cola: t = tiempoProceso + tiempoColaPendientes.                 * 
*                                                                       *
* Compilación: cd (ruta_archivos)                                       *
* gcc -o colaDeProcesosSO colaDeProcesosSO.c presentacion(Win|Lin).c    *
* TADCola(Est|Din|Circ).c                                               *
*************************************************************************/
//LIBRERÍAS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lib\gotoxy.h"
#include "lib\TADColaDin.h"
#include "lib\tabla.h"

//DECLARACIÓN DE FUNCIONES
void imprimir(char const *cadena, int y);
void letreros();
int otroProceso();
void colaDeProcesos();
void pedirProceso();

//MAIN
int main(){
	do{
		cleanScreen();
		pedirProceso();
	}while(otroProceso() == 1);
	getchar();
	return 0;
}

//DEFINICIÓN DE FUNCIONES

/*
void imprimir()
Función que imprime una cadena centrada y en la coordenada y especificada.
Argumentos: 
- char const *cadena (una cadena a imprimir)
- int y (la coordenada y donde se va a imprimir)
Retorna: void
*/
void imprimir(char const *cadena, int y){
	gotoxy((80-strlen(cadena))/2, y);
	puts(cadena);
	return;
}

/*
void letreros()
Función que imprime los letreros de presentación del
programa.
Argumentos: void
Retorna: void
*/
void letreros(){
	imprimir("Instituto Politecnico Nacional", 0);
	imprimir("ESCOM", 1);
	imprimir("Cola de procesos de Sistema Operativo", 2);
	return;
}

/*
int otroProceso()
Función que pregunta al usuario si desea introducir otro proceso (ya sea
durante la función pedirProceso() o al final cuando debe decidir si reiniciar
el programa para simular otra cola de procesos, o salir del programa). 
Argumentos: void
Retorna: 1 si selecciona 's'|'S' y 2 si selecciona 'n'|'N'
*/
int otroProceso(){
	char sn;
	printf("\nDesea introducir otro proceso(s|S,n|N)?: ");
	setbuf(stdin, NULL);
	scanf("%c", &sn);
	tolower(sn);
	return(sn == 's')?1:2;
}

/*
void colaDeProcesos(int anchoColumnas[], cola *nombre, cola *id, cola *actividad, cola *tiempo)
Función que simula la cola de procesos del SO, mostrando gráficamente (con interfaz con caracteres
ASCII) la cola de ejecución y la cola de terminados, en las cuales aparecen nombre, id, descripción y 
tiempo de ejecución de cada proceso.
Al final muestra la cola de terminados y el tiempo total de ejecución.
Argumentos:
- int anchoColumnas[] (es un arreglo que indica el ancho de la columna a imprimir en 
función del cálculo que se hace en la función pedir proceso)
- cola *nombre, cola *id, cola *actividad, cola *tiempo (se pasan por referencia)
Retorna: void
*/
void colaDeProcesos(int anchoColumnas[], cola *nombre, cola *id, cola *actividad, cola *tiempo){
	char nom[32], ids[32];
	int t;
	cola nombreFinalizado, idFinalizado, actividadFinalizado, tiempoFinalizado;
	elemento e1;
	int i, j, desplazamiento = 0, tiempoTotal = 0, tiempoEjecucion = 0;
	Initialize(&nombreFinalizado);
	Initialize(&idFinalizado);
	Initialize(&actividadFinalizado);
	Initialize(&tiempoFinalizado);
	i = 0;
	while(Empty(tiempo) == FALSE){ //Mientras la cola tiempo (aunque podría ser cualquiera de las que se recibieron, ya que tienen el mismo tamaño)
		letreros();				   //no este vacía
		dibujarTabla(anchoColumnas, nombre, id, actividad, tiempo, 10, "ejecucion", 1);//Dibuja la tabla que contiene al proceso en ejecución
		//dibujarTabla(anchoColumnas, &nombreFinalizado, &idFinalizado, &actividadFinalizado, &tiempoFinalizado, 19, "finalizados", Size(&nombreFinalizado));
		while(Empty(tiempo) == FALSE){ //Algoritmo de encolado y desencolado para paso de cola de espera a ejecución cuando transcurre un quantum
			cleanScreen();
			letreros();
			dibujarTabla(anchoColumnas, nombre, id, actividad, tiempo, 10, "ejecucion", 1);//Dibuja la tabla que contiene al proceso en ejecución
			dibujarTabla(anchoColumnas, &nombreFinalizado, &idFinalizado, &actividadFinalizado, &tiempoFinalizado, 28, "finalizados", Size(&nombreFinalizado));
			if(i != 0){
				e1 = Element(nombre, Size(tiempo));
				strcpy(nom, e1.array);
				e1 = Element(id, Size(tiempo));
				strcpy(ids, e1.array);
				e1 = Element(tiempo, Size(tiempo));
				t = e1.n;
				imprimir("Ultimo proceso Ejecutado: ", 14); 
				gotoxy(0,15);
				printf("Nombre = %s \t ID = %s \tTiempo para que finalice = %d", nom, ids, t);
				imprimir("Proximo proceso a ejecutarse: ", 18);
				if(Size(nombre) > 1){
					e1 = Element(nombre, 2);
					strcpy(nom, e1.array);
					e1 = Element(id, 2);
					strcpy(ids, e1.array);
					e1 = Element(tiempo, 2);
					t = e1.n;
				}
				else{
					e1 = Front(nombre);
					strcpy(nom, e1.array);
					e1 = Front(id);
					strcpy(ids, e1.array);
					e1 = Front(tiempo);
					t = e1.n;
				}
				gotoxy(0,19);
				printf("Nombre = %s \t ID = %s \tTiempo para que finalice = %d", nom, ids, t);
			}
			e1 = Dequeue(tiempo);
			gotoxy(72,10);
			printf("%ds", e1.n);
			delay_ms(1000);
			if(e1.n > 0){ //Si el tiempo de ese proceso aun no acaba (t == 0 es el criterio de finalización)
				e1.n--;
				Queue(tiempo, e1); //Encola el nuevo tiempo
				Queue(nombre, Dequeue(nombre)); //Encola (lleva al final) el nombre que se encontraba al principio
				Queue(id, Dequeue(id));
				Queue(actividad, Dequeue(actividad));
			}
			else{
				e1.n = tiempoEjecucion;
				Queue(&tiempoFinalizado, e1); //Se encola el tiempoEjecucion de ese proceso en tiempoFinalizado
				Queue(&nombreFinalizado, Dequeue(nombre)); //Se desencola el nombre de la cola de ejecución y se encola en finalizado
				Queue(&idFinalizado, Dequeue(id));
				Queue(&actividadFinalizado, Dequeue(actividad));
				break;
			}
			tiempoEjecucion++;
			i++;
		}
		//imprimir("Ultimo proceso Ejecutado: ", 14); 
		//gotoxy(10,15);
		//printf("Nombre = %s \t ID = %s \tTiempo para que finalice = %d", nom, ids, t);
		dibujarTabla(anchoColumnas, &nombreFinalizado, &idFinalizado, &actividadFinalizado, &tiempoFinalizado, 28, "finalizados", Size(&nombreFinalizado));
		if(Empty(nombre) == TRUE){ //Una vez que se vacía la cola de ejecución
			printf("\n\tEl SO ha ejecutado todos los procesos en la cola. \n\tPresione cualquier tecla para continuar ...");
			getchar();
		}
	}
	cleanScreen();
	letreros();
	dibujarTabla(anchoColumnas, &nombreFinalizado, &idFinalizado, &actividadFinalizado, &tiempoFinalizado, 10, "finalizados", Size(&tiempoFinalizado));
	printf("\n\t\tEl tiempo total de ejecucion fue de %ds \n", tiempoEjecucion); //Se indica el tiempo (tiempo de proceso 1 + proceso 2 + ... + proceso n)
	Destroy(&nombreFinalizado); //Destruye las colas pensando en un posible nuevo proceso
	Destroy(&idFinalizado);
	Destroy(&actividadFinalizado);
	Destroy(&tiempoFinalizado);
	Destroy(nombre);
	Destroy(id);
	Destroy(actividad);
	Destroy(tiempo);
	return;
}


/*
void pedirProceso()
Función que pide los datos del proceso, es decir, id, nombre, descripción y tiempo de
ejecución, y los va almacenando en colas con la misma etiqueta del dato (hay una cola
para nombres, otra para id´s, etc). Asimismo, llama a las funciones dibujarTabla() (de
la librería tabla.h) y colaDeProcesos.
Argumentos: void
Retorna: void
*/
void pedirProceso(){
	int i = 5, j = 0, tam[20], tiempo;
	char id[32], nombre[32], actividad[200], temp[200];
	cola nombres, actividades, ids, tiempos;
	elemento e1;
	Initialize(&nombres);
	Initialize(&actividades);
	Initialize(&ids);
	Initialize(&tiempos);
	do{
		tam[j] = 1; //tam[j] nos indicará el ancho de columna de acuerdo a la longitud de las cadenas (nombre, id y actividad)
		setbuf(stdin, NULL);
		letreros();
		imprimir("A continuacion introduzca los parametros del proceso que se le solicitan: ", 4);
		imprimir("Precondiciones (strlen(nombre) y strlen(id)) <= 32, strlen(descripion) <= 200", 5);
		gotoxy(5,6); 
		printf("Introduzca el nombre del proceso: ");
		gets(nombre);
		if(strlen(nombre) >= 10) tam[j] = strlen(nombre)/10 + 1; //el tamaño del renglón donde se imprimirá es de 10 así que la
		gotoxy(5,7);											//columa será de ancho igual al número de veces que exceda el 10
		printf("Introduzca el ID del proceso: ");
		gets(id);
		if(strlen(id) >= 10) tam[j] = strlen(id)/10 + 1;
		gotoxy(5,8);
		printf("Introduzca la descripcion: ");
		gets(actividad);
		i = 9;	
		if(strlen(actividad) > 48){	//Ciclo para dar saltos de linea durante la introducción de la cadena en caso de que sea de longitud mayor a
			i = i + (strlen(actividad) - 48)/80 + 1; //48 (80 - 32 que es la longitud del letrero "Introduzca ..." + el desplazamiento en x) y que
		}											 //así no se afecte la impresión de los siguientes letreros (que no se encime)
		gotoxy(5,i);
		printf("Introduzca el tiempo de ejecucion (en segs): ");
		scanf("%d", &tiempo);
		if(i > 9){ //Se asume que si i  es mayor a 9, entonces actividad superaría su espacio de impresión en el renglón 
			tam[j] = strlen(actividad)/50 + 1;
		}
		strcpy(e1.array, nombre); //Se copia el nombre al elemento e1 en su parte array[]
		Queue(&nombres, e1);	  //Se encola el nombre en la cola nombres
		strcpy(e1.array, actividad);
		Queue(&actividades, e1);
		strcpy(e1.array, id);
		Queue(&ids, e1);
		e1.n = tiempo;
		Queue(&tiempos, e1);
		if(otroProceso() == 2) break; //Se pregunta si se desea introducir otro proceso, en caso de que no, se sale del ciclo
		cleanScreen();
		j++; 
		if(j == 19) break; //Si se ha superado el número máximo de datos a introducir
	}while(1);
	dibujarTabla(tam, &nombres, &ids, &actividades, &tiempos, 18, "espera", Size(&tiempos)); //Dibuja la tabla con los datos introducidos
	getchar();
	printf("\nPresione cualquier tecla para proceder a la inicializacion de la Cola de proceso");
	getchar();
	cleanScreen();
	delay_ms(500);
	colaDeProcesos(tam, &nombres, &ids, &actividades, &tiempos); //Llama a la función que simulará la cola de procesos
	return;
}


	