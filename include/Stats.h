#pragma once

#include "Externs.h"

// Collect and display statistics
class Stats
{
    static long totalRays;

public:
    static void raysCast() { STAT(totalRays++); }
    static void startTrace();
    static void endTrace();
    static void print();
};
