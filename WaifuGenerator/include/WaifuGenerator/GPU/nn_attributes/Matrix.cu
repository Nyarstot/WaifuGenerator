#include "Matrix.hh"

#include "../cuda/cu_core.hh"

WaifuGPU::Matrix::Matrix()
{
    m_Rows = 0;
    m_Cols = 0;

    m_Buffer = nullptr;
}

WaifuGPU::Matrix::Matrix(const size_t& size) : m_Rows(size), m_Cols(size)
{
    this->init(m_Rows, m_Cols);
}

WaifuGPU::Matrix::~Matrix()
{
    cudaFree(m_Buffer);
    m_Buffer = nullptr;
}

void WaifuGPU::Matrix::init(const size_t& rows, const size_t& cols)
{
    m_Rows = rows;
    m_Cols = cols;

    if ((m_Rows > 0) && (m_Cols > 0)) {
        cudaMalloc((void**)&m_Buffer, m_Rows * m_Cols * sizeof(double));
        cudaMemset(m_Buffer, 0, m_Rows * m_Cols * sizeof(double));
    }
}

void WaifuGPU::Matrix::rand()
{
    double rand_value = 0;

    for (size_t i{}; i < m_Rows; i++) {
        for (size_t j{}; j < m_Cols; j++) {
            rand_value = ((std::rand() % 100)) * 0.03 / (m_Rows + 35);
            cudaMemcpy(&m_Buffer[j * m_Rows + i], &rand_value, sizeof(double), cudaMemcpyHostToDevice);
        }
    }
}

size_t WaifuGPU::Matrix::get_rows()
{
    return this->m_Rows;
}

size_t WaifuGPU::Matrix::get_cols()
{
    return this->m_Cols;
}

void WaifuGPU::Matrix::debug_print()
{
    double tmp;

    for (size_t i{}; i < m_Rows; i++) {
        for (size_t j{}; j < m_Cols; j++) {
            cudaMemcpy(&tmp, &m_Buffer[j * m_Rows + i], sizeof(double), cudaMemcpyDeviceToHost);
            std::cout << tmp << " ";
        }
        std::cout << "\n";
    }
}