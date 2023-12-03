/*****************************************************************************************************************
	UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO
	FACULTAD DE ESTUDIOS SUPERIORES -ARAGON-

	Computadoras y programacion. 
	(c) Ponga su nombre y numero de cuenta aqui.
	
	Quiso decir: Programa principal de la aplicacion de la distancia de Levenstein.
	
******************************************************************************************************************/

#include <stdlib.h>
#include "stdafx.h"
#include <string.h>
#include "corrector.h"
#include <ctype.h>
#define LONGI 32
char abecedario[LONGI + 6] = "abcdefghijklmnopqrstuvwxyzáéíóú";
                  
//Funciones publicas del proyecto
/*****************************************************************************************************************
	DICCIONARIO: Esta funcion crea el diccionario completo
	char *	szNombre				:	Nombre del archivo de donde se sacaran las palabras del diccionario	
	char	szPalabras[][TAMTOKEN]	:	Arreglo con las palabras completas del diccionario
	int		iEstadisticas[]			:	Arreglo con el numero de veces que aparecen las palabras en el diccionario
	int &	iNumElementos			:	Numero de elementos en el diccionario
******************************************************************************************************************/
void Diccionario(char* szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos)
{
	FILE* fpDicc;
	int i;
	iNumElementos = 0;
	char caracter, palabra[TAMTOKEN];

	//Arreglo de estadisticas
	for (i = 0; i < NUMPALABRAS; i++)
	iEstadisticas[i] = 0;

	//Abrir archivo//
	fopen_s(&fp, szNombre, "r");

	int cont = 0;
	char puntuacion[] = " \t\n\r.,;() ";

	//Verificar que el archivo si abrio//
	if (fp == NULL)
		return;
	
	while ((caracter = fgetc(fp)) != EOF) {

		//Creamos una marca para saber si es un signo de puntuacion o no
		bool esPuntuacion = true;

		//Pasar mayusculas a minusculas//

		caracter = tolower(caracter);

		//Palabras con signo de puntuacion//
		for (i = 0; i < strlen(puntuacion); i++)

			//Comparar si el caracter es un signo de puntuacion
			if (puntuacion[i] == caracter)
				esPuntuacion = false;

		if (cont < TAMTOKEN && esPuntuacion) {
			palabra[cont++] = caracter;
			continue;
		}

		else if (cont == 0)
			continue;

		else if (cont == 1 && esPuntuacion) {
			cont = 0;
			continue;
		}

		//Marcar un espacio cuando encuentre un signo de puntuacion
		palabra[cont] = '\0';

		//Abecedario y puntuacion
		for (i = 0; i < iNumElementos && !esPuntuacion; i++) {

			//Comparacion de las palabras en el diccionario//
			if (strcmp(szPalabras[i], palabra) == 0) {
				//Hasta que se forme una palabra//
				iEstadisticas[i]++;
				esPuntuacion = true;

			}
		}
	
	 //Si es diferente de la marca//
	 if(!esPuntuacion) {
		//Pasar las palabras 
		strcpy_s(szPalabaras[iNumElementos], palabra);
		iEstadisticas[iNumElementos++]++;
	 }//Para retornar
	 cont = 0;
	
	}//Fin del documento o while//
	 fclose(fp);

     //Ordenamiento por el Metodo burbuja//
	 for (int j=0; j<iNumElementos-1; j++) > 0) {

		 for (i = j + 1; i < iNumElementos; i++) {

			 if(strcmp(szPalabras[j], szPalabras[i]) > 0) {
				strcpy_s(palabra, szPalabras[j]);
			    strcpy_s(szPalabras[j], szPalabras[i]);
				strcpy_s(szPalabras[i], palabra);
				cont = iEstadisticas[j];
				iEstadisticas[j] = iEstadisticas[i];
				iEstadisticas[i] = cont;
		
			 }
		 }
    }
 	 
}

/*****************************************************************************************************************
	ListaCandidatas: Esta funcion recupera desde el diccionario las palabras validas y su peso
	Regresa las palabras ordenadas por su peso
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
******************************************************************************************************************/
void	ListaCandidatas		(
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
{

	//Sustituya estas lineas por su código
	strcpy(szListaFinal[0], szPalabrasSugeridas[ 0] ); //la palabra candidata
	iPeso[0] = iEstadisticas[0];			// el peso de la palabra candidata
	
	iNumLista = 1;							//Una sola palabra candidata
}

/*****************************************************************************************************************
	ClonaPalabras: toma una palabra y obtiene todas las combinaciones y permutaciones requeridas por el metodo
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
******************************************************************************************************************/
void	ClonaPalabras(
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
{
	//Sustituya estas lineas por su código
	
	char aux[TAMTOKEN] iNumSugeridas = 0;
