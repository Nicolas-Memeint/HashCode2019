#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct Slide
{
    long long id;
    bool horizontal;
    set<string> tags;

    unsigned long score(const Slide& other)
    {
        auto size1 = tags.size();
        auto size2 = other.tags.size();

        vector<string> inter(max(size1, size2));
        set_intersection(tags.begin(), tags.end(), other.tags.begin(),
                         other.tags.end(), inter.begin());

        while (!inter.empty() && inter.back() == "")
        {
            inter.pop_back();
        }

        auto size_inter = inter.size();
        return min(size_inter, min(size1 - size_inter, size2 - size_inter));
    }
};

class Program
{
public:
    void parse(int argc, char* argv[])
    {
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
            auto tok = str.substr(pos, new_pos - pos);
            S.horizontal = tok[0] == 'H';
            S.id = i;
            pos = new_pos;
            new_pos = str.find(" ", pos + 1);
            tok = str.substr(pos, new_pos - pos);
            auto tags = atol(tok.c_str());
            auto end = str.find("\n");
            for (auto i = 0u; i < tags - 1; ++i)
            {
                pos = new_pos;
                new_pos = str.find(" ", pos + 1);
                tok = str.substr(pos, new_pos - pos);
                S.tags.emplace(tok);
            }
            new_pos = str.find(" ", pos + 1);
            tok = str.substr(new_pos, end - new_pos);
            S.tags.emplace(tok);
            v.push_back(S);
        }
        fs.close();

        slides_ = v;
    }

    void execute()
    {
        vector<Slide> res;
        res.resize(slides_.size());

        res.push_back(slides_.back());
        slides_.pop_back();
        while (slides_.size() > 1)
        {
            Slide best = pop_random_slide(rand());
            auto best_score = res.back().score(best);

            constexpr auto window = 10;
            for (unsigned i = 0; i < window; ++i)
            {
                auto rand_num = rand();
                auto cur = res.back().score(slides_[rand_num]);

                if (cur > best_score)
                {
                    slides_.push_back(best);
                    best = pop_random_slide(rand_num);
                    best_score = cur;
                }
            }

            res.push_back(best);
        }

        if (!slides_.empty())
        {
            res.push_back(slides_.front());
        }

        slides_ = std::move(res);

        // Do output file
        print_result(slides_);

        clog << "score: " << score() << '\n';
    }

    void print_result(const vector<Slide>& res)
    {
        cout << res.size() << '\n';
        for (const auto& e : res)
        {
            cout << e.id;
        }
    }

    unsigned long rand()
    {
        const unsigned long n = std::distance(slides_.begin(), slides_.end());
        const unsigned long divisor = (RAND_MAX + 1) / n;

        unsigned long k;
        do
        {
            k = std::rand() / divisor;
        } while (k >= n);

        return k;
    }

    Slide pop_random_slide(unsigned long k)
    {
        Slide s = slides_[k];
        slides_.erase(slides_.begin() + k);
        return s;
    }

    unsigned long score()
    {
        unsigned long score = 0;
        for (unsigned long i = 0; i < slides_.size() - 1; ++i)
        {
            auto set1 = slides_[i];
            auto set2 = slides_[i + 1];

            score += set1.score(set2);
        }

        return score;
    }

private:
    vector<Slide> slides_;
};

int main(int argc, char *argv[])
{
    Program p;
    p.parse(argc, argv);
    p.execute();
    return 0;
}
