// SingletonPattern.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<string>
#include<map>

class camera {};//简单定义一下
class CameraManager {
public:
	//全局访问点，获取唯一实例

	static CameraManager* getInstance() {
		if(instance == nullptr){
			instance = new CameraManager();
		}
		return instance;
	}

	void init() {
		//初始化摄像机对象并存储在cameraidMap中
	}
		//业务方法
		void openCamera(std::string cameraId) {
		auto it = cameraidMap.find(cameraId);
		if (it != cameraidMap.end()) {
			//找到了，使用it->second访问摄像机对象
			camera* cam = it->second;
			std::cout << "Opening camera with ID " << cameraId << std::endl;
		}
		else {
			std::cout << "Camera with ID " << cameraId << " not found." << std::endl;
		}
	}
private:
	//私有函数，禁止外部创建实例
	static CameraManager* instance;//静态成员变量，指向唯一实例，内存中只有一个实例
	std::map<std::string, camera*>cameraidMap;//存储摄像机对象的容器

	CameraManager() {  }//私有构造函数，禁止外部创建实例

	CameraManager(const CameraManager&) = delete;//禁止拷贝构造函数
	CameraManager& operator=(const CameraManager&) = delete;//禁止赋值运算符


};
	//初始化静态成员变量
	CameraManager* CameraManager::instance = nullptr;
int main()
{
	std::string id = "123";
	CameraManager::getInstance()->openCamera(id);
    std::cout << "Hello World!\n";
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
