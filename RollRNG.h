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

    inline std::uniform_int_distribution<int> roll100 {1, 100 };
    inline std::uniform_int_distribution<int> roll25 {1, 25 };
    inline std::uniform_int_distribution<int> rollboon {1, 37 };
inline std::uniform_int_distribution<int> rollchoice {1, 5};

#endif //PROJECT1_ROLLRNG_H