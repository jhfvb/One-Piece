// math_lib.cpp : 定义静态库的函数。 
#include "framework.h"
#include"pch.h"
#include "math_lib.h"

int MathUtils::Add(int a, int b) {
    return a + b;
}

int MathUtils::Multiply(int a, int b) {
    return a * b;
}

double MathUtils::Divide(double a, double b) {
    if (b == 0) return 0.0;
    return a / b;
}