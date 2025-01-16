#include "ArraysAndStringProblems.hpp"
#include "LinkedListTest.hpp"
#include "LinkListProblems.hpp"
#include "StackProblemsTest.hpp"
#include "QueueProblemsTest.hpp"
#include "TreeNodeTest.hpp"
#include "BSTreeProblems.hpp"
#include "GraphProblemsTest.hpp"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv); 
    auto retVal = RUN_ALL_TESTS();
    std::cout << std::endl << std::endl;
    return retVal;
}
