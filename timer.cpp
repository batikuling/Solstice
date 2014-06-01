#include "timer.hpp"

Timer::Timer(const sf::Time& time_to_countdown, std::function<void(Timer&)> callback):
    _time_to_countdown(time_to_countdown),
    _remaining_time(time_to_countdown),
    _callback(callback){

}


void Timer::start(){
    _running = true;
}


void Timer::stop(){
    _running = false;
}


void Timer::update(){
    if (_running){
        _remaining_time -= _clock.restart();

        if (_remaining_time <= sf::Time::Zero){
            _expired = true;
            _running = false;
            _callback(*this);
        }
    }

}


bool Timer::is_running(){
    return _running;
}


bool Timer::has_expired(){
    return _expired;
}


void Timer::reset(){
    _remaining_time = _time_to_countdown;
    _expired = false;
}

void Timer::restart(){
    reset();
    start();
}


sf::Time Timer::get_remaining_time(){
    return _remaining_time;
}


void Timer::set_timer(const sf::Time& time_to_countdown){
    _time_to_countdown = time_to_countdown;
}


void Timer::set_callback(std::function<void(Timer&)> callback){
    _callback = callback;
}
