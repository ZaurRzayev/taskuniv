#include <iostream>
#include <thread>
#include <vector>
#include <numeric>

// A function that computes the running sum of an array
void run_sum(std::vector<int>& arr, std::vector<int>& sums) {
    // Use std::accumulate to compute the sum of the range [arr.begin(), arr.end())
    // and store it in the last element of sums
    sums.back() = std::accumulate(arr.begin(), arr.end(), 0);
}

// A function that computes the running product of an array
void run_product(std::vector<int>& arr, std::vector<int>& products) {
    // Use std::accumulate to compute the product of the range [arr.begin(), arr.end())
    // and store it in the last element of products
    // Use std::multiplies<int>() as the binary operation
    products.back() = std::accumulate(arr.begin(), arr.end(), 1, std::multiplies<int>());
}

// A function that prints the running sum and product of an array
void print_result(std::vector<int>& arr, std::vector<int>& sums, std::vector<int>& products) {
    // Print the array
    std::cout << "The array is: ";
    for (int x : arr) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    // Print the running sum
    std::cout << "The running sum is: ";
    for (int x : sums) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    // Print the running product
    std::cout << "The running product is: ";
    for (int x : products) {
        std::cout << x << " ";
    }
    std::cout << "\n";
}

int main() {
    // Test the code with some examples
    std::vector<int> arr1 = {1, 2, 3, 4, 5};
    std::vector<int> arr2 = {5, 4, 3, 2, 1};
    std::vector<int> arr3 = {1, 3, 2, 5, 4};

    // Create vectors to store the running sum and product of each array
    // Initialize them with the same size as the array and zero values
    std::vector<int> sums1(arr1.size(), 0);
    std::vector<int> sums2(arr2.size(), 0);
    std::vector<int> sums3(arr3.size(), 0);

    std::vector<int> products1(arr1.size(), 0);
    std::vector<int> products2(arr2.size(), 0);
    std::vector<int> products3(arr3.size(), 0);

    // Create threads to compute the running sum and product of each array
    // Pass the arrays and the result vectors as references to the functions
    std::thread t1(run_sum, std::ref(arr1), std::ref(sums1));
    std::thread t2(run_product, std::ref(arr1), std::ref(products1));

    std::thread t3(run_sum, std::ref(arr2), std::ref(sums2));
    std::thread t4(run_product, std::ref(arr2), std::ref(products2));

    std::thread t5(run_sum, std::ref(arr3), std::ref(sums3));
    std::thread t6(run_product, std::ref(arr3), std::ref(products3));

    // Wait for the threads to finish
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();

    // Print the results
    print_result(arr1, sums1, products1);
    print_result(arr2, sums2, products2);
    print_result(arr3, sums3, products3);

    return 0;
}
