#ifndef SOL_RANDOM_HPP
#define SOL_RANDOM_HPP

#include <random>
#include <algorithm>
#include <chrono>
#include <iterator>


namespace sol{

/**
*** randint(start, end) returns a random number N from the specified range such that
*** start <= N <= end
**/

int randint(int start, int end);

/**
*** choice(start, end) returns a random iterator in the given iterator range
**/

template <typename iterator>
iterator choice(iterator begin, iterator end){
    int num_elements = randint(0, std::distance(begin, end) - 1);
    std::advance(begin, num_elements);
    return begin;
} //return a random item


/**
*** shuffle(begin, end) re-arranges the order of items on the iterator range
**/

template <typename iterator>
void shuffle(iterator begin, iterator end){
    std::mt19937 random_generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::shuffle(begin, end, random_generator);
} // shuffles the items on the collection


//TODO: (in the near future maybe)
//collection sample(collection start, collection end, num_sample)


} // end namespace sol


#endif // SOL_RANDOM_HPP
