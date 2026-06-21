#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "funciones.h"

int main() {
    FILE *archivo = fopen("vehiculos.dat", "wb");
    if (!archivo) {
        printf("Error al crear el archivo de vehiculos.\n");
        return 1;
    }

    srand(time(NULL));

    char *marcas[] = {"Chevrolet", "Toyota", "Ford", "Nissan", "Kia", "Hyundai", "Mazda", "Honda"};
    char *tipos[] = {"Camioneta", "Sedan", "SUV", "Hatchback"};
    char *condiciones[] = {"Nuevo", "Usado"};

    char *modelos_chevrolet[] = {"Silverado", "Dmax", "Colorado", "Spark", "Sail"};
    char *modelos_toyota[] = {"Hilux", "Corolla", "Yaris", "RAV4", "Fortuner"};
    char *modelos_ford[] = {"F150", "Explorer", "Escape", "Focus", "Fiesta"};
    char *modelos_nissan[] = {"Frontier", "Versa", "Sentra", "X-Trail", "Qashqai"};
    char *modelos_kia[] = {"Rio", "Picanto", "Sportage", "Sorento", "Cerato"};
    char *modelos_hyundai[] = {"Accent", "Tucson", "Santa Fe", "Elantra", "i10"};
    char *modelos_mazda[] = {"BT-50", "Mazda3", "CX-5", "Mazda2", "CX-9"};
    char *modelos_honda[] = {"Civic", "CR-V", "Accord", "Pilot", "Fit"};

    char **modelos_por_marca[] = {modelos_chevrolet, modelos_toyota, modelos_ford, modelos_nissan, modelos_kia, modelos_hyundai, modelos_mazda, modelos_honda};

    for (int i = 1; i <= 50; i++) {
        Vehiculo v;
        v.id = i;
        
        int marca_idx = rand() % 8;
        strcpy(v.marca, marcas[marca_idx]);
        
        int modelo_idx = rand() % 5;
        strcpy(v.modelo, modelos_por_marca[marca_idx][modelo_idx]);
        
        strcpy(v.tipo, tipos[rand() % 4]);
        strcpy(v.condicion, condiciones[rand() % 2]);
        
        v.precio = 5000.0f + (rand() % 35000);
        v.disponible = 1;
        
        fwrite(&v, sizeof(Vehiculo), 1, archivo);
    }

    fclose(archivo);

    FILE *f_clientes = fopen("clientes.dat", "wb");
    if (f_clientes) fclose(f_clientes);
    
    FILE *f_ventas = fopen("ventas.dat", "wb");
    if (f_ventas) fclose(f_ventas);

    printf("Base de datos de 50 vehiculos generada exitosamente en 'vehiculos.dat'.\n");
    printf("Archivos de ventas y clientes fueron reiniciados.\n");
    return 0;
}
