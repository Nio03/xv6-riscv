#include "kernel/types.h"
#include "user/user.h"

void child_process(int id)
{
    for (int i = 0; i < 5; i++)
    {
        printf("Ejecutando proceso %d\n", id);
        sleep(1); // Dormir por 1 segundo
    }
    exit(0);
}

int main(int argc, char *argv[])
{
    for (int i = 0; i < 20; i++)
    {
        if (fork() == 0)
        {
            child_process(i);
        }
    }

    for (int i = 0; i < 20; i++)
    {
        wait(0); // Esperar a que terminen todos los procesos hijos
    }

    exit(0);
}
