#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_set>

using namespace std;

struct Slide
{
    long long id;
    bool horizontal;
    unordered_set<string> tags;
};

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
