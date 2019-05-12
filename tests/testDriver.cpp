//
// Created by Connor Baker on 2019-05-12.
//

#include "gtest/gtest.h"
#include <iostream>
//#include <omp.h> // For printing the OMP version

int main(int argc, char **argv) {
//    printf("Your OpenMP version is from %d (YYYYMM)\n", _OPENMP);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}