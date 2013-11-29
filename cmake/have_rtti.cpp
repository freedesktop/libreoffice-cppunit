#include <typeinfo>

// Check whether the compiler supports run-time type information (RTTI)
int main()
{
    int t = 0;
    const char* id = typeid(t).name();
    return t;
}
