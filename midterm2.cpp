// Burak Kara S009893
#include <iostream>
#include <vector>
template<typename ...> struct TD; // your compile time debug helper (TypeDisplayer)

// WRITE YOUR CODE HERE (STARTS)

template<typename T>
struct Vector : std::vector<T>
{
    std::vector<T> vector;

    template<typename ...Ts>
    Vector(Ts... ts)
    {
        vector = {ts...};
    }
};

//template<typename First, typename Rest>
//struct Vector<First, Rest> : std::vector<First>
//{
//    std::vector<First> vector;
//    Vector(First first, Rest rest)
//    {
//        vector = {first, rest};
//    }
//};

//template<typename First, typename ...Rest>
//struct Vector<First, Rest...> : std::vector<First>
//{
//    std::vector<First> vector;
//    Vector(First first, Rest... rest)
//    {
//        vector = {first, rest...};
//    }
//};

// week10 app3
template<typename First, typename ... Rest>
Vector(First&& first, Rest&& ... rest) -> Vector<std::remove_reference_t<First>>;

//template<typename First, typename Rest>
//Vector(First, Rest) -> Vector<First, Rest>;

//template<typename First, typename ...Rest>
//Vector(First, Rest ...) -> Vector<First, Rest ...>;

void vector_printer(const auto& vector)
{
    std::cout << "Size = " << vector.size() << std::endl;
    for(const auto& item : vector)
    {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

template<typename ...>
void print();

template<typename T>
void print(const T& t)
{
    if constexpr(std::is_same_v<T, Vector>)
    {
        std::cout<< "vector" << std::endl;
    }
    else
    {
        std::cout<< "non-vector" << std::endl;
    }
//    std::cout << t << std::endl;
}

template<typename First, typename ...Rest>
void print(const First& first, const Rest&& ...rest)
{
    if constexpr(std::is_same_v<First, Vector>)
    {
        std::cout<< "vector" << std::endl;
        vector_printer(first);
    }
    else
    {
        std::cout<< "non-vector" << std::endl;
        std::cout << first << std::endl;
        print(rest...);
    }
}

// WRITE YOUR CODE HERE (ENDS)
int main()
{
    // design a print overload-set or a single print function that can generically print any number of
    // containers and strings and other values in a single call to print. check the below usage of print.
    // design a math expression system that lazily represents an operation over values that will be later provided
    // use $1, $2, $3 as special variables of this math expression toolkit
    // $1 means the first value, $2 means the second, $3 means the third value supplied to a function/lambda
    // (yes, using $ is valid for variables!)
    // for instance; auto e=$3-$1+$2 creates an expression via composing 3 different lambdas
    // when later called with (10, 20, 30, 40, 50, ...) evaluates to 30-10+20
    // your design shall take care of at least +, -, *, /, ++, > operators
    // note that ++i and i++ are different overloads. How to overload both of them? Check the internet.
    // > will create a lazy boolean expression
    // ++ will also touch and change the item itself
    // (for instance running $1++ over a vector will increment all elements by one after the evaluation is done)
    // operator precedence is the same as the precedences that are defined in the C++ language
    // if you do compose two lambdas from left to right, there shall be no problem with the precedence
    // language will take care of it for you
    // create a Vector<...> class that inherits from vector<...> and extends it so that after auto v = Vector{...};
    // v[boolean expression] outputs a mask of vector<bool>
    // v[other expression] creates a new vector that contains transformed items according to the expression
    // v[vector<bool>] selects only the elements that correspond to boolean true locations of the vector<bool> mask
    // v[index] works as before
    // v[-index] selects the item starting from the end of the vector. For instance, -1 is the last element.

    // Q1 (15 pts) - print overload-set working correctly as used below in all questions

    // Q2 (30 pts) – below and all expressions that can be written with $1, $2, $3 and +, -, *, / works correctly

//    auto $1 = 5;
//    auto $2 = 5;
//    auto $3 = 5;

    auto l1 = (1.1 + $3) * ($1 + $2 / 2.0);
    print("l1(5, 10, 15)", l1(5, 10, 15));

    // Q3 (5 pts) - deduction guide for below line
    // you can change below line to Vector<int>{10, 20, 30} if you want to skip this question
    auto v = Vector{10, 20, 30}; // not written Vector<int>{10, 20, 30} especially.

    // Q4 (5 pts) - $1>10 works as expected

    // Q5 (10 pts) - masking of a Vector works
    auto mask_gt_10 = v[$1 > 10];

    // Q6 (10 pts) - selection of Vector elements by means of a mask
    auto v_selected = v[mask_gt_10];
    print("v", v, "Mask of $1>10", mask_gt_10, "v_selected", v_selected);

    // Q7 (10 pts) - accessing elements of a Vector in standard way and in reverse direction
    print("First element of v", v[0], "Last Element of v", v[-1]);
    print("v", v);

    // Q8 (only for CS409) (15 pts) - item++ operator works on Vector<int>
    // print("v applied with $1++ * 3", v[$1++ * 3]);
    // print("v", v); // note that v's items are now incremented by one due to $1++ above

    // Q8 (only for CS509) (15 pts) - ++item operator works on Vector<double>
    // you can change below line to Vector<double>{1.1, 2.2, 3.3} if you don't want points from Q3
    auto v2 = Vector{1.1, 2.2, 3.3};
    print("v2", v2);
    print("v2 applied with ++$1 - 1", v2[++$1 - 1]);
    print("v2", v2); // note that v's items are now incremented by one due to $1++ above

    return 0;
}