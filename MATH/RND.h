#ifndef RND_H_INCLUDED
#define RND_H_INCLUDED

//Random number generator
#include <random>

double GRNG(double mn, double mx){//Generate random number between limits
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(mn, mx);
    return dis(gen);
}

#endif
