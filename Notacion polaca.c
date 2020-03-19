#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int contador=0,i; //contador servirá para recorrer el arreglo.
int JerarquiaTope,JerarquiaCaracter;
int TamFrase,tope_pila=-1,tope_aux=-1;	//tope en -1 ya que aún no existe.

//JERARQUÍA
/*Podría usarse un switch que retorne un valor específico para compararlo con la prioridad del tope.
// Función que devolverá un valor numérico para asignar que operación se insertará. Debido al funcionamiento
de la notación Polaca, y para que funcione correctamente, el paréntesis no tiene jerarquía.*/
int Jerarquia(char J)
	{
		if((J=='(')||(J==')')) return 0;
		else if((J=='/')||(J=='*')) return 2;	
			else if((J=='+')||(J=='-')) return 1;
	}

//Función para determinar si lo ingresado corresponde a un caracter válido. Consultada de internet.
int esOperando(char ch) 
	{ 
	/*Se establece que solo se pueden ingresar letras de la A a la Z y numeros del 0 al 9 para ser operando, 
	los signos aritméticos para ser operador, y los paréntesis que darán prioridad a las operaciones.
	Funciona asignando un valor numerico dependiendo de la condición que se cumpla para posteriormente
	con ayuda de un switch, proceder de la manera adecuada.*/
		if ((ch >= 'a' && ch <= 'z')||(ch >= '0' && ch <= '9')||(ch>= 'A' && ch <= 'Z')) return 1;
		else if ((ch=='+')||(ch=='-')||(ch=='*')||(ch=='/')) return 2;
			else if (ch=='(') return 3;
				else if (ch==')') return 4;
					else return 0;
	} 

int main()
	{
		char pila[TamFrase+1], aux[TamFrase+1];	//Creación de las 2 pilas.
		char frase[50],*ArregloDinamico, CaracterComparar, Caracter; //variables para iniciar a procesar la expresión.
		printf("Ingrese la expresion a convertir:");
		scanf("%s",&frase); // Guardado de la expresión.
		TamFrase=strlen(frase);	//Contará el tamaño de la expresión ingresada.
		ArregloDinamico=(char*)malloc(TamFrase*sizeof(char)); //Se crea la pila del tamaño justo para la expresión
		strcpy(ArregloDinamico,frase);
		if (ArregloDinamico!=NULL)	//Si el equipo permite guardar la expresión...
			{
				for (contador;contador<=TamFrase;contador++)	//Permite  recorrer el arreglo caracter por caracter.
					{
						CaracterComparar=esOperando(ArregloDinamico[contador]); //Le asigna un valor númerico al resultado de la función.
						switch(CaracterComparar)
							{
								case 0:
									//printf("No es posible realizar la operacion");	//Se ingresó un carácter no válido.
									contador=TamFrase+1;
								break;
								case 1:
										tope_pila++;
										pila[tope_pila]=ArregloDinamico[contador];		//push(pila,caracter)
										printf("operando\n");
								break;
								case 2:
									if (tope_aux==-1)
										{
											tope_aux++;
											aux[tope_aux]=ArregloDinamico[contador];	
										}
									else
										{
											JerarquiaTope=Jerarquia(aux[tope_aux]);
											JerarquiaCaracter=Jerarquia(ArregloDinamico[contador]);  //Define las respectivas jerarquías
											while (JerarquiaTope>=JerarquiaCaracter)
												{
													Caracter=aux[tope_aux];	//pop (aux)
													tope_aux--;
													tope_pila++;
													pila[tope_pila]=Caracter;	//push(pila,caracter)
													JerarquiaTope=Jerarquia(aux[tope_aux]);
													printf("%i",JerarquiaTope);	
												}
											tope_pila++;
											pila[tope_pila]=ArregloDinamico[contador];
										}
									printf("operador\n");
								break;
								case 3:
									tope_aux++;
									aux[tope_aux]=ArregloDinamico[contador];	//push(aux,caracter)
									printf("Parentesis\n");
								break;
								case 4:
									while((aux[tope_aux]!='(')&&(tope_aux>=0))
										{
											Caracter=aux[tope_aux];	//pop (aux)
											tope_aux--;
											tope_pila++;
											pila[tope_pila]=Caracter;	//push(pila,caracter)
										}
									tope_aux--;			//permite respetar los paréntesis.
									printf("Cerrando\n");
								break;
								default:
									printf("Si llegas a ver esto, felicidades, rompiste mi programa ¬_¬");
								break;
							}
					}
			free(ArregloDinamico);	
			}	
		else 
			{
				printf("Error de memoria.");
				return 0;
			}
		while (tope_aux>=0)
			{
				Caracter=aux[tope_aux];	//pop (aux)
				tope_aux--;
				tope_pila++;
				pila[tope_pila]=Caracter;	//push(pila,caracter)
			}
		printf("\n\n\n");
		//Mostrar contenido de pila
		for (i=tope_pila;i>=0;i--)
			{
				printf("%c",pila[i]);
			}
		getchar();
		return 0;
	}

