// StudentID: S009893, Name: Burak KARA
#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <map>
#include <variant>

using namespace std;
template<typename ...> struct TD;

// Solve Q1a (10pts), Q1b (5pts) here:
// LIMITATION! For Q1a and Q1b in total, you can use at most 6 semicolon (;) characters including the struct ending semicolon

template<typename T>
struct Mat
{
    int rows, cols;
    vector<vector<T>> vec;

    Mat(int rows, int cols, T initial_value) : rows{rows}, cols{cols}, vec(rows, vector<T>(cols, initial_value)) {}

    vector<T>& operator[](size_t index) { return vec[index]; }
};

// Solve Q1c here (5pts)

template<typename T>
void print(const Mat<T>& mat)
{
    for (const auto& vec : mat.vec)
    {
        for (const auto& item : vec)
        {
            if constexpr(is_same_v<string, T>)
            {
                cout << "\"" << item << "\" " ;
            }
            else
            {
                cout << item << " " ;
            }
        }
        cout << endl;
    }
    cout << endl;
}

// Solve Q2 here (15 pts)
template<typename T>
void call_site_info(Mat<T>&)
{
    cout << "Transforming l-value parameter" << endl;
}

template<typename T>
void call_site_info(Mat<T>&&)
{
    cout << "Transforming r-value parameter" << endl;
}

template<typename T>
auto transform(T&& mat_src, auto&& func)
{
    call_site_info(forward<T>(mat_src));
    // since we are keeping Original matrix untouched,
    // i didnt specialize transfrom impl to steal if it is "homeless guy"
    auto new_mat = Mat(mat_src.rows, mat_src.cols, func(mat_src[0][0]));
    for(size_t i=0; i<mat_src.rows; ++i)
    {
        for(size_t j=0; j<mat_src.cols; ++j)
            new_mat[i][j] = func(mat_src[i][j]);

    }
    return new_mat;
}

// Solve Q3a (10pts) and Q3b (10pts) here

template<typename T>
concept is_numeric = !is_same_v<T, remove_reference_t<Mat<string>>>;

template<typename T>
auto inc(T&& mat) requires(is_numeric<T>)
{
    if constexpr(is_same_v<T, T&>)
    {
        cout << "Incrementing l-value matrix" << endl;
    }
    else
    {
        cout << "Incrementing r-value matrix" << endl;
    }
    return transform(mat, []<typename K>(K&& item) { return item + 1; });
}

// Solve Q4 here (10 pts)
// Extra specifications for void to use in Q6,

template <typename ...>
struct concat_;

template <typename First, typename Rest>
struct concat_<First, Rest> {
    using type = tuple<Rest, First>;
};

template <typename First, typename ...Rest>
struct concat_<First, tuple<Rest...>> {
    using type = tuple<Rest..., First>;
};

template <typename ...>
struct concat;

template <typename First, typename RestFirst, typename... Rest>
struct concat<First, tuple<RestFirst, Rest...>> {
    using type = typename concat<typename concat_<RestFirst, First>::type, tuple<Rest...>>::type;
};

template <typename First, typename Rest>
struct concat<First, tuple<Rest>> {
    using type = typename concat_<Rest, First>::type;
};

template<typename First, typename ...Rest>
struct concat<void, tuple<First, Rest...>> {
    using type = tuple<First, Rest...>;
};

template<typename Rest>
struct concat<void, tuple<Rest>> {
    using type = tuple<Rest>;
};

template<typename T>
struct concat<T, void> { using type = T; };

template<typename First, typename Rest>
using concat_t = typename concat<First, Rest>::type;

// Solve Q5 here (5 pts)

template<typename ...>  struct IsIntegral       { static const bool value = false; };
template<>              struct IsIntegral<int>  { static const bool value = true; };
template<>              struct IsIntegral<long> { static const bool value = true; };
template<>              struct IsIntegral<short>{ static const bool value = true; };
template<>              struct IsIntegral<char> { static const bool value = true; };

// Solve Q6 here (15 pts)

template<bool, typename >
struct ConditionalType;

template<typename First>
struct ConditionalType<false, First>{ using type = void; };

template<typename First>
struct ConditionalType<true, First> { using type = tuple<First>; };

template<bool Filtered, typename First>
using ConditionalType_t = typename ConditionalType<Filtered, First>::type;

template<typename ...>
struct filter_types;

template<
        template<typename...> typename FilterType,
        typename T
        >
struct filter_types<FilterType<void>, tuple<T>>
{
    using type = ConditionalType_t<FilterType<T>::value, T>;
};

template<
        template<typename...> typename FilterType,
        typename First,
        typename ... Rest
        >
struct filter_types<FilterType<void>, tuple<First, Rest...>>
{
    using type = concat_t<
    ConditionalType_t<FilterType<First>::value, First>,
    typename filter_types<FilterType<void>, tuple<Rest...>>::type
    >;
};

template<typename T>
struct filter_types<IsIntegral<>, tuple<T>>
{
    using type = ConditionalType_t<IsIntegral<T>::value, T>;
};

template<typename First,typename ... Rest>
struct filter_types<IsIntegral<>, tuple<First, Rest...>>
{
    using type = concat_t<
    ConditionalType_t<IsIntegral<First>::value, First>,
    typename filter_types<IsIntegral<>, tuple<Rest...>>::type
    >;
};

template<typename FilterType, typename T>
using filter_types_t = typename filter_types<FilterType, T>::type;


// Solve Q7 here (15pts)

// A String class to hide the underlying details of std::string (i.e. std::basic_string<char, ...>) This shows as "String" when type-debugging, and facilitates
struct String : string { using string::string; };
// The transformer required by Q7 is supplied here
template<typename ...> struct Transformer;
template<typename T>   struct Transformer<T>      { using type = T; };
template<>             struct Transformer<char>   { using type = int; };
template<>             struct Transformer<short>  { using type = int; };
template<>             struct Transformer<long>   { using type = int; };
template<>             struct Transformer<double> { using type = float; };
template<>             struct Transformer<string> { using type = String; };

template<typename T>
using Transformer_t = tuple<typename Transformer<T>::type>;

template<typename ...>
struct transform_types;

template<typename T>
struct transform_types<Transformer<>, tuple<T>>
{
    using type = Transformer_t<T>;
};

template<typename First, typename ... Rest>
struct transform_types<Transformer<>, tuple<First, Rest...>>
{
    using type = concat_t<Transformer_t<First>,
    typename transform_types<Transformer<>, tuple<Rest...>>::type
    >;
};

template<typename FilterType, typename Second>
using transform_types_t = typename transform_types<Transformer<>, Second>::type;

// Solve Q8 here (10 pts)

template<
        template<typename...> typename FuncType,
        typename ... Ts
        >
constexpr int count_types(tuple<Ts...>)
{
    return tuple_size_v<filter_types_t<FuncType<void>, tuple<Ts...>>>;
}

int main()
{
    // LIMITATION! For Q1a and Q1b in total, you can use at most 6 semicolon (;) characters
    // including the struct ending semicolon. More than 6 semicolons, you get zero points.
    // Q1a - Create a Mat<T> class with a constructor of Mat(rows, cols, initial_value)
    // T is automatically deduced from the initial_value's type
    auto m1 = Mat(2, 3, 9.9); // 2 row, 3 column matrix with double values is initialized to 9.9 for each cell
    print(m1);

    // Q1b - Make below assignment style work (i.e. m1[rowindex][colindex])
    for(size_t i=0; i<m1.rows; ++i)
        m1[i][i] = 1.1;

    // Q1c - write a print free-function that prints an instance of Mat<T>
    // if T is string, it puts " around the value, otherwise it directly prints the value
    print(m1);

    // Q2 - Write a "auto transform(const Mat<T>& mat_src, auto&& func)" free-function
    // that can take a source matrix and transform its contents globally.
    // At the end it returns the transformed matrix. Original matrix stays untouched.
    // Returned matrix can be of a different type depending on the "func"'s return value.
    // i.e. Mat<int> after transformation can be Mat<double> for instance.

    auto m2 = transform(
                Mat{2, 1,
                    map<string, variant<string, double, int>>{
                        {"pi", 3.14},
                        {"CS", "409/509"},
                        {"year", 2021}
                    }
                }, []<typename T>(T&& map_) {
                    auto s = string{};
                    for(const auto& [key, value] : map_)
                    {
                        auto value_str = string{};
                        if(holds_alternative<string>(value))
                        value_str = get<string>(value);
                        else if(holds_alternative<double>(value))
                        value_str = to_string(get<double>(value));
                        else if(holds_alternative<int>(value))
                        value_str = to_string(get<int>(value));
                        s += key + ": " + value_str + " ";
                    }
                    return s;
                });
    print(m1);
    print(m2);

    // Q3a - Write a SINGLE (overloading inc is not allowed) free-function named "inc".
    // writing overloads for inc function will get you zero points
    // This function returns a new Mat<T> whose contents are incremented by 1.
    // It also writes l-value or r-value to the console based on its parameter's situation at the call site.
    // Q3b - Make the SINGLE "inc" function available only for Mat<T> types using concepts
    // writing overloads for "inc" function will get you zero points
    // For instance, Mat<string> cannot be incremented. Mat<int>, Mat<float>, ... can be incremented.

    print(inc(m1));
    print(inc(Mat(1, 4, 1)));

    // Q4 - Write a concat struct that can concatenate tuples at least as described below
    // concat omits the void at the end
    // concat concatenates types of two tuples into one tuple

    using T1 = tuple<int, double, float>;
//     TD< concat_t<T1, void> > q4a; // ---> tuple<int, double, float>
//     TD< concat_t<T1, T1> > q4b; // ---> tuple<int, double, float, int, double, float>

    // Q5 - Write IsIntegral value-trait which is similar to std::is_integral.
    // But your implementation must also accept  IsIntegral<> as a valid entry.
    // i.e. <> means an empty parameter-pack

    // Q6 - Write "filter_types" type-trait
    // that accepts a value-trait and many types
    // as a value trait you must support at least both of IsIntegral<> and is_integral<void>
    // a value-trait can be, for instance, IsIntegral that checks if a type is suitable or not
    // in the end, filter_types struct supplies the types filtered according to the value-trait in its "type" attribute
    // Do not write templated classes in the main() function block. Leave them in the global namespace.

    using TUPLE = tuple<int, float, string, char, short, double, string, double, float>;
    using TUPLE_INTEGRAL = filter_types_t<IsIntegral<>, TUPLE>;

    // TUPLE_INTEGRAL --> tuple<int, char, short>
    // TD< TUPLE_INTEGRAL > q6a;

    using TUPLE_FLOATING = filter_types_t<is_floating_point<void>, TUPLE>;

    // TUPLE_FLOATING --> tuple<float, double, double, float>
    // TD< TUPLE_FLOATING > q6b;

    // Q7 - Write a "transform_types" type trait
    // that accepts convertion type-trait and many types
    // a type-trait specialized for your scenario is already supplied. Its called "Transformer".
    // in the end, transform_types struct supplies the transformed types according to the type-trait in its "type" attribute
    // Do not write templated classes in the main() function block. Leave them in the global namespace.

    using TUPLE_TRANSFORMED = transform_types_t<Transformer<>, TUPLE>;

    // TUPLE_TRANSFORMED --> tuple<int, float, String, int, int, float, String, float, float>
    // TD< TUPLE_TRANSFORMED > q7a;

    // Q8 - Write a constexpr free-function named count_types
    // when used as shown below it returns the number of types in a tuple that fits to the criterion supplied

    cout << "Number of integral types in TUPLE is " << count_types<IsIntegral>(TUPLE{}) << endl;
    cout << "Number of integral types in TUPLE is " << count_types<is_integral>(TUPLE{}) << endl;
    cout << "Number of floating types in TUPLE is " << count_types<is_floating_point>(TUPLE{})<< endl;

    return 0;
}
