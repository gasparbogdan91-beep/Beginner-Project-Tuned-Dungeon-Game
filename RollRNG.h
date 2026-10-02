//
// Created by bgdan on 10/2/26.
//

#ifndef PROJECT1_ROLLRNG_H
#define PROJECT1_ROLLRNG_H

#include <random>

    // roll rng//
    inline std::random_device rd {};

    inline std::seed_seq ss { rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
    inline std::mt19937 rng { ss };

    inline std::uniform_int_distribution<int> roll {1, 100 };


#endif //PROJECT1_ROLLRNG_H