#pragma  once
#include <type_traits>


template <typename, typename T>
struct has_method {
    static_assert (std::integral_constant<T, false>::value,
            "second parameter mush be a function delc");
};

template <typename ClassType, typename ReturnType, typename ...Args>
struct has_method <ClassType, ReturnType(Args...)> {
private:
    template<typename T>
    static constexpr auto check(T*)
    -> typename std::is_same<decltype(std::declval<T>().method(std::declval<Args>()...) ), ReturnType>::type;

    template<typename>
    static constexpr std::false_type check(...);
    typedef decltype (check<ClassType>(0)) type;

    public:
        static constexpr bool value = type::value;
};
