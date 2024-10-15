## Cambios Realizados

1. **Estructura del Proceso** (`proc.h`):
   - Se añadio a la estructura de procesos (`struct proc`):
     ```c
     int priority;
     int boost;
     ```

2. En la función `allocproc()`, que se utiliza para inicializar nuevos procesos, se agregaron las siguientes líneas para inicializar los campos:
     ```c
     p->priority = 0;
     p->boost = 1;
     ```

3. - Se añadió "lógica" en el scheduler para aumentar la prioridad de los procesos ejecutables (`RUNNABLE`) en función de su boost:
     ```c
     for(p = proc; p < &proc[NPROC]; p++) {
       if(p->state == RUNNABLE) {
         p->priority += p->boost;  // Incrementar la prioridad

         // Ajustar el boost si la prioridad alcanza límites
         if(p->priority >= 9) {
           p->boost = -1;  // Disminuir boost si la prioridad llega a 9
         } else if(p->priority <= 0) {
           p->boost = 1;   // Aumentar boost si la prioridad llega a 0
         }
       }
     }
     ```

## Problemas Encontrados

1. **Error de variable no inicializada**:
   - Al intentar asignar los valores de `priority` y `boost` en la función `allocproc()`, se generaba un error de compilación:
     ```
     kernel/proc.c:117:15: error: 'p' is used uninitialized [-Werror=uninitialized]
     ```
   - **Solución**: El error ocurrió porque `p` no estaba correctamente inicializado. Para corregirlo, se movio a la linea 131 donde p se volvia 'used'
     ```c
      p->pid = allocpid();
      p->state = USED;

      p->priority = 0; // Inicializar prioridad en 0
      p->boost = 1;
     }
     ```

## Archivo de Prueba: `test_priority.c`

-Para ejecutarlo se añadio un ```$U/_test_priority\``` en el makefile linea 142

El archivo `test_priority.c` es un programa de prueba que genera 20 procesos mediante llamadas a `fork()`. Cada proceso imprime un mensaje en pantalla que indica que está siendo ejecutado y luego duerme por un tiempo determinado usando `sleep()`.

   - Utiliza `fork()` para crear 20 procesos hijos.
   - Cada proceso hijo imprime un mensaje en pantalla con su `PID`.
   - Cada proceso duerme por unos segundos usando la función `sleep(10)` para simular una carga de trabajo.
   - El proceso padre espera a que todos los procesos hijos terminen con `wait()` antes de finalizar.
 

##Ejecucion
```
    make clean #empieze de 0
    make qemu
    test_priority
```

