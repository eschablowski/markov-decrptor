#include "MarkovChain/Extractor.h"

const MarkovChain::markov_map &MarkovChain::extract::operator()(MarkovChain &chain)
{
    return *(markov_map *)chain.information_map;
}

std::unordered_map<std::string, mpf_class> MarkovChain::extract::get_probability(MarkovChain &chain, std::string from)
{
    std::unordered_map<std::string, mpf_class> probabililities;
    markov_map &inf_map = *(markov_map *)chain.information_map;
    auto from_bucket = inf_map.find(from);
    if (from_bucket != inf_map.end())
    {
        for (auto to : from_bucket->second.second)
        {
            probabililities[to.first] = to.second / from_bucket->second.first;
        }
    }
    return probabililities;
}
