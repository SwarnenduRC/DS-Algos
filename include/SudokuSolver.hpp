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
        /**
         * @brief Prints the Sudoku board
         *        It prints out a given sudoku board in a pretty format
         * @param board The board to be printed
         */
        static void printBoard(const Matrix& board) noexcept;
        /**
         * @brief Gets the next row
         *        It gets the next row for current row & col values
         * 
         * @param row The current row
         * @param col The column in the current row
         * @return size_t The next row
         */
        static size_t getNextRow(const size_t row, const size_t col) noexcept;
        /**
         * @brief Gets the next column number
         *        It returns the next colum for the given column
         * 
         * @param col The current column
         * @return size_t The next column
         */
        static size_t getNextCol(const size_t col) noexcept;
        /**
         * @brief Gets the grid to which a cell belongs to
         *        For a given cell, i.e.; Matrix[row][col]
         *        it returns the the grid no to which the
         *        cell belongs to. Grids are starting from
         *        0 and goes upto 8 (9 in total)
         * 
         * @param row The current row
         * @param col The current column
         * @return size_t The grid
         */
        static size_t getGrid(const size_t row, const size_t col) noexcept;

        /**
         * @brief Checks if a digit is valid for the the row
         *        It checks if a new numbe/digit (1 to 9) which
         *        needs to be inserted in an empty cell stands
         *        valid for the current row
         * 
         * @param val The value which needs to be checked
         * @param row The row number where the value is to be inserted
         * @return true If valid, otherwise 
         * @return false 
         */
        bool isValidForRow(const int val, const size_t row) const noexcept;
        /**
         * @brief Checks if a digit is valid for the the column
         *        It checks if a new numbe/digit (1 to 9) which
         *        needs to be inserted in an empty cell stands
         *        valid for the current column
         * 
         * @param val The value which needs to be checked
         * @param col The column number where the value is to be inserted
         * @return true If valid, otherwise 
         * @return false 
         */
        bool isValidForCol(const int val, const size_t col) const noexcept;
        /**
         * @brief Checks if a digit is valid for the the grid
         *        It checks if a new numbe/digit (1 to 9) which
         *        needs to be inserted in an empty cell stands
         *        valid for the current grid in which the cell exists
         * 
         * @param val The value which needs to be checked
         * @param grid The grid number where the cell is belonged to
         * @return true If valid, otherwise 
         * @return false 
         */
        bool isValidForGrid(const int val, const size_t grid) const noexcept;
        /**
         * @brief Returns the internal Matrix
         * 
         * @return Matrix The matrix
         */
        Matrix getBoard() const noexcept;
        
        /**
         * @brief Initializes a sudoku board
         *        It initilizes a sudoku board aka 9X9 matrix
         *        from an arrary of 81 characters. Internally
         *        it calls @initializeBoard(const Matrix& board)
         * 
         * @param board The character array
         */
        void initializeBoard(const std::array<char, 81>& board) noexcept;
        /**
         * @brief Initializes a sudoku board
         *        It initilizes a sudoku board aka 9X9 matrix
         *        from an arrary of 81 strings. Internally
         *        it calls @initializeBoard(const Matrix& board)
         * 
         * @param board The string array
         */
        void initializeBoard(const std::array<std::string, 81>& board) noexcept;
        /**
         * @brief Initializes a sudoku board
         *        It initilizes a sudoku board aka 9X9 matrix
         *        from an arrary of 81 integers. Internally
         *        it calls @initializeBoard(const Matrix& board)
         * 
         * @param board The interger array
         */
        void initializeBoard(const std::array<int, 81>& board) noexcept;
        /**
         * @brief Initializes a sudoku board from a 9X9 matrix
         *        It initializes the sudoku board from a given
         *        9X9 integer matrix and also populates the values
         *        for solving the board. See @populateValues
         * 
         * @param board The board
         */
        void initializeBoard(const Matrix& board) noexcept;
        /**
         * @brief It solves a sudoku board
         *        It solves a sudoku board from a given flat board
         *        using the populated values and inserting new possible
         *        values into each empty cell
         * 
         * @return true If it can solve a board, otherwise 
         * @return false 
         */
        bool solveBoard() noexcept;

    protected:
        /**
         * @brief Populates the values from a flat board
         *        It populates the values from a given flat
         *        board so that while inserting new possible
         *        values in each empty cell we can check for
         *        cross reference
         */
        void populateValues() noexcept;
        /**
         * @brief Checks if a value is valid or not
         *        It checks the validity of a value
         *        (1 to 9) while entering into an empty
         *        cell aka Matrix[row][col], in respect
         *        to the row, column and the grid the cell
         *        belongs to
         * 
         * @param row The row number
         * @param col The column number
         * @return true If the value is ok to be entered, otherwise
         * @return false 
         */
        bool isValid(const size_t row, const size_t col) const noexcept;
        /**
         * @brief Gets the next empty cell in the board
         *        It returns the next empty cell in the board
         *        for a given row & column combination
         * 
         * @param row The current row number
         * @param col The current column number
         * @return std::pair<size_t, size_t> Next empty cell in a row-column pair
         */
        std::pair<size_t, size_t> getNextEmptyCell(const size_t row, const size_t col) noexcept;
        /**
         * @brief Solves a sudoku board
         *        It solves a sudoku board from a given flat board
         *        (if possible at all) using recusrsion and backtracking.
         * 
         * @param startRow Starting row (assumes for the previous rows the board is already resolved)
         * @param startCol Starting column (assumes for the previous columns the board is already resolved)
         * @return true If it is able to solve the borad, otherwise 
         * @return false 
         */
        bool solve(const size_t startRow, const size_t startCol) noexcept;

    private:
        Matrix m_board;
        BitSetArray m_rowValues = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        BitSetArray m_colValues = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        BitSetArray m_gridValues = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
};

#endif