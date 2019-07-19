#include<stdio.h>
#include<queue>
#include<stack>
#include<iostream>
#include<algorithm>
using namespace std;
stack<int> stack1;
stack<int> stack2;

void appedTail(int n) // n 为入栈元素个数
{
    for(int i=0;i<n;i++){
        int t; cin>>t;
        stack1.push(t);
    }
}

void deleteHead(){
    if(stack2.size()<=0){ // 注意当 stack2 不为空时，不要压入其他元素进入 stack2 中
                            // 否则队列顺序会打乱。
        while(stack1.size()>0){
            int data = stack1.top();
            stack1.pop();
            stack2.push(data);
        }
    }

    if(stack2.size()==0){
        cout<<"queue is empty"<<endl;
        return ;
    }
    int head = stack2.top();
    stack2.pop();
    cout<<"delete head = "<<head<<" successful"<<endl;
}

int main()
{

    int n; cin>>n;
    appedTail(n);
    deleteHead();

    while(stack2.size()){
        printf("%d\n",stack2.top());
        stack2.pop();
    }
 //   stack1.push(8);//deleteHead();
    while(stack1.size()){
        printf("%d\n",stack1.top());
        stack1.pop();
    }
    return 0;
}
