// test2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include"include/math_lib.h"
#pragma comment(lib, "libs/math_lib.lib")//利用#pragma comment(lib, "math_lib.lib")指令链接math_lib.lib库文件
/*
// 情况1：相对路径
#pragma comment(lib, "math.lib")           // 当前目录
#pragma comment(lib, "libs/math.lib")      // 当前目录下的libs子目录
#pragma comment(lib, "../thirdparty/math.lib") // 上级目录的thirdparty子目录

// 情况2：绝对路径
#pragma comment(lib, "C:/libraries/math.lib")
#pragma comment(lib, "D:/project/libs/math.lib")
*/

int main() {
    std::cout << "MathUtils::Add(5, 3)= " << MathUtils::Add(5, 3) << std::endl;
    std::cout << "MathUtils::Multiply(5, 3)= " << MathUtils::Multiply(5, 3) << std::endl;
    std::cout << "MathUtils::Divide(10.0, 3.0)= " << MathUtils::Divide(10.0, 3.0) << std::endl;
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
