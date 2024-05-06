#include "SudokuSolverTest.hpp"

TEST_F(SudokuSolverTest, testInitializeBoard)
{
    {
        std::array<char, 81> flatBoard = 
            {'5', '3', '.', '.', '7', '.', '.', '.', '.', 
             '6', '.', '.', '1', '9', '5', '.', '.', '.', 
             '.', '9', '8', '.', '.', '.', '.', '6', '.', 
             '8', '.', '.', '.', '6', '.', '.', '.', '3', 
             '4', '.', '.', '8', '.', '3', '.', '.', '1', 
             '7', '.', '.', '.', '2', '.', '.', '.', '6', 
             '.', '6', '.', '.', '.', '.', '2', '8', '.', 
             '.', '.', '.', '4', '1', '9', '.', '.', '5', 
             '.', '.', '.', '.', '8', '.', '.', '7', '9'};

        std::array<std::array<int, 9>, 9> expectedBoard =
            { { { 5, 3, 0, 0, 7, 0, 0, 0, 0 }
              , { 6, 0, 0, 1, 9, 5, 0, 0, 0 }
              , { 0, 9, 8, 0, 0, 0, 0, 6, 0 }
              , { 8, 0, 0, 0, 6, 0, 0, 0, 3 }
              , { 4, 0, 0, 8, 0, 3, 0, 0, 1 }
              , { 7, 0, 0, 0, 2, 0, 0, 0, 6 }
              , { 0, 6, 0, 0, 0, 0, 2, 8, 0 }
              , { 0, 0, 0, 4, 1, 9, 0, 0, 5 }
              , { 0, 0, 0, 0, 8, 0, 0, 7, 9 } } };
        
        m_SudokuBoard.initializeBoard(flatBoard);
        EXPECT_EQ(expectedBoard, m_SudokuBoard.getBoard());
    }
    {
        std::array<std::string, 81> flatBoard = 
            {"5", "3", ".", ".", "7", ".", ".", ".", ".", 
             "6", ".", ".", "1", "9", "5", ".", ".", ".", 
             ".", "9", "8", ".", ".", ".", ".", "6", ".", 
             "8", ".", ".", ".", "6", ".", ".", ".", "3", 
             "4", ".", ".", "8", ".", "3", ".", ".", "1", 
             "7", ".", ".", ".", "2", ".", ".", ".", "6", 
             ".", "6", ".", ".", ".", ".", "2", "8", ".", 
             ".", ".", ".", "4", "1", "9", ".", ".", "5", 
             ".", ".", ".", ".", "8", ".", ".", "7", "9"};

        std::array<std::array<int, 9>, 9> expectedBoard =
            { { { 5, 3, 0, 0, 7, 0, 0, 0, 0 }
              , { 6, 0, 0, 1, 9, 5, 0, 0, 0 }
              , { 0, 9, 8, 0, 0, 0, 0, 6, 0 }
              , { 8, 0, 0, 0, 6, 0, 0, 0, 3 }
              , { 4, 0, 0, 8, 0, 3, 0, 0, 1 }
              , { 7, 0, 0, 0, 2, 0, 0, 0, 6 }
              , { 0, 6, 0, 0, 0, 0, 2, 8, 0 }
              , { 0, 0, 0, 4, 1, 9, 0, 0, 5 }
              , { 0, 0, 0, 0, 8, 0, 0, 7, 9 } } };
        
        m_SudokuBoard.initializeBoard(flatBoard);
        EXPECT_EQ(expectedBoard, m_SudokuBoard.getBoard());
    }
    {
        std::array<int, 81> flatBoard = 
            {5, 3, 0, 0, 7, 0, 0, 0, 0, 
             6, 0, 0, 1, 9, 5, 0, 0, 0, 
             0, 9, 8, 0, 0, 0, 0, 6, 0, 
             8, 0, 0, 0, 6, 0, 0, 0, 3, 
             4, 0, 0, 8, 0, 3, 0, 0, 1, 
             7, 0, 0, 0, 2, 0, 0, 0, 6, 
             0, 6, 0, 0, 0, 0, 2, 8, 0, 
             0, 0, 0, 4, 1, 9, 0, 0, 5, 
             0, 0, 0, 0, 8, 0, 0, 7, 9};

        std::array<std::array<int, 9>, 9> expectedBoard =
            { { { 5, 3, 0, 0, 7, 0, 0, 0, 0 }
              , { 6, 0, 0, 1, 9, 5, 0, 0, 0 }
              , { 0, 9, 8, 0, 0, 0, 0, 6, 0 }
              , { 8, 0, 0, 0, 6, 0, 0, 0, 3 }
              , { 4, 0, 0, 8, 0, 3, 0, 0, 1 }
              , { 7, 0, 0, 0, 2, 0, 0, 0, 6 }
              , { 0, 6, 0, 0, 0, 0, 2, 8, 0 }
              , { 0, 0, 0, 4, 1, 9, 0, 0, 5 }
              , { 0, 0, 0, 0, 8, 0, 0, 7, 9 } } };
        
        m_SudokuBoard.initializeBoard(flatBoard);
        EXPECT_EQ(expectedBoard, m_SudokuBoard.getBoard());
    }
}

TEST_F(SudokuSolverTest, testNextRow)
{
    {
        std::array<std::array<int, 9>, 9> flatBoard =
            { { { 5, 3, 0, 0, 7, 0, 0, 0, 0 }
              , { 6, 0, 0, 1, 9, 5, 0, 0, 0 }
              , { 0, 9, 8, 0, 0, 0, 0, 6, 0 }
              , { 8, 0, 0, 0, 6, 0, 0, 0, 3 }
              , { 4, 0, 0, 8, 0, 3, 0, 0, 1 }
              , { 7, 0, 0, 0, 2, 0, 0, 0, 6 }
              , { 0, 6, 0, 0, 0, 0, 2, 8, 0 }
              , { 0, 0, 0, 4, 1, 9, 0, 0, 5 }
              , { 0, 0, 0, 0, 8, 0, 0, 7, 9 } } };

        for (size_t row = 0; row < flatBoard.size(); row++)
        {
            for (size_t col = 0; col < flatBoard.size(); col++)
            {
                // If row = 0 and col = 8 (last column) then the next row should be row = 1 
                // as all the columns in the current row are visited. Similar way for other
                // row and col no combinations
                auto nextRow = row + (col + 1) / 9;
                EXPECT_EQ(nextRow, SudokuSolver::getNextRow(row, col));
            }
        }
    }
}

TEST_F(SudokuSolverTest, testNextCol)
{
    {
        std::array<std::array<int, 9>, 9> flatBoard =
            { { { 5, 3, 0, 0, 7, 0, 0, 0, 0 }
              , { 6, 0, 0, 1, 9, 5, 0, 0, 0 }
              , { 0, 9, 8, 0, 0, 0, 0, 6, 0 }
              , { 8, 0, 0, 0, 6, 0, 0, 0, 3 }
              , { 4, 0, 0, 8, 0, 3, 0, 0, 1 }
              , { 7, 0, 0, 0, 2, 0, 0, 0, 6 }
              , { 0, 6, 0, 0, 0, 0, 2, 8, 0 }
              , { 0, 0, 0, 4, 1, 9, 0, 0, 5 }
              , { 0, 0, 0, 0, 8, 0, 0, 7, 9 } } };

        for (size_t row = 0; row < flatBoard.size(); row++)
        {
            for (size_t col = 0; col < flatBoard.size(); col++)
            {
                // If col = 8 (last column) then the next col should be col = 0
                // as all the columns in the current row are visited.
                auto nextCol = (col + 1) % 9;
                EXPECT_EQ(nextCol, SudokuSolver::getNextCol(col));
            }
        }
    }
}

TEST_F(SudokuSolverTest, testGetGrid)
{
    {
        std::array<std::array<int, 9>, 9> flatBoard =
            { { { 5, 3, 0, 0, 7, 0, 0, 0, 0 }
              , { 6, 0, 0, 1, 9, 5, 0, 0, 0 }
              , { 0, 9, 8, 0, 0, 0, 0, 6, 0 }
              , { 8, 0, 0, 0, 6, 0, 0, 0, 3 }
              , { 4, 0, 0, 8, 0, 3, 0, 0, 1 }
              , { 7, 0, 0, 0, 2, 0, 0, 0, 6 }
              , { 0, 6, 0, 0, 0, 0, 2, 8, 0 }
              , { 0, 0, 0, 4, 1, 9, 0, 0, 5 }
              , { 0, 0, 0, 0, 8, 0, 0, 7, 9 } } };

        for (size_t row = 0; row < flatBoard.size(); row++)
        {
            for (size_t col = 0; col < flatBoard.size(); col++)
            {
                /**
                 * @brief A grid in a Sudoku board is nothing but
                 * a combination of 3 rows and 3 columns in a sequence.
                 * So the first grid is containing cells board[0-2][0-2],
                 * the second grid contains cells board[3-5][3-5] and so
                 * on. If we translate this into a math formula then it
                 * comes to (row / 3) * 3 + (col / 3)
                 */
                auto expGrid = (row / 3) * 3 + (col / 3);
                EXPECT_EQ(expGrid, SudokuSolver::getGrid(row, col));
            }
        }
    }
}

TEST_F(SudokuSolverTest, testPopulateValues)
{
    {
        std::array<std::array<int, 9>, 9> flatBoard =
            { { { 5, 3, 0, 0, 7, 0, 0, 0, 0 }
              , { 6, 0, 0, 1, 9, 5, 0, 0, 0 }
              , { 0, 9, 8, 0, 0, 0, 0, 6, 0 }
              , { 8, 0, 0, 0, 6, 0, 0, 0, 3 }
              , { 4, 0, 0, 8, 0, 3, 0, 0, 1 }
              , { 7, 0, 0, 0, 2, 0, 0, 0, 6 }
              , { 0, 6, 0, 0, 0, 0, 2, 8, 0 }
              , { 0, 0, 0, 4, 1, 9, 0, 0, 5 }
              , { 0, 0, 0, 0, 8, 0, 0, 7, 9 } } };

        SudokuSolver board;
        board.initializeBoard(flatBoard);
        auto sudokuBoard = board.getBoard();

        for (size_t row = 0; row < sudokuBoard.size(); row++)
        {
            for (size_t col = 0; col < sudokuBoard.size(); col++)
            {
                auto grid = SudokuSolver::getGrid(row, col);
                if (sudokuBoard[row][col] != 0)
                {
                    EXPECT_FALSE(board.isValidForRow(sudokuBoard[row][col], row));
                    EXPECT_FALSE(board.isValidForCol(sudokuBoard[row][col], col));
                    EXPECT_FALSE(board.isValidForGrid(sudokuBoard[row][col], grid));
                }
            }
        }
    }
}

TEST_F(SudokuSolverTest, testPrintBoard)
{
    {
        std::array<std::array<int, 9>, 9> flatBoard =
            { { { 5, 3, 0, 0, 7, 0, 0, 0, 0 }
              , { 6, 0, 0, 1, 9, 5, 0, 0, 0 }
              , { 0, 9, 8, 0, 0, 0, 0, 6, 0 }
              , { 8, 0, 0, 0, 6, 0, 0, 0, 3 }
              , { 4, 0, 0, 8, 0, 3, 0, 0, 1 }
              , { 7, 0, 0, 0, 2, 0, 0, 0, 6 }
              , { 0, 6, 0, 0, 0, 0, 2, 8, 0 }
              , { 0, 0, 0, 4, 1, 9, 0, 0, 5 }
              , { 0, 0, 0, 0, 8, 0, 0, 7, 9 } } };

        SudokuSolver board;
        board.initializeBoard(flatBoard);
        auto sudokuBoard = board.getBoard();

        std::cout << std::endl << std::endl;
        EXPECT_NO_FATAL_FAILURE(SudokuSolver::printBoard(sudokuBoard));
        std::cout << std::endl << std::endl;
    }
}

TEST_F(SudokuSolverTest, testSolveBoard)
{
    {
        std::array<std::array<int, 9>, 9> flatBoard =
            { { { 0, 0, 0, 0, 0, 0, 2, 0, 0 }
              , { 0, 8, 0, 0, 0, 7, 0, 9, 0 }
              , { 6, 0, 2, 0, 0, 0, 5, 0, 0 }
              , { 0, 7, 0, 0, 6, 0, 0, 0, 0 }
              , { 0, 0, 0, 9, 0, 1, 0, 0, 0 }
              , { 0, 0, 0, 0, 2, 0, 0, 4, 0 }
              , { 0, 0, 5, 0, 0, 0, 6, 0, 3 }
              , { 0, 9, 0, 4, 0, 0, 0, 7, 0 }
              , { 0, 0, 6, 0, 0, 0, 0, 0, 0 } } };

        std::cout << std::endl << "Unsolved board" << std::endl;
        EXPECT_NO_FATAL_FAILURE(SudokuSolver::printBoard(flatBoard));
        std::cout << std::endl << std::endl;

        SudokuSolver board;
        board.initializeBoard(flatBoard);
        EXPECT_TRUE(board.solveBoard());
        auto sudokuBoard = board.getBoard();

        std::cout << std::endl << "Solved board" << std::endl;
        EXPECT_NO_FATAL_FAILURE(SudokuSolver::printBoard(sudokuBoard));
        std::cout << std::endl << std::endl;
    }
    {
        std::array<std::string, 81> flatBoard = 
            {"", "1", "3", "8", "", "", "4", "", "5", 
             "", "2", "4", "6", "", "5", "", "", "", 
             "", "8", "7", "", "", "", "9", "3", "", 
             "4", "9", "", "3", "", "6", "", "", "", 
             "", "", "1", "", "", "", "5", "", "", 
             "", "", "", "7", "", "1", "", "9", "3", 
             "", "6", "9", "", "", "", "7", "4", "", 
             "", "", "", "2", "", "7", "6", "8", "", 
             "1", "", "2", "", "", "8", "3", "5", ""};

        m_SudokuBoard.initializeBoard(flatBoard);
        auto unsolvedBoard = m_SudokuBoard.getBoard();

        std::cout << std::endl << "Unsolved board" << std::endl;
        EXPECT_NO_FATAL_FAILURE(SudokuSolver::printBoard(unsolvedBoard));
        std::cout << std::endl << std::endl;

        EXPECT_TRUE(m_SudokuBoard.solveBoard());
        auto sudokuBoard = m_SudokuBoard.getBoard();

        std::cout << std::endl << "Solved board" << std::endl;
        EXPECT_NO_FATAL_FAILURE(SudokuSolver::printBoard(sudokuBoard));
        std::cout << std::endl << std::endl;
    }
    {
        std::array<std::string, 81> flatBoard = 
            {"", "", "2", "", "", "", "", "4", "1", 
             "", "", "", "", "8", "2", "", "7", "", 
             "", "", "", "", "4", "", "", "", "9", 
             "2", "", "", "", "7", "9", "3", "", "", 
             "", "1", "", "", "", "", "", "8", "", 
             "", "", "6", "8", "1", "", "", "", "4", 
             "1", "", "", "", "9", "", "", "", "", 
             "", "6", "", "4", "3", "", "", "", "", 
             "8", "5", "", "", "", "", "4", "", ""};

        m_SudokuBoard.initializeBoard(flatBoard);
        auto unsolvedBoard = m_SudokuBoard.getBoard();

        std::cout << std::endl << "Unsolved board" << std::endl;
        EXPECT_NO_FATAL_FAILURE(SudokuSolver::printBoard(unsolvedBoard));
        std::cout << std::endl << std::endl;

        EXPECT_FALSE(m_SudokuBoard.solveBoard());
    }
}

TEST_F(SudokuSolverTest, DISABLED_testBitSet)
{
    std::array<std::bitset<9>, 9> bitSet = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    /* for (auto idx = 0; idx <= 9; ++idx)
        bitSet[idx].set(idx); */

    size_t expCnt = 1;
    for (auto idx = 0; idx < 10; ++idx)
        EXPECT_EQ(expCnt, bitSet[idx].count());
}

