
#include "Tools.hpp"

float power(float x, int p) {
    if (p == 0) {
        return 1;
    }
    if (p == 1) {
        return x;
    }
    float half_p_res = power(x, p / 2);
    if (p & 1) { // нечетное
        return x * half_p_res * half_p_res;
    } else {
        return half_p_res * half_p_res;
    }
}