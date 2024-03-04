// test_sala.c
// ===============
// Batería de pruebas de la biblioteca "sala"

#ifndef TEST
#include "sala.h"
#endif

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define DebeSerCierto(x)	assert(x)
#define DebeSerFalso(x)		assert(!(x))

void INICIO_TEST (const char* titulo_test)
{
	printf("- batería de pruebas para %s: ", titulo_test); 
	fflush(stdout);
}

void FIN_TEST (const char* titulo_test)
{
  printf ("hecho\n");
}

void test_reserva_asiento()
{
	int mi_asiento;
	#define CAPACIDAD_CUYAS 500
	#define ID_1 1500

	INICIO_TEST("+++ Reserva básica");
	crea_sala(CAPACIDAD_CUYAS);
	DebeSerCierto(capacidad_sala()==CAPACIDAD_CUYAS);
	DebeSerCierto((mi_asiento=reserva_asiento(ID_1))>=0);
	DebeSerCierto((asientos_libres()+asientos_ocupados())==CAPACIDAD_CUYAS);
	DebeSerCierto(estado_asiento(mi_asiento)==-1);
	DebeSerCierto(libera_asiento(mi_asiento)==ID_1);
	DebeSerCierto((asientos_libres()+asientos_ocupados())==CAPACIDAD_CUYAS);
	elimina_sala();
	FIN_TEST("Reserva básica");
}

void test_estado_asiento(){

	#define CAPACIDAD_CUYAS 500
	#define ID_1 1500
	int mi_asiento, asiento_libre, asiento_ocupado;
	
	INICIO_TEST("+++ Estado asiento");
	
	crea_sala(CAPACIDAD_CUYAS);
	
	DebeSerCierto(capacidad_sala()==CAPACIDAD_CUYAS);
	
	
	DebeSerCierto((asiento_libre = asientos_libres())==CAPACIDAD_CUYAS);
	
	int id = 900, id2 = 439;
	DebeSerCierto((mi_asiento=reserva_asiento(id))>=0);
	DebeSerFalso(reserva_asiento(mi_asiento)==id);
	DebeSerCierto((mi_asiento=reserva_asiento(id2))>=0);
	
	DebeSerCierto((asiento_ocupado = asientos_ocupados())!=CAPACIDAD_CUYAS);
	
	DebeSerCierto((asiento_libre = asientos_libres()));
	
	DebeSerFalso(libera_asiento(mi_asiento)==id);
	DebeSerCierto((asiento_ocupado = asientos_ocupados())!=CAPACIDAD_CUYAS);
	DebeSerFalso(libera_asiento(mi_asiento)!=-1);
	DebeSerFalso(libera_asiento(-3)!=-1);

	DebeSerCierto((asiento_libre = asientos_libres()));
	
	elimina_sala();

	FIN_TEST("Estado asiento");
}

void test_crea_sala(int capacidad) {
	int resultado; 

	INICIO_TEST("+++ Crea Sala");

    resultado = crea_sala(capacidad);
    
    DebeSerCierto(resultado == capacidad);

    FIN_TEST("+++ Terminado crea sala");

}

void test_elimina_sala() {
    int resultado;

    INICIO_TEST ("+++ ELimina Sala");
    
    resultado = elimina_sala();
    
    DebeSerCierto(resultado == 0); 
    
    FIN_TEST ("+++ Terminado elimina sala");
}

void ejecuta_tests ()
{
	
    test_reserva_asiento();
    test_estado_asiento();
	test_crea_sala(10);
	test_elimina_sala();
	
}

main()
{
	puts("Iniciando tests...");
	
	ejecuta_tests();
	
	puts("Batería de test completa.");
	
	exit(0);
}
