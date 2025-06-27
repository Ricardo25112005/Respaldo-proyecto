#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Map.h"
#include "List.h"
#include "utils.h"
#include "App.h"


int main() {
    HashMap *productosPorCodigo = createMap(2000);
    HashMap *productosPorNombre = createMap(2000);
    HashMap *productosPorCategoria = createMap(2000);
    HashMap *contadorProducto = createMap(2000);

    List *carrito = createList();
    List *historialCompras = createList();

    int opcion, tipoUsuario;
    bool primerIngreso = true;
    while (1) {
        printf("\n=== Sistema de Gestión de Inventario ===\n");
        printf("1. Administrador\n2. Cliente\n0. Salir\n");
        printf("Seleccione tipo de usuario: ");
        scanf("%d", &tipoUsuario);
        getchar(); // Limpiar buffer

        if (tipoUsuario == 0) break;

        if (tipoUsuario == 1) {
            while (1) {
                mostrarMenuAdministrador();
                scanf("%d", &opcion);
                getchar(); // Limpiar buffer

                if (opcion == 0) break; //comentario de prueba

                switch (opcion) {
                    case 1:
                        limpiarPantalla();
                        if (primerIngreso != true) {
                            puts("El inventario ya ha sido cargado.");
                            puts("Si desea reiniciar el inventario, por favor cierre la aplicación y vuelva a abrirla.");
                            presioneTeclaParaContinuar();
                            break;
                        }
                        printf("Ingrese el nombre del archivo CSV para cargar el inventario: ");
                        char nombreArchivo[100];
                        fgets(nombreArchivo, sizeof(nombreArchivo), stdin);
                        nombreArchivo[strcspn(nombreArchivo, "\n")] = 0; // Eliminar el salto de línea 
                        cargarInventario(nombreArchivo, productosPorNombre, productosPorCodigo, productosPorCategoria); 
                        if (firstMap(productosPorCodigo) != NULL) primerIngreso = false;
                        break;
                    case 2:
                        limpiarPantalla(); 
                        menuBusqueda();
                        int opcionBusqueda;
                        scanf("%d", &opcionBusqueda);
                        getchar(); // Limpiar buffer
                        switch (opcionBusqueda) {
                            case 1: buscarPorNombre(productosPorNombre); break;
                            case 2: buscarPorCategoria(productosPorCategoria); break;
                            case 3: mostrarProductosStock(productosPorCodigo); break;
                            case 4: mostrarVentasProductos(productosPorCodigo); break; 
                            default: printf("Opción no válida.\n");
                        }
                        break;
                    case 3:
                        limpiarPantalla(); 
                        menuModificarInventario();
                        int opcionModificar;
                        scanf("%d", &opcionModificar);
                        getchar(); // Limpiar buffer
                        switch (opcionModificar) {
                            case 1: registrarProducto(productosPorCodigo, productosPorCategoria, productosPorNombre); break;
                            case 2: modificarStock(productosPorCodigo, productosPorCategoria, productosPorNombre); break;
                            case 3: eliminarProducto(productosPorCodigo, productosPorCategoria, productosPorNombre); break;
                            default: printf("Opción no válida.\n");
                        }
                        break;
                    case 4: guardarInventario(productosPorCodigo); break;
                    case 5: generarReporte(productosPorCodigo, productosPorCategoria, productosPorNombre,historialCompras, contadorProducto); break;
                    default: printf("Opción no válida.\n");
                }
            }
        } else if (tipoUsuario == 2) {
            while (1) {
                mostrarMenuCliente();
                scanf("%d", &opcion);
                getchar(); 

                if (opcion == 0) break;

                switch (opcion) {
                    case 1: agregarAlCarrito(productosPorCodigo, carrito); break;
                    case 2: eliminarDelCarrito(carrito); break;
                    case 3: verCarrito(carrito); break;
                    case 4: confirmarCompra(carrito, historialCompras, productosPorNombre, productosPorCategoria, productosPorCodigo, contadorProducto); break;
                    default: printf("Opción no válida.\n");
                }
            }
        } else {
            printf("Tipo de usuario no válido.\n");
        }
    }

    // Liberar memoria
    cleanList(carrito);
    cleanList(historialCompras);
    map_clean(productosPorCodigo);
    
    return 0;
} 