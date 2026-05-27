// test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include"include/math_dll.h"
#include"include/math_dll_c.h" 


int main() {
    // 使用类
    std::cout << "MathLibrary::Add(8, 4)= " << MathLibrary::Add(8, 4) << std::endl;

    // 使用C风格函数
    MathHandle handle = NULL;
	int result = 0;
    //创建句柄
	MathHandleErrorCode error = math_handle_create(&handle);
	error = math_handle_add(handle, 10,20, &result);
	std::cout << "math_handle_add(10, 20) = " << result << std::endl;

	// 销毁句柄
	error = math_handle_destroy(handle);
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
