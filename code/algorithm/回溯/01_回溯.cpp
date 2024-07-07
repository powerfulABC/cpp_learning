// 数组的全排列
// cpp的prev_permutation和next_permutation
// prev_permutation获取上一个全排列，如果没有返回false
// next_permutation获取下一个全排列，如果没有返回false

#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	std::vector<int> vec{ 1,2,3,4,5 };
    
	// 正向打印全排列
	do {
		for (auto i : vec)
			std::cout << i << " ";
		std::cout << std::endl;
	} while (std::next_permutation(vec.begin(), vec.end()));
	
	// 反向打印全排列
	do {
		for (auto i : vec)
			std::cout << i << " ";
		std::cout << std::endl;
	} while (std::prev_permutation(vec.begin(), vec.end()));

	return 0;
}