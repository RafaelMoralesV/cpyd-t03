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
### Argumentos necesarios
El programa requiere de dos argumentos. <input file> representa la ruta al archivo de entrada. <output file>, la ruta al archivo de salida deseado
```console
test-check <input file> <output file>  # Argumentos requeridos
```

### Ejemplo output personalizado
Ejecutar el programa de manera secuencial sobre el archivo pruebas.csv, y producir un archivo resultado de nombre foo.csv
```console
test-check pruebas.csv foo.csv --modo secuencial # "--modo secuencial" es opcional para la ejecucion de forma secuencial.
```

### Ejemplo utilizando openmp o mpi
Ejecuta el programa en hilos paralelos o de manera distrubuida, y producir un resultado llamado output.csv
```console
test-check pruebas.csv resultado.csv --modo openmp
test-check pruebas.csv resultado.csv --modo mpi
```

## Jerarquía
Existen un total de siete clases dispuestas en la siguiente Jerarquía. Las razones de esta jerarquia se explica en los archivos .h de cada clase.
 - BaseInputReader
   - InputReader
     - SecuentialInputReader  # Ejecuta el modo secuencial
     - OpenMPInputReader      # Ejecuta el modo openmp
   - MPIInputReader
     - MPIHostInputReader     # Ejecuta el modo mpi con rango 0
     - MPINodeInputReader     # Ejecuta el modo mpi con rango distinto de 0
 
