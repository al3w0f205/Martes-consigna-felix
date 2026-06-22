#include <stdio.h>
#include <string.h>
#include "funciones.h"

void leer_cadena(char *cadena, int longitud) {
    fgets(cadena, longitud, stdin);
    cadena[strcspn(cadena, "\n")] = 0;
}

int son_iguales_ignorando_mayusculas(const char *cadena1, const char *cadena2) {
    for (; *cadena1 && *cadena2; cadena1++, cadena2++) {
        char c1;
        char c2;
        
        if (*cadena1 >= 'A' && *cadena1 <= 'Z') {
            c1 = *cadena1 + ('a' - 'A');
        } else {
            c1 = *cadena1;
        }
        
        if (*cadena2 >= 'A' && *cadena2 <= 'Z') {
            c2 = *cadena2 + ('a' - 'A');
        } else {
            c2 = *cadena2;
        }
        
        if (c1 != c2) {
            return 0;
        }
    }
    return (*cadena1 == '\0' && *cadena2 == '\0');
}

int leer_entero_rango(const char *mensaje, int min, int max) {
    int valor, leidos;
    do {
        printf("%s", mensaje);
        leidos = scanf("%d", &valor);
        while (getchar() != '\n');
        if (leidos != 1 || valor < min || valor > max) {
            printf("Error: Ingrese un numero valido entre %d y %d.\n", min, max);
        }
    } while (leidos != 1 || valor < min || valor > max);
    return valor;
}

int leer_entero_positivo(const char *mensaje) {
    int valor, leidos;
    do {
        printf("%s", mensaje);
        leidos = scanf("%d", &valor);
        while (getchar() != '\n');
        if (leidos != 1 || valor <= 0) {
            printf("Error: Ingrese un numero entero positivo.\n");
        }
    } while (leidos != 1 || valor <= 0);
    return valor;
}

float leer_flotante_positivo(const char *mensaje) {
    float valor;
    int leidos;
    do {
        printf("%s", mensaje);
        leidos = scanf("%f", &valor);
        while (getchar() != '\n');
        if (leidos != 1 || valor <= 0.0f) {
            printf("Error: Ingrese un valor numerico positivo.\n");
        }
    } while (leidos != 1 || valor <= 0.0f);
    return valor;
}

void mostrar_menu() {
    printf("\n------------------------------------------\n");
    printf("   SISTEMA DE GESTION - RUEDAS DE ORO\n");
    printf("------------------------------------------\n");
    printf("1. Ver Inventario de Vehiculos\n");
    printf("2. Buscar Vehiculo (por preferencias)\n");
    printf("3. Registrar Venta\n");
    printf("4. Ver Historial de Ventas\n");
    printf("5. Gestionar Inventario\n");
    printf("6. Salir\n");
    printf("------------------------------------------\n");
}

void ver_inventario() {
    FILE *archivo = fopen("vehiculos.dat", "rb");
    Vehiculo v;

    if (!archivo) {
        printf("Error: No se pudo abrir el archivo de vehiculos o no hay datos registrados.\n");
        return;
    }

    printf("\n--- Inventario de Vehiculos ---\n");
    printf("ID\tMarca\t\tModelo\t\tTipo\t\tCondicion\tPrecio\t\tDisponible\n");
    printf("----------------------------------------------------------------------------------------------------\n");
    
    while (fread(&v, sizeof(Vehiculo), 1, archivo) == 1) {
        printf("%d\t%-15s\t%-15s\t%-15s\t%-15s\t$%.2f\t%s\n", 
               v.id, v.marca, v.modelo, v.tipo, v.condicion, v.precio, v.disponible ? "SI" : "NO");
    }
    
    fclose(archivo);
}

void buscar_vehiculo() {
    char tipo[50], marca[50], condicion[50];
    float presupuesto;
    FILE *archivo;
    Vehiculo v;
    int encontrados = 0;
    char tipos_disp[20][50]; int n_tipos = 0;
    char marcas_disp[20][50]; int n_marcas = 0;
    char cond_disp[5][50]; int n_cond = 0;

    archivo = fopen("vehiculos.dat", "rb");
    if (!archivo) {
        printf("Error al abrir el archivo de vehiculos o no existe inventario.\n");
        return;
    }

    while (fread(&v, sizeof(Vehiculo), 1, archivo) == 1) {
        if (v.disponible) {
            int existe_tipo = 0, existe_marca = 0, existe_cond = 0;
            for(int i=0; i<n_tipos; i++) if(son_iguales_ignorando_mayusculas(tipos_disp[i], v.tipo)) existe_tipo = 1;
            for(int i=0; i<n_marcas; i++) if(son_iguales_ignorando_mayusculas(marcas_disp[i], v.marca)) existe_marca = 1;
            for(int i=0; i<n_cond; i++) if(son_iguales_ignorando_mayusculas(cond_disp[i], v.condicion)) existe_cond = 1;

            if(!existe_tipo && n_tipos < 20) strcpy(tipos_disp[n_tipos++], v.tipo);
            if(!existe_marca && n_marcas < 20) strcpy(marcas_disp[n_marcas++], v.marca);
            if(!existe_cond && n_cond < 5) strcpy(cond_disp[n_cond++], v.condicion);
        }
    }

    printf("\n--- Opciones disponibles en el inventario ---\n");
    printf("Tipos: ");
    for(int i=0; i<n_tipos; i++) printf("%s%s", tipos_disp[i], i<n_tipos-1 ? ", " : "\n");
    printf("Marcas: ");
    for(int i=0; i<n_marcas; i++) printf("%s%s", marcas_disp[i], i<n_marcas-1 ? ", " : "\n");
    printf("Condiciones: ");
    for(int i=0; i<n_cond; i++) printf("%s%s", cond_disp[i], i<n_cond-1 ? ", " : "\n");
    printf("---------------------------------------------\n");

    printf("\n--- Busqueda de Vehiculos ---\n");
    printf("Ingrese tipo de vehiculo (o 'Todos' para omitir): ");
    leer_cadena(tipo, 50);
    printf("Ingrese marca (o 'Todos' para omitir): ");
    leer_cadena(marca, 50);
    printf("Ingrese condicion (o 'Todos' para omitir): ");
    leer_cadena(condicion, 50);
    presupuesto = leer_flotante_positivo("Ingrese su presupuesto maximo: $");

    rewind(archivo);

    printf("\nResultados de la busqueda (Disponibles y dentro de presupuesto):\n");
    printf("ID\tMarca\t\tModelo\t\tTipo\t\tCondicion\tPrecio\n");
    printf("--------------------------------------------------------------------------------------\n");
    
    while (fread(&v, sizeof(Vehiculo), 1, archivo) == 1) {
        if (v.disponible && v.precio <= presupuesto) {
            int cumple_tipo = son_iguales_ignorando_mayusculas(tipo, "Todos") || son_iguales_ignorando_mayusculas(v.tipo, tipo);
            int cumple_marca = son_iguales_ignorando_mayusculas(marca, "Todos") || son_iguales_ignorando_mayusculas(v.marca, marca);
            int cumple_condicion = son_iguales_ignorando_mayusculas(condicion, "Todos") || son_iguales_ignorando_mayusculas(v.condicion, condicion);

            if (cumple_tipo && cumple_marca && cumple_condicion) {
                printf("%d\t%-15s\t%-15s\t%-15s\t%-15s\t$%.2f\n", 
                       v.id, v.marca, v.modelo, v.tipo, v.condicion, v.precio);
                encontrados++;
            }
        }
    }
    
    if (!encontrados) {
        printf("No se encontraron vehiculos disponibles que coincidan con los criterios y el presupuesto.\n");
    }
    fclose(archivo);
}

void registrar_venta() {
    char cedula[20], fecha[20];
    int id_vehiculo, cliente_existe = 0, vehiculo_encontrado = 0;
    FILE *f_clientes, *f_vehiculos, *f_ventas;
    Cliente c;
    Vehiculo v;
    
    printf("\n--- Registrar Venta ---\n");
    printf("Ingrese la cedula del cliente: ");
    leer_cadena(cedula, 20);

    f_clientes = fopen("clientes.dat", "ab+");
    if (!f_clientes) { 
        printf("Error al abrir o crear archivo de clientes.\n"); 
        return; 
    }
    rewind(f_clientes);
    
    while (fread(&c, sizeof(Cliente), 1, f_clientes) == 1) {
        if (strcmp(c.cedula, cedula) == 0) {
            cliente_existe = 1;
            printf("Cliente encontrado: %s\n", c.nombre);
            break;
        }
    }

    if (!cliente_existe) {
        printf("Cliente nuevo. Ingrese nombre y apellido (Ej. Ruben_Perez): ");
        leer_cadena(c.nombre, 50);
        c.edad = leer_entero_positivo("Ingrese edad: ");
        strcpy(c.cedula, cedula);
        
        fseek(f_clientes, 0, SEEK_END);
        fwrite(&c, sizeof(Cliente), 1, f_clientes);
        printf("Cliente registrado correctamente.\n");
    }
    fclose(f_clientes);

    id_vehiculo = leer_entero_positivo("Ingrese el ID del vehiculo a comprar: ");
    
    printf("Ingrese fecha de venta (DD/MM/AAAA): ");
    leer_cadena(fecha, 20);

    f_vehiculos = fopen("vehiculos.dat", "rb+");
    if (!f_vehiculos) {
        printf("Error al acceder al inventario de vehiculos.\n");
        return;
    }

    long pos;
    while (fread(&v, sizeof(Vehiculo), 1, f_vehiculos) == 1) {
        if (v.id == id_vehiculo) {
            vehiculo_encontrado = 1;
            if (!v.disponible) {
                printf("Error: El vehiculo con ID %d ya ha sido vendido.\n", id_vehiculo);
                break;
            }

            v.disponible = 0;
            
            pos = ftell(f_vehiculos) - sizeof(Vehiculo);
            fseek(f_vehiculos, pos, SEEK_SET);
            fwrite(&v, sizeof(Vehiculo), 1, f_vehiculos);
            
            f_ventas = fopen("ventas.dat", "ab");
            if (f_ventas) {
                Venta venta_nueva;
                strcpy(venta_nueva.cedula_cliente, cedula);
                venta_nueva.id_vehiculo = id_vehiculo;
                strcpy(venta_nueva.fecha, fecha);
                venta_nueva.monto_final = v.precio;
                
                fwrite(&venta_nueva, sizeof(Venta), 1, f_ventas);
                fclose(f_ventas);
                printf("\n====================================\n");
                printf("       COMPROBANTE DE VENTA         \n");
                printf("====================================\n");
                printf("Fecha: %s\n", fecha);
                printf("Cliente: %s (Cedula: %s)\n", c.nombre, c.cedula);
                printf("Vehiculo ID %d: %s %s\n", v.id, v.marca, v.modelo);
                printf("Monto Total Pagado: $%.2f\n", v.precio);
                printf("====================================\n");
            } else {
                printf("Error al abrir el archivo de ventas.\n");
            }
            break; 
        }
    }

    fclose(f_vehiculos);

    if (!vehiculo_encontrado) {
        printf("Error: Vehiculo no encontrado.\n");
    }
}

void ver_historial_ventas() {
    FILE *f_ventas = fopen("ventas.dat", "rb");
    Venta venta;

    if (!f_ventas) {
        printf("Error: No se pudo abrir el archivo de ventas o no hay ventas registradas.\n");
        return;
    }

    printf("\n--- Historial de Ventas ---\n");
    printf("Fecha\t\tCedula Cliente\tID Vehiculo\tMonto\n");
    printf("------------------------------------------------------------\n");

    int hay_ventas = 0;
    while (fread(&venta, sizeof(Venta), 1, f_ventas) == 1) {
        printf("%-15s\t%-15s\t%d\t\t$%.2f\n", 
               venta.fecha, venta.cedula_cliente, venta.id_vehiculo, venta.monto_final);
        hay_ventas++;
    }

    if (!hay_ventas) {
        printf("No hay ventas registradas en el sistema.\n");
    }

    fclose(f_ventas);
}

void gestionar_inventario() {
    int opcion;
    do {
        printf("\n--- Gestionar Inventario ---\n");
        printf("1. Agregar Vehiculo\n");
        printf("2. Editar Vehiculo\n");
        printf("3. Eliminar Vehiculo\n");
        printf("4. Volver al Menu Principal\n");
        printf("----------------------------\n");
        opcion = leer_entero_rango("Ingrese una opcion: ", 1, 4);

        switch (opcion) {
            case 1:
                agregar_vehiculo();
                break;
            case 2: {
                int confirmar_editar = leer_entero_rango(
                    "\nSeleccionaste Editar Vehiculo. Confirmar? (1=Si / 0=Cancelar): ", 0, 1
                );
                if (confirmar_editar == 1) {
                    editar_vehiculo();
                } else {
                    printf("Operacion cancelada. Volviendo al menu de gestion...\n");
                }
                break;
            }
            case 3: {
                int confirmar_eliminar = leer_entero_rango(
                    "\nSeleccionaste Eliminar Vehiculo. Confirmar? (1=Si / 0=Cancelar): ", 0, 1
                );
                if (confirmar_eliminar == 1) {
                    eliminar_vehiculo();
                } else {
                    printf("Operacion cancelada. Volviendo al menu de gestion...\n");
                }
                break;
            }
            case 4:
                printf("Volviendo al menu principal...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (opcion != 4);
}

void agregar_vehiculo() {
    FILE *archivo = fopen("vehiculos.dat", "ab+");
    if (!archivo) {
        printf("Error al abrir el archivo de vehiculos.\n");
        return;
    }

    Vehiculo v;
    Vehiculo v_temp;
    int max_id = 0;

    rewind(archivo);
    while (fread(&v_temp, sizeof(Vehiculo), 1, archivo) == 1) {
        if (v_temp.id > max_id) {
            max_id = v_temp.id;
        }
    }

    v.id = max_id + 1;

    printf("\n--- Agregar Vehiculo (Nuevo ID: %d) ---\n", v.id);
    printf("Ingrese marca: ");
    leer_cadena(v.marca, 50);
    printf("Ingrese modelo: ");
    leer_cadena(v.modelo, 50);
    printf("Ingrese tipo: ");
    leer_cadena(v.tipo, 50);
    printf("Ingrese condicion: ");
    leer_cadena(v.condicion, 50);
    v.precio = leer_flotante_positivo("Ingrese precio: $");
    
    int disp;
    do {
        disp = leer_entero_rango("¿Esta disponible? (1 para SI, 0 para NO): ", 0, 1);
    } while (disp != 0 && disp != 1);
    v.disponible = disp;

    fwrite(&v, sizeof(Vehiculo), 1, archivo);
    fclose(archivo);
    printf("Vehiculo agregado exitosamente.\n");
}

void editar_vehiculo() {
    int id_buscar = leer_entero_positivo("Ingrese el ID del vehiculo a editar: ");
    FILE *archivo = fopen("vehiculos.dat", "rb+");
    if (!archivo) {
        printf("Error al abrir el archivo de vehiculos.\n");
        return;
    }

    Vehiculo v;
    int encontrado = 0;
    long pos;

    while (fread(&v, sizeof(Vehiculo), 1, archivo) == 1) {
        if (v.id == id_buscar) {
            encontrado = 1;
            pos = ftell(archivo) - sizeof(Vehiculo);
            
            printf("\nVehiculo encontrado:\n");
            printf("Marca: %s\nModelo: %s\nTipo: %s\nCondicion: %s\nPrecio: $%.2f\nDisponible: %s\n", 
                   v.marca, v.modelo, v.tipo, v.condicion, v.precio, v.disponible ? "SI" : "NO");
            
            printf("\n--- Nuevos datos (presione Enter para mantener el actual) ---\n");
            
            char buffer[50];
            
            printf("Marca actual (%s): ", v.marca);
            leer_cadena(buffer, 50);
            if (strlen(buffer) > 0) strcpy(v.marca, buffer);
            
            printf("Modelo actual (%s): ", v.modelo);
            leer_cadena(buffer, 50);
            if (strlen(buffer) > 0) strcpy(v.modelo, buffer);
            
            printf("Tipo actual (%s): ", v.tipo);
            leer_cadena(buffer, 50);
            if (strlen(buffer) > 0) strcpy(v.tipo, buffer);
            
            printf("Condicion actual (%s): ", v.condicion);
            leer_cadena(buffer, 50);
            if (strlen(buffer) > 0) strcpy(v.condicion, buffer);
            
            printf("Precio actual ($%.2f) - Ingrese nuevo precio (o <= 0 para no cambiar): $", v.precio);
            float n_precio;
            int leidos = scanf("%f", &n_precio);
            while (getchar() != '\n');
            if (leidos == 1 && n_precio > 0) {
                v.precio = n_precio;
            }
            
            printf("Disponible actual (%s) - Ingrese 1(SI), 0(NO) o -1(no cambiar): ", v.disponible ? "SI" : "NO");
            int n_disp;
            leidos = scanf("%d", &n_disp);
            while (getchar() != '\n');
            if (leidos == 1 && (n_disp == 0 || n_disp == 1)) {
                v.disponible = n_disp;
            }

            fseek(archivo, pos, SEEK_SET);
            fwrite(&v, sizeof(Vehiculo), 1, archivo);
            printf("Vehiculo actualizado exitosamente.\n");
            break;
        }
    }

    if (!encontrado) {
        printf("No se encontro un vehiculo con ese ID.\n");
    }

    fclose(archivo);
}

void eliminar_vehiculo() {
    int id_borrar = leer_entero_positivo("Ingrese el ID del vehiculo a eliminar: ");
    
    FILE *archivo = fopen("vehiculos.dat", "rb");
    if (!archivo) {
        printf("Error al abrir el archivo de vehiculos.\n");
        return;
    }
    
    FILE *temp = fopen("vehiculos_temp.dat", "wb");
    if (!temp) {
        printf("Error al crear archivo temporal.\n");
        fclose(archivo);
        return;
    }

    Vehiculo v;
    int encontrado = 0;

    while (fread(&v, sizeof(Vehiculo), 1, archivo) == 1) {
        if (v.id == id_borrar) {
            encontrado = 1;
            printf("\nVehiculo encontrado y será eliminado:\n");
            printf("ID: %d | Marca: %s | Modelo: %s | Precio: $%.2f\n", v.id, v.marca, v.modelo, v.precio);
            
            int conf = leer_entero_rango("¿Seguro que desea eliminarlo? (1 para SI, 0 para Cancelar): ", 0, 1);
            if (conf == 0) {
                printf("Operacion cancelada.\n");
                // Lo escribimos porque canceló
                fwrite(&v, sizeof(Vehiculo), 1, temp);
                encontrado = 2; // Para saber que lo encontro pero no lo borró
            } else {
                printf("Vehiculo eliminado exitosamente.\n");
            }
        } else {
            fwrite(&v, sizeof(Vehiculo), 1, temp);
        }
    }

    fclose(archivo);
    fclose(temp);

    if (encontrado == 0) {
        printf("No se encontro un vehiculo con ese ID.\n");
        remove("vehiculos_temp.dat");
    } else {
        remove("vehiculos.dat");
        rename("vehiculos_temp.dat", "vehiculos.dat");
    }
}
