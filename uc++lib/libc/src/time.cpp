#include "time.h"

extern "C" {

double difftime(time_t end, time_t beginning) {
    double res = end;
    res -= beginning;
    return res;
}

}