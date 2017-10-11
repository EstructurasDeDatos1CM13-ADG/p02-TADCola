/************************************************************************
 LIBRERIA: TADColaDin.h 												
 AUTORES:																
 - Oledo Enriquez Gilberto Irving										
 - Alanís Ramírez Damián                                               
 - Mendieta Torres Alfonso Ulises                                      
 VERSIÓN: 1.0                                                          
                                                                       
 DESCRIPCIÓN: TAD Cola o Queue.                                        
 Estructura de datos en la que se cumple:                              
 Los elementos se insertan en un extremo (el final) y las supresiones  
 tienen lugar en el otro extremo (frente).                             
                                                                       
 OBSERVACIONES: Hablamos de una Estructura de datos dinámica           
 cuando se le asigna memoria a medida que es necesitada,               
 durante la ejecución del programa.                                    
                                                                       
*************************************************************************/

//DEFINICIONES
#define TRUE	1
#define FALSE	0

//DEFINICIONES DE TIPOS DE DATO
//Definir un boolean (Se modela con un char)
typedef unsigned char boolean;

//Definir un elemento (por medio de una estructura elemento)
typedef struct elemento{
	//Variables de la estructura "elemento" (El usuario las puede modificar)
	int n;
	char array[200];
	//***
	//***
	//***
} elemento;

//Se define un nodo por medio de una estructura, cada nodo contiene
//un elemento y a un apuntador al siguiente nodo
typedef struct nodo{
	elemento e; //Elemento a almacenar en cada nodo de la cola
	struct nodo *siguiente;//Apuntador al nodo siguiente
}nodo;

//Se define una cola por medio de una estructura que incluye dos 
//apuntadores a nodo, para controlar el frente y final de la cola
typedef struct cola{
	nodo *frente;
	nodo *final;
	int num_elem;
} cola;

//DECLARACIÓN DE FUNCIONES
void Initialize(cola *c);			//Inicializar cola (Initialize): Recibe una cola y la inicializa para su trabajo normal.
void Queue(cola *c, elemento e);	//Encolar (Queue): Recibe una cola y agrega un elemento al final de ella. 
elemento Dequeue(cola *c);			//Desencolar (Dequeue): Recibe una cola y remueve el elemento del frente retornándolo.
boolean Empty(cola *c);				//Es vacía (Empty): Recibe la cola y devuelve verdadero si esta esta vacía.
elemento Front(cola *c);			//Frente (Front): Recibe una cola y retorna el elemento del frente.	
elemento Final(cola *c);			//Final (Final): Recibe una cola y retorna el elemento del final.
elemento Element(cola *c, int i); 	// Recibe una cola y un número de elemento de 1 al tamaño de la cola y retorna el elemento de esa posición.
int Size(cola *c);					//Tamaño (Size): Retorna el tamaño de la cola 	
void Destroy(cola *c);				//Eliminar cola (Destroy): Recibe una cola y la libera completamente.
