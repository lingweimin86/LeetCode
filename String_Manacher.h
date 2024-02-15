#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;
// 求字符串中最大的回文长度
// 如 1221312214


// 经典解法 O(n*n)
// 加入特殊字符,特殊字符在不在原字符串中出现过无所谓，
// 因为每次比较都是真实字符与真实字符比较，特殊字符与特殊字符比较
// 如 #1#2#2#1#3#1#2#2#1#4#
// 遍历加工后的字符串，从i位置开始分别对往左右方向的字符进行比较，
// 求出i位置的最大回文长度，最终的长度等于求值长度%2
 

// Manacher 算法
// 新建一个数组，存放计算出的回文半径
// 遍历过程：
// 比较当前位置与R的值（上次回文最右边界），
//		如果不在右边界里，用经典解法计算这i的回文值
//      如果在，分三种情况讨论

// 情况1，i~ 的回文在c的回文半径内，根据i~直接算出i的回文长度
//	  L i~  c   i R 
// ..[abcbdkskdbcba]...

// 情况2，i~ 的回文在c的回文半径外，
//
//	    L i~   c    i R 
// ..ab[cdedcbakabcdedc]ft...
// i~ 的回文为abcdedcba, a 在L外, 则i的回文半径就是R-i
//

// 情况3，i~ 的回文刚好与c 左边重合
//
//	   L  i~   c    i  R 
// ..z[abcdcbakskabcdcba]k...
// i~ 和c的回文左边界都是L，则以i为中心在R半径里肯定是回文，然后继续判断R之后的字符
//    如上述情况中R后面是k,则i的回文半径继续扩大。
//


string longestPalindrome(string s) {
    const char splitChar = '#';
    int L = 0, R = 0, c = 0; // R - the most right index of max radius, c - the center point of max radius
    vector<char> ns;

    ns.push_back(splitChar);
    for (int i = 0; i < s.length(); i++)
    {
        ns.push_back(s[i]);
        ns.push_back(splitChar);
    }

    vector<int> radius(ns.size(), 1);

    string show;
    show.assign(ns.begin(), ns.end());

    cout << show << endl;

    for (int i = 1; i < ns.size(); i++)
    {
        if (i <= R)
        {
            int ip = 2 * c - i; // the mirror index base on c
            int L_ip = ip - radius[ip] + 1;
            if (L_ip > L) // ip's radius is in c's radius
            {
                radius[i] = radius[ip];
            }
            else if (L_ip < L)
            {
                radius[i] = R - i + 1;
            }
            else
            {
                radius[i] = R - i + 1;
                int L_i = 2 * i - R - 1;
                int R_i = R + 1;
                while ( L_i >=0 && R_i < ns.size() && ns[L_i] == ns[R_i])
                {
                    radius[i]++;
                    L_i--;
                    R_i++;
                }

                if (R_i - 1 > R)
                {
                    R = R_i - 1;
                    L = L_i + 1;
                    c = i;
                }
            }
        }
        else // the usual way
        {
            int L_i = i - 1;
            int R_i = i + 1;
            while (L_i >= 0 && R_i < ns.size() && ns[L_i] == ns[R_i])
            {
                radius[i]++;
                L_i--;
                R_i++;
            }

            if (R_i - 1 > R)
            {
                R = R_i - 1;
                L = L_i + 1;
                c = i;
            }
        }

        cout << "i: " << i << " c: " << c << " L: " << L << " R: " << R << " radius: " << radius[i] << endl;
    }

    auto iter = max_element(radius.begin(), radius.end());

    int index = iter - radius.begin();

    stringstream ss;

    for (int i = index - *iter + 1; i < index + *iter; i++)
    {
        if (ns[i] != '#')
        {
            ss << ns[i];
        }
    }
    return ss.str();
}

void test_longestPalindrome()
{
    //string str1 = "zabcbdkskdbcbak";
    //cout << " the result of " << str1 << " is: " << longestPalindrome(str1) << endl;;

    //string str2 = "abcdedcbakabcdedcft";
    //cout << " the result of " << str2 << " is: " << longestPalindrome(str2) << endl;

    string str3 = "aba";
    cout << " the result of " << str3 << " is: " << longestPalindrome(str3) << endl;
}

