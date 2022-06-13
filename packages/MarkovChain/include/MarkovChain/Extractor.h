#ifndef MARKOV_CHAIN_EXTRACTOR_H
#define MARKOV_CHAIN_EXTRACTOR_H

#include <unordered_map>

#include "gmpxx.h"

#include "MarkovChain.h"

namespace MarkovChain
{
    typedef std::unordered_map<std::string, mpz_class> markov_to;
    typedef std::pair<mpz_class, markov_to> markov_from;
    typedef std::unordered_map<std::string, markov_from> markov_map;

    struct extract
    {
        extract() = delete;
        const markov_map &operator()(MarkovChain &chain);
        std::unordered_map<std::string, mpf_class> get_probability(MarkovChain &chain, std::string from);
    };
} // namespace MarkovChain

template <class T1, class T2>
struct std::hash<std::pair<T1, T2>>
{
    std::size_t operator()(std::pair<T1, T2> const &s) const noexcept
    {
        std::size_t h1 = std::hash<T1>{}(s.first);
        std::size_t h2 = std::hash<T2>{}(s.second);
        return h1 ^ (h2 << 1); // or use boost::hash_combine
    }
};

#endif // MARKOV_CHAIN_EXTRACTOR_H