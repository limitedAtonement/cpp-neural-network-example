#include "stdafx.hpp"

#include "util.hpp"

double sigmoid(double value, bool deriv)
{
    if (deriv)
        return sigmoid(value) * (1 - sigmoid(value));
    return 1 / (1 + std::exp(-value));
}

matrix sigmoid(matrix const & value, bool deriv)
{
    matrix ret{value.rows(), value.cols()};
    for (int row{0}; row < value.rows(); ++row)
        for (int col{0}; col < value.cols(); ++col)
            ret(row, col) = sigmoid(value(row, col), deriv);
    return ret;
}

matrix get_random_matrix(int rows, int cols)
{
    const int seed{1};
    static std::mt19937 mt{seed};
    static std::uniform_real_distribution<> dist{-1, 1};
    matrix ret{rows, cols};
    for (int row{0}; row < rows; ++row)
        for (int col{0}; col < cols; ++col)
            ret(row, col) = dist(mt);
    return ret;
}
