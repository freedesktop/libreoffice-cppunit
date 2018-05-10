// Check whether the compiler supports default arguments for template parameters
template<typename T=int>
class Foo
{
public:
    T bar(T param)
    {
        return param;
    }
};

int main()
{
    Foo<> f;
    return f.bar(0);
}
