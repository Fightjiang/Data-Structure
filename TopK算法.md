### TopK 算法

> 什么是 Top K 问题？简单来说就是在一组数据里面找到[频率出现最高的前 K 个数](https://leetcode-cn.com/problems/top-k-frequent-elements/)，或[前 K 大](https://leetcode-cn.com/problems/kth-largest-element-in-an-array/)（当然也可以是[前 K 小](https://leetcode-cn.com/problems/zui-xiao-de-kge-shu-lcof/)）的数。

1. 堆排序

* 当数据量特别大的时候，推荐使用堆来求 TopK 问题，因为输入很大、k很小的情况，k 远小于n，时间复杂度O(nlogk)趋近于O(n) 。

**具体步骤如下：**

* 从数组中取前 k 个数（ 0 到 k-1 位），构造一个小顶堆
* 从 k 位开始遍历数组，每一个数据都和小顶堆的堆顶元素进行比较，如果小于堆顶元素，则不做任何处理，继续遍历下一元素；如果大于堆顶元素，则将这个元素替换掉堆顶元素，然后再堆化成一个小顶堆。
* 遍历完成后，堆顶的数据就是第 K 大的数据
* 我的代码是手写的堆，也可以采用 STL 中的 priority_queue ，构建最小堆（默认最大堆需要重载）。

* 代码：
```C++
class Solution {
public:
    void HeapAdjust(vector<int>& heap , int start , int end) {

        int current = heap[start] ; 
        for(int i = start*2 + 1 ; i < end ; i = i*2 + 1 ) {
            if(i + 1 < end && heap[i+1] < heap[i]) ++i ; 
            if(heap[i] > current) break ;
            heap[start] = heap[i] ; 
            start = i ;
        }
        heap[start] = current ; 

    }

    void buildHeap(vector<int>& heap , int end) {
        for(int i = end / 2 - 1 ; i >= 0 ; --i) {
            HeapAdjust(heap , i , end) ; 
        }
    }

    int findKthLargest(vector<int> &nums  , int k ) {

        vector<int> heap ;
        for(int i = 0 ; i < k ; ++i) {
            heap.push_back(nums[i]) ; 
        }

        buildHeap(heap , k) ; // 建立大小为 K 的小顶堆

        for(int i = k ; i < nums.size() ; ++i){
            if(nums[i] > heap[0]) { // 如果大于堆顶元素，则替换堆顶重新堆化
                heap[0] = nums[i] ;
                HeapAdjust(heap , 0 , k) ;
            }
        }
        return heap[0] ; 
    }
};
```

2. 快速选择算法：

无论是排序算法还是构造堆求解 Top k问题，我们都经过的一定量的不必要操作：

* 如果使用排序算法，我们仅仅想要的是第 k 个最大值，但是我们却对数组进行了整体或局部的排序
* 如果使用堆排序，需要维护一个大小为 k 的堆(大顶堆，小顶堆)，同时花费时间也很昂贵，时间复杂度为 O(nlogk)

我们可以实现快速排序来取第 k 个最大值，但是其实没必要那么麻烦，我们仅仅需要在每执行一次快排的时候，比较基准值位置是否在 n-k 位置上，

* 如果小于 n-k ，则第 k 个最大值在基准值的右边，我们只需递归快排基准值右边的子序列即可；
* 如果大于 n-k ，则第 k 个最大值在基准值的做边，我们只需递归快排基准值左边的子序列即可；
* 如果等于 n-k ，则第 k 个最大值就是基准值

优化： 可以通过优化快速选择（quickselect）算法中 Partion 中的基准值的选取，也就是BFPTR算法，使得最坏情况下时间复杂度在 O(n) , 普通的最坏复杂度在 O(n^2) ; 
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

3. 频率出现最高的前 K 个数

这个感觉不完全是 TOPK 问题，频率采用的是桶排序的算法，感觉比建立大小根堆和快选更的效果更佳

* 代码：
```C++
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        
        // 统计出现个数
        unordered_map<int , int > Count_map ; 
        for(auto num : nums) {
            Count_map[num]++ ; 
        }

        //桶排序，将数字的频次 作为桶的索引index
        vector<vector<int> > Nums_vec(nums.size() + 1) ;
        int max_size = INT_MIN ; 
        for(auto iter = Count_map.begin() ; iter != Count_map.end() ; iter++){
            Nums_vec[iter->second].push_back(iter->first) ;
            max_size = max(max_size , iter->second) ; 
        }

        //从索引高到低依次遍历每个桶，如果桶不空，则取数直至取出前k个数
        int sum = 0 ;
        vector<int> ans ; 
        for(int i = max_size ; i>=0 ;i--){
            if(Nums_vec[i].size() != 0 && sum < k ){
                for(int j = 0 ; j < Nums_vec[i].size() ; j++){
                    if(sum < k ) ans.push_back(Nums_vec[i][j]) ; 
                    ++sum ; 
                }
            }
        }
        
        return ans; 
    }
};
```

*　附参考资料  
[二分查找有几种写法？它们的区别是什么？](https://www.zhihu.com/question/36132386)  
[快速排序算法详解（原理、实现和时间复杂度）](http://data.biancheng.net/view/117.html)
[进阶算法10：别再说你不懂topk问题了](https://github.com/sisterAn/JavaScript-Algorithms/issues/73)