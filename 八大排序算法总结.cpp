#include<bits/stdc++.h>
using namespace std ; 
typedef long long ll ;

/*
	直接插入排序
	int ai[] 为需要排序的数组
	start 为起始位置，要求 start>=1 ,因为 ai[0] 要作为“哨兵”使用。
	end 为结束位置

	代码思路：看后面的数字有没有比前面的大，比前面的大则需要插入交换，从后往前，依次比较，依次往后移一位，直到不满足

*/
void InsertSort(int ai[] , int start , int end)
{
	int i , j ; 
	for(i=start; i<=end; i++){
		if(ai[i]<ai[i-1]){
			ai[0] = ai[i] ; 
			ai[i] = ai[i-1] ; 
			for(j=i-2; ai[j]>ai[0]; j--){
				ai[j+1] = ai[j] ; 
			}
			ai[j+1] = ai[0] ; 
		}
	}
}

/**
 * 折半插入排序
 * 不论初始序列情况如何，在插入第 i 个记录时，需要经过 log2i + 1 次比较
 * 折半插入排序仅减少了关键字间的比较次数，而记录的移动次数不变
 * 
*/
void BInsertSort(int ai[] , int start , int end)
{
	int i,j ; 
	for(i=start; i<=end; i++){
		if(ai[i] < ai[i-1]){
			ai[0] = ai[i] ; 
			int low = 1, high = i-1  ;
			while(low<=high){
				int mild = (low + high)/2 ; 
				if(ai[mild] > ai[0]){
					high = mild - 1 ; 
				}else {
					low = mild + 1 ; 
				}
			}

			for(j=i-1; j>=high+1; j--){
				ai[j+1] = ai[j] ; 
			}
			ai[j+1] = ai[0];
		}
	}
}

/**
 * 希尔排序
 * 分组插入排序、时间复杂度取决于所取“增量”序列函数、不稳定
 * 增量序列中的值没有除 1 之外的公因子，并且最后一个增量值必须等于 1 。
*/
void ShellInsert(int ai[], int start, int end, int dt)
{
	int i, j ; 
	for(i=start+dt; i<=end; i++){
		if(ai[i] < ai[i-dt]){
			ai[0] = ai[i];
			for(j=i-dt; j>0 && ai[0]<ai[j]; j-=dt){
				ai[j+dt] = ai[j] ; 
			}
			ai[j+dt] = ai[0] ; 
		}
	}
}

void ShellSort(int ai[],int start, int end)
{
	int dt[3] = {5,3,1}; 
	for(int i=0; i<3; i++){
		ShellInsert(ai,start,end,dt[i]) ; 
	}
}

/**
 * 冒泡排序
 * 两两比较相邻数的大小，逆序则交换，从而使最小的数如气泡一般逐渐上升，或者最大的数逐渐“坠落“
 * int a[]为需要排序的数组
 * start为起始位置，要求start>=1
 * end为结束位置
 */
void BubbleSort(int ai[], int start, int end)
{
	bool flag = true ; 
	for(int i=start; i<=end-1 && flag; i++)
	{
		flag = false ; 
		for(int j=start; j<=end-i; j++){
			if(ai[j] > ai[j+1]){
				flag = true ;
				int t = ai[j]; ai[j] = ai[j+1]; ai[j+1] = t;
			}
		}
	}
}

/**
 * 快速排序
 * 一次排序消除多个逆序
 * 递归，分治法
 */
int Partition(int ai[], int low, int high)
{
	int privotkey = ai[low];
	while(low<high){
		while(low<high && ai[high] >= privotkey) high--;
		ai[low] = ai[high];
		while(low<high && ai[low] <= privotkey) low++;
		ai[high] = ai[low];
	}
	ai[low] = privotkey;
	return low;
}

void Qsort(int ai[], int low, int high)
{
	if(low < high){
		int pivotloc = Partition(ai,low,high); // 将 ai 一分为二，pivotloc 是枢轴位置
		Qsort(ai, low, pivotloc-1); 
		Qsort(ai, pivotloc+1, high);
	}
}

/**
 * 简单选择排序
 * 找到最小的与相应第一个交换
 * 
 */
void SelectSort(int ai[], int start, int end)
{
	for(int i=start; i<end; i++){// n-1 次比较
		int k = i ; 
		for(int j=i+1; j<=end; j++){
			if(ai[j] < ai[k]) k = j ;
		}
		if(k != i){
			int t = ai[i] ; ai[i] = ai[k] ; ai[k] = t ; 
		}
	}
}
/**
 * 堆排序，大根堆，升序,完全二叉树
 * 筛选法，初建堆从 n/2 开始从下往上，父节点大于子节点
 * 堆排序，调整堆，从 1 往下，交换了则需要继续往下递归，否则跳出。
 * 最坏O(nlog2n)，而快排最坏O(n^2),当记录较多时较为高效
*/

void HeapAdjust(int ai[],int start,int end)
{
	int rc = ai[start] ; 
	for(int i=2*start; i<=end; i*=2){
		if(i < end && ai[i] < ai[i+1]) i++;
		if(rc > ai[i]) break ;
		ai[start] = ai[i]; start = i; 
	}
	ai[start] = rc ;
}

void CreateHeap(int ai[],int end)
{
	for(int i=end/2; i>0; i--){
		HeapAdjust(ai,i,end) ; 
	}
}

void HeapSort(int ai[],int end)
{
	CreateHeap(ai,end);
	for(int i=end; i>0; i--){
		ai[0] = ai[1];
		ai[1] = ai[i];
		ai[i] = ai[0];
		HeapAdjust(ai,1,i-1) ; 
	} 
}

/**
 * 归并排序
 * int ai[]为需要排序的数组
 * cnt为求逆序对数目，是归并排序的拓展
*/
int cnt = 0 ; 
// 合并 ai 数组，排好序，临时存放在 temp 数组里，然后再拷贝到原来的数组 ai 
void Merge(int ai[], int L, int mild, int R)
{
	int *temp = new int[R-L+1] ; 
	int k = L, i = L, j = mild + 1 ; 
	while(i<=mild && j <= R){
		if(ai[i]<=ai[j]) temp[k++] = ai[i++];
		else{
			temp[k++] = ai[j++];
			cnt += mild - i + 1 ;
			/**
			 * 举个例子: A=1,4,6,7,9 B=2,3,5,10,13,21.在Merge中发现当前i号元素4比2大,那么4的逆序数需要+1,又因6,7,9都排在4后面,那么6,7,9的逆序数也应该+1,
			 * 所以总体的逆序数应该加上last-i+1.(如果i号元素比B[j]小（比如4比5小）,无法确定逆序数的变化,不作任何修改).
			*/
		}
	}
	while(i<=mild) temp[k++] = ai[i++] ; 
	while(j<=R) temp[k++] = ai[j++];
	
	for(int i=L;i<k;i++){
		ai[i] = temp[i] ; 	
	}
}
// 归并排序，将 ai 数组前半部分后半部分分成最小单元，然后在合并
void MergeSort(int ai[], int L, int R)
{
	if(L==R){
		return ;
	} else {
		int mild = (L + R) / 2 ; 
		MergeSort(ai,L,mild); 
		MergeSort(ai,mild + 1, R);
		Merge(ai,L,mild,R);
	}
}

/**
 * 基数排序
 * 分配 + 收集
 * 分配：我们将 ai[] 中的元素取出，首先确定其个位上的数字，根据该数字分配到与之序号相同的桶中 range 
 * 收集：当序列中所有的元素都分配到对应的桶中，再按照顺序依次将桶中的元素收集形成新的一个待排序列 ai[ ]
 * 需要知道各级关键字的主次关系和各级关键字的取值范围
*/
void countSort(int ai[], int exp, int len)
{
	vector<int> range[10] ; 

	for(int i=1; i<=len; i++){ // 分配
		int t = (ai[i]/exp)%10 ; 
		range[t].push_back(ai[i]);
	}

	int ant = 1 ;
	for(int i=0; i<10; i++){ // 收集
		for(int j=0;j<range[i].size();j++){
			ai[ant++] = range[i][j] ;
		}
	}

}

void RadixSort(int ai[],int start, int end)
{
	
	int maxn = -1 ; 
	int len = end - start + 1 ; 
	for(int i=start; i<end; i++){ // 提取出最大值
		maxn = max(maxn,ai[i]) ; 
	}

	for(int exp=1; (maxn/exp)> 0; exp*=10){
		countSort(ai,exp,len) ; 
	}
	
}

int main()
{
    int ai[] = {0,49,38,65,97,76,13,27,49};
	/**
	 * 插入排序
	 * InsertSort(ai,2,8) ; // 直接插入排序
	 * BInsertSort(ai,2,10) ; // 折半插入排序
	 * ShellSort(ai,1,10); // 希尔排序
	*/

	/** 
	 * 交换排序
	 * BubbleSort(ai,1,10) ; // 冒泡排序 
	 * Qsort(ai,1,10) ; // 快速排序
	 */

	/**
	 * 选择排序
	 * SelectSort(ai,1,10); // 简单选择排序
	 * HeapSort(ai,8) ;  // 堆排序
	*/

	/**
	 * MergeSort(ai,1,8) ; // 归并排序
	 * RadixSort(ai,1,8) ; // 基数排序
	*/
	
	
	for(int i=1;i<=8;i++){
		cout<<ai[i]<<" "; 
	}
	cout<<endl; 

	return 0 ; 
}
