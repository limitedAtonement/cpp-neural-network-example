#include "stdafx.hpp"

#include "shallow_ffn.hpp"
#include "util.hpp"

shallow_ffn::shallow_ffn(int input_size, int output_size)
    : /*rows, columns*/
      syn{get_random_matrix(output_size, input_size)}
{
}

void shallow_ffn::train_one_epoch(std::vector<matrix> const & training_examples, std::vector<matrix> const & expected_output)
{
    for (unsigned example{0}; example < training_examples.size(); ++example)
        train(training_examples[example], expected_output[example]);
}

void shallow_ffn::train(std::vector<matrix> const & training_examples, std::vector<matrix> const & expected_output, unsigned epochs)
{
    for (unsigned epoch{0}; epoch < epochs; ++epoch)
        train_one_epoch(training_examples, expected_output);
}

matrix shallow_ffn::feed_forward(matrix const & input) const
{
    return syn * input;
}

void shallow_ffn::train(matrix const & input, matrix const & expected)
{
    matrix calculated{feed_forward(input)};
    matrix error{expected - calculated};
    matrix confidence{logistic(calculated, true)};
    /*component-wise multiplication with ::array()*/
    matrix weighted_error{error.array() * confidence.array()};
    matrix adjustment{weighted_error * input.transpose()};
    syn += adjustment;
}

/*Shows synapse values*/
std::string shallow_ffn::to_string(void) const
{
    std::ostringstream ret;
    ret << syn;
    return ret.str();
}
