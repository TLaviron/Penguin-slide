#include "./../include/Utils.hpp"
#include "./../include/log.hpp"

#include <chrono>
#include <random>
#include <glm/gtx/color_space.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

// A random engine initialized on the current time.
// This way, the random numbers generated won't be the same at each execution.
static std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count() );

float random(float a, float b)
{
    uniform_real_distribution<> distribution(a,b);
    return distribution(generator);
}

glm::vec4 randomColor()
{
    uniform_real_distribution<> distribution(0,360);
    float hue = distribution(generator), saturation = 1.0, black = 1.0;
    glm::vec3 hsvColor( hue, saturation, black);
    glm::vec3 rgbColor = glm::rgbColor(hsvColor);
    return glm::vec4(rgbColor[0], rgbColor[1], rgbColor[2], 1.0);
}

glm::vec4 getColor(const float& factor, const float& low, const float& high)
{
    float hue = 0.0, saturation = 1.0, black = 1.0;
    if(factor<low) hue = 240.0;
    else if(factor>high) hue = 0.0;
    else hue = 240 + (factor-low)/(high-low)*(0.0-240.0);
    glm::vec3 hsvColor( hue, saturation, black);
    glm::vec3 rgbColor = glm::rgbColor(hsvColor);
    return glm::vec4(rgbColor[0], rgbColor[1], rgbColor[2], 1.0);
}

template<class T>
T & hermiteInterp(const std::vector<T> &points, float t) {
    if (t < 0 || t > points.size() - 3)
        return points.front(); //exception!

    unsigned int i = floor(t);
    T p0 = points[i + 1];
    T p1 = points[i + 2];
    T t0 = (points[i + 2] - points[i]) / 2;
    T t1 = (points[i + 3] - points[i + 1]) / 2;
    array<T, 4> bezierContPt = { p0, p0 + t0 / 3, p1 - t1 / 3, p1 };
    float l = t - i; // fractional part of t
    for (int k = 3; k > 0; k--) {
        for (int j = 0; j < k; j++) {
            bezierContPt[j] = bezierContPt[j] * (1 - l) + bezierContPt[j + 1] * l;
        }
    }
    return bezierContPt[0];
}
