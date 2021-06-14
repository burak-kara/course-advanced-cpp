// Burak Kara S009893
#include <iostream>
#include <vector>


template<typename ...>
struct TD; // your compile time debug helper (TypeDisplayer)

// WRITE YOUR CODE HERE (STARTS)

template<typename T>
concept is_numeric = std::is_integral_v<std::remove_reference_t<T>> ||
                     std::is_floating_point_v<std::remove_reference_t<T>>;

auto $1 = [](auto &first, auto ...rest) {
    return first;
};
auto $2 = [](auto first, auto ...rest) {
    return $1(rest...);
};
auto $3 = [](auto first, auto ...rest) {
    return $2(rest...);
};

// definitely the best solution... lots of code repetition......
auto operator+(auto arg1, auto arg2) {
    if constexpr(is_numeric<decltype(arg1)>) {
        if constexpr(is_numeric<decltype(arg2)>) {
            return [arg1, arg2](auto ...args) {
                return arg1 + arg2;
            };
        } else {
            return [arg1, arg2](auto ...args) {
                return arg2(args...) + arg1;
            };
        }
    } else if constexpr(is_numeric<decltype(arg2)>) {
        return [arg1, arg2](auto ...args) {
            return arg1(args...) + arg2;
        };
    } else {
        return [arg1, arg2](auto ...args) {
            return arg1(args...) + arg2(args...);
        };
    }
}

auto operator-(auto arg1, auto arg2) {
    if constexpr(is_numeric<decltype(arg1)>) {
        if constexpr(is_numeric<decltype(arg2)>) {
            return [arg1, arg2](auto ...args) {
                return arg1 - arg2;
            };
        } else {
            return [arg1, arg2](auto ...args) {
                return arg2(args...) - arg1;
            };
        }
    } else if constexpr(is_numeric<decltype(arg2)>) {
        return [arg1, arg2](auto &...args) {
            return arg1(args...) - arg2;
        };
    } else {
        return [arg1, arg2](auto ...args) {
            return arg1(args...) - arg2(args...);
        };
    }
}

auto operator/(auto arg1, auto arg2) {
    if constexpr(is_numeric<decltype(arg1)>) {
        if constexpr(is_numeric<decltype(arg2)>) {
            return [arg1, arg2](auto ...args) {
                return arg1 / arg2;
            };
        } else {
            return [arg1, arg2](auto ...args) {
                return arg2(args...) / arg1;
            };
        }
    } else if constexpr(is_numeric<decltype(arg2)>) {
        return [arg1, arg2](auto ...args) {
            return arg1(args...) / arg2;
        };
    } else {
        return [arg1, arg2](auto ...args) {
            return arg1(args...) / arg2(args...);
        };
    }
}

auto operator*(auto arg1, auto arg2) {
    if constexpr(is_numeric<decltype(arg1)>) {
        if constexpr(is_numeric<decltype(arg2)>) {
            return [arg1, arg2](auto ...args) {
                return arg1 * arg2;
            };
        } else {
            return [arg1, arg2](auto ...args) {
                return arg2(args...) * arg1;
            };
        }
    } else if constexpr(is_numeric<decltype(arg2)>) {
        return [arg1, arg2](auto ...args) {
            return arg1(args...) * arg2;
        };
    } else {
        return [arg1, arg2](auto ...args) {
            return arg1(args...) * arg2(args...);
        };
    }
}

auto operator>(auto arg1, auto arg2) {
    if constexpr(is_numeric<decltype(arg1)>) {
        if constexpr(is_numeric<decltype(arg2)>) {
            return [arg1, arg2](auto ...args) {
                return arg1 > arg2;
            };
        } else {
            return [arg1, arg2](auto ...args) {
                return arg1 > arg2(args...);
            };
        }
    } else if constexpr(is_numeric<decltype(arg2)>) {
        return [arg1, arg2](auto ...args) {
            return arg1(args...) > arg2;
        };
    } else {
        return [arg1, arg2](auto ...args) {
            return arg1(args...) > arg2(args...);
        };
    }
}

auto operator++(auto arg1) {
    // actually arg1 is always lambda
    if constexpr(is_numeric<decltype(arg1)>) {
        return [arg1](auto ...args) {
            return ++arg1;
        };
    } else {
        return [arg1](auto &arg) {
            return arg1(++arg);
        };
    }
}

// week12 app2
template<bool, typename T>
struct enableIf {
};
template<typename T>
struct enableIf<true, T> {
    using type = T;
};

template<typename T>
struct Vector : std::vector<T> {
    std::vector<T> vector;

    template<typename ...Ts>
    explicit Vector(Ts... ts) {
        vector = {ts...};
    }

    // index operations
    T operator[](is_numeric auto &&index) {
        return vector[index >= 0 ? index : vector.size() + index];
    }

    // bool expressions
    std::vector<bool> operator[](const auto &&lambda) {
        auto vec = std::vector<bool>{};
        for (auto &v :vector) {
            auto a = lambda(v);
//            auto td = TD<decltype(a)>{};
            vec.push_back(a);
        }
        return vec;
    }

    // for other expressions
//    auto operator[](const auto &&lambda) {
//        for (auto &v :vector)
//            lambda(v);
//        return vector;
//    }

    Vector<T> operator[](const std::vector<bool> &filter) {
        auto temp_vec = Vector{};
        for (size_t i = 0; i < filter.size(); ++i) {
            if (filter[i])
                temp_vec.vector.push_back(vector[i]);
        }
        return temp_vec;
    }

    [[nodiscard]] size_t getSize() const { return vector.size(); }
};

// week10 app3
template<typename First, typename ... Rest>
Vector(First &&first, Rest &&... rest) -> Vector<std::remove_reference_t<First>>;

template<typename T>
struct is_vector : std::false_type {
};
template<typename T>
struct is_vector<Vector<T>> : std::true_type {
};

template<typename T>
struct is_std_vector : std::false_type {
};
template<typename T>
struct is_std_vector<std::vector<T>> : std::true_type {
};

void std_vector_printer(const auto &vector) {
    for (auto i = 0; i < vector.size(); i++) {
        std::cout << vector[i] << " ";
    }
    std::cout << std::endl;
}

void vector_printer(auto &vector) {
    for (auto i = 0; i < vector.getSize(); i++) {
        std::cout << vector[i] << " ";
    }
    std::cout << std::endl;
}

template<typename ...>
void print();

template<typename T>
void print(T &&t) {
    if constexpr(is_vector<std::remove_reference_t<T>>::value) {
        vector_printer(t);
    } else if constexpr(is_std_vector<std::remove_reference_t<T>>::value) {
        std_vector_printer(t);
    } else {
        std::cout << t << std::endl;
    }
}

template<typename First, typename ...Rest>
void print(First &&first, Rest &&...rest) {
    if constexpr(is_vector<std::remove_reference_t<First>>::value) {
        vector_printer(first);
    } else if constexpr(is_std_vector<std::remove_reference_t<First>>::value) {
        std_vector_printer(first);
    } else {
        std::cout << first << std::endl;
    }
    print(rest...);
}

// WRITE YOUR CODE HERE (ENDS)
int main() {
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
