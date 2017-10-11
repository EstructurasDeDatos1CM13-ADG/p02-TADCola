/************************************************************************
 LIBRERIA: tabla.h                                                     
 AUTORES:																
 - Oledo Enriquez Gilberto Irving										
 - Alanís Ramírez Damián                                               
 - Mendieta Torres Alfonso Ulises    
 VERSIÓN: 2.4                                                          
                                                                       
 DESCRIPCIÓN: Las funciones de esta librería permiten generar la tabla  
 con los datos que se introducen por el usuario para cada proceso (nom-
 bre, id, descripción, tiempo, etc) de n renglones. Cada renglón es ca-
 paz de ajustar dinámicamente su altura, en función de cuantos espacios
 se requeririan para imprimir el dato completo sin que este se encime o
 desaparezca parte del mismo al imprimir el dato del siguiente campo   
 sobre este.															
                                                                       
*************************************************************************/
#include <stdio.h>
#include <conio.h>
#include "gotoxy.h"

/*
void imprimirParedes(int coordenada Y)
Función que imprime una pared (un caracter |) marcando el final de cada campo en el eje x,
es decir, es el delimitador de las columnas.
Argumentos:
- int coordenadaY (es la coordenada de la consola en la que se imprimirá la pared)
Retorna: void
*/
void imprimirParedes(int coordenadaY){
	int posicion[5] = {0, 11, 21, 71, 79}, i; //posicion[] es para imprimir a lo largo del eje X (   |      |            |      |)
	for(i = 0; i < 5; i++){
		gotoxy(posicion[i], coordenadaY);
		printf("%c", 179);
	}
	return;
}

/*
void imprimirRenglon(char cadena[], int coordenada Y, int coordenadaX, int tipo)
Función que imprime el dato en la tabla, de tal manera que si la longitud de la cadena
a imprimir supera el espacio horizontal por defecto (es decir, 9 espacios para el tipo 0 y 
49 para el tipo 1, el cual es la descripción, ya que este cuenta con 49 espacios sobre el
eje x para poder imprimirse, es la columna más amplia).
Si se sobrepasa se continua imprimiendo el dato pero con un desplazamiento, es decir, salta
a la siguiente posición en y y se continua imprimiendo.
Argumentos:
- char cadena[] (es el dato a imprimir en su campo: nombre, id o descripción)
- int coordenadaY (es la coordenada y de la consola en la que se encuentra el caracter a imprimir)
- int coordenadaX (es la coordenada x de la consola en la que se encuentra el caracter a imprimir)
- int tipo (indica si se trata de un dato con un ancho de columna permitido de 9 espacios por renglón- 
id y nombre- o uno de 49 espacios por renglón - descripción -)
Retorna: desplazamiento (retorna el desplazamiento que sufrió el renglón para poder imprimirse correctamente)
*/
int imprimirRenglon(char cadena[], int coordenadaY, int coordenadaX, int tipo){
	int j, desplazamiento, x[4];
	if(tipo == 1){ //Ayuda a indicar si se trata de una columna tipo 1 (de 49 espacios) o de una tipo 0 (de 9 espacios)
		x[0] = 49;
		x[1] = 98;
		x[2] = 147;
		x[3] = 196;
		if(strlen(cadena) < 50) desplazamiento = 0; //Si la cadena se puede imprimir en menos de 50 espacios entonces no habrá salto de renglón
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
			if(j == x[0]){ //Si la longitud que va hasta ahora de la cadena es igual a 9
				imprimirParedes(coordenadaY + 1); //Imprime las paredes en el siguiente, sin cerrar todavía el renglón con una linea horizontal
				gotoxy(coordenadaX, coordenadaY + 1);
				printf("%c", cadena[j]);
				desplazamiento = 1; //El desplazamiento ya vale 1, pues ya se tuvo que aumentar la altura del renglón para darle cabida al dato
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
			printf("%c", cadena[j]); //En caso de que se encuentre dentro del campo de impresión se imprime normalmente el caracter
		}
	}
	return desplazamiento;
}

/*
void imprimirDatos(cola *nombre, cola *id, cola *actividad, cola *tiempo, int desplazamiento, int numeroItem, int y)
Función que se encarga de la impresión de la tabla con los datos, ya que aquí es donde se obtienen los datos directamente de las colas
que se tienen como argumentos y se pasan a la función imprimirRenglon().
Se apoya del desplazamiento generado por la función imprimirRenglon() para ir imprimiendo adecuadamente cada renglón sin que se encime.
Al final el desplazamiento definitivo lo determinará el dato que más se haya desplazado. Por ejemplo, si se tiene un nombre de tamaño 12
entonces este se imprime del 1 al 9 en el renglón 1 y luego se desplaza 1 unidad en la coordenada Y y se imprimen los caracteres restantes
en el siguiente renglón. Pero si se tiene una descripción de 100 caracteres, entonces esta ya sufrió 2 saltos o desplazamientos, por lo que
el desplazamiento total de esa fila va a ser el del dato que sufrió el mayor desplazamiento, en este caso, la descripción.
Argumentos:
- cola *nombre (puntero a cola, servirá para pasarle la cola nombre a la función)
- cola *id (puntero a cola, servirá para pasarle la cola id a la función)
- cola *actividad (puntero a cola, servirá para pasarle la cola actividad - la cual contiene las descripciones - a la función)	
- cola *tiempo (puntero a cola, servirá para pasarle la cola tiempo a la función)
- int desplazamiento (es un desplazamiento de acarreo, es decir, que se va generando con cada iteración, inicialmente es 0 en la función que llama
a imprimirDatos())
- int numeroItem (da el elemento a obtener para su impresión, viene dado por el contador que se encuentra en la función dibujarTabla(), que es la 
que llama a esta función)
- int y (es la coordenada Y en la cual se imprimiran los datos, a esta se le sumará el desplazamiento de acarreo)
Retorna: void
*/
void imprimirDatos(cola *nombre, cola *id, cola *actividad, cola *tiempo, int desplazamiento, int numeroItem, int y){
	int i, j, desplazamientoNombre, desplazamientoId, desplazamientoActividad;
	elemento e1;
					//┌    |	-	  ┐	  ┘    └
	char tabla[6] = {218, 179, 196, 191, 217, 192};
	gotoxy(0, y + desplazamiento); 
	putchar(tabla[1]);
	gotoxy(1, y + desplazamiento);
	e1 = Element(nombre, numeroItem); //guarda en e1 el elemento numeroItem
	desplazamientoNombre = imprimirRenglon(e1.array, y + desplazamiento, 1, 0); //Se imprime el nombre, guardando su desplazamiento en 
	gotoxy(11, y + desplazamiento);										//desplazamientoNombre,
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
	printf("%ds", e1.n); //Se imprime el tiempo
	gotoxy(79, y + desplazamiento);
	putchar(tabla[1]);
	if(desplazamientoActividad >= desplazamientoNombre && desplazamientoActividad >= desplazamientoId){ //En caso de que el
		desplazamiento = desplazamiento + desplazamientoActividad;	//desplazamiento de la activiad sea el mayor de todos
	}
	else{
		if(desplazamientoNombre >= desplazamientoActividad && desplazamientoNombre >= desplazamientoId){ //En caso de que el 
			desplazamiento = desplazamiento + desplazamientoNombre;	//desplazamiento del nombre sea el mayor de todos
		}
		else desplazamiento = desplazamiento + desplazamientoId; //Por descarte se tiene que si el control llega hasta aquí es porque
	}															//el desplazamiento del id es el mayor
	gotoxy(0, y + 1 + desplazamiento); //Se imprimen las esquinas inferiores de la tabla
	putchar(tabla[5]);
	gotoxy(79, y + 1 + desplazamiento);
	putchar(tabla[4]);
	gotoxy(1, y + 1 + desplazamiento);
	for(i = 0; i < 78; i++) printf("-"); //Al final de cada renglón imprime la linea horizontal para indicar su fin
}

/*
void dibujarEncabezados(int y, char titulo[])
Función que imprime la parte de arriba de la tabla, es decir, el encabezado, el cual es
 -----------------------------------------------------------------------
 |Nombre      |     ID     |          Descripción            | Tiempo  |
 -----------------------------------------------------------------------
 Se considero pertinente hacerlo una función ya que será un dato estático que se imprimirá
 constantemente.
 Argumentos:  
- int y (es la coordenada de la consola en la que se posicionará)
- char titulo[] (es la etiqueta de la cola, ejemplo: listos, finalizados, etc)
Retorna: void
*/
void dibujarEncabezados(int y, char titulo[]){
	int i;
					//┌    |	-	  ┐	  ┘    └
	char tabla[6] = {218, 179, 196, 191, 217, 192};

	gotoxy((80-(strlen("Cola de") + strlen(titulo)))/2, y); //Va a la coordenada x en la que se imprima centrada la cabecera
	printf("Cola de %s", titulo);
	gotoxy(0, y + 1);
	putchar(tabla[0]); //Imprime la tabla con las etiquetas de cada columna (nombre, id, descripción y tiempo), es decir, los campos
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

/*
void dibujarTabla(int anchoColumnas[], cola *nombre, cola *id, cola *actividad, cola *tiempo, int y, char titulo[], int tam)
Función que se encarga de llamar a las otras funciones esenciales para dibujar la tabla, además, es la que tiene el contador
que va recorriendo los elementos encolados, y que proceden de las colas en las que se almacenaron los datos introducidos por
el usuario, y los va imprimiendo de manera coherente (sin encimarse ni recortarse). Es importante observar que se tiene un 
desplazamiento de acarreo o ancho de columna que viene desde el mismo programa colaDeProcesosSO.c, y que depende de si el
dato desde un inicio se sabe que va a rebasar el espacio para su impresión.
Argumentos:
- int anchoColumnas[] (arreglo que contiene los desplazamientos en concreto para cada dato conforme fueron introducidos)
- cola *nombre (puntero a cola, servirá para pasarle la cola nombre a la función)
- cola *id (puntero a cola, servirá para pasarle la cola id a la función)
- cola *actividad (puntero a cola, servirá para pasarle la cola actividad - la cual contiene las descripciones - a la función)	
- cola *tiempo (puntero a cola, servirá para pasarle la cola tiempo a la función)
- int y (coordenada y en la que se posicionará)
- char titulo[] (indica que tipo de cola será, de ejecución, de finalizado)
- int y (es la coordenada Y en la cual se imprimiran los datos, a esta se le sumará el desplazamiento de acarreo)
- int tam (indica el numero de iteraciones a realizar, depende del numero de procesos introducidos por el usuario, es decir, si en 
colDeProcesosSO el usuario introdujo 7 datos, entonces se deberá realizar este ciclo 7 veces, ya que cada ciclo imprime un dato)
Retorna: void
*/
void dibujarTabla(int anchoColumnas[], cola *nombre, cola *id, cola *actividad, cola *tiempo, int y, char titulo[], int tam){
	int desplazamiento = 0, i, j;
	elemento e1;
	dibujarEncabezados(y - 4, titulo);
	for(i = 0; i < tam; i++){
		imprimirDatos(nombre, id, actividad, tiempo, desplazamiento, i + 1, y);
		desplazamiento = desplazamiento + anchoColumnas[i] + 1; //En el desplazamiento en y influye el desplazamiento de acarreo (el que
	} 										//venía desde que el usuario introdujo los datos), y el propio desplazamiento anterior más 1
	return;
}
