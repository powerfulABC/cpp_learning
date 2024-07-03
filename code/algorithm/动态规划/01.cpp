#include <vector>
#include <functional>

using std::vector;
using std::function;
using std::max;

// 01_递归搜索
class Solution {
public:
    int rob(vector<int>& nums) {
        function<int(int)> dfs = [&](int i)->int{
            if (i == 0)
                return nums[0];
            if (i == 1)
                return max(nums[0], nums[1]);

            return max(dfs(i - 1), dfs(i-2) + nums[i]);
        };
        return dfs(nums.size() - 1);
    }
};


// 02_记忆化搜索
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        vector<int> memo(n, -1);
        function<int(int)> dfs = [&](int i)->int{
            if (memo[i] != -1)
                return memo[i];

            int ret;
            if (i == 0)
                ret = nums[0];
            else if (i == 1)
                ret = max(nums[0], nums[1]);
            else
                ret = max(dfs(i - 1), dfs(i-2) + nums[i]);
            memo[i] = ret;
            return ret;
        };
        return dfs(n - 1);
    }
};

// 递推
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        int dp1 = nums[0];
        if (n == 1)
            return dp1;
        int dp2 = max(nums[0], nums[1]);
        for (int i = 2; i < n; ++i)
        {
            int temp = max(dp1 + nums[i], dp2);
            dp1 = dp2;
            dp2 = temp;
        }

        return dp2;
    }
};