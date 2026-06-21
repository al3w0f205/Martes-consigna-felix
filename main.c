#include <stdio.h>
#include "funciones.h"

int main() {
    int opcion;
    
    do {
        mostrar_menu();
        opcion = leer_entero_rango("Ingrese una opcion: ", 1, 6);

        switch (opcion) {
            case 1: 
                ver_inventario();
                break;
            case 2: 
                buscar_vehiculo();
                break;
            case 3: 
                registrar_venta();
                break;
            case 4: 
                ver_historial_ventas();
                break;
            case 5:
                gestionar_inventario();
                break;
            case 6: 
                printf("\nGuardando datos...\n");
                printf("Saliendo del Sistema de Gestion - Ruedas de Oro. Hasta pronto!\n");
                break;
            default: 
                printf("Opcion invalida. Intente de nuevo.\n");
        }
    } while (opcion != 6);
    
    return 0;
}
