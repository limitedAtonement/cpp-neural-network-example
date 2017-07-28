#pragma once

using matrix = Eigen::MatrixXd;

double sigmoid(double value, bool deriv = false);
matrix sigmoid(matrix const & value, bool deriv = false);
matrix get_random_matrix(int rows, int cols);

template <typename A, typename... B>
matrix create_row_vector(A arg1, B... args)
{
    /*rows, cols*/
    matrix ret{1, sizeof...(args) + 1};
    ((ret << arg1), ..., args);
    return ret;
}

template <typename A, typename... B>
matrix create_column_vector(A arg1, B... args)
{
    /*rows, cols*/
    matrix ret{sizeof...(args) + 1, 1};
    ((ret << arg1), ..., args);
    return ret;
}
