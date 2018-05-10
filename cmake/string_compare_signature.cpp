// Check whether the std::string::compare method takes a size_t as first argument
#include <string>

int main()
{
    std::string s1("Test");
    std::string s2("test");
    int res = s2.compare(0, std::string::npos, s1);

    return 0;
}
