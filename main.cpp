#include "ArraysAndStringProblems.hpp"
#include "LinkedListTest.hpp"
#include "LinkListProblems.hpp"
#include "StackProblemsTest.hpp"
#include "QueueProblemsTest.hpp"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
