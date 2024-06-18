#include <iostream>
#include <vector>
#include <limits>

std::vector<int> getPositiveNumbers(const int count) {

    // Define the dynamic storage
    std::vector<int> result{};

    // Give user instruction
    std::cout << "Please enter " << count << " positive numbers:\n";

    do {
        int number{};
        if (std::cin >> number) {
            // Check if number is positive
            if (number >= 0)
                // Yes, the store it
                result.push_back(number);
            else
                // negative number given. Show error message
                std::cout << "\n*** Error: Neagtive value given. Please try again\n\n";
        }
        else {
            // Invalid input given, for example "abc"
            // Show error message
            std::cout << "\n*** Error: invalid input format. Please try again\n\n";
            // Clear error state of std::cin
            std::cin.clear();
            // And ignore all invalid characters in the input buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (result.size() < count);

    // return the vector to the calling instance
    return result;
}
int main() {
    // Call the function
    std::vector<int> values = getPositiveNumbers(3);

    std::cout << "\n\n--------------------------------\nEntered values are:\n";
    for (const int i : values) std::cout << i << ' ';
    std::cout << "\n\n";
}