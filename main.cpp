#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    if(argc == 1){
        std::cout << "Utilización: ./test-check --file ./file.csv --modo secuencial " << std::endl;
        std::cout << "Puedes utilizar --help para más información." << std::endl;
        return 0;
    }

    std::vector<std::string> args;

    for(int i = 1; i < argc; i++){
        std::string str(argv[i]);
        args.push_back(str);
    }

    if(std::find(args.begin(), args.end(), "--help") != args.end()){
        if(argc > 2) {
            std::cout   << "--help evitará el resto de la ejecución."
                        << " No lo incluyas con el resto de argumentos!"
                        << std::endl;
        }

        std::cout << "El programa acepta 2 argumentos posicionales: " << std::endl
            << "--file, que debe ser seguido por la ruta relativa a este programa." << std::endl
            << "\te.j: --file ./pruebas.csv" << std::endl << std::endl
            << "--modo (opcional), acepta 3 valores distintos: secuencial, openmp, mpi." << std::endl
            << "\tCada uno de estos modos altera la forma en que se comporta la ejecucion del codigo." << std::endl
            << "\tPor defecto, este programa ejecuta el modo secuencial." << std::endl;

        return 0;
    }

    auto file_index = std::find(args.begin(), args.end(), "--file");
    if(file_index == args.end()) {
        std::cout << "--file necesita ser seguido por el nombre del archivo .csv a revisar.";
        return 1;
    }

    std::string filename = file_index[1];

    auto mode_index = std::find(args.begin(), args.end(), "--modo");
    std::string mode = mode_index == args.end() ? "secuencial" : mode_index[1];

    std::vector<std::string> modos {"secuencial", "openmp", "mpi"};
    if(std::find(modos.begin(), modos.end(), mode) == modos.end()) {
        std::cout   << "El modo elegido es invalido! "
                    << "Fijate que esté escrito totalmente en minúsculas y prueba de nuevo"
                    << std::endl;
        return 1;
    }

    return 0;
}
