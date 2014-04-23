#include <iostream>
#include <vector>

#include "random.hpp"

using namespace std;

int main(void){

    //test randint()
    cout << "calling randint(1, 10) ten times: " << endl << "  ";
    for (int i = 0; i < 10 ; i++)
        cout << sol::randint(1, 10) << " ";

    //test shuffle()
    cout << endl << "calling shuffle on {1, 2, 3, 4, 5, 6}: " << endl << "  ";
    vector<int> numbers = {1, 2, 3, 4, 5, 6};
    sol::shuffle(numbers.begin(), numbers.end());

    for(int num : numbers)
        cout << num << " ";

    //test choice() ----> successful since it can result from 1 - 6
    cout << endl << "calling choice(numbers) 10 times: " << endl << "  ";
    for(int i = 0; i < 10 ; i++)
        cout << *sol::choice(numbers.begin(), numbers.end()) << " ";
}
