// NumericOverflows.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>     // std::cout
#include <limits>       // std::numeric_limits

/// <summary>
/// Template function to abstract away the logic of:
///   start + (increment * steps)
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="increment">How much to add each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <returns>start + (increment * steps)</returns>
template <typename T>
T add_numbers(T const& start, T const& increment, unsigned long int const& steps, bool& success)
{
    T result = start;
    success = true; // ensure boolean is true for each add test

    for (unsigned long int i = 0; i < steps; ++i)
    {
        if (std::is_integral<T>::value) // checks int values as others handle overflow different than overwriting
        {
            if (increment > 0 && result > std::numeric_limits<T>::max() - increment) // checks if result is in a range that adding the increment would make it above the limit
            {
                success = false; // false if overflow would occure
                return T{}; // returns empty for test cases
            }    
        }
        result += increment; // adds increment if no int overflow would occur
        
        if (std::isinf(result)) {
            success = false;
            return T{}; // returns empty for test cases
        }
    }
    return result; // returns result, so non overflow results are able to be used
}

/// <summary>
/// Template function to abstract away the logic of:
///   start - (increment * steps)
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="increment">How much to subtract each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <returns>start - (increment * steps)</returns>

template <typename T>
T subtract_numbers(T const& start, T const& decrement, unsigned long int const& steps, bool& success)
{
    T result = start;
    success = true; // ensure boolean is true for each subtraction test

   for (unsigned long int i = 0; i < steps; ++i)
    {
        if (std::is_integral<T>::value)
        {
            if (decrement > 0 && result < std::numeric_limits<T>::min() + decrement)
            {
                success = false; // underflow detected
                return T{};      // return default value
            }
        }

        result -= decrement; // subtracts increment if no int underrflow would occur

        if (std::isinf(result)) // checks if an inf number is returned, as a result of underflow
        {
            success = false;
            return T{}; // returns empty for test cases
        }
    }

    return result; // returns result, so non underflow results are able to be used
}


//  NOTE:
//    You will see the unary ('+') operator used in front of the variables in the test_XXX methods.
//    This forces the output to be a number for cases where cout would assume it is a character. 

template <typename T>
void test_overflow()
{
    // START DO NOT CHANGE
    //  how many times will we iterate
    const unsigned long int steps = 5;
    // how much will we add each step (result should be: start + (increment * steps))
    const T increment = std::numeric_limits<T>::max() / steps;
    // whats our starting point
    const T start = 0;

    std::cout << "Overflow Test of Type = " << typeid(T).name() << std::endl;
    // END DO NOT CHANGE

    bool success = true; // used to flag when overflow or underflow happen

    std::cout << "\tAdding Numbers Without Overflow (" << +start << ", " << +increment << ", " << steps << ") = ";
    T result = add_numbers<T>(start, increment, steps, success);
    if (success) // checks success flag and returns value if no overflow
    {
        std::cout << +result << std::endl;
    }
    else // returns error message if not successful
    {
        std::cout << "Overflow occurred!" << std::endl;
    }

    std::cout << "\tAdding Numbers With Overflow (" << +start << ", " << +increment << ", " << (steps + 1) << ") = ";
    result = add_numbers<T>(start, increment, steps + 1, success);
    if (success) // checks success flag and returns value if no overflow
    {
        std::cout << +result << std::endl;
    }
    else
    {
        std::cout << "Overflow occurred!" << std::endl; // returns error message if not successful
    }
}

template <typename T>
void test_underflow()
{
    // START DO NOT CHANGE
    //  how many times will we iterate
    const unsigned long int steps = 5;
    // how much will we subtract each step (result should be: start - (increment * steps))
    const T decrement = std::numeric_limits<T>::max() / steps;
    // whats our starting point
    const T start = std::numeric_limits<T>::max();

    std::cout << "Underflow Test of Type = " << typeid(T).name() << std::endl;
    // END DO NOT CHANGE

    bool success = true; // used to flag when overflow or underflow happen

    std::cout << "\tSubtracting Numbers Without Overflow (" << +start << ", " << +decrement << ", " << steps << ") = ";
    auto result = subtract_numbers<T>(start, decrement, steps, success);
    if (success) // checks success flag and returns value if no underflow
    {
        std::cout << +result << std::endl;
    }
    else
    {
        std::cout << "Underflow occurred!" << std::endl; // returns error message if not successful
    }

    std::cout << "\tSubtracting Numbers With Overflow (" << +start << ", " << +decrement << ", " << (steps + 1) << ") = ";
    result = subtract_numbers<T>(start, decrement, steps + 1, success);
    if (success) // checks success flag and returns value if no underflow
    {
        std::cout << +result << std::endl;
    }
    else
    {
        std::cout << "Underflow occurred!" << std::endl; // returns error message if not successful
    }
}

void do_overflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Overflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Testing C++ primative times see: https://www.geeksforgeeks.org/c-data-types/
    // signed integers
    test_overflow<char>();
    test_overflow<wchar_t>();
    test_overflow<short int>();
    test_overflow<int>();
    test_overflow<long>();
    test_overflow<long long>();

    // unsigned integers
    test_overflow<unsigned char>();
    test_overflow<unsigned short int>();
    test_overflow<unsigned int>();
    test_overflow<unsigned long>();
    test_overflow<unsigned long long>();

    // real numbers
    test_overflow<float>();
    test_overflow<double>();
    test_overflow<long double>();
}

void do_underflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Undeflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Testing C++ primative times see: https://www.geeksforgeeks.org/c-data-types/
    // signed integers
    test_underflow<char>();
    test_underflow<wchar_t>();
    test_underflow<short int>();
    test_underflow<int>();
    test_underflow<long>();
    test_underflow<long long>();

    // unsigned integers
    test_underflow<unsigned char>();
    test_underflow<unsigned short int>();
    test_underflow<unsigned int>();
    test_underflow<unsigned long>();
    test_underflow<unsigned long long>();

    // real numbers
    test_underflow<float>();
    test_underflow<double>();
    test_underflow<long double>();
}

/// <summary>
/// Entry point into the application
/// </summary>
/// <returns>0 when complete</returns>
int main()
{
    //  create a string of "*" to use in the console
    const std::string star_line = std::string(50, '*');

    std::cout << "Starting Numeric Underflow / Overflow Tests!" << std::endl;

    // run the overflow tests
    do_overflow_tests(star_line);

    // run the underflow tests
    do_underflow_tests(star_line);

    std::cout << std::endl << "All Numeric Underflow / Overflow Tests Complete!" << std::endl;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu