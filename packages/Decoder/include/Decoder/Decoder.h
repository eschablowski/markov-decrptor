#ifndef DECODER_DECODER_H
#define DECODER_DECODER_H

#include "MarkovChain/MarkovChain.h"
#include "unordered_map"

namespace Decoder
{
    std::unordered_map<char, char> decode(MarkovChain::MarkovChain &reference, MarkovChain::MarkovChain &target);
} // namespace Decoder


#endif // DECODER_DECODER_H