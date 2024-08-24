<ins>Instalacion:<ins>

1. Instalar y ejecutar Ubuntu en Virtualbox.
2. Instalar VScode: `sudo apt install ./<file>.deb`
3. Instalar git: `sudo apt install git-all`
4. Instalar gcc: `sudo apt install build-essential`
5. Instalar qemu: `sudo apt-get install qemu-system`
6. Instalar `gnu-toolchain-riscv "sudo apt install gcc-riscv64-unknown-elf`
7. Clonar xv6-riscv: `git clone https://github.com/mit-pdos/xv6-riscv.git`
8. Abrir VScode en el directorio xv6-riscv.
9. En la terminal de vscode, ejecutar el comando `make qemu`
10. Comprobar que compilo correctamente con los siguientes comandos:
    <ol type="a">
    <li>`ls`</li>
    <li>`echo "Hola xv6`</li>
    <li>`cat README`</li>
    </ol>

    Donde se deberian observar:
    [screenshot1.png](screenshot1.png) y [screenshot2.png](screenshot1.png)

<ins>Problemas:<ins>

Uno de los problemas que encontre, fue que no me quedaba claro como instalar el gnu-toolchain, dado que en el repositorio oficial, aparecen una serie de procesos que no me quedaba claro como aplicarlos, y dada mi falta de experiencia con el sistema linux, no se me ocurrio instalarlo con "apt install".
Originalmente, tenia planeado utilizar el sistema wsl de windows, pero a la hora de instalar el emulador qemu, me daba una serie de errores.
