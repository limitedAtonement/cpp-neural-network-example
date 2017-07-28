#pragma once
#include "util.hpp"

/**
 * A single-layer feedforward network.
 */
struct shallow_ffn
{
    shallow_ffn(int input_size, int output_size);
    /*
     * Returns a column vector
     */
    matrix feed_forward(matrix const & input) const;
    std::string to_string(void) const;
    /**
     * inputs and outputs should be column vectors.
     */
    void train(std::vector<matrix> const & training_examples, std::vector<matrix> const & expected_output, unsigned epochs);

private:
    /*output_size rows, input_size columns*/
    matrix syn;

    void train(matrix const &, matrix const &);
    void train_one_epoch(std::vector<matrix> const &, std::vector<matrix> const &);
};
