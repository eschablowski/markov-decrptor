#include "Decoder/Decoder.h"

#include <cassert>
#include <set>

#include "MarkovChain/Extractor.h"

struct less_than_pair;
std::set<std::pair<std::string, mpz_class>, less_than_pair> get_frequencies(MarkovChain::markov_map &map);
std::pair<std::string, std::string> get_common(const MarkovChain::markov_map const &map);

std::unordered_map<char, char>
Decoder::decode(MarkovChain::MarkovChain &reference, MarkovChain::MarkovChain &target)
{
    assert(reference.get_string_length() == target.get_string_length());

    std::unordered_map<char, char> decode_map(32);

    auto refence_table = MarkovChain::extract{}(reference);
    auto target_table = MarkovChain::extract{}(target);
    auto target_table_copy = target_table;
    std::pair<std::string, std::string> reference_common = get_common(refence_table);
    std::pair<std::string, std::string> target_common = get_common(target_table);

    // Add the most common into the 
    for (int i = 0; i < target.get_string_length(); i++)
    {
        decode_map[target_common.first.at(i)] = reference_common.first.at(i);
        decode_map[target_common.second.at(i)] = reference_common.second.at(i);
    }

    while(!target_table_copy.empty()) {
        bool solved_something;
        
    }
}

std::pair<std::string, std::string> get_common(const MarkovChain::markov_map const &map)
{
    std::pair<std::pair<std::string, std::string>, mpz_class> common{{"", ""}, 0};
    for (auto from : map)
    {
        for (auto to : from.second.second)
        {
            if (to.second > common.second)
            {
                common = {{from.first, to.first}, to.second};
            }
        }
    }
    return common.first;
}

std::set<std::pair<std::string, mpz_class>, less_than_pair> get_frequencies(MarkovChain::markov_map &map)
{
    std::set<std::pair<std::string, mpz_class>> frequencies;
    for (auto from : map)
    {
        frequencies.insert({from.first, from.second.first});
    }
}

struct less_than_pair
{
    bool operator()(std::pair<std::string, mpf_class> p1, std::pair<std::string, mpf_class> p2)
    {
        return p1 < p2;
    }
};