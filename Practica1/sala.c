#include "sala.h"
#include <stdlib.h>

static int *asientos = NULL;
static int capacidad_actual = 0;
static int asientosOcupados = 0;

int crea_sala(int capacidad) {
    if (asientos != NULL || capacidad <= 0) {
        return -1;
    }
    asientos = (int *)malloc(capacidad * sizeof(int));
    if (asientos == NULL) {
        return -1;
    }
    for (int i = 0; i < capacidad; i++) {
        asientos[i] = -1;
    }
    capacidad_actual = capacidad;
    asientosOcupados = 0;
    return capacidad;
}

int elimina_sala() {
    if (asientos == NULL) {
        return -1;
    }
    free(asientos);
    asientos = NULL;
    capacidad_actual = 0;
    asientosOcupados = 0;
    return 0;
}

int reserva_asiento(int id_persona) {
    if (asientos == NULL || id_persona <= 0) {
        return -1;
    }
    for (int i = 0; i < capacidad_actual; i++) {
        if (asientos[i] == -1) {
            asientos[i] = id_persona;
            asientosOcupados++;
            return i + 1;
        }
    }
    return -1;
}

int libera_asiento(int id_asiento) {
    if (asientos == NULL || id_asiento < 1 || id_asiento > capacidad_actual) {
        return -1;
    }
    int index = id_asiento - 1;
    if (asientos[index] == -1) {
        return -1;
    }
    int id_persona = asientos[index];
    asientos[index] = -1;
    asientosOcupados--;
    return id_persona;
}

int estado_asiento(int id_asiento) {
    if (asientos == NULL || id_asiento < 1 || id_asiento > capacidad_actual) {
        return -1;
    }
    int index = id_asiento - 1;
    return asientos[index];
}

int asientos_libres() {
    if (asientos == NULL) {
        return -1;
    }
    return capacidad_actual - asientosOcupados;
}

int asientos_ocupados() {
    if (asientos == NULL) {
        return -1;
    }
    return asientosOcupados;
}

int capacidad_sala() {
    return capacidad_actual;
}
