//Fermin Covarrubias Ramos - 20110309 - 8K
//Practica el cual inicializamos la pantalla y mostramos el nombre del usuario

#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#define E PTAD_PTAD1 //definir nuestro enable para uso mas practico
#define RS PTAD_PTAD0 //definir nuestro ReadState para uso mas practico

void MCUinit(void); //iniciar puertos del QG8
void inicio (void); //Inicializar la pantalla para enviar 
void enable(void); //Clase que se encarga de enviar la alerta de que se enclaven los datos a los pines de la pantalla
void retardoRTI(void); //delay para ver mejor el proceso de la pantalla y que no se sature el circuito
void comando(unsigned char bipbup); //Dar orden al QG8 para que mande el dato requerido hacia la pantalla
void datos(unsigned char datoperacion); //datos en hexadecimal el cual sera la palabra, digito o caracter en ascii el cual sera mandado por comandos


void main(void) {
	SOPT1=0X12; //quitar el watchdog
	MCUinit(); //inicializar los puertos
	inicio(); //inicializar la pantalla antes de mandar datos
	datos(0x46); //Mandando en hexadecimal ASCII la letra F
	datos(0x45); //Mandando en hexadecimal ASCII la letra E
	datos(0x52); //Mandando en hexadecimal ASCII la letra R
	datos(0x4D); //Mandando en hexadecimal ASCII la letra M
	datos(0x49); //Mandando en hexadecimal ASCII la letra I
	datos(0x4E); //Mandando en hexadecimal ASCII la letra N
	datos(0x2D); //Mandando en hexadecimal ASCII un guion (-)
	datos(0x32); //Mandando en hexadecimal ASCII el numero 2
	datos(0x30); //Mandando en hexadecimal ASCII el numero 0
	datos(0x31); //Mandando en hexadecimal ASCII el numero 1
	datos(0x31); //Mandando en hexadecimal ASCII el numero 1
	datos(0x30); //Mandando en hexadecimal ASCII el numero 0
	datos(0x33); //Mandando en hexadecimal ASCII el numero 3
	datos(0x30); //Mandando en hexadecimal ASCII el numero 0
	datos(0x39); //Mandando en hexadecimal ASCII el numero 9
    for(;;) {
    
    } 
}

void inicio (void){ //clase de inicio de pantalla
	unsigned char i=0; //variable iniciada en 0 la cual nos dara orden en enviar los datos enviados de la pantalla
	//inicializacion de la pantalla la cual indica cuantos bits sera (8 bits), su fuente, cuanto incremeto por desplazamiento tendra, que caracteristicas tendra como un cursor, parpadeo apagado, etc. (control de pantalla) y limpiar la pantalla por si hay algo de una practica pasada
	unsigned char tabla[8]={0x38,0x38,0x38,0x38,0x0F,0x06,0x01,0x00};
	while(i!=8){ //cuantos espacios tendra la pantalla, contando desde 0
		comando(tabla[i]); //clase para mandar los datos de la tabla por ReadState, enable y puertos de salida.
		i++; //deslizarnos un espacio en el array de la tabla
	}

}

void retardoRTI(void){ //clase de delay en tiempo real (RTI)
	SRTISC=0x01; //Habilita el bit RTIE en el SRTISC dandonos una interrupcion con temporizador
	while(SRTISC_RTIF==0); //se hace un bucle esperando la bandera que indique la interrupcion RTIF
	SRTISC_RTIACK=1; //Se borra la bandera que esta en bucle activando el RTIACK
	SRTISC=0x00; //Se deshabilita las interrupciones de este delay
}

void MCUinit(void){ //declaracion de puertos del QG8
	PTBDD=0xFF; //hacer salidas PTBD
	PTADD=0x03; //inicializar puertos A en entradas
	PTADD_PTADD0=0x01; //Inicializar el puerto RS
	PTADD_PTADD1=0x01; //Inicializar el puerto E
}

void enable(void){ //clase para el habilitador de la pantalla.
	E=1; //cuando se ejecuta, lo pone en 1 con la declaracion al inicio del codigo
	retardoRTI(); //se aplicar un delay RTI
	E=0; //se desactiva antes de finalizar
}

void comando(unsigned char bipbup) //clase para realizar comandos en el sistema para envio de datos en la pantalla
{
	unsigned char comandante=0; //inicializa la variable que mandara la orden indicada por el codigo en 0
	comandante=bipbup; //se indica una variable extra para el uso en el codigo
	RS=0; //el readstate se inicia en 0
	PTBD=comandante; //se indica que las salidas del QG8 seran mandadas por el comando
	enable(); // se brinca hacia la clase de enable para activar el pin de la tarjeta
}


void datos(unsigned char datoperacion) //clase para recibir datos de la pantalla
{
	RS=1;//el readstate se inicia en 1
	PTBD=datoperacion;//se indica que las salidas del QG8 seran mandadas por el comando
	enable();// se brinca hacia la clase de enable para activar el pin de la tarjeta
}
