/**
 * @file SudokuSolver.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _SUDOKU_SOLVER_HPP_
#define _SUDOKU_SOLVER_HPP_

#include <array>
#include <bitset>

using Matrix = std::array<std::array<int, 9>, 9>;
using BitSetArray = std::array<std::bitset<9>, 9>;

class SudokuSolver
{
    public:
        static void printBoard(const Matrix& board) noexcept;
        static size_t getNextRow(const size_t row, const size_t col) noexcept;
        static size_t getNextCol(const size_t col) noexcept;
        static size_t getGrid(const size_t row, const size_t col) noexcept;
        
        void initializeBoard(const std::array<const std::string, 81>& board) noexcept;
        void initializeBoard(const std::array<int, 81>& board) noexcept;
        void initializeBoard(const Matrix& board) noexcept;
        bool solveBoard() noexcept;
        Matrix getBoard() const noexcept;

    protected:
        void populateValues() noexcept;
        bool isValid(const size_t row, const size_t col) const noexcept;
        std::pair<size_t, size_t> getNextEmptyCell(const size_t row, const size_t col) noexcept;
        bool solve(const size_t startRow, const size_t startCol) noexcept;

    private:
        Matrix m_board;
        BitSetArray m_rowValues = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        BitSetArray m_colValues = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        BitSetArray m_gridValues = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
};

#endif