#pragma once

//导出宏定义
#ifdef MATHDLL_EXPORTS
#define MATH_API __declspec(dllexport)
#else
#define MATH_API __declspec(dllimport)
#endif

// 导出类
class MATH_API MathLibrary {
public:
	static int Add(int a, int b);
	static int Multiply(int a, int b);
	static double Divide(double a, double b);
};




class math_dll
{
};

