
#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
using namespace std;

/**
 * 这题有点难度, 没有做出来, 看 花花酱的 解答 http://zxi.mytechroad.com/blog/searching/leetcode-126-word-ladder-ii/
 * 
*/

// Author: Huahua
// Running Time: 216 ms (better than 65.42%)
class SolutionHuaHuaBFS1
{
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList)
    {

        // 使用 set 存储字典
        unordered_set<string> dict(wordList.begin(), wordList.end());
        // 计数特定的key
        if (!dict.count(endWord))
            return {};
        // 移出两个元素
        dict.erase(beginWord);
        dict.erase(endWord);

        // 记录步长
        unordered_map<string, int> steps{{beginWord, 1}};
        // 记录父节点, 用于后期dfs
        unordered_map<string, vector<string>> parents;
        // 用于bfs 确定 level 以及 所有路径的 节点图
        queue<string> q;
        q.push(beginWord);

        vector<vector<string>> ans;

        const int l = beginWord.length();
        int step = 0;
        // 确定当前level能够找到最短路径
        bool found = false;

        while (!q.empty() && !found)
        {
            ++step;
            for (int size = q.size(); size > 0; size--)
            {
                const string p = q.front();
                q.pop();
                string w = p;
                for (int i = 0; i < l; i++)
                {
                    const char ch = w[i];
                    for (int j = 'a'; j <= 'z'; j++)
                    {
                        if (j == ch)
                            continue;
                        w[i] = j;
                        if (w == endWord)
                        {
                            parents[w].push_back(p);
                            found = true;
                        }
                        else
                        {
                            // Not a new word, but another transform
                            // with the same number of steps
                            if (steps.count(w) && step < steps.at(w))
                                parents[w].push_back(p);
                        }

                        if (!dict.count(w))
                            continue;
                        dict.erase(w);
                        q.push(w);
                        steps[w] = steps.at(p) + 1;
                        parents[w].push_back(p);
                    }
                    w[i] = ch;
                }
            }
        }

        if (found)
        {
            vector<string> curr{endWord};
            getPaths(endWord, beginWord, parents, curr, ans);
        }

        return ans;
    }

private:
    void getPaths(const string &word,
                  const string &beginWord,
                  const unordered_map<string, vector<string>> &parents,
                  vector<string> &curr,
                  vector<vector<string>> &ans)
    {

        if (word == beginWord)
        {
            ans.push_back(vector<string>(curr.rbegin(), curr.rend()));
            return;
        }

        for (const string &p : parents.at(word))
        {
            curr.push_back(p);
            getPaths(p, beginWord, parents, curr, ans);
            curr.pop_back();
        }
    }
};

// Author: Huahua
// Running time: 129 ms (better than 80.67%)
class SolutionBFS2
{
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList)
    {
        vector<vector<string>> ans;
        unordered_set<string> dict(wordList.begin(), wordList.end());
        if (!dict.count(endWord))
            return ans;
        dict.erase(endWord);

        const int l = beginWord.length();
        unordered_set<string> q{beginWord}, p;
        unordered_map<string, vector<string>> children;
        bool found = false;

        while (!q.empty() && !found)
        {

            for (const string &word : q)
                dict.erase(word);

            for (const string &word : q)
            {
                string curr = word;
                for (int i = 0; i < l; i++)
                {
                    char ch = curr[i];
                    for (int j = 'a'; j <= 'z'; j++)
                    {
                        curr[i] = j;
                        if (curr == endWord)
                        {
                            found = true;
                            children[word].push_back(curr);
                        }
                        else if (dict.count(curr) && !found)
                        {
                            p.insert(curr);
                            children[word].push_back(curr);
                        }
                    }
                    curr[i] = ch;
                }
            }

            std::swap(p, q);
            p.clear();
        }

        if (found)
        {
            vector<string> path{beginWord};
            getPaths(beginWord, endWord, children, path, ans);
        }

        return ans;
    }

private:
    void getPaths(const string &word,
                  const string &endWord,
                  const unordered_map<string, vector<string>> &children,
                  vector<string> &path,
                  vector<vector<string>> &ans)
    {
        if (word == endWord)
        {
            ans.push_back(path);
            return;
        }

        const auto it = children.find(word);
        if (it == children.cend())
            return;

        for (const string &child : it->second)
        {
            path.push_back(child);
            getPaths(child, endWord, children, path, ans);
            path.pop_back();
        }
    }
};

// Author: Huahua 双广搜索
// Running time: 39 ms (better than 93.74%)
class SolutionBidirectionalBFS
{
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList)
    {
        vector<vector<string>> ans;
        unordered_set<string> dict(wordList.begin(), wordList.end());
        if (!dict.count(endWord))
            return ans;

        int l = beginWord.length();

        unordered_set<string> q1{beginWord};
        unordered_set<string> q2{endWord};
        unordered_map<string, vector<string>> children;

        bool found = false;
        bool backward = false;

        while (!q1.empty() && !q2.empty() && !found)
        {
            // Always expend the smaller queue first
            if (q1.size() > q2.size())
            {
                std::swap(q1, q2);
                backward = !backward;
            }

            for (const string &w : q1)
                dict.erase(w);
            for (const string &w : q2)
                dict.erase(w);

            unordered_set<string> q;

            for (const string &word : q1)
            {
                string curr = word;
                for (int i = 0; i < l; i++)
                {
                    char ch = curr[i];
                    for (int j = 'a'; j <= 'z'; j++)
                    {
                        curr[i] = j;

                        const string *parent = &word;
                        const string *child = &curr;

                        if (backward)
                            std::swap(parent, child);

                        if (q2.count(curr))
                        {
                            found = true;
                            children[*parent].push_back(*child);
                        }
                        else if (dict.count(curr) && !found)
                        {
                            q.insert(curr);
                            children[*parent].push_back(*child);
                        }
                    }
                    curr[i] = ch;
                }
            }

            std::swap(q, q1);
        }

        if (found)
        {
            vector<string> path{beginWord};
            getPaths(beginWord, endWord, children, path, ans);
        }

        return ans;
    }

private:
    void getPaths(const string &word,
                  const string &endWord,
                  const unordered_map<string, vector<string>> &children,
                  vector<string> &path,
                  vector<vector<string>> &ans)
    {
        if (word == endWord)
        {
            ans.push_back(path);
            return;
        }

        const auto it = children.find(word);
        if (it == children.cend())
            return;

        for (const string &child : it->second)
        {
            path.push_back(child);
            getPaths(child, endWord, children, path, ans);
            path.pop_back();
        }
    }
};
