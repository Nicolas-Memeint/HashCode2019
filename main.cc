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
    long long id2;
    bool horizontal;
    set<string> tags;
    set<string> tags2;

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

    size_t compare(Slide s, Slide s2)
    {
        std::vector<string> set(1);
        auto ls = std::set_difference(s.tags.begin(), s.tags.end(),
                                    s2.tags.begin(), s2.tags.end(),
                                    set.begin());
        return set.size();
    }

    void parse(int argc, char* argv[])
    {
        std::fstream fs;
        fs.open(argv[1]);

        std::string str;
        getline(fs, str);
        size_t nb = atol(str.c_str());
        auto v = std::vector<Slide>();
        auto vv = std::vector<Slide>();
        auto vh = std::vector<Slide>();
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
            if (S.horizontal)
                vh.push_back(S);
            else
                vv.push_back(S);
        }
        fs.close();
        for (; !vv.empty(); vv.pop_back())
        {
            auto last = vv.end() - 1;
            auto best = vv.begin();
            auto max = 0;
            for (auto it = vv.begin(); it != last; it++)
            {
                auto nb = compare(*it, *last);
                if (nb > max)
                {
                    best = it;
                    max = nb;
                }
            }
            last->id2 = best->id;
            last->tags.merge(best->tags);
            vh.emplace_back(*last);
            vv.erase(best);
        }
        slides_ = vh;
    }

    void execute()
    {
        vector<Slide> res;
        res.reserve(slides_.size());

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
            if (!e.horizontal)
            {
                cout << " ";
                cout << e.id2;
            }
            cout << "\n";
        }
    }

    unsigned long rand()
    {
        const unsigned long n = std::distance(slides_.begin(), slides_.end());
        const unsigned long divisor = RAND_MAX / n;

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
