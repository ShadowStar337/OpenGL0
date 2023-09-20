#pragma once
#include <cstdint>
#include <vector>

class Test
{
public:
    Test();
    void matrixMultiplicationTest();
private:
    bool testMatrixMultiplication(
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
    );
};