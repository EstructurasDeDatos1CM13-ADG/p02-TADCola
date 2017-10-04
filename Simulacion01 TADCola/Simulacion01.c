/********************************************************************************
* PROGRAMA: Simulacion01.c                                       				*
* AUTORES:    
* - Oledo Enriquez Gilberto Irving                                    			*
* - Alanís Ramírez Damián                                               		*
* - Mendieta Torres Alfonso Ulises                                      		*
*                                       										*
* VERSIÓN: 1.5                                                          		*
*                                                                       		*
* DESCRIPCIÓN: Programa que simula la atención de clientes en un supermerc-		*
* ado, el cual debera atender al menos 100 clientes para poder cerrar y no 		*
* tener perdidas, por lo tanto, si ya se atendieron a mas de 100 personas y		*
* no hay gente formada en las filas, la tienda piede cerra, mientras la tienda  *
* no cierre los clientes pueden seguir llegando a comprar.  					*
*                    															*
* Compilación: cd (ruta_archivos)                                       		*
* gcc -o Simulacion01 Simulacion01.c TADCola(Est|Din|Cir).o presentacionWin.o 	*
*********************************************************************************/

/*
Aqui se incluyen todas las librerias necesarias para poder hacer uso
de todas las funciones que conforman el programa principal
NOTA: Se puede incluir "TADColaEst.h" - "TADColaCir.h"
*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include "TADColaDin.h"
#include "presentacion.h"


//Definición de constantes

#define WidthConsole 90 //Se define el ancho de consola
#define TimetoDraw 20 //Se define el tiempo para dibujar
#define ClientTime 5//Se define el tiempo para dibujar a un cliente
//Funcion utilizada para erradicar el "parpadeo"
void hidecursor(void){
 HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
/* Nombre de la funcion: DrawCashier
Descripción: Esta funcion una caja del supermercado
Recibe: 2 enteros(x, y) que son las coordenadas del cursor para comenzar a dibujar; un entero(IdDrawCashier)que es el numero de la caja; un caracter(Letra que define el estado actual de la caja), y un entero
(velocidad) que es la velocidad de atencion de cada cajera, 
velocidad en que la cajera atendera los clientes
Devuelve: No tiene ningun retorno */
void DrawCashier(int x, int y, int IdDrawCashier, char estado, int vel){ //Se define la funcion para dibujar una caja
	MoverCursor(x,y); //Se posiciona el cursor antes de comenzar a dibujar la caja
	printf(" %c%c%c\t",205,205,187);//Se dibuja una parte de la caja (NOTA: Se utilizaron simbolos del ASCII)
	//Estado (A=Atendiendo)- (F=Cerrada)
	if(estado == 'A'){ //Se crea una condicional para saber si la caja esta atendiendo 
		MoverCursor(x+7, y);//Funcion encontrada en "presentacion".h
		printf("                               ");
		MoverCursor(x+7, y);//Funcion encontrada en "presentacion".h
		printf("Atendiendo");//Se imprrime si la caja esta atendiendo
	}
	else
		if(estado == 'F'){//Se crea una condicional para saber si la caja esta cerrada
			MoverCursor(x+7, y);//Funcion encontrada en "presentacion".h
			printf("                               ");
			MoverCursor(x+7, y);//Funcion encontrada en "presentacion".h
			printf("CAJA CERRADA\n");//Se imprime si la caja esta cerrada
		}
		else{ //La caja esta abierta pero esta vacia
			MoverCursor(x+7, y);//Funcion encontrada en "presentacion".h
			printf("                               ");
			MoverCursor(x+7, y);//Funcion encontrada en "presentacion".h
			printf("Caja Vacia");
		}
	MoverCursor(x+2,y+1);//Funcion encontrada en "presentacion".h
	printf(" %c\t    Caja %d",186, IdDrawCashier+1);//Se dibuja la parte central de la caja (NOTA: Se utilizaron simbolos del ASCII) 
	MoverCursor(x,y+2);//Funcion encontrada en "presentacion".h
	printf(" %c%c%c\t",205,205,188);//Se dibuja la ultima parte de la caja (NOTA: Se utilizaron simbolos del ASCII) 
	printf("La caja %d  atiende 1 cliente cada %d milisegundos\n",IdDrawCashier+1, vel);// Se muestra informacion individual sobre cada caja 
	//(Numero de caja, cual es el tiempo que tarda en atender a cada cliente)
}
/* Nombre de la funcion: Cashier
Descripción: Dibuja el numero de cajas indicado e imprime en pantalla: Nombre de supermercado,
El tiempo de llegada de los clientes, El numero de clientes que ha llegado y el numero de clientes atendidos
Recibe: La cantidad de cajas que se van a dibujar, el espacio que tendra la fila de cada cajera,
el estado de cada una de las cajas(El estado se definio anteriormente), 
el nombre del supermercado, la velocidad de llegada de los clientes(ingresado desde el teclado), la velocidad en que cada cajera atendera a los clientes, la cantidad de clientes que han 
llegado y finalmente la cantidad de clientes atendidos.
Devuelve: Un entero que representa una posicion abajo de lo que se dibujo anteriormente */
int Cashier(int cant, int largo, char estadoCajeras[], char marketName[], int llegadaClientes, int tiempoAtencion[], int cantClientesLlegados, int cantClientesAtendidos){
	int i;
	MoverCursor(0,40);
	printf("                                                                                                             ");
	MoverCursor(0,41);//Funcion encontrada en "presentacion".h
	printf("|Nombre del supermercado: %s|\t|Recibiendo 1 cliente cada %d segundos|\t\t|Han llegado %d clientes |\t|%d clientes han sido atendidos\t|", marketName, llegadaClientes, cantClientesLlegados, cantClientesAtendidos);
	if(cantClientesAtendidos>100){ //Condicional que presenta la especificacion del problema
		printf("\t\tEL SUPERMERCADO CERRARA\n");
	}
	for(i=0; i<cant; i++){
		DrawCashier(largo+1, i*4+1, i, estadoCajeras[i], tiempoAtencion[i]);
	}
	return i*4+5;
}
/* Nombre de la funcion: Paint
Descripcion: Dibuja cada uno de los clientes del supermercado 
Recibe: la fila en la que se dibujara, la posiscion, el cliente y un caracter que describe si 
la fila se ha terminado.
Devuelve: No tiene ningun retorno */
void Paint(int filaPaint, int Posicion, elemento Cliente, char acaboFila){
	char temp[4];//Creamos un arreglo auxiliar de caracteres
	itoa(Cliente.n,temp,10);// Convierte a cadena el entero que esta dentro de la estructura elemento
	int x = WidthConsole - ClientTime*Posicion - 3; //cordenada en x donde se dibujara 
	int y = filaPaint * 4 + 2; //cordenada en y donde se dibujara 
	if(acaboFila == 'S'){ //Se crea una condicional para comprobar el espacio disponible en la cola
		for(int i=0; i<x; i++){//Se limpia la cola mediante un ciclo for
			MoverCursor(i,y);//Recorrer el cursor desde el inicio hasta el final de la cola
			printf(" ");
		}
	}
	else{
		MoverCursor(x,y);
		printf("     ");
		MoverCursor(x,y);
		fflush(stdout);
		printf(" %c",254);//Se impre al cliente en la cola seleccionada (NOTA: Se utilizaron simbolos del ASCII)
	}
	return;
}

//Programa principal (Main)

int main(void){
	//Se definenen todas las varibles y solo son de dos tipos int y char
	int tiempo, cliente, atendidos, minClientes, fila,columna, alto, cantCajeras, filaElegida, llegadaClientes;
	elemento aux;
	char marketName[30], fin = 'N'; //Fin es utilizado para declarar el estado donde el supermercado cerrara
system("cls");//Se limpia la pantalla antes de comenzar el programa
	//Con ayuda de MoverCursor
	MoverCursor(40,2); printf ("***************************************\n");
	MoverCursor(43,4); printf ("Instituto Politecnico Nacional\n");
	MoverCursor(43,5); printf ("Escuela Superior de Computo\n");
	MoverCursor(43,6); printf ("Estructuras de Datos: Simulacion 01\n");
	MoverCursor(40,8); printf ("***************************************\n\n");
	MoverCursor(5,10);
	printf ("Ingrese los datos que a continuacion de solicitan\n\n");
	printf("  Ingrese el nombre del supermercado: ");
	scanf("%s", &marketName);
	printf("  Ingrese la cantidad de cajeras (0-10): ");
	scanf("%d", &cantCajeras);

	if(cantCajeras>10 || cantCajeras < 1){ //Condicion de la especificacion del problema
		//el numero de cajeras solo puede ser mayor o igual a 1 y menor o igual a 10
		printf("ERROR: Cantidad de cajeras no valida\n"); //Si el numero de cajeras no esta dentro de este rango se 
		//dice que la cantidad de cajeras no es valida
		exit(0);
	}

	printf("  Ingrese la cantidad minima de clientes atentidos para que el supermercado pueda cerrar: ");
	scanf("%d", &minClientes);//Cantidad minima de clientes atendidos para que el supermercado pueda cerra

	char estadoCajeras[cantCajeras];// Arreglo para almacenear el estado de las cajeras
	int tiempoAtencion[cantCajeras];//Arreglo para almacenar la velocidad a la que atenderan las cajeras
	cola filaCajera[cantCajeras];// Se crean las filas (colas) donde se almacenaran a los clientes 
	for(int i=0; i<cantCajeras; i++)
		Initialize(&filaCajera[i]);//Se inicializan todas las filas (colas)

	for(int i=0; i<cantCajeras; i++){
		printf("  Tiempo de atencion de la caja #%d: ", i+1);
		scanf("%d", &tiempoAtencion[i]);//Se guardan los tiempos de antencion de cada una de las cajas en milisegundos (Multiplos de 10)
	}
	printf("  Ingrese el tiempo de llegada de los Clientes: ");
	scanf("%d", &llegadaClientes);//Se guardan los tiempos de llegada de los clientes

	alto = Cashier(cantCajeras, WidthConsole, estadoCajeras, marketName, llegadaClientes, tiempoAtencion, cliente, atendidos);
	tiempo = 0; cliente = 0; atendidos = 0;//Inicializamos las variables

	system("cls");//Se limpia la pantalla
	hidecursor();//Ocultamos el cursor para que no parpadee
	srand(time(NULL));//Se generan numeros aleatorios

	while(fin == 'N'){//Se hace un ciclo que representara el tiempo en que esta funcionando el supermercado
		tiempo++;//Se aumenta en 1 el tiempo cada que entre en el ciclo
		fin = 'S';//El supermecado cerrara

		for(int i=0; i<cantCajeras; i++){//Se inicia un ciclo desde 0 hasta el numero de cajeras	
			if((!Empty(&filaCajera[i])) && estadoCajeras[i] != 'F'){//Si la fila no esta vacia y la caja no esta cerrada
				if(tiempo % tiempoAtencion[i] == 0){//Si ya se ha atendido un clinete	
					aux = Dequeue(&filaCajera[i]);//Se remueve el cliente de la fila
					
					atendidos++;//Se aumenta en uno el contador de clientes antendidos
				}
				estadoCajeras[i] = 'A'; //Se cambia el estado de la caja a Atendiendo
			}
			else{
				
				estadoCajeras[i] = 'Z';//Se cambia el estado de la caja a vacia
				if(atendidos>minClientes)//Si ya se cumplio con el minimo de clientes atendidos
					estadoCajeras[i] = 'F'; //Se cambie el estado de la caja a cerrada
			}
			//Se dibuja la simulacion actualizandola cada vez que entre al ciclo
			Cashier(cantCajeras,WidthConsole, estadoCajeras, marketName, llegadaClientes, tiempoAtencion, cliente, atendidos);
		}

		//Se dibujan los clientes
		for(int i=0; i<cantCajeras; i++){//Se inicia un ciclo que vaya desde 0 hasta el numero de cajeras
			//Se incia un ciclo que vaya desde 0 hasta el numero de cajeras
			for(int j=0; j<=Size(&filaCajera[i]); j++){

				if(j == Size(&filaCajera[i])){
					Paint(i,j-1,aux, 'S');
				}
				else{
					aux = Element(&filaCajera[i],j+1);
					Paint(i, j, aux, 'N');
				}
			}
		}
		//Cuando se ha antedido a un cliente y el supermecado sigue abierto
		if((tiempo % llegadaClientes == 0) && atendidos<=minClientes){
			cliente++;//Se aumenta la cantidada de clientes
			aux.n = cliente;//Se almacenan al cliente dentro del elemento auxiliar para poder encolarlo
			filaElegida = rand()%cantCajeras;//Asignmos la fila aleatoriamente al cliente
			Queue(&filaCajera[filaElegida], aux);//Encolamos en la fila(cola) al cliente
		}

		Sleep(TimetoDraw); // Se aplica sleep para "dormir al programa con el tiempo TimetoDraw"
		for(int a=0; a<cantCajeras; a++){//Se verifica que todas las cajas esten funcionando
			if(estadoCajeras[a] != 'F')
				fin = 'N';//Se verifica que todas las cajas esten funcionando

			MoverCursor(0, alto+5); //Se mueve el cursor para poder terminar en programa sin que se empalmen los textos
			//printf("%c\n", fin);
			
		}
	}

	MoverCursor(0,42);//Se mueve el cursor para poder terminar en programa sin que se empalmen los textos
			

	return 0;
}
