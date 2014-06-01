#include <iostream>
using namespace std;

#include "../timer.hpp"

int main(void){


    int wait_time = 2;
    Timer timer(sf::seconds(wait_time), [](Timer&){cout << "expired!" << endl;});
    timer.start();

    while (true){
        timer.update();

        if (timer.has_expired()){
            wait_time++;
            timer.set_timer(sf::seconds(wait_time));
            timer.restart();
        }
    }


}
