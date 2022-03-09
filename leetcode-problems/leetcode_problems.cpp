#include "leetcode_problems.h"

#include <unordered_map>

using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
    vector<int> result;
    unordered_map<int, int> seen;
    
    for (auto i=0u; i<nums.size(); i++)
    {
        if (seen.count(target - nums[i]))
        {
            auto answer = seen[target - nums[i]];
            result.push_back(i);
            result.push_back(answer);
            return result;
        }
        
        seen.insert(make_pair(nums[i], i));
    }
    return result;
}

int romanToInt(string s) {
    int result{};
    auto lastIndex = s.size() - 1;
    for (auto i=0u; i<s.size(); i++)
    {
        char current = s[i];
        if (current == 'I')
        {
            if (i != lastIndex && s[i+1] == 'V')
            {
                result += 4;
                i++;
                continue;
            }
            if (i != lastIndex && s[i+1] == 'X')
            {
                result += 9;
                i++;
                continue;
            }
            result += 1;
            continue;
        }
        
        if (current == 'X')
        {
            if (i != lastIndex && s[i+1] == 'L')
            {
                result += 40;
                i++;
                continue;
            }
            
            if (i != lastIndex && s[i+1] == 'C')
            {
                result += 90;
                i++;
                continue;
            }
            result += 10;
            continue;
        }
        
        if (current == 'C')
        {
            if (i != lastIndex && s[i+1] == 'D')
            {
                result += 400;
                i++;
                continue;
            }
            
            if (i != lastIndex && s[i+1] == 'M')
            {
                result += 900;
                i++;
                continue;
            }
            
            result += 100;
            continue;
        }
        
        if (current == 'V')
        {
            result += 5;
            continue;
        }
        
        if (current == 'L')
        {
            result += 50;
            continue;
        }
        
        if (current == 'D')
        {
            result += 500;
            continue;
        }
        
        if (current == 'M')
        {
            result += 1000;
            continue;
        }
    }
    return result;
}