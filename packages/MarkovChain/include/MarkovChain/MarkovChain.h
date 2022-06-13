namespace MarkovChain
{
    class MarkovChain;
    struct extract;
} // namespace MarkovChain


#ifndef MARKOV_CHAIN_MARKOV_CHAIN_H
#define MARKOV_CHAIN_MARKOV_CHAIN_H

#include <string>
#include <istream>
#include <ostream>

namespace MarkovChain
{
    /**
     * @brief This implements a basic Markov Chain which is able to add samples and retrieve probabilities
     */
    class MarkovChain
    {
    private:
        /**
         * @brief This is the `unordered_map` that holds all the sample counts
         */
        void *information_map;
        /**
         * @brief The length of the from and to strings for this Markov Chain
         */
        const int string_length;

        template<class T> void _add_samples(std::string from, std::string to, T count);

    public:
        MarkovChain(int string_length);
        ~MarkovChain();

        void add_sample(std::string from, std::string to);
        void add_samples(std::istream &stream);
        double get_probability(std::string from, std::string to) const;

        const int get_string_length() const;

        friend std::ostream &operator<<(std::ostream &os, const MarkovChain &chain);
        friend std::istream &operator>>(std::istream &os, const MarkovChain &chain);
        friend extract;
    };
    std::ostream &operator<<(std::ostream &os, const MarkovChain &chain);
} // namespace MarkovChain

#endif // MARKOV_CHAIN_MARKOV_CHAIN_H