#include "stdafx.hpp"

#include "deep_ffn.hpp"
#include "util.hpp"

deep_ffn::deep_ffn(int input_size, int output_size, int hidden_nodes)
    : /*rows, columns*/
      syn0{get_random_matrix(hidden_nodes, input_size)},
      syn1{get_random_matrix(output_size, hidden_nodes)}
{
}

void deep_ffn::train_one_epoch(std::vector<matrix> const & training_examples, std::vector<matrix> const & expected_output)
{
    for (unsigned example{0}; example < training_examples.size(); ++example)
        train(training_examples[example], expected_output[example]);
}

double learning_rate = 25;
void deep_ffn::train(std::vector<matrix> const & training_examples, std::vector<matrix> const & expected_output, unsigned epochs)
{
    for (unsigned epoch{0}; epoch < epochs; ++epoch)
        train_one_epoch(training_examples, expected_output);
}

matrix deep_ffn::feed_forward(matrix const & input) const
{
    return logistic(syn1 * logistic(syn0 * input));
}

void deep_ffn::train(matrix const & input, matrix const & expected)
{
    matrix calculated0{logistic(syn0 * input)};
    matrix calculated1{logistic(syn1 * calculated0)};
    matrix out_error{calculated1 - expected};
    matrix out_sigmoid{logistic(calculated1)};
    /*Weights between hidden and output*/
    matrix weighted_out_with_error{out_sigmoid.array() * out_error.array()};
    matrix weighted_out_with_error_with_learning_rate{weighted_out_with_error * learning_rate};
    matrix adjustment1{weighted_out_with_error_with_learning_rate * calculated0.transpose()};
    /*Weights between input and hidden*/
    matrix err_with_hid{out_sigmoid.array() * out_error.array()};
    matrix extra{err_with_hid * syn1};
    matrix extra_with_learning{extra * learning_rate};
    matrix hid_sigmoid{logistic(calculated0, true)};
    matrix extra_with_hid{hid_sigmoid.array() * extra_with_learning.transpose().array()};
    matrix adjustment0{extra_with_hid * input.transpose()};
    syn0 -= adjustment0;
    syn1 -= adjustment1;
}

/*Shows synapse values*/
std::string deep_ffn::to_string(void) const
{
    std::ostringstream ret;
    ret << syn0 << '\n';
    ret << syn1;
    return ret.str();
}
