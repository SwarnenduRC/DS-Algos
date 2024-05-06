#include "SudokuSolver.hpp"

#include <iostream>
#include <exception>

#define ARRAY_LENGTH 9

void SudokuSolver::printBoard(const Matrix& board) noexcept
{
    if (board.empty())
        return;

    std::cout << "------+-------+------" << std::endl;
    for (size_t row = 0; row < ARRAY_LENGTH; ++row)
    {
        for (size_t col = 0; col < ARRAY_LENGTH; ++col)
        {
            std::cout << board[row][col] << " ";
            if ((col + 1) % 3 == 0 && (col < ARRAY_LENGTH - 1))
                std::cout << "| ";
        }
        std::cout << std::endl;
        if ((row + 1) % 3 == 0 && (row < ARRAY_LENGTH - 1))
            std::cout << "------+-------+------" << std::endl;
    }
    std::cout << "------+-------+------";
    std::cout << std::endl << std::endl;
}

size_t SudokuSolver::getNextRow(const size_t row, const size_t col) noexcept
{
    return row + (col + 1) / ARRAY_LENGTH;
}

size_t SudokuSolver::getNextCol(const size_t col) noexcept
{
    return (col + 1) % ARRAY_LENGTH;
}

size_t SudokuSolver::getGrid(const size_t row, const size_t col) noexcept
{
    return (row / 3) * 3 + col / 3;
}

std::pair<size_t, size_t> SudokuSolver::getNextEmptyCell(const size_t row, const size_t col) noexcept
{
    auto nextRow = row;
    auto nextCol = col;
    while (row < ARRAY_LENGTH)
    {
        if (m_board[nextRow][nextCol] == 0)
            return {nextRow, nextCol};

        nextRow = getNextRow(nextRow, nextCol);
        nextCol = getNextCol(nextCol);
    }
    return {ARRAY_LENGTH, 0};
}

bool SudokuSolver::isValidForRow(const int val, const size_t row) const noexcept
{
    return !m_rowValues[row][val - 1];
}

bool SudokuSolver::isValidForCol(const int val, const size_t col) const noexcept
{
    return !m_colValues[col][val - 1];
}

bool SudokuSolver::isValidForGrid(const int val, const size_t grid) const noexcept
{
    return !m_gridValues[grid][val - 1];
}

bool SudokuSolver::isValid(const size_t row, const size_t col) const noexcept
{
    const auto grid = getGrid(row, col);
    const auto combi = m_rowValues[row] | m_colValues[col] | m_gridValues[grid];
    return !combi.all();
}

void SudokuSolver::initializeBoard(const Matrix& board) noexcept
{
    if (board.empty())
        return;
    
    m_board = board;
    populateValues();
}

void SudokuSolver::initializeBoard(const std::array<char, 81>& board) noexcept
{
    if (board.empty())
        return;

    std::array<int, 81> flatBoard;
    for (size_t idx = 0; idx < board.size(); ++idx)
    {
        if (board[idx] == ' ' || board[idx] == '-' || board[idx] == '.')
        {
            flatBoard[idx] = 0;
        }
        else
        {
            auto val = static_cast<int>(board[idx] - '0');
            flatBoard[idx] = val;
        }
    }
    initializeBoard(flatBoard);
}

void SudokuSolver::initializeBoard(const std::array<std::string, 81>& board) noexcept
{
    if (board.empty())
        return;

    std::array<int, 81> flatBoard;
    for (size_t idx = 0; idx < board.size(); ++idx)
    {
        if (board[idx] == "" || board[idx] == " " || board[idx] == "-" || board[idx] == ".")
        {
            flatBoard[idx] = 0;
        }
        else
        {
            auto val = std::stoi(board[idx]);
            flatBoard[idx] = val;
        }
    }
    initializeBoard(flatBoard);
}

void SudokuSolver::initializeBoard(const std::array<int, 81>& board) noexcept
{
    if (board.empty())
        return;

    for (size_t arrIdx = 0, boardRowIdx = 0; arrIdx < board.size() && boardRowIdx < ARRAY_LENGTH; ++boardRowIdx)
    {
        size_t colIdx = 0;
        std::array<int, ARRAY_LENGTH> row;
        while (colIdx < ARRAY_LENGTH)
        {
            row[colIdx] = board[arrIdx];
            ++colIdx;
            ++arrIdx;
        }
        m_board[boardRowIdx] = row;
    }
    populateValues();
}

Matrix SudokuSolver::getBoard() const noexcept
{
    return m_board;
}

void SudokuSolver::populateValues() noexcept
{
    for (auto row = 0; row < ARRAY_LENGTH; ++row)
    {
        for (auto col = 0; col < ARRAY_LENGTH; ++col)
        {
            auto val = m_board[row][col];
            if (0 != val)
            {
                val = val - 1;
                m_rowValues[row].set(val);
                m_colValues[col].set(val);
                auto grid = getGrid(row, col);
                m_gridValues[grid].set(val);
            }
        }
    }
}

bool SudokuSolver::solveBoard() noexcept
{
    return solve(0, 0);
}

bool SudokuSolver::solve(const size_t startRow, const size_t startCol) noexcept
{
    auto [row, col] = getNextEmptyCell(startRow, startCol);
    if (row == ARRAY_LENGTH)
        return true;
    
    if (!isValid(row, col))
        return false;

    auto grid = getGrid(row, col);
    for (auto val = 0; val < ARRAY_LENGTH; val++)
    {
        auto newVal = val + 1;
        if (isValidForRow(newVal, row) && isValidForCol(newVal, col) && isValidForGrid(newVal, grid))        
        {
            m_board[row][col] = newVal;
            
            m_rowValues[row].set(val);
            m_colValues[col].set(val);
            m_gridValues[grid].set(val);
            if (solve(row, col))    // Here the recursion happenes
                return true;

            m_rowValues[row].reset(val);    // Here the backtracking
            m_colValues[col].reset(val);
            m_gridValues[grid].reset(val);
        }
    }
    m_board[row][col] = 0;  
    return false;
}

