# Informe de Implementación de `mprotect` y `munprotect` en xv6

## Cambios Realizados
1. **Implementación de las Funciones del Kernel**:
   - Se implementaron las funciones `sys_mprotect` y `sys_munprotect` en `kernel/sysproc.c` para manejar la protección y desprotección de memoria de procesos de usuario.
   - Se utilizó la función `walk()` para acceder a las entradas de la tabla de páginas y modificar el bit de permiso de escritura (`PTE_W`).

2. **Declaración de las Funciones en el Espacio de Usuario**:
   - Se agregaron las declaraciones de `mprotect` y `munprotect` en `user/user.h` para que pudieran ser utilizadas por los programas de usuario.
   - Se incluyeron las funciones en `user/usys.pl` para generar los stubs de las llamadas al sistema.

3. **Modificaciones en `syscall`**:
   - **Declaración de Nuevas Llamadas al Sistema**:
     - Se agregaron las entradas de `SYS_mprotect` y `SYS_munprotect` en `kernel/syscall.h` para definir los números de llamada al sistema.
     - En `kernel/syscall.c`, se incluyeron las referencias a `sys_mprotect` y `sys_munprotect` en el arreglo `syscalls[]`.

   - **Asignación de Números de Llamada al Sistema**:
     - En `kernel/syscall.h`, se definieron los números de las nuevas llamadas al sistema:
       ```c
       #define SYS_mprotect 22  // Número de ejemplo
       #define SYS_munprotect 23 // Número de ejemplo
       ```

     - En `kernel/syscall.c`, se añadieron las funciones:
       ```c
       extern uint64 sys_mprotect(void);
       extern uint64 sys_munprotect(void);

       static uint64 (*syscalls[])(void) = {
         // Otras llamadas al sistema existentes
         [SYS_mprotect]    sys_mprotect,
         [SYS_munprotect]  sys_munprotect,
       };
       ```

   Estas modificaciones permitieron que las llamadas al sistema `mprotect` y `munprotect` fueran reconocidas y ejecutadas por el kernel de xv6.


4. **Modificaciones en `makefile`**:
   - **Declaración al nuevo archivo**:
     - Se agrego la entrada de `test_prot` en la entrada User ($U) para definir el archivo ejecutable en la carpeta User llamado `test_prot.c`.

5. **Programa de Prueba (`test_prot.c`)**:
   - Se creó un programa de usuario llamado `test_prot.c` que verifica si `mprotect` y `munprotect` funcionan correctamente.
   - `test_prot` protege una página de memoria y luego intenta escribir en ella, lo que debería generar una excepción si la protección funciona.

## Problemas Resueltos
1. **Errores de Declaración Implícita**:
   - El compilador arrojaba errores de "implicit declaration of function" al usar `mprotect` y `munprotect` en el programa de prueba.
   - **Solución**: Se agregaron las declaraciones de las funciones en `user/user.h` y las entradas correspondientes en `user/usys.pl`.

2. **Funciones `argaddr` y `argint` como `void`**:
   - Inicialmente, se asumió incorrectamente que `argaddr` y `argint` devolvían un valor de estado. Sin embargo, estas funciones son `void` y modifican sus argumentos por referencia.
   - **Solución**: Se ajustó el código para usar `argaddr` y `argint` sin verificar un valor de retorno, y se agregó lógica manual de comprobación de errores después de usarlas.

3. **Excepciones de Trampa Inesperadas**:
   - Durante la ejecución de `test_prot`, se observó una excepción de trampa (`unexpected scause 0xf`).
   - **Explicación**: Esto confirmó que la protección de memoria estaba funcionando, ya que se generaba una excepción al intentar escribir en una página de solo lectura.
   - **Solución**: Se confirmó que este comportamiento era esperado y significaba que `mprotect` estaba funcionando correctamente.

## Ejecución de `test_prot`
1. Compila xv6 con el programa de prueba:
   ```bash
   make clean
   make qemu

2. En el shell de xv6, ejecuta el programa test_prot:
   
bash
   $ test_prot


## Resultados Esperados
- Deberías ver la salida:
  
mprotect fue exitoso
  Intentando escribir en la página protegida...
