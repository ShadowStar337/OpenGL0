#include <iostream>
#include "LinearAlgebra.h"

Matrix::Matrix()
{

}

void Matrix::init(uint32_t rows, uint32_t columns)
{
    data.reserve(rows * columns);
    this->rows = rows;
    this->columns = columns;

    clear();
}

void Matrix::setData(const std::vector<float> &newData)
{
    if (newData.size() != rows * columns)
    {
        std::cout << "[Matrix]: Matrix::setData failed." << std::endl;
        std::cout << "Expected size: " << rows * columns << std::endl;
        std::cout << "Actual size: " << newData.size() << std::endl;
    }

    data = newData;
}

void Matrix::clear()
{
    data.clear();
    for (uint32_t i = 0; i < rows * columns; i++)
    {
        data.push_back(0.0f);
    }
}

bool Matrix::equals(const Matrix &otherMatrix) const
{
    return data == otherMatrix.getData();
}

void Matrix::setToIdentity()
{
    for (uint32_t i = 0; i < rows; i++)
    {
        for (uint32_t j = 0; j < columns; j++)
        {
            data[i * columns + j] = 0.0f;
            if (i == j)
            {
                data[i * columns + j] = 1.0f;
            }
        }
    }
}

Matrix Matrix::multiply(const Matrix& otherMatrix) const
{
    Matrix newMatrix = Matrix();
    newMatrix.init(otherMatrix.getRows(), columns);

    if (otherMatrix.getColumns() != rows)
    {
        std::cout << "[Matrix]: Matrix dimensions do not match." << std::endl;
        std::cout << "Expected columns: " << rows << std::endl;
        std::cout << "Actual columns: " << otherMatrix.getColumns() << std::endl;
        return newMatrix;
    }

    const std::vector<float>& otherData = otherMatrix.getData();

    std::vector<float> newData;
    newData.reserve(rows * columns);

    for (uint32_t i = 0; i < otherMatrix.getRows(); i++)
    {
        for (uint32_t j = 0; j < columns; j++)
        {
            float sum = 0.0f;
            uint32_t l = otherMatrix.getColumns() * i;
            uint32_t m = j;
            for (uint32_t k = 0; k < rows; k++)
            {
                sum += otherData[l] * data[m];
                l += 1;
                m += columns;
            }
            newData.push_back(sum);
        }
    }

    newMatrix.setData(newData);

    return newMatrix;
}



std::ostream &operator<<(std::ostream &outputStream, const Matrix &matrix)
{
    const std::vector<float> &matrixData = matrix.getData();
    for (uint32_t i = 0; i < matrix.getRows(); i++)
    {
        for (uint32_t j = 0; j < matrix.getColumns(); j++)
        {
            outputStream << matrixData[i * matrix.getColumns() + j] << ' ';
        }
        outputStream << std::endl;
    }

    return outputStream;
}