namespace MarkovChain
{
    class Builder;
} // namespace MarkovChain


#ifndef MARKOV_CHAIN_BUILDER_H
#define MARKOV_CHAIN_BUILDER_H

#include <string>
#include <istream>
#include <ostream>

#include "MarkovChain/MarkovChain.h"

namespace MarkovChain
{
   MarkovChain build(std::istream &input, std::ostream &output, int string_length);
} // namespace MarkovChain

#endif // MARKOV_CHAIN_BUILDER_H