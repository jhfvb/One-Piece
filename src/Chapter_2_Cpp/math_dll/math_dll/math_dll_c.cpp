#include "pch.h"
#include "math_dll_c.h"
#include"math_dll.h"
#include<map>
#include<mutex>

std::mutex handle_mutex;
std::map<MathHandle, std::shared_ptr<MathLibrary>> handle_map;

MATH_HANDLE_API MathHandleErrorCode math_handle_create(MathHandle* handle) {
	if (handle == nullptr) {
		return MATH_C_ERROR_NULL_PTR;
	}
	auto creat = [&]()->MathHandleErrorCode {
		//impl是实现的缩写，表示创建了一个MathLibrary对象的智能指针。
		auto impl = std::make_shared<MathLibrary>();
		MathHandle new_handle = static_cast<MathHandle>(impl.get()); {
			std::lock_guard<std::mutex> lock(handle_mutex);
			handle_map[new_handle] = impl;
		}
		*handle = new_handle;
		return MATH_C_SUCCESS;
		};
	return creat();
}

MATH_HANDLE_API MathHandleErrorCode math_handle_destroy(MathHandle handle) {
	if (handle == nullptr) {
		return MATH_C_SUCCESS;//允许销毁句柄
	}
	auto destory = [&]()->MathHandleErrorCode {
		std::lock_guard<std::mutex> lock(handle_mutex);
		auto it = handle_map.find(handle);
		if (it != handle_map.end()) {
			handle_map.erase(it);
			//直接删掉智能指针，智能指针会自动调用析构函数释放资源
			return MATH_C_SUCCESS;
		}
		else {
			return MATH_C_ERROR_INVALID_ARG;
		}
		};
	return destory();
}
MATH_HANDLE_API MathHandleErrorCode math_handle_add(
	MathHandle handle, int a, int b, int* result) {
	if (result == nullptr) {
		return MATH_C_ERROR_NULL_PTR;
	}
	auto add = [&]()->MathHandleErrorCode {
		std::shared_ptr<MathLibrary> impl;
		{
			std::lock_guard<std::mutex> lock(handle_mutex);
			auto it = handle_map.find(handle);
			if (it != handle_map.end()) {
				impl = it->second;
			}
			else {
				return MATH_C_ERROR_INVALID_ARG;
			}
		}
		try {
			*result = impl->Add(a, b);
			return MATH_C_SUCCESS;
		}
		catch (const std::exception& e) {
			return MATH_C_ERROR_INTERNAL;
		}
		};
	return add();
}