# cpyd-t01
Trabajo 1 para Computación paralela y distribuida, primer semestre 2022.

## Integrantes
- Rafael Morales Venegas
- Diego Oyarce Trejo

## Instalacion
La herramienta de construcción elegida para este proyecto fue CMake.
Como mínimo, es requerido la versión 3.22
Para Ubuntu y distribuciones similares, se puede instalar utilizando el siguiente comando:
```bash
 user@machine:~$ sudo apt install cmake
```

Para poder compilar el archivo, se requieren de los siguientes comandos:
```bash
git clone https://github.com/RafaelMoralesV/cpyd-t01  # Clonar el repositorio
cd cpyd-t01
mkdir build                                           # Crear carpeta para la compilacion
cd build
cmake ..                                              # Construir el proyecto con CMake
make                                                  # Compilar
```

Esto producirá un archivo binario dentro de la carpeta build con el nombre "test-check", que contiene todo el programa.
Puede copiar el archivo con el nombre y a la carpeta que necesite y utilizarlo desde ahí

## Uso
### Ejemplo simple
Ejecutar el programa de manera secuencial sobre el archivo pruebas.csv, y producir un resultado llamado output.csv
```console
test-check --file pruebas.csv
```

### Ejemplo output personalizado
Ejecutar el programa de manera secuencial sobre el archivo pruebas.csv, y producir un archivo resultado de nombre foo.csv
```console
test-check --file pruebas.csv --out foo.csv
```

### Ejemplo utilizando openmp o mpi
Ejecuta el programa en hilos paralelos o de manera distrubuida, y producir un resultado llamado output.csv
```console
test-check --file pruebas.csv --modo openmp
test-check --file pruebas.csv --modo mpi
```

### Errores
La implementación de MPI aún no está lista, y crasheará el programa en ejecución.
