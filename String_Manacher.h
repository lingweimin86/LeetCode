#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;
// ���ַ��������Ļ��ĳ���
// �� 1221312214


// ����ⷨ O(n*n)
// ���������ַ�,�����ַ��ڲ���ԭ�ַ����г��ֹ�����ν��
// ��Ϊÿ�αȽ϶�����ʵ�ַ�����ʵ�ַ��Ƚϣ������ַ��������ַ��Ƚ�
// �� #1#2#2#1#3#1#2#2#1#4#
// �����ӹ�����ַ�������iλ�ÿ�ʼ�ֱ�������ҷ�����ַ����бȽϣ�
// ���iλ�õ������ĳ��ȣ����յĳ��ȵ�����ֵ����%2
 

// Manacher �㷨
// �½�һ�����飬��ż�����Ļ��İ뾶
// �������̣�
// �Ƚϵ�ǰλ����R��ֵ���ϴλ������ұ߽磩��
//		��������ұ߽���þ���ⷨ������i�Ļ���ֵ
//      ����ڣ��������������

// ���1��i~ �Ļ�����c�Ļ��İ뾶�ڣ�����i~ֱ�����i�Ļ��ĳ���
//	  L i~  c   i R 
// ..[abcbdkskdbcba]...

// ���2��i~ �Ļ�����c�Ļ��İ뾶�⣬
//
//	    L i~   c    i R 
// ..ab[cdedcbakabcdedc]ft...
// i~ �Ļ���Ϊabcdedcba, a ��L��, ��i�Ļ��İ뾶����R-i
//

// ���3��i~ �Ļ��ĸպ���c ����غ�
//
//	   L  i~   c    i  R 
// ..z[abcdcbakskabcdcba]k...
// i~ ��c�Ļ�����߽綼��L������iΪ������R�뾶��϶��ǻ��ģ�Ȼ������ж�R֮����ַ�
//    �����������R������k,��i�Ļ��İ뾶��������
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

