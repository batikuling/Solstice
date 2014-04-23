#include <random>
#include <chrono>

#include "random.hpp"



namespace sol{

std::mt19937 _random_generator(std::chrono::system_clock::now().time_since_epoch().count());


int randint(int start, int end){

    std::uniform_int_distribution<int> distribution(start, end);
    return distribution(_random_generator);
} //end randint()


} // end namespace sol
