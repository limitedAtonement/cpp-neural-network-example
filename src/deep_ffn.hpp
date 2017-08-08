#pragma once
#include "util.hpp"

/**
 * A double-layer feedforward network.
 */
struct deep_ffn
{
    deep_ffn(int input_size, int output_size, int hidden_nodes);
    /*
     * Returns a column vector
     */
    matrix feed_forward(matrix const & input) const;
    std::string to_string(void) const;
    /**
     * inputs and outputs should be column vectors.
     */
    void train(std::vector<matrix> const & training_examples, std::vector<matrix> const & expected_output, unsigned epochs);
    void quick_train(matrix const &, matrix const &);

private:
    /*output_size rows, input_size columns*/
    matrix syn0;
    matrix syn1;

    void train_synapse(matrix const &, matrix &, matrix const &, matrix const &);
    void train(matrix const &, matrix const &);
    void train_one_epoch(std::vector<matrix> const &, std::vector<matrix> const &);
};
