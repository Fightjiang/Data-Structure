## KMP 算法
碰到了一个用 `KMP` 算法解决的问题，特地花了将近一天的时间弄明白了 `KMP` 的相关实现。

**求 `NEXT` 数组：**
* 方法一
```C++
vector<int> get_next(string S){
    vector<int> next  ; 
    next.push_back(-1) ; 
    int n = S.size() , i = 0 , j = -1 ;  
    while(i < n){
        if(j == -1 || S[i] == S[j]){
            i++ ; j++ ; 
            next.push_back(j) ; 
        }else {
            j = next[j] ; 
        }
    }
    return next ; 
}
```
* 方法二
```C++
vector<int> get_next(string s){
    vector<int> next(s.size() , 0) ; 
    for(int i = 1 ; i < s.size() ; i++){
        int j = next[i-1] ; 
        while(s[i] != s[j] && j > 0){
            j = next[j-1] ; 
        }
        if(s[i] == s[j]){
            next[i] = j + 1 ;
        }else {
            next[i] = 0 ; 
        }
    }
    return next ; 
}
```

注：其实两种方法的思路是一样的，都是用到了 next 自身的回溯 ，个人觉得第二种方法更容易理解。 next 数组其实就是当前位置，相同前缀和后缀最长的值。

**使用`NEXT`数组比较：**
```C++
int len1 = T.size() , len2 = S.size() ; 
int i = 0 , j = 0 ; 
while( i < len1 && j < len2){
    if(j == -1 || T[i] == S[j]){
        i++; j++ ; 
    }else {
        j = next[j] ; 
    }
}
```

**参考链接：**  
[KMP算法（研究总结，字符串）](https://www.cnblogs.com/SYCstudio/p/7194315.html)  
[字符串匹配的KMP算法](http://www.ruanyifeng.com/blog/2013/05/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm.html)  

**相关题目：**  
[HDU Number Sequence](http://acm.hdu.edu.cn/showproblem.php?pid=1711)  
[leetcode-cn 实现 strStr()](https://leetcode-cn.com/problems/implement-strstr)
