### Cambios realizados:

1. En el archivo syscall.h se agrego la definicion `#define SYS_getppid 22` .
2. En el archivo syscall.c linea 100 se agrego : `extern uint64 sys_getppid(void);`
    Y en la linea 126 se agrego: `[SYS_getppid] sys_getppid,`
3. En el archivo user.h en la linea 45 se agrego: `int getppid(void);`
4. En el usys.pl linea 39 se agrego: `int "getppid(void")`
5. En el Makefile en la linea 32 se agrego: `$K/sysgetppid.o`
   Y en la linea 143 se agrego: `$U/_test\`
6.En la carpeta user se creo un archivo llamado test.c con el codigo
    ```
        #include "kernel/types.h"
        #include "kernel/stat.h"
        #include "user/user.h"
        
        int main(void)
        {
        
            int ppid = getppid();
            printf("Parent PID: %d\n", ppid);
            exit(0);
        }
    ```
   


### Ejecucion:

1. Inicializar el sistema operativo xv6-riscv
2. Ejecutar el comando: `test`
  

### Problemas:

Uno de los problemas que encontre, fue que al inicializar el sistema operativo me daba un error el sprinlock.h dado que lo ejecuta despues del proc.h, esto lo resolvi removiendo ambas referencias del archivo test.c
