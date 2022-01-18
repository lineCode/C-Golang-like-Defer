// Cursed Golang-like defer() operation in C++
// See results: https://godbolt.org/z/nKx4hMG79

#include <iostream>
#include <functional>

/*
  defer_t will accept a void functor and it will execute the contents at the deconstructor
*/
struct defer_t {
    std::function<void()> func;
    defer_t(const std::function<void()>& func) : func(func) {}

    ~defer_t() {
        func();
    }
};

/*
  we want to create simple Go-like syntax so we must used macros to create 
  hidden and unused variable names
*/
#define DEFER_VAR_NAME_CONCAT(x,y) x ## y
#define DEFER_VAR_NAME(x,y) DEFER_VAR_NAME_CONCAT(x,y)
#define defer(x) defer_t DEFER_VAR_NAME(_defer,__LINE__)([&]{ x; });

// Foo struct to see output
struct Foo {
    void Bar() {
        std::cout << "Foo::Bar" << std::endl;
    }

    void Ray() {
        std::cout << "Foo::Ray" << std::endl;
    }
};

int main() {
    // Test
    Foo foo;
    
    // First time used
    defer(
        foo.Bar();
    );

    int i = 4;
    std::cout << "i = " << 4 << std::endl;

    // Second time used
    defer(
        foo.Ray();
    );

    std::cout << "This line is before the return statement" << std::endl;
    return 0;
}

// expected output:
// i = 4
// This line is before the return statement
// Foo::Ray
// Foo::Bar
