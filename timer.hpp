#ifndef _SOLSTICE_TIMER_HPP_
#define _SOLSTICE_TIMER_HPP_



#include <functional>

#include <SFML/System.hpp>


/**
*** This class represents a countdown timer that may call a handler during expiration
*** Usage:
***     Create a timer and start() it
***     update() every frame
***     check if expired for your purpose and reset as needed before starting again
**/


class Timer {
public:
    Timer(const sf::Time& time_to_countdown, std::function<void(Timer&)> callback = [](Timer& t){;});

    // make timer run
    void        start();

    // stop timer from running
    void        stop();

    // call this on every frame to update timer
    // this updates the timer and when it expires, the timer stops and calls the handler
    void        update();

    bool        is_running();

    // returns true if timer has ran out
    bool        has_expired();

    // reset back timer but does not start it
    void        reset();

    // like reset, but calls start
    void        restart();

    sf::Time    get_remaining_time();
    void        set_timer(const sf::Time& time_to_countdown);
    void        set_callback(std::function<void(Timer&)> callback);


private:
    sf::Time    _time_to_countdown;
    sf::Time    _remaining_time;
    bool        _running = false;
    bool        _expired = false;
    sf::Clock   _clock;

    std::function<void(Timer&)> _callback;

};


#endif // _SOLSTICE_TIMER_HPP_
