#include <iostream>
#include <vector>
#include "headers/SequentialInputReader.h"
#include "headers/OpenMPInputReader.h"
#include "headers/MPIInputReader.h"

using namespace cpyd;

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0){
        std::cout << "Integrantes: " << std::endl
                  << "\tRafael Morales Venegas" << std::endl
                  << "\tDiego Oyarce Trejo" << std::endl;
    }

    // No arguments prompt
    if(argc == 1 && rank == 0){
        std::cout << "Utilización: ./test-check --file ./file.csv --out output.csv" << std::endl;
        std::cout << "Puedes utilizar --help para más información." << std::endl;

        MPI_Finalize();
        return 0;
    }

    std::vector<std::string> args;

    for(int i = 1; i < argc; i++){
        std::string str(argv[i]);
        args.push_back(str);
    }

    // Help message
    if(std::find(args.begin(), args.end(), "--help") != args.end() && rank == 0){
        if(argc > 2) {
            std::cout   << "--help evitará el resto de la ejecución."
                        << " No lo incluyas con el resto de argumentos!"
                        << std::endl;
        }

        std::cout << "El programa requiere 2 argumentos posicionales: " << std::endl
            << "--file, que debe ser seguido por la ruta relativa a este programa." << std::endl
            << "\te.j: --file ./pruebas.csv" << std::endl << std::endl
            << "--out, seguido por el archivo de output a utilizar. Por defecto, el programa creara un " << std::endl
            << "\tarchivo llamado 'output.csv'." << std::endl << std::endl
            << "--modo [secuencial|openmp|mpi] (Default: secuencial)" << std::endl
            << "\tCada uno de estos modos altera la forma en que se comporta la ejecucion del codigo." << std::endl
            << "\tPor defecto, este programa ejecuta el modo secuencial." << std::endl;

        MPI_Finalize();
        return 0;
    }

    // Input file
    auto file_index = std::find(args.begin(), args.end(), "--file");
    if((file_index == args.end() || argc < 3) && rank == 0) {
        std::cout << "--file necesita ser seguido por el nombre del archivo .csv a revisar." << std::endl;

        MPI_Finalize();
        return 1;
    }

    std::string filename = file_index[1];
    if(filename.compare(filename.length() - 4, 4, ".csv") != 0 && rank == 0) {
        std::cout << "El archivo de INPUT debe terminar en '.csv'!" << std::endl;

        MPI_Finalize();
        return 1;
    }

    // Output file
    auto out_index = std::find(args.begin(), args.end(), "--out");
    std::string output_filename = out_index == args.end() ? "output.csv" : out_index[1];

    if(output_filename.compare(output_filename.length() - 4, 4, ".csv") != 0 && rank == 0) {
        std::cout << "El archivo de OUTPUT debe terminar en '.csv'!" << std::endl;

        MPI_Finalize();
        return 1;
    }

    // Selected mode
    auto mode_index = std::find(args.begin(), args.end(), "--modo");
    std::string mode = mode_index == args.end() ? "secuencial" : mode_index[1];

    InputReader* reader;
    std::vector<std::string> modos {"secuencial", "openmp", "mpi"};
    auto selected = std::find(modos.begin(), modos.end(), mode);

    switch (selected - modos.begin()) {
        case 0:
            reader = new SequentialInputReader(filename, output_filename);
            break;
        case 1:
            reader = new OpenMPInputReader(filename, output_filename);
            std::cout << "Selected: OpenMP" << std::endl;
            break;
        case 2:
            reader = new MPIInputReader(filename, output_filename);
            if (rank == 0) std::cout << "Selected: MPI" << std::endl;
            break;
        default:
            if(rank == 0) {
                std::cout << "El modo elegido es invalido! "
                          << "Fijate que esté escrito totalmente en minúsculas y prueba de nuevo"
                          << std::endl;
            }
            MPI_Finalize();
            return 1;
    }

    if(reader->invalidInputFile() && rank == 0){
        std::cout << "El archivo sugerido de input no existe!" << std::endl;

        MPI_Finalize();
        return 1;
    }

    if(reader->invalidOutputFile() && rank == 0){
        std::cout << "El archivo sugerido de output es invalido!" << std::endl;

        MPI_Finalize();
        return 1;
    }

    reader->readFile();

    MPI_Finalize();
    return 0;
}
