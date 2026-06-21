typedef struct {
    int id;
    char marca[50];
    char modelo[50];
    char tipo[50];
    char condicion[50];
    float precio;
    int disponible;
} Vehiculo;

typedef struct {
    char cedula[20];
    char nombre[50];
    int edad;
} Cliente;

typedef struct {
    char cedula_cliente[20];
    int id_vehiculo;
    char fecha[20];
    float monto_final;
} Venta;

void mostrar_menu();
void ver_inventario();
void buscar_vehiculo();
void registrar_venta();
void ver_historial_ventas();
void gestionar_inventario();
void agregar_vehiculo();
void editar_vehiculo();
void eliminar_vehiculo();

void leer_cadena(char *cadena, int longitud);
int son_iguales_ignorando_mayusculas(const char *cadena1, const char *cadena2);
int leer_entero_rango(const char *mensaje, int min, int max);
int leer_entero_positivo(const char *mensaje);
float leer_flotante_positivo(const char *mensaje);