#include <string>
#include <vector>
using namespace std;

vector<int> getKArray(string s)
{
	int len = s.length();
	vector<int> vec(len, 0);
	vec[0] = -1;
	vec[1] = 0;
	int cn = 0;
	int i = 2;
	while(i < len)
	{
		if (s[i - 1] == s[cn])
		{
			vec[i++] = ++cn;
		}
		else if (cn > 0)
		{
			cn = vec[cn];
		}
		else
		{
			vec[i++] = 0;
		}
	}
	return vec;
}

int getIndexOf(string s1, string s2)
{
	int i1 = 0;
	int i2 = 0;
	vector<int> k_array = getKArray(s2);
	int len1 = s1.length();
	int len2 = s2.length();
	while (i1 < len1 && i2 < len2)
	{
		if (s1[i1] == s2[i2])
		{
			i1++;
			i2++;
		}
		else if (k_array[i2] == -1) {// or i2 == 0
			i1++;
		}
		else
		{
			i2 = k_array[i2]; // jump forward
		}
	}

	return i2 == s2.length() ? i1 - i2 : -1;
}
