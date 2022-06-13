#include <iostream>
#include <fstream>

#include "MarkovChain/Builder.h"

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cout << "Usage " << argv[0] << " <string length> <input file> [output file]" << std::endl;
        std::exit(20);
    }

    int string_length = std::stoi(argv[1]);
    std::ifstream input_file(argv[2]);
    std::ostream *output_stream;
    if (argc == 3)
    {
        output_stream = &std::cout;
    }
    else
    {
        output_stream = new std::ofstream(argv[3]);
    }

    MarkovChain::MarkovChain chain = MarkovChain::build(input_file, *output_stream, string_length);

    *output_stream << chain << std::flush;

    std::exit(0);
}