#ifndef GPU_WAIFUGENERATOR_MATRIX_HH
#define GPU_WAIFUGENERATOR_MATRIX_HH

namespace WaifuGPU
{
    class Matrix
    {
    private:
        double* m_Buffer;

        size_t m_Rows;
        size_t m_Cols;
    public:
        Matrix();
        Matrix(const size_t& size);
        ~Matrix();

        void init(const size_t& rows, const size_t& cols);
        void rand();
        
        size_t get_rows();
        size_t get_cols();

        void debug_print();

        static void mul(const Matrix& mtx, const double* bfr, size_t n, const double& c);
    };
}

#endif // !GPU_WAIFUGENERATOR_MATRIX_HH
