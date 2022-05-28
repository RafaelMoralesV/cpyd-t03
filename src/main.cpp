#include <iostream>
#include <vector>
#include "headers/SequentialInputReader.h"
#include "headers/OpenMPInputReader.h"
#include "headers/MPIInputReader.h"

using namespace cpyd;

struct config {
    std::string input;
    std::string output;
    std::string mode;
};

config getConfig(std::vector<std::string> args){
    config conf;
    std::stringstream excep_message;

    // Se encontro "--help" entre los argumentos.
    if(std::find(args.begin(), args.end(), "--help") != args.end()){
        if(args.size() > 1) {
            excep_message   << "--help evitará el resto de la ejecución."
                        << " No lo incluyas con el resto de argumentos!"
                        << std::endl;
        }

        excep_message << "El programa requiere 2 argumentos posicionales: " << std::endl
                  << "<file>, que es la ruta de un archivo .csv de entrada" << std::endl
                  << "<output>, que es la ruta de un archivo .csv de salida" << std::endl << std::endl

                  << "Adicionalmente hay un argumento opcional, que adopta uno de tres valores: " << std::endl
                  << "--modo [secuencial|openmp|mpi] (Default: secuencial)" << std::endl
                  << "\tCada uno de estos modos altera la forma en que se comporta la ejecucion del codigo." << std::endl
                  << "\tPor defecto, este programa ejecuta el modo secuencial." << std::endl << std::endl

                  << "Ejemplo: test-check ./pruebas.csv ./output.csv --modo openmp" << std::endl;

        throw std::invalid_argument(excep_message.str());
    }

    // No se han enviado argumentos.
    if(args.size() < 2){
        excep_message   << "ERROR: Muy pocos parametros."                   << std::endl
                        << "Utilización: ./test-check <file> <output>"      << std::endl
                        << "Utiliza --help para más información."           << std::endl;

        throw std::invalid_argument(excep_message.str());
    }

    conf.input = args[0];
    conf.output = args[1];

    if(conf.input.compare(conf.input.length() - 4, 4, ".csv") != 0) {
        excep_message << "El archivo de INPUT debe terminar en '.csv'!" << std::endl;

        throw std::invalid_argument(excep_message.str());
    }

    if(conf.output.compare(conf.output.length() - 4, 4, ".csv") != 0) {
        excep_message << "El archivo de OUTPUT debe terminar en '.csv'!" << std::endl;

        throw std::invalid_argument(excep_message.str());
    }

    return conf;
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    std::vector<std::string> args;
    for(int i = 1; i < argc; i++){
        std::string str(argv[i]);
        args.push_back(str);
    }

    std::cout << "Integrantes: " << std::endl
              << "\tRafael Morales Venegas" << std::endl
              << "\tDiego Oyarce Trejo" << std::endl;

    config conf;

    // Consigo Input y Output
    try{ conf = getConfig(args); }
    catch (std::invalid_argument & e) {
        if(rank == 0) std::cout << e.what();

        MPI_Finalize();
        return 1;
    }


    InputReader* reader;

    // Selected mode
    auto mode_index = std::find(args.begin(), args.end(), "--modo");
    std::string mode = mode_index == args.end() ? "secuencial" : mode_index[1];

    std::vector<std::string> modos {"secuencial", "openmp", "mpi"};
    auto selected = std::find(modos.begin(), modos.end(), mode);

    switch (selected - modos.begin()) {
        case 0:
            if(rank != 0) break;
            reader = new SequentialInputReader(conf.input, conf.output);
            break;
        case 1:
            if(rank != 0) break;
            reader = new OpenMPInputReader(conf.input, conf.output);
            std::cout << "Selected: OpenMP" << std::endl;
            break;
        case 2:
            reader = new MPIInputReader(conf.input, conf.output);
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
