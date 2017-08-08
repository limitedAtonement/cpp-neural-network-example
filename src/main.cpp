#include "stdafx.hpp"

#include "deep_ffn.hpp"
#include "shallow_ffn.hpp"

std::vector<matrix> deep_training_examples{
    create_column_vector(0, 1, 1),
    create_column_vector(0, 0, 1),
    create_column_vector(0, 0, 0),
    create_column_vector(1, 1, 0)};
std::vector<matrix> deep_expected_output{
    create_column_vector(0),
    create_column_vector(1),
    create_column_vector(0),
    create_column_vector(1),
};
const unsigned deep_epochs{5000};
const int hidden_neurons{4};
matrix deep_untrained_input{create_column_vector(1, 1, 0)};
matrix deep_untrained_expected_output{create_column_vector(1)};

void print_summary(deep_ffn const & neural_network)
{
    std::cout << "Deep trained examples:\n";
    for (unsigned example{0}; example < deep_training_examples.size(); ++example)
    {
        auto input{deep_training_examples[example]};
        auto expected{deep_expected_output[example]};
        auto calculated{neural_network.feed_forward(input)};
        auto error{expected - calculated};
        std::cout << "  Input:             {" << input.transpose() << "}\n";
        std::cout << "  Output:            {" << calculated.transpose() << "}\n";
        std::cout << "  Expected output:   {" << expected.transpose() << "}\n";
        std::cout << "     Error:             {" << error << "}\n";
    }
    auto input{deep_untrained_input};
    auto expected{deep_untrained_expected_output};
    auto calculated{neural_network.feed_forward(input)};
    auto error{expected - calculated};
    std::cout << "Untrained input:     {" << input.transpose() << "}\n";
    std::cout << "Calculated output:   {" << calculated.transpose() << "}\n";
    std::cout << "Expected output:     {" << expected.transpose() << "}\n";
    std::cout << "   Untrained Error:      {" << error << "}\n\n";
}

void deep_feed_forward()
{
    deep_ffn f{(int)deep_training_examples[0].rows(), (int)deep_expected_output[0].rows(), hidden_neurons};
    f.train(deep_training_examples, deep_expected_output, deep_epochs);
    print_summary(f);
}

std::vector<matrix> shallow_training_examples{
    create_column_vector(-1, 1, 1),
    create_column_vector(1, 1, 1),
    create_column_vector(-1, -1, 1),
    create_column_vector(1, -1, 1)};
std::vector<matrix> shallow_expected_output{
    create_column_vector(-1),
    create_column_vector(1),
    create_column_vector(-1),
    create_column_vector(1),
};
const unsigned shallow_epochs{15};
matrix shallow_untrained_input{create_column_vector(1, 1, -1)};
matrix shallow_untrained_expected_output{create_column_vector(1)};

void print_summary(shallow_ffn const & neural_network)
{
    std::cout << "Shallow trained examples:\n";
    for (unsigned example{0}; example < shallow_training_examples.size(); ++example)
    {
        auto input{shallow_training_examples[example]};
        auto expected{shallow_expected_output[example]};
        auto calculated{neural_network.feed_forward(input)};
        auto error{expected - calculated};
        std::cout << "  Input:             {" << input.transpose() << "}\n";
        std::cout << "  Output:            {" << calculated.transpose() << "}\n";
        std::cout << "  Expected output:   {" << expected.transpose() << "}\n";
        std::cout << "  Error:             {" << error << "}\n";
    }
    auto input{shallow_untrained_input};
    auto expected{shallow_untrained_expected_output};
    auto calculated{neural_network.feed_forward(input)};
    auto error{expected - calculated};
    std::cout << "Untrained input:     {" << input.transpose() << "}\n";
    std::cout << "Calculated output:   {" << calculated.transpose() << "}\n";
    std::cout << "Expected output:     {" << expected.transpose() << "}\n";
    std::cout << "Error:               {" << error << "}\n\n";
}

void shallow_feed_forward(void)
{
    shallow_ffn f{(int)shallow_training_examples[0].rows(), (int)shallow_expected_output[0].rows()};
    f.train(shallow_training_examples, shallow_expected_output, shallow_epochs);
    print_summary(f);
}

int main(int /*argc*/, char const ** /*args*/)
{
    shallow_feed_forward();
    deep_feed_forward();
    return 0;
}
