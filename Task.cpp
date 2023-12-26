#include <iostream>
#include <vector>
#include <numeric>
#include <thread>
#include <mutex>
#include <chrono>

void calculateRunningSum(const std::vector<int>& data, int& result, std::mutex& mtx, double& duration) {
    auto start = std::chrono::steady_clock::now();
    int partialSum = std::accumulate(data.begin(), data.end(), 0);
    auto end = std::chrono::steady_clock::now();

    std::lock_guard<std::mutex> lock(mtx);
    result += partialSum;
    duration = std::chrono::duration<double>(end - start).count();
}

void calculateRunningProduct(const std::vector<int>& data, unsigned long long& result, std::mutex& mtx, double& duration) {
    auto start = std::chrono::steady_clock::now();
    unsigned long long partialProduct = 1ULL;
    for (int val : data) {
        partialProduct *= static_cast<unsigned long long>(val);
    }
    auto end = std::chrono::steady_clock::now();

    std::lock_guard<std::mutex> lock(mtx);
    result *= partialProduct;
    duration = std::chrono::duration<double>(end - start).count();
}

int main() {
    const int size = 10000000000;
    const int numThreads = 16;

    std::vector<int> values(size, 2);

    int totalSum = 0;
    unsigned long long totalProduct = 1ULL;

    std::mutex sumMutex;
    std::mutex productMutex;

    std::vector<std::thread> threads;
    std::vector<double> sumDurations(numThreads);
    std::vector<double> productDurations(numThreads);

    auto overallStart = std::chrono::steady_clock::now();

    for (int i = 0; i < numThreads; ++i) {
        int start = i * (size / numThreads);
        int end = (i + 1) * (size / numThreads);

        threads.emplace_back([&values, start, end, &totalSum, &sumMutex, &totalProduct, &productMutex, &sumDurations, &productDurations, i]() {
            std::vector<int> subData(values.begin() + start, values.begin() + end);
            double sumDuration = 0.0, productDuration = 0.0;

            calculateRunningSum(subData, totalSum, sumMutex, sumDuration);
            calculateRunningProduct(subData, totalProduct, productMutex, productDuration);

            sumDurations[i] = sumDuration;
            productDurations[i] = productDuration;
            });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    auto overallEnd = std::chrono::steady_clock::now();
    double overallDuration = std::chrono::duration<double>(overallEnd - overallStart).count();

    std::cout << "Running Sum: " << totalSum << std::endl;
    std::cout << "Running Product: " << totalProduct << std::endl;

    for (int i = 0; i < numThreads; ++i) {
        std::cout << "Thread " << i << " - Sum Duration: " << sumDurations[i] << " seconds"
            << ", Product Duration: " << productDurations[i] << " seconds" << std::endl;
    }

    std::cout << "Overall Duration: " << overallDuration << " seconds" << std::endl;

    return 0;
}
