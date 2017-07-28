#include "stdafx.hpp"

#include "shallow_ffn.hpp"

std::vector<matrix> training_examples{
    create_column_vector(-1, 1, 1),
    create_column_vector(1, 1, 1),
    create_column_vector(-1, -1, 1),
    create_column_vector(1, -1, 1)};

std::vector<matrix> expected_output{
    create_column_vector(-1),
    create_column_vector(1),
    create_column_vector(-1),
    create_column_vector(1),
};

const unsigned epochs{15};

matrix untrained_input{create_column_vector(1, 1, -1)};

matrix untrained_expected_output{create_column_vector(1)};

void print_summary(shallow_ffn const & neural_network)
{
    std::cout << "Trained examples:\n";
    for (unsigned example{0}; example < training_examples.size(); ++example)
    {
        auto input{training_examples[example]};
        auto expected{expected_output[example]};
        auto calculated{neural_network.feed_forward(input)};
        auto error{expected - calculated};
        std::cout << "  Input:             {" << input.transpose() << "}\n";
        std::cout << "  Output:            {" << calculated.transpose() << "}\n";
        std::cout << "  Expected output:   {" << expected.transpose() << "}\n";
        std::cout << "  Error:             {" << error << "}\n\n";
    }
    auto input{untrained_input};
    auto expected{untrained_expected_output};
    auto calculated{neural_network.feed_forward(input)};
    auto error{expected - calculated};
    std::cout << "\n\nUntrained input:     {" << input.transpose() << "}\n";
    std::cout << "Calculated output:   {" << calculated.transpose() << "}\n";
    std::cout << "Expected output:     {" << expected.transpose() << "}\n";
    std::cout << "Error:               {" << error << "}\n";
}

void simple_feed_forward(void)
{
    shallow_ffn f{(int)training_examples[0].rows(), (int)expected_output[0].rows()};
    f.train(training_examples, expected_output, epochs);
    print_summary(f);
}

int main(int /*argc*/, char const ** /*args*/)
{
    simple_feed_forward();
    return 0;
}
