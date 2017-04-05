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


glm::vec3 & hermiteInterp(std::vector<glm::vec3> &points, float t) {
    if (t < 0 || t > points.size() - 3)
        return points.front(); //exception!

    unsigned int i = floor(t);
    glm::vec3 p0 = points[i + 1];
    glm::vec3 p1 = points[i + 2];
    glm::vec3 t0 = (points[i + 2] - points[i]) * 0.5f;
    glm::vec3 t1 = (points[i + 3] - points[i + 1]) * 0.5f;
    array<glm::vec3, 4> bezierContPt = { p0, p0 + t0 * (1 / 3.0f), p1 - t1 * (1 / 3.0f), p1 };
    float l = t - i; // fractional part of t

    // De Casteljau evaluation
    for (int k = 3; k > 0; k--) {
        for (int j = 0; j < k; j++) {
            bezierContPt[j] = bezierContPt[j] * (1 - l) + bezierContPt[j + 1] * l;
        }
    }
    return bezierContPt[0];
}

glm::vec3 & hermiteTangent(std::vector<glm::vec3> &points, float t) {
    if (t < 0 || t > points.size() - 3)
        return points.front(); //exception!

    unsigned int i = floor(t);
    glm::vec3 p0 = points[i + 1];
    glm::vec3 p1 = points[i + 2];
    glm::vec3 t0 = (points[i + 2] - points[i]) * 0.5f;
    glm::vec3 t1 = (points[i + 3] - points[i + 1]) * 0.5f;
    array<glm::vec3, 4> bezierContPt = { p0, p0 + t0 * (1 / 3.0f), p1 - t1 * (1 / 3.0f), p1 };
    float l = t - i; // fractional part of t

    //computing derivative bezier curve
    for (int k = 0; k < 3; k++)
        bezierContPt[k] = bezierContPt[k + 1] - bezierContPt[k];

    // De Casteljau evaluation
    for (int k = 2; k > 0; k--) {
        for (int j = 0; j < k; j++) {
            bezierContPt[j] = bezierContPt[j] * (1 - l) + bezierContPt[j + 1] * l;
        }
    }
    return bezierContPt[0] = glm::normalize(bezierContPt[0]);
}
