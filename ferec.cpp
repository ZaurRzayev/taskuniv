#include <iostream>
#include <thread>
#include <algorithm>

// A function that checks if an array is sorted in ascending order
bool is_ascending(int arr[], int n) {
    return std::is_sorted(arr, arr + n);
}

// A function that checks if an array is sorted in descending order
bool is_descending(int arr[], int n) {
    return std::is_sorted(arr, arr + n, std::greater<int>());
}

// A function that prints the sorting order of an array
void print_order(int arr[], int n) {
    // Create two threads to check the ascending and descending order
    std::thread t1(is_ascending, arr, n);
    std::thread t2(is_descending, arr, n);

    // Wait for the threads to finish
    t1.join();
    t2.join();

    // Get the results from the threads
    bool asc = t1.get();
    bool desc = t2.get();

    // Print the sorting order based on the results
    if (asc) {
        std::cout << "The array is sorted in ascending order.\n";
    } else if (desc) {
        std::cout << "The array is sorted in descending order.\n";
    } else {
        std::cout << "The array is unsorted.\n";
    }
}

int main() {
    // Test the code with some examples
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {5, 4, 3, 2, 1};
    int arr3[] = {1, 3, 2, 5, 4};

    print_order(arr1, 5);
    print_order(arr2, 5);
    print_order(arr3, 5);

    return 0;
}
