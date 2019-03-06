/* Operations in C++ */

#include<iostream>
#include<cmath>

using namespace std;

enum interrupts{INICIO, UART, SPI, I2C, CAN, FIN};
enum state{OFF, ON};
enum interrupts interrupcion = INICIO;
enum state estado = OFF;

/*1. Organice de manera adecuada el orden de los operadores aritmeticos, sin utilizar
     los operadores parentesis y corchetes de modo que el resultado de la operación sea 8 */
	 
void operacion1(void)
{
	unsigned int a = 3, b = 5, c = 10, d = 8, e = 7;
	float resultado = 0.0;
	
	resultado = c*d/a*e/b*a/e*c/b; 
	
	cout<<((resultado==8)?"Operacion 1 OK! :-)":"Operacion 1 Mal! :-(")<<endl;	
}

/*2. En un microcontrolador ud tiene un registro de 16 bits mediante el cual controla las banderas de 
	 de atención a interrupción de los periféricos del microcontrolador, son 4 perifericos: UART, SPI,
	 I2C y CAN que están asignados en ese orden a un bit de por medio a partir del bit 7 en los
	 8 bits menos significativos del registro. Las interrupciones de SPI e I2C trabajan en lógica invertida (activo en bajo).
	 
	 En el estado INICIO de la maquina_de_interrupciones el registro debe tener los 8 bits más significativos
	 en el valor en decimal 170 y así deben permanecer hasta el estado FIN donde deben obtener el valor en
	 decimal 85, los otros 4 bits de los periféricos deben estar desactivados, es decir, en 1 o 0 de 
	 acuerdo con la lógica de activacion (alto/bajo), los bits de por medio entre perifericos deben permanecer en
	 alto (1) en todos los estados de la máquina.
	 
	 En cada interrupción en el estado OFF se debe desactivar la interrupción anterior y en el estado ON se debe 
	 activar la interrupción actual. Ejemplo:
	 
	 En la interrupción I2C estado OFF se debe desactivar la interrupción SPI y en el estado ON activar
	 la interrupción I2C.
	 
	 Las interrupciones se activan/desactivan poniendo en 1 o 0 el bit correspondiente a la interrupción
	 en el registo de control de las interrupcciones, de acuerdo con la lógica en la que trabaje el periférico
	 y sin tocar ningun otro bit que no este involucrado en la interrupción (bit de otro periférico).
	 
	 Las activaciones/desactivaciones de interrupciones solo se pueden hacer con operaciones a nivel de bit. Está
	 estrictamente prohibido hacer asignaciones directas de valores numéricos al registro de control.
	 Para tal cometido se recomienda utilizar máscaras de bit. Ejemplo: Para una interrupción que usa el bit 11 y tiene
	 lógica con activación en alto entonces la máscara sería: unsigned short Mask_Perif = 2048;*/
	 

void operacion2(void)  /*Maquina de atención a interrupcciones */
{
	static short registro_control_interrupciones;
	/*Aqui usted puede definir las mascaras de activación de las interrupciones */
	
	switch (interrupcion){
		case INICIO:
			/*Aqui usted debe inicializar el registro de control*/
			
			cout<<"Estado inicial interrupcciones del micro..."<<endl;
			if(estado == OFF || estado == ON)
			{
			    if((~registro_control_interrupciones) == 0x5582)
				{
					interrupcion = UART;
					estado = ON;
				}
				else
				{
					cout<<"Problemas en el estado inicial interrupcciones del micro..."<<endl;
					interrupcion = INICIO;
					estado = OFF;
				}
			}
			break;
		case UART:
			cout<<"Estado interrupcion de UART..."<<endl;
			if(estado == ON)
			{
				/*Aqui usted debe activar la interrupcion de UART*/
				
				if(~registro_control_interrupciones == 0x5502)
				{
					interrupcion = SPI;
					estado = OFF;
					cout<<"		UART activada..."<<endl;
				}
			}
			break;
		case SPI:
			cout<<"Estado interrupcion de SPI..."<<endl;
			if(estado == OFF)
			{
				/*Aqui usted debe desactivar la interrupcion de UART*/
				
				if(~(registro_control_interrupciones & 0xAA7D) == -43646)
				{
				    interrupcion = SPI;
					estado = ON;
					cout<<"		UART desactivada..."<<endl;
				}
			}
			else /*estado == ON */
			{
				/*Aqui usted debe activar la interrupcion de SPI*/
				
				if(~registro_control_interrupciones == 0x55A2)
				{
					interrupcion = I2C;
					estado = OFF;
					cout<<"		SPI activada..."<<endl;
				}
			}
			break;
		case I2C:
			cout<<"Estado interrupcion de I2C..."<<endl;
			if(estado == OFF)
			{
				/*Aqui usted debe desactivar la interrupcion de SPI*/
				
				if(~(registro_control_interrupciones & 0xAA7D) == -43646)
				{
					interrupcion = I2C;
					estado = ON;
					cout<<"		SPI desactivada..."<<endl;
				}
			}
			else /*estado == ON */
			{
				/*Aqui usted debe activar la interrupcion de I2C*/
				
				if(~registro_control_interrupciones == 0x558A)
				{
					interrupcion = CAN;
					estado = OFF;
					cout<<"		I2C activada..."<<endl;
				}
			}
			break;
		case CAN:
			cout<<"Estado interrupcion de CAN..."<<endl;
			if(estado == OFF)
			{
				/*Aqui usted debe desactivar la interrupcion de I2C*/
				
				if(~(registro_control_interrupciones & 0xAA7D) == -43646)
				{
					interrupcion = CAN;
					estado = ON;
					cout<<"		I2C desactivada..."<<endl;
				}
			}
			else /*estado == ON */
			{
				/*Aqui usted debe activar la interrupcion de CAN*/
				
				if(~registro_control_interrupciones == 0x5580)
				{
					interrupcion = FIN;
					estado = OFF;
					cout<<"		CAN activada..."<<endl;
				}
			}
			break;
		default:
		    cout<<"Todas las interrupciones probadas..."<<endl;
			/* Aqui debe desactivar todas las interrupciones y cambiar los 8 bits
			   más significativos del registro de control (asignando el valor en decimal 85) */
			interrupcion = INICIO;
			estado = OFF;
			break;
	}	
}

/* 3. Escriba utilizando los operadores arritmeticos de C++ las siguientes formulas y ecuaciones e
	  imprima el resultado de cada una*/

void otros_calculos(void)
{
	/*Nota1: la operación raíz cuadrada la puede implementar usando la función: sqrt(x) */
	/*Nota2: Recuerde declarar las variables/constantes que vaya a utilizar en sus ecuaciones/formulas */
	
    /* Serie simple (1/[(x^2) + (x+1)]) para x entre 1 y 199*/
    for(int x=1; x<200; x++)
	{
		//Agregue aqui la formula
	}
        
    /* Volumen de la esfera */
      //Agregue aqui la formula

    /* Raices de la ecuacion cuadrática (3*x^2) + (5*x) + 8  = 0 */
      //Agregue aqui la formula

    /* Impedancia tipica de una linea de transmision
     * Z0 = [(R + (w x L))/(G + (w x C))]^(1/2)
     * w = frecuencia angular = 2*pi*f, f = 10kHz */
        //Agregue aqui la formula

    /* Constante de fase de una fibra optica
     * B = {[((a^2)-(b^2)) x c+(b^2)]^(1/2)} x betacero
     * betacero = w x (mu x epsi)^(1/2)
     * w = frecuencia angular = 2 x pi x f, f = 5GHz
     * mu = 0.00000125664
     * epsi = 0.00000000000088542  */
	 //Agregue aqui la formula

}

int main()
{
	operacion1();
	
	cout<<endl;
	
	for(int i=0; i<5; i++)
	{
		for(int j=0; j<2; j++)
			operacion2();
	}
	
	cout<<endl;
	
	otros_calculos();
	
	return 0;
}
















