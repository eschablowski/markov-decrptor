#include "MarkovChain/Builder.h"

#define BUFFER_SIZE 1024

MarkovChain::MarkovChain MarkovChain::build(std::istream &input_stream, std::ostream &output_stream, int string_length)
{
    MarkovChain markov_chain(string_length);
    char buff[BUFFER_SIZE];
    char buff2[BUFFER_SIZE];
    input_stream.read(buff, BUFFER_SIZE);
    char from[string_length + 1], to[string_length + 1];
    from[string_length] = to[string_length] = '\0';
    int processable_charachters;

    while (!input_stream.eof())
    {
        // Filter out newlines, etc.
        processable_charachters = 0;
        for (int i = 0, j = 0; i < BUFFER_SIZE; i++)
        {
            switch (buff[i])
            {
            case '\r':
                continue;
            case '\n':
            case '\t':
            case ' ':
                buff2[j++] = ' ';
                processable_charachters++;
                continue;
            default:
                processable_charachters++;
                buff2[j++] = buff[i];
                continue;
            }
        }
        for (int i = 0; i < processable_charachters - 2 * string_length && buff[i + 2 * string_length] != '\0'; i++)
        {
            for (int j = 0; j < string_length; j++)
            {
                from[j] = buff2[i + j];
                to[j] = buff2[i + j + string_length];
            }
            markov_chain.add_sample(std::string(from), std::string(to));
        }
        // Move the back of the string to the front
        for (int i = 0; i < string_length - 1; i++)
        {
            buff[i] = buff2[processable_charachters - i - 1];
        }
        input_stream.read(buff + string_length, BUFFER_SIZE - string_length);
    }

    return markov_chain;
}