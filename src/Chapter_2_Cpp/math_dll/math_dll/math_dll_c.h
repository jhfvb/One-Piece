#pragma once

// 平台特定的导出导入宏
#ifdef _WIN32
#ifdef MATHDLL_EXPORTS
#define MATH_HANDLE_API __declspec(dllexport)
#else
#define MATH_HANDLE_API __declspec(dllimport)
#endif
#else
#ifdef MATHDLL_EXPORTS
#define MATH_HANDLE_API __attribute__((visibility("default")))
#else
#define MATH_HANDLE_API
#endif
#endif

//==================C语言兼容性==================
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//========================不透明句柄类型========================
	typedef void* MathHandle;//typedef 就是给void*起了个别名叫MathHandle，这样在使用时就可以直接使用MathHandle来声明变量，而不需要每次都写void*，提高了代码的可读性和可维护性。
	
	
	// ==================== 错误码定义 ====================
	typedef enum {
		MATH_C_SUCCESS = 0,
		MATH_C_ERROR_NULL_PTR = -1,
		MATH_C_ERROR_INVALID_ARG = -2,
		MATH_C_ERROR_DIVIDE_BY_ZERO = -3,
		MATH_C_ERROR_INTERNAL = -4,
		MATH_C_ERROR_OUT_OF_MEMORY = -5
	}
	MathHandleErrorCode; 

	//====================句柄生命周期管理函数====================
	MATH_HANDLE_API MathHandleErrorCode math_handle_create(MathHandle* handle);
	MATH_HANDLE_API MathHandleErrorCode math_handle_destroy(MathHandle handle);

	//====================数学运算函数====================
	MATH_HANDLE_API MathHandleErrorCode math_handle_add(MathHandle handle, int a, int b, int* result);





#ifdef __cplusplus
}
#endif // __cplusplus


