// Check whether the compiler supports namespaces
namespace o {
namespace i {
int r = 0;
}
}

using namespace o::i;

int main()
{
    return r;
}
