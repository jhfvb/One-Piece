// main.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include"Aloginterface.h"
#include"AlgorithmFactory.h"


// 传统方式的问题 - 紧耦合


AlgorithmInterface* creatAlgo(const std::string& algorithmType) {
    if (algorithmType == "CannyEdge") {
        return new CannyEdgeDetector();
    }
    else if (algorithmType == "SIFTFeature") {
        return new SIFTFeatureExtractor();
    }
    else if (algorithmType == "HoughLine") {
        return new HoughLineDetector();
    }
    // 每增加新算法都需要修改此处代码
}
// 使用REGISTER_ALGORITHM宏进行自动注册
REGISTER_ALGORITHM(CannyEdgeDetector, "CannyEdgeDetector")
REGISTER_ALGORITHM(SIFTFeatureExtractor, "SIFTFeatureExtractor")
REGISTER_ALGORITHM(HoughLineDetector, "HoughLineDetector")
REGISTER_ALGORITHM(ORBFeatureExtractor, "ORBFeatureExtractor")

int main()
{

	
    std::cout << "Hello World!\n";

    // 手动注册一些算法
    auto& factory = AlgorithmFactory::getInstance();

    // 方法1：使用模板方法注册
    factory.registerAlgorithm<CannyEdgeDetector>("Canny");

    // 方法2：使用通用注册方法
    factory.registerAlgorithm("HoughLineDetector",
        []() -> std::unique_ptr<HoughLineDetector> {
            auto algo = std::make_unique<HoughLineDetector>();
            // 自定义创建逻辑
            return algo;
        });

    // 演示工厂使用
    factory.printAvailableAlgorithms();// 打印可用算法

    // 创建算法实例
    std::cout << "\nCreating algorithms:\n";

    // 使用宏注册的算法
    auto canny1 = factory.createAlgorithm("CannyEdgeDetector");
    if (canny1) {
        std::cout << "Created: " << canny1->getName() << "\n";
        canny1->process(cv::Mat());
    }

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
