#pragma once
#include"Aloginterface.h"
#include"AlgorithmFactory.h"
#include"json.hpp"
#include<vector>

using Algos = std::vector<std::unique_ptr<AlgorithmInterface>>;
class parseAlgoJson {
private:
    parseAlgoJson() = default;
public:
    static parseAlgoJson& instance() {
        static parseAlgoJson instance;
        return instance;
    }
    //反序列化
    Algos parseFromJson(const std::string& jsonStr);
    //序列化
    std::string parseToJson(const Algos& algos);
};

//反序列化：从JSON字符串创建算法实例
Algos parseAlgoJson::parseFromJson(const std::string& jsonStr) {
    Algos algorithms;

    try {
        nlohmann::json j = nlohmann::json::parse(jsonStr);
        auto pipeline = j["processing_pipeline"];

        for (const auto& algoConfig : pipeline) {
            std::string algorithmName = algoConfig["algorithm"];

            auto algorithm = AlgorithmFactory::getInstance().createAlgorithm(algorithmName);
            if (!algorithm) {
                throw std::runtime_error("Unknown algorithm: " + algorithmName);
            }

            // 通用的参数解析
            ParameterMap params;
            auto jsonParams = algoConfig["parameters"];

            for (auto it = jsonParams.begin(); it != jsonParams.end(); ++it) {
                std::string key = it.key();
                nlohmann::json value = it.value();

                // 根据JSON值的类型转换为ParameterValue
                if (value.is_number_integer()) {
                    params[key] = value.get<int>();
                }
                else if (value.is_number_float()) {
                    params[key] = value.get<double>();
                }
                else if (value.is_boolean()) {
                    params[key] = value.get<bool>();
                }
                else if (value.is_string()) {
                    params[key] = value.get<std::string>();
                }
            }

            algorithm->setParameters(params);
            algorithms.push_back(std::move(algorithm));
        }

    }
    catch (const std::exception& e) {
        throw std::runtime_error("Error parsing JSON: " + std::string(e.what()));
    }

    return algorithms;
}

//序列化：将算法实例转换为JSON字符串
std::string parseAlgoJson::parseToJson(const Algos& algos) {
    try {
        nlohmann::json j;
        nlohmann::json pipelineArray = nlohmann::json::array();

        // 遍历所有算法
        for (const auto& algo : algos) {
            if (!algo) {
                continue;  // 跳过空指针
            }

            nlohmann::json algoJson;

            // 算法名称
            algoJson["algorithm"] = algo->getName();

            // 参数
            ParameterMap params = algo->getParameters();
            nlohmann::json paramsJson = nlohmann::json::object();

            // 遍历所有参数
            for (const auto& [key, value] : params) {
                // 根据参数值的类型存储到 JSON
                if (std::holds_alternative<int>(value)) {
                    paramsJson[key] = std::get<int>(value);
                }
                else if (std::holds_alternative<double>(value)) {
                    paramsJson[key] = std::get<double>(value);
                }
                else if (std::holds_alternative<bool>(value)) {
                    paramsJson[key] = std::get<bool>(value);
                }
                else if (std::holds_alternative<std::string>(value)) {
                    paramsJson[key] = std::get<std::string>(value);
                }
            }

            algoJson["parameters"] = paramsJson;
            pipelineArray.push_back(algoJson);
        }

        // 构建完整的 JSON 结构
        j["processing_pipeline"] = pipelineArray;

        // 可选：添加元数据
        j["metadata"]["algorithm_count"] = algos.size();
        j["metadata"]["timestamp"] = std::time(nullptr);

        // 转换为字符串
        std::string jsonStr = j.dump(4);  // 缩进4个空格，便于阅读
        return jsonStr;

    }
    catch (const std::exception& e) {
        std::cerr << "Error serializing to JSON: " << e.what() << std::endl;
        return "";
    }
}

