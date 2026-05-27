#include "pch.h"
#include "math_dll.h"


// 类的实现
int MathLibrary::Add(int a, int b) {
    return a + b;
}

int MathLibrary::Multiply(int a, int b) {
    return a * b;
}

double MathLibrary::Divide(double a, double b) {
    if (b == 0) return 0.0;
    return a / b;
}