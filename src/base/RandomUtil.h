#pragma once
#include <random>

static std::random_device rd;
static std::default_random_engine eng(rd());

template<typename T =float>
static T RandRange(T min,T max)
{
    std::uniform_real_distribution<T> dist(min,max);
    return dist(eng);
}

static float Rand01F()
{
    RandRange(0.f,1.f);
}