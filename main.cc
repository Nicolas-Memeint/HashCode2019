#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <vector>
#include <string>

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
        std::fstream fs;
        fs.open(argv[1]);

        std::string str;
        getline(fs, str);
        size_t nb = atol(str.c_str());
        auto v = std::vector<Slide>();
        for (auto i = 0u; i < nb; ++i)
        {
            auto S = Slide();
            size_t pos = 0;
            getline(fs, str);
            auto new_pos = str.find(" ", pos);
            auto tok = str.substr(pos, new_pos);
            S.horizontal = tok[0] == 'H';
            S.id = i;
            pos = new_pos;
            new_pos = str.find(" ", pos + 1);
            tok = str.substr(pos, new_pos);
            auto tags = atol(tok.c_str());
            auto end = str.find("\n");
            for (auto i = 0u; i < tags - 1; ++i)
            {
                pos = new_pos;
                new_pos = str.find(" ", pos + 1);
                tok = str.substr(pos, new_pos);
                S.tags.emplace(tok);
            }
            tok = str.substr(pos, end);
            S.tags.emplace(tok);
        }
        fs.close();
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
