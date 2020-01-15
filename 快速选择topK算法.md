### 一段时间不写就容易忘记 ， 所以特定整理记录了下来。

*　附参考资料  
[二分查找有几种写法？它们的区别是什么？](https://www.zhihu.com/question/36132386)  
[快速排序算法详解（原理、实现和时间复杂度）](http://data.biancheng.net/view/117.html)

* 代码:
    ```C++
    #include <bits/stdc++.h> 
    using namespace std ;

    int partition(vector<int> &nums , int low ,int high) {
        int tmp = nums[low] ; 
        while(low < high) {
            while(low < high && nums[high] >= tmp) --high ; 
            nums[low] = nums[high] ;
            while(low < high && nums[low] <= tmp) ++low ; 
            nums[high] = nums[low] ; 
        }
        nums[low] = tmp ; 
        return low ;
    }

    // 快速选择 topK 
    int QuickSelect(vector<int> &nums , int target) {
        int left = 0 , right = nums.size() - 1 ; 
        while (left <= right)
        {
            int mild = partition(nums , left , right) ; 
            if(target > mild) {
                left = mild + 1 ; 
            }else if(target < mild) {
                right = mild - 1 ; 
            }else {
                target = nums[mild] ; 
                break; 
            }
        }
        return target ; 
    }

    // 快速排序
    void QuickSort(vector<int> &nums , int low , int high) {
        if(low < high){
            int pivotloc = partition(nums , low ,high) ; 
            QuickSort(nums , low , pivotloc - 1) ; 
            QuickSort(nums , pivotloc + 1 , high) ;  
        }
    }

    int main() 
    {
        vector<int> nums = {45,16,49,12,78,64,16,38,65,79} ; 
        int ans = QuickSelect(nums , 5) ; 
        cout<<ans<<endl ; 
        QuickSort(nums , 0 , nums.size() - 1) ; 
        for(auto num : nums) {
            cout<<num<<" " ; 
        }
        cout<<endl ; 
        return 0 ; 
    }
    ```