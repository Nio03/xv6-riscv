
# Informe de Implementación de `mprotect` y `munprotect` en xv6

## Cambios Realizados
1. **Implementación de las Funciones del Kernel**:
   - Se implementaron las funciones `sys_mprotect` y `sys_munprotect` en `kernel/sysproc.c` para manejar la protección y desprotección de memoria de procesos de usuario.
   - Se utilizó la función `walk()` para acceder a las entradas de la tabla de páginas y modificar el bit de permiso de escritura (`PTE_W`).

2. **Declaración de las Funciones en el Espacio de Usuario**:
   - Se agregaron las declaraciones de `mprotect` y `munprotect` en `user/user.h` para que pudieran ser utilizadas por los programas de usuario.
   - Se incluyeron las funciones en `user/usys.pl` para generar los stubs de las llamadas al sistema.

3. **Programa de Prueba (`test_prot.c`)**:
   - Se creó un programa de usuario llamado `test_prot.c` que verifica si `mprotect` y `munprotect` funcionan correctamente.
   - `test_prot` protege una página de memoria y luego intenta escribir en ella, lo que debería generar una excepción si la protección funciona.

## Problemas Resueltos
1. **Errores de Declaración Implícita**:
   - El compilador arrojaba errores de "implicit declaration of function" al usar `mprotect` y `munprotect` en el programa de prueba.
   - **Solución**: Se agregaron las declaraciones de las funciones en `user/user.h` y las entradas correspondientes en `user/usys.pl`.

2. **Excepciones de Trampa Inesperadas**:
   - Durante la ejecución de `test_prot`, se observó una excepción de trampa (`unexpected scause 0xf`).
   - **Explicación**: Esto confirmó que la protección de memoria estaba funcionando, ya que se generaba una excepción al intentar escribir en una página de solo lectura.
   - **Solución**: Se confirmó que este comportamiento era esperado y significaba que `mprotect` estaba funcionando correctamente.

## Cómo Resolver los Problemas
- **Declaración de las Funciones**: Se agregaron las declaraciones de `mprotect` y `munprotect` en `user/user.h` y `user/usys.pl` para evitar los errores de compilación.
- **Verificación de Protección**: La excepción de trampa mostró que `mprotect` había protegido correctamente la página de memoria, cumpliendo con los requisitos de la tarea.

## Ejecución de `test_prot`
1. Compila xv6 con el programa de prueba:
   ```bash
   make clean
   make qemu
   ```
2. En el shell de xv6, ejecuta el programa `test_prot`:
   ```bash
   $ test_prot
   ```

## Resultados Esperados
- Deberías ver la salida:
  ```
  mprotect fue exitoso
  Intentando escribir en la página protegida...
  ```
- La excepción de trampa al escribir en la página protegida confirmará que la función `mprotect` está funcionando correctamente.
- Si `munprotect` es exitoso, deberías poder escribir en la página desprotegida sin errores.
