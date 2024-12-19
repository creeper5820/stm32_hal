#pragma once
namespace util {

template <typename T> T limit(T ratio, T limit) {
    if (ratio > limit) ratio = limit;
    else if (ratio < -limit) ratio = -limit;
    return ratio;
}

}