/************************************************************************
 LIBRERIA: presentacion.h 												
 AUTORES:																
 - Oledo Enriquez Gilberto Irving										
 - Alanís Ramírez Damián                                               
 - Mendieta Torres Alfonso Ulises                                      
 VERSIÓN: 1.0                                                          
                                                                       
 DESCRIPCIÓN: Cabecera de la libreria para recrear presentaciones más 
 agradables al usuario, permitiendo mostrar gráficos en el modo consola                            
                                                                       
 OBSERVACIONES: La implementación de esta libreria es distinta si se 
 trata de Windows o Linux, ya que requerirá de funciones no ANSI C                                  
                                                                       
*************************************************************************/

//DECLARACIÓN DE FUNCIONES
void gotoxy( int x, int y );	//Función para mover el cursor de escritura de pantalla

void delay_ms(int t);			//Función para esperar un tiempo en milisegundos

void cleanScreen(void);			//Función para borrar la pantalla de la consola

int whereY(void);				//Función que devuelve la coordenada Y en la que se ubica el cursor