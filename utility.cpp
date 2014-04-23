#include <unordered_map>
#include <string>

#include "utility.hpp"

namespace sol{


float radians_to_degrees(const float radians){
    return radians * 180.f / PI;
}

float degrees_to_radians(const float degrees){
    return degrees * PI / 180.f;
}

}//end namespace sol
