#include "MarkovChain/MarkovChain.h"

#include <unordered_map>
#include <cassert>

#include "MarkovChain/Extractor.h"

MarkovChain::MarkovChain::MarkovChain(int string_length)
    : information_map(new markov_map(string_length * 26)),
      string_length(string_length)
{
}

MarkovChain::MarkovChain::~MarkovChain()
{
    delete (markov_map *)this->information_map;
}

void MarkovChain::MarkovChain::add_sample(std::string from, std::string to)
{
    this->_add_samples(from, to, 1);
}

template <class T>
void MarkovChain::MarkovChain::_add_samples(std::string from, std::string to, T count)
{
    // Assert that to and from have the same length as we defined.
    assert(from.length() == this->string_length);
    assert(to.length() == this->string_length);

    markov_map &inf_map = *(markov_map *)this->information_map;
    auto from_bucket = inf_map.find(from);
    if (from_bucket != inf_map.end())
    {
        auto to_bucket = from_bucket->second.second.find(to);
        if (to_bucket != from_bucket->second.second.end())
        {
            to_bucket->second += count;
        }
        else
        {
            from_bucket->second.second[to] = count;
        }
        from_bucket->second.first += count; // Increase sample count
    }
    else
    {
        inf_map.emplace(from, markov_from{1, markov_to(string_length * 26)});
        inf_map[from].second[to] = count;
        inf_map[from].first = count;
    }
}

double MarkovChain::MarkovChain::get_probability(std::string from, std::string to) const
{
    // Assert that to and from have the same length as we defined.
    assert(from.length() == this->string_length);
    assert(to.length() == this->string_length);

    markov_map &inf_map = *(markov_map *)this->information_map;
    auto from_bucket = inf_map.find(from);
    if (from_bucket != inf_map.end())
    {
        auto to_bucket = from_bucket->second.second.find(to);
        if (to_bucket != from_bucket->second.second.end())
        {
            mpz_class sample_count = from_bucket->second.first;
            mpf_class probability = to_bucket->second;
            probability /= sample_count;
            return probability.get_d();
        }
    }
    return 0;
}

const int MarkovChain::MarkovChain::get_string_length() const
{
    return this->string_length;
}

void MarkovChain::MarkovChain::add_samples(std::istream &istream)
{
    markov_map &inf_map = *((markov_map *)this->information_map);
    while (!istream.eof())
    {
        char *from = new char[this->string_length];
        char *to = new char[this->string_length];
        istream.read(from, this->string_length);
        istream.read(to, this->string_length);

        std::string instances;
        istream >> instances;

        this->_add_samples(from, to, mpz_class(instances));
    }
}

std::ostream &MarkovChain::operator<<(std::ostream &os, const MarkovChain &chain)
{
    for (auto from : *((markov_map *)chain.information_map))
    {
        for (auto to : from.second.second)
        {
            os
                << from.first
                << to.first
                << to.second.get_str()
                << "\n";
        }
    }
    return os;
}
