#include <string>
#include <iostream>

// 匹配算法

// BF - Brute Force 算法 ， 一个一个字符进行匹配，暴力简单

// BM - Boyer Moore
// text:   Here is a simple example
// search: example
// step 1: 从字符串的最后一个字符开始匹配，s与e, 不匹配且s在查找的字符串中没出现过，故s为坏字符
// step 2:        example
//         把查找字符串移动n位， n = 查找字符串的长度, 同样比对最后一个字符 p 与e, p在查找字符串的倒数第三位上，移动字符串两位
