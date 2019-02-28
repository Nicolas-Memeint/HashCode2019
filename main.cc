#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

class Program
{
public:
    void parse(int argc, char* argv[])
    {
        std::cout << argv[1] << '\n';
    }

    void execute()
    {}

private:
};

int main(int argc, char *argv[])
{
    Program p;
    p.parse(argc, argv);
    p.execute();
    return 0;
}
