//Librerias
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Encabezado
#include "sala.h"

//Variables globales
int* asientos_totales;
int capacidad_asientos;

int reserva_asiento (int id_persona){

	//Comprobación de errores
	if (asientos_totales == NULL || id_persona <= 0) {
        return -1;
    }

	for (int i = 0; i < capacidad_asientos; i++){
  		if(asientos_totales[i] == -1){
  			
  			asientos_totales[i] = id_persona;
  	
  			return i;
  		}
  	}
  	
	return -1;

}

int libera_asiento(int id_asiento){
	
	//Comprobación de errores
	if (asientos_totales == NULL || id_asiento < 0 || id_asiento >= capacidad_asientos){
  		return -1;
  	}
  
  	if (asientos_totales[id_asiento] > -1){
  		
  		int aux = asientos_totales[id_asiento];	

  		asientos_totales[id_asiento] = -1;
  	
  		return aux;
    }
	
	return -1;
}

int estado_asiento(int id_asiento) {

	//Control de errores
    if (asientos_totales == NULL || id_asiento < 1 || id_asiento > capacidad_asientos) {
        return -1;
    }
    
    if (asientos_totales[id_asiento] >= 0 ) {
    	return asientos_totales[id_asiento];
    }
    
    return 0;
}

int asientos_libres (){

	int asiento_libre = 0;
	
	for(int i = 0; i < capacidad_asientos; i++){
	
		//Corrección de errores
		if(asientos_totales==NULL){
	 		return -1;
	 	}
		
		if(asientos_totales[i] == -1){
			asiento_libre++;
		}
	}
	
	return asiento_libre;

}

int asientos_ocupados (){

	int asiento_ocupado = 0;
	
	for(int i = 0; i < capacidad_asientos; i++){
	
		//Corrección de errores
		if(asientos_totales==NULL){
	 		return -1;
	 	}
		
		if(asientos_totales[i] > -1){
			asiento_ocupado++;
		}
	}
	
	return asiento_ocupado;

}

int capacidad_sala (){

	return asientos_libres() + asientos_ocupados();

}

int crea_sala (int capacidad){
	
	asientos_totales = (int*)malloc( capacidad *sizeof(int));
		
	//Corrección de errores
	if(asientos_totales==NULL){
 		return -1;
 	}
 	
 	capacidad_asientos = capacidad;
 	
 	for(int i=0;i<capacidad; i++){
 		asientos_totales[i]= -1;
	}	
	
	return capacidad;
}

int elimina_sala(){

	//Corrección de errores
	if (asientos_totales == NULL){
		return -1;
	}

	free(asientos_totales);
	asientos_totales = NULL;
	capacidad_asientos = 0;
	return 0;

}
