#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main()
{
    // Reservar una página de memoria
    char *addr = sbrk(4096);

    // Verificar si la dirección es válida
    if (addr == (char *)-1)
    {
        printf("Error al asignar memoria\n");
        exit(1);
    }

    // Proteger la página con mprotect
    if (mprotect(addr, 1) == -1)
    {
        printf("Error: mprotect falló\n");
        exit(1);
    }
    else
    {
        printf("mprotect fue exitoso\n");
    }

    // Intentar escribir en la página protegida
    printf("Intentando escribir en la página protegida...\n");
    *addr = 'A'; // Esto debería fallar y provocar un error de segmentación si funciona correctamente

    // Imprimir el valor para ver si la protección se mantuvo
    printf("Valor en la dirección: %c\n", *addr);

    // Desproteger la página con munprotect
    if (munprotect(addr, 1) == -1)
    {
        printf("Error: munprotect falló\n");
        exit(1);
    }
    else
    {
        printf("munprotect fue exitoso\n");
    }

    // Intentar escribir en la página desprotegida
    *addr = 'B'; // Esto debería funcionar sin errores
    printf("Valor en la dirección después de munprotect: %c\n", *addr);

    exit(0);
}
