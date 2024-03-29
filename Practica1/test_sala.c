// test_sala.c
// ===============
// Batería de pruebas de la biblioteca "sala.h/sala.c"
//
#include "sala.h"
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

#define DebeSerCierto(x)	assert(x)
#define DebeSerFalso(x)		assert(!(x))

#define ID_1 1500

void INICIO_TEST (const char* titulo_test)
{
  printf("********** batería de pruebas para %s: ", titulo_test); 
	fflush(stdout);
}

void FIN_TEST (const char* titulo_test)
{
  printf ("********** hecho\n");
}

void test_ReservaBasica()
{
	int mi_asiento;
		
	INICIO_TEST("Reserva básica");
	crea_sala(CAPACIDAD_MAXIMA);
	DebeSerCierto(capacidad_sala()==CAPACIDAD_MAXIMA);
	DebeSerCierto((mi_asiento=reserva_asiento(ID_1))>=0);
	DebeSerCierto((asientos_libres()+asientos_ocupados())==CAPACIDAD_MAXIMA);
	DebeSerCierto(estado_asiento(mi_asiento)>0);
	DebeSerCierto(libera_asiento(mi_asiento)==ID_1);
	DebeSerCierto((asientos_libres()+asientos_ocupados())==CAPACIDAD_MAXIMA);
	elimina_sala();
	FIN_TEST("Reserva básica");
}

void test_ReservaFallida() 
{
    int mi_asiento;

    INICIO_TEST("Reserva fallida");
    mi_asiento = reserva_asiento(ID_1);
    DebeSerFalso(mi_asiento >= 0);
    crea_sala(CAPACIDAD_MAXIMA);
    DebeSerFalso(reserva_asiento(0) >= 0);
    DebeSerFalso(reserva_asiento(-1) >= 0);
    for (int i = 0; i < CAPACIDAD_MAXIMA; i++) {
        reserva_asiento(ID_1);
    }
    DebeSerFalso(reserva_asiento(ID_1) >= 0);
    elimina_sala();
    FIN_TEST("Reserva fallida");
}

void test_Reserva_Libera() {
    int mi_asiento;
    int id_persona = 100;
    int asientosLibresAntes, asientosOcupadosAntes, asientosLibresDespues, asientosOcupadosDespues;

    INICIO_TEST("Reserva y Libera Asiento");
    crea_sala(CAPACIDAD_MAXIMA);
    asientosLibresAntes = asientos_libres();
    asientosOcupadosAntes = asientos_ocupados();
    mi_asiento = reserva_asiento(id_persona);
    DebeSerCierto(mi_asiento >= 0);
    DebeSerCierto(estado_asiento(mi_asiento) == id_persona);
    asientosLibresDespues = asientos_libres();
    asientosOcupadosDespues = asientos_ocupados();
    DebeSerCierto(asientosLibresAntes - 1 == asientosLibresDespues);
    DebeSerCierto(asientosOcupadosAntes + 1 == asientosOcupadosDespues);
    DebeSerCierto(libera_asiento(mi_asiento) == id_persona);
    DebeSerCierto(estado_asiento(mi_asiento) == -1);
    DebeSerCierto(asientos_libres() == asientosLibresAntes);
    DebeSerCierto(asientos_ocupados() == asientosOcupadosAntes);
    elimina_sala();

    FIN_TEST("Reserva y Libera Asiento");
}

void test_reserva_multiple(int npersonas, int* lista_id) {
    INICIO_TEST("Reserva Múltiple de Asientos");
    crea_sala(CAPACIDAD_MAXIMA);
    bool exito = true;
    for (int i = 0; i < npersonas && exito; i++) {
        if (reserva_asiento(lista_id[i]) < 0) {
            exito = false;
            for (int j = 0; j < i; j++) {
                libera_asiento(lista_id[j]);
            }
        }
    }
    DebeSerCierto(exito);
    elimina_sala();
    FIN_TEST("Reserva Múltiple de Asientos");
}


void test_estado_sala() {
    INICIO_TEST("Estado de la Sala");
    crea_sala(CAPACIDAD_MAXIMA);
    reserva_asiento(1);
    reserva_asiento(2);
    DebeSerCierto(estado_asiento(1) > 0);
    DebeSerCierto(estado_asiento(2) > 0);
    elimina_sala();
    FIN_TEST("Estado de la Sala");
}


void test_sentarse(int id) {
    INICIO_TEST("Sentarse en un Asiento");
    crea_sala(CAPACIDAD_MAXIMA);
    int asiento = reserva_asiento(id);
    DebeSerCierto(asiento >= 0);
    elimina_sala();
    FIN_TEST("Sentarse en un Asiento");
}


void test_levantarse(int id_persona) {
    INICIO_TEST("Levantarse de un Asiento");
    crea_sala(CAPACIDAD_MAXIMA);
    int id_asiento = reserva_asiento(id_persona);
    DebeSerCierto(id_asiento >= 0);
    DebeSerCierto(libera_asiento(id_asiento) == id_persona);
    elimina_sala();
    FIN_TEST("Levantarse de un Asiento");
}

void test_asientos_libres() {
    INICIO_TEST("Asientos Libres");
    crea_sala(CAPACIDAD_MAXIMA);
    DebeSerCierto(asientos_libres() == CAPACIDAD_MAXIMA);
    reserva_asiento(1);
    DebeSerCierto(asientos_libres() == CAPACIDAD_MAXIMA - 1);
    DebeSerCierto(estado_asiento(1) == 1);
    elimina_sala();
    FIN_TEST("Asientos Libres");
}

void test_PruebasDeLimites() {
    INICIO_TEST("Pruebas de Límites");
    crea_sala(CAPACIDAD_MAXIMA);
    DebeSerFalso(reserva_asiento(ID_1) >= CAPACIDAD_MAXIMA + 1);
    DebeSerFalso(libera_asiento(CAPACIDAD_MAXIMA + 1) >= 0);
    DebeSerFalso(libera_asiento(0) >= 0);
    elimina_sala();
    FIN_TEST("Pruebas de Límites");
}

void test_CreaSalaConEntradaNegativa() {
    INICIO_TEST("Crea Sala con Entrada Negativa o Cero");
    DebeSerFalso(crea_sala(-1) >= 0);
    DebeSerFalso(crea_sala(0) >= 0);
    FIN_TEST("Crea Sala con Entrada Negativa o Cero");
}

void test_LlenarSala_VaciarSala(){
    INICIO_TEST("Llenar Sala y luego Vaciarla");
    crea_sala(CAPACIDAD_MAXIMA);
    for (int i = 1; i <= CAPACIDAD_MAXIMA; i++) {
        reserva_asiento(i);
    }
    DebeSerCierto(asientos_libres() == 0);
    DebeSerCierto(asientos_ocupados() == CAPACIDAD_MAXIMA);
    for (int i = 1; i <= CAPACIDAD_MAXIMA; i++) {
        libera_asiento(i);
    }
    DebeSerCierto(asientos_libres() == CAPACIDAD_MAXIMA);
    DebeSerCierto(asientos_ocupados() == 0);

    elimina_sala();
    FIN_TEST("Llenar Sala y luego Vaciarla");
}

void test_ReservaEnSalaLlena() {
    int resultado;
    INICIO_TEST("Reserva en Sala Llena");
    crea_sala(CAPACIDAD_MAXIMA);
    for (int i = 0; i < CAPACIDAD_MAXIMA; i++) {
        reserva_asiento(i+1);
    }
    resultado = reserva_asiento(CAPACIDAD_MAXIMA + 1);
    DebeSerCierto(resultado == -1);
    elimina_sala();
    FIN_TEST("Reserva en Sala Llena");
}

void test_LiberarAsientoNoOcupado() {
    int resultado;
    INICIO_TEST("Liberar Asiento No Ocupado");
    crea_sala(CAPACIDAD_MAXIMA);
    resultado = libera_asiento(1);
    DebeSerCierto(resultado == -1);
    elimina_sala();
    FIN_TEST("Liberar Asiento No Ocupado");
}

void ejecuta_tests ()
{
	test_ReservaBasica();
    test_ReservaFallida();
	test_Reserva_Libera();
    test_estado_sala();
    test_sentarse(123);
    test_levantarse(123);
    test_asientos_libres();
    int lista_id[] = {1, 2, 3, 4, 5};
    test_reserva_multiple(5, lista_id);
    test_PruebasDeLimites();
    test_CreaSalaConEntradaNegativa();
    test_LlenarSala_VaciarSala();
    test_ReservaEnSalaLlena();
    test_LiberarAsientoNoOcupado();
}

int main()
{
	puts("Iniciando tests...");
	
	ejecuta_tests();
	
	puts("Batería de test completa.");
}