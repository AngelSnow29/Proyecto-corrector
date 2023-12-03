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
	fopen_s(&fpDicc, szNombre, "r");

	int cont = 0;
	char puntuacion[] = " \t\n\r.,;() ";

	//Verificar que el archivo sí abrió//
	if (fpDicc == NULL)
		return;

	while ((caracter = fgetc(fpDicc)) != EOF) {

		//Creamos una marca para saber si es un signo de puntuación o no
		bool esPuntuacion = true;

		//Pasar mayúsculas a minúsculas//

		char caracterMinuscula = tolower(caracter);

		//Palabras con signo de puntuación//
		for (i = 0; i < strlen(puntuacion); i++)

			//Comparar si el caracter es un signo de puntuación
			if (puntuacion[i] == caracter)
				esPuntuacion = false;

		if (cont < TAMTOKEN && esPuntuacion) {
			palabra[cont++] = caracterMinuscula;
			continue;
		}

		else if (cont == 0)
			continue;

		else if (cont == 1 && esPuntuacion) {
			cont = 0;
			continue;
		}

		//Marcar un espacio cuando encuentre un signo de puntuación
		palabra[cont] = '\0';

		//Abecedario y puntuación
		for (i = 0; i < iNumElementos && !esPuntuacion; i++) {

			//Comparación de las palabras en el diccionario//
			if (strcmp(szPalabras[i], palabra) == 0) {
				//Hasta que se forme una palabra//
				iEstadisticas[i]++;
				esPuntuacion = true;

			}
		}

		//Si es diferente de la marca//
		if (!esPuntuacion) {
			//Pasar las palabras 
			strcpy_s(szPalabras[iNumElementos], palabra);
			iEstadisticas[iNumElementos++]++;
		} //Para retornar
		cont = 0;

	} //Fin del documento o while//
	fclose(fpDicc);

	//Ordenamiento por el Método burbuja//
	for (int j = 0; j < iNumElementos - 1; j++) {
		for (i = j + 1; i < iNumElementos; i++) {
			if (strcmp(szPalabras[j], szPalabras[i]) > 0) {
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
void	ListaCandidatas(
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int& iNumLista)							//Numero de elementos en la szListaFinal
{

	iNumLista = 0;

	for (int i = 0; i < iNumSugeridas; i++) {
		for (int j = 0; j < iNumElementos; j++) {
			// Comparar palabras del diccionario con las palabras clonadas
			if (strcmp(szPalabrasSugeridas[i], szPalabras[j]) == 0) {
				// Verificar si la palabra ya está en la lista final
				bool palabraEnListaFinal = false;
				for (int k = 0; k < iNumLista && !palabraEnListaFinal; k++) {
					// Comparar palabras del diccionario con la lista final de palabras a sugerir
					if (strcmp(szListaFinal[k], szPalabras[j]) == 0) {
						palabraEnListaFinal = true;
					}
				}

				// Pasar de la lista de palabras clonadas a la lista final de palabras a sugerir
				if (palabraEnListaFinal) continue;

				strcpy_s(szListaFinal[iNumLista], szPalabrasSugeridas[i]);
				iPeso[iNumLista++] = iEstadisticas[j];
			}
		}
	}

	// Ordenar por peso de forma descendente
	for (int i = 0; i < iNumLista; i++) {
		for (int j = 0; j < iNumLista - 1; j++) {
			// Ordenar la lista final y sus pesos
			if (iPeso[j] < iPeso[j + 1]) {
				// Variables para el método de las candidatas
				int pesoTemporal; char palabraTemporal[TAMTOKEN];
				strcpy_s(palabraTemporal, szListaFinal[j + 1]); pesoTemporal = iPeso[j + 1];
				strcpy_s(szListaFinal[j + 1], szListaFinal[j]); iPeso[j + 1] = iPeso[j];
				strcpy_s(szListaFinal[j], palabraTemporal); iPeso[j] = pesoTemporal;
			}
		}
	}
}

	//iNumLista = 0;
	   // for (int j = 0; j < iNumLista - 1; j++) {
		//	for (int j = 0; j < iNumElementos; j++) {
				//Comparar palabras del diccionario con las palabras clonadas//
			//	if (strcmp(szPalabrasSugeridas[i], szPalabras[j]) == 0) {
					//Verificar si la palabra ya esta en la lista final/
				//	bool palabraEnListaFinal = false;
					//for (int k = 0; k < iNumLista && !palabraEnListaFinal; k++)
					//Comparar palabras del diccionario con la lista final de palabras a sugerir//
					//	if (strcmp(szListaFinal[K], szPalabras[j]) == 0)
					//		palabraEnListaFinal = true;
					//Pasamos de la lista de palabras clondas a la lista final de palabras a sugerir//
					//if (palabraEnListaFinal) continue;
					//strcpy_s(szListaFinal[iNumLista], szPalabrasSugeridas[i]);
					//iPeso[iNumLista++] = iEstadisticas[j];

				//}
			//}
		//}

	//Ordenar por peso de forma descendente
	//for(int i=0; i < iNumLista; i++) {
		//for(int j = 0; iNumLista - 1; j++) {
			////Ordenar la lista final y sus pesos
			//if (iPeso[j] < iPeso[j + 1]) {
				////Variables para el metodo de las candidatas//
				//int pesoTemporal; char palabraTemporal[50];
				//strcpy_s(palabraTemporal, szListaFinal[j + 1]); pesoTemporal = iPeso[j + 1];
				//strcpy_s(szListaFinal[j + 1], szListaFinal[j]); iPeso[j + 1] = iPeso[j];
				//strcpy_s(szListaFinal[j], palabraTemporal); iPeso[j] = pesoTemporal;
			//}
		//}
	//}

//}
   
/*****************************************************************************************************************
	ClonaPalabras: toma una palabra y obtiene todas las combinaciones y permutaciones requeridas por el metodo
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
******************************************************************************************************************/

void ClonaPalabras(
	char* szPalabraLeida,						// Palabra a clonar
	char szPalabrasSugeridas[][TAMTOKEN], 	  //Lista de palabras clonadas
	int& iNumSugeridas)					  //Numero de elementos en la lista
{
	char palabraClonada[TAMTOKEN];

	// Genera palabras reemplazando cada letra con todas las letras del abecedario
	for (int i = 0; i < strlen(szPalabraLeida); i++) {
		for (int j = 0; j < LONGI; j++) {
			szPalabraLeida[i] = abecedario[j];
			strcpy_s(szPalabrasSugeridas[iNumSugeridas++], szPalabraLeida);
		}
		szPalabraLeida[i] = szPalabraLeida[i];
	}

	// Genera palabras insertando cada letra del abecedario en todas las partes posibles
	for (int k = 0; k <= strlen(szPalabraLeida); k++) {
		for (int i = 0; i < LONGI; i++) {
			char temp = szPalabraLeida[k];
			szPalabraLeida[k] = abecedario[i];
			strcpy_s(szPalabrasSugeridas[iNumSugeridas++], szPalabraLeida);
			// Restaura la letra original
			szPalabraLeida[k] = temp;
		}
	}

	// Genera palabras eliminando la letra de la palabra original
	for (int i = 0; i < strlen(szPalabraLeida) && strlen(szPalabraLeida) != 1; i++) {
		char temp = szPalabraLeida[i];
		for (int j = i; j < strlen(szPalabraLeida) - 1; j++) {
			szPalabraLeida[j] = szPalabraLeida[j + 1];
		}
		szPalabraLeida[strlen(szPalabraLeida) - 1] = '\0';
		strcpy_s(szPalabrasSugeridas[iNumSugeridas++], szPalabraLeida);
		// Restaura la letra original
		szPalabraLeida[i] = temp;
	}

	// Genera palabras intercambiando letras 
	for (int i = 0; i < strlen(szPalabraLeida) - 1; i++) {
		// Intercambia las letras adyacentes 
		char temp = szPalabraLeida[i];
		szPalabraLeida[i] = szPalabraLeida[i + 1];
		szPalabraLeida[i + 1] = temp;
		strcpy_s(szPalabrasSugeridas[iNumSugeridas++], szPalabraLeida);
		// Restaura la palabra original
		szPalabraLeida[i + 1] = szPalabraLeida[i];
		szPalabraLeida[i] = temp;
	}

	// Ordena las palabras con el metodo burbuja
	for (int j = 0; j < iNumSugeridas - 1; j++) {
		for (int i = j + 1; i < iNumSugeridas; i++) {
			if (strcmp(szPalabrasSugeridas[j], szPalabrasSugeridas[i]) > 0) {
				char temp[TAMTOKEN];
				strcpy_s(temp, szPalabrasSugeridas[j]);
				strcpy_s(szPalabrasSugeridas[j], szPalabrasSugeridas[i]);
				strcpy_s(szPalabrasSugeridas[i], temp);
			}
		}
	}
}
	
	
// Palabra original
//strcpy_s(palabraClonada, szPalabraLeida);

// Pasar el abecedario en cada caracter
//for (int i = 0; i < strlen(szPalabraLeida); i++) {
	//for (int j = 0; j < LONGITUD; j++) {
		//palabraClonada[i] = abecedario[j];
		//strcpy_s(szPalabrasSugeridas[iNumSugeridas++], palabraClonada);
	//palabraClonada[i] = szPalabraLeida[i];

// Generar palabras con el abecedario
//for (int k = 1; k < strlen(szPalabraLeida) + 1; k++) {
	//palabraClonada[k] = szPalabraLeida[k - 1];
	//for (int i = 0; i < LONGITUD; i++) {
		//palabraClonada[k - 1] = abecedario[i];
		//strcpy_s(szPalabrasSugeridas[iNumSugeridas++], palabraClonada);
	
	//palabraClonada[k] = szPalabraLeida[k - 1];


// Eliminar los caracteres
//for (int i = 0; i < strlen(szPalabraLeida) && strlen(szPalabraLeida) != 1; i++) {
	//for (int j = 0; j < strlen(szPalabraLeida); j++) {
		//if (j != i)
			//palabraClonada[conta++] = szPalabraLeida[j];
	
	//palabraClonada[conta] = '\0';
	//strcpy_s(szPalabrasSugeridas[iNumSugeridas++], palabraClonada);
	//strcpy_s(palabraClonada, szPalabraLeida);
	//conta = 0;


// Generar palabras
//for (int i = 0; i < strlen(szPalabraLeida) - 1; i++) {
	//palabraClonada[i] = szPalabraLeida[i + 1];
	//palabraClonada[i + 1] = szPalabraLeida[i];
	//strcpy_s(szPalabrasSugeridas[iNumSugeridas++], palabraClonada);
	//strcpy_s(palabraClonada, szPalabraLeida);


//incluir la palabra original en las sugerencias
//strcpy_s(szPalabrasSugeridas[iNumSugeridas++], szPalabraLeida);

// Ordenar las palabras con el metodo burbuja
//for (int j = 0; j < iNumSugeridas - 1; j++) {
	//for (int i = j + 1; i < iNumSugeridas; i++) {
		//if (strcmp(szPalabrasSugeridas[j], szPalabrasSugeridas[i]) > 0) {
			//strcpy_s(palabraClonada, szPalabrasSugeridas[j]);
			//strcpy_s(szPalabrasSugeridas[j], szPalabrasSugeridas[i]);
			//strcpy_s(szPalabrasSugeridas[i], palabraClonada);
		
