#include "Test.h"
#include "LinearAlgebra.h"

Test::Test()
{

}

void Test::matrixMultiplicationTest()
{
    bool test1 = testMatrixMultiplication(
        1, 3, 2, 2, 3, 2, 2,
        {
            7.0f, 8.0f,
            9.0f, 10.0f,
            11.0f, 12.0f
        },
        {
            1.0f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f
        },
        {
            58.0f, 64.0f,
            139.0f, 154.0f
        }
    );

    bool test2 = testMatrixMultiplication(
        2, 3, 4, 1, 3, 1, 4,
        {
            13.0f, 9.0f, 7.0f, 15.0f,
            8.0f, 7.0f, 4.0f, 6.0f,
            6.0f, 4.0f, 0.0f, 3.0f
        },
        {
            3.0f, 4.0f, 2.0f
        },
        {
            83.0f, 63.0f, 37.0f, 75.0f
        }
    );

    if (test1 && test2)
    {
        std::cout << "Matrix Multiplication Test succeeded." << std::endl;
    }
}

bool Test::testMatrixMultiplication(
    uint32_t testId,
    uint32_t matrix1Rows,
    uint32_t matrix1Columns,
    uint32_t matrix2Rows,
    uint32_t matrix2Columns,
    uint32_t solutionRows,
    uint32_t solutionColumns,
    const std::vector<float> &matrix1Values,
    const std::vector<float> &matrix2Values,
    const std::vector<float> &solutionValues
)
{
    
    Matrix matrix = Matrix();
    Matrix matrix2 = Matrix();
    Matrix solution = Matrix();

    matrix.init(matrix1Rows, matrix1Columns);
    matrix2.init(matrix2Rows, matrix2Columns);
    solution.init(solutionRows, solutionColumns);

    matrix.setData(matrix1Values);
    matrix2.setData(matrix2Values);
    solution.setData(solutionValues);

    if (!matrix.multiply(matrix2).equals(solution))
    {
        std::cout << "Matrix Multiplication Test " << testId << " failed." << std::endl;
        return false;
    }

    return true;
}