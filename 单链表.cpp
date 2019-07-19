#include<stdio.h>
#include<string.h>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
int n;

// --------- 单链表的存储结构---------

typedef struct Lnode{
    int data;           // 结点的数据域
    struct Lnode *next; // 结点的指针域
}Lnode;

// 单链表初始化
Lnode *Initlist(Lnode *head)// 函数返回是与节点相同的指针
{
    head = new Lnode ;
    head->next = NULL;
    return head;
}

// 后插法建立链表
Lnode *Createlist(Lnode *head,int n){
// 正位序输入 n 个元素的值，建立带表头结点的单链表 head;
    head = new Lnode ;
    head->next = NULL;// 先建立一个带头结点的空链表
    Lnode *r = head; // 指针 r 指向头结点
    for(int i=0;i<n;++i)
    {
        Lnode *p = new Lnode ;// 生成新结点 *p
        cin>>p->data;   // 输入元素值赋值给新结点*p 的数据域
        p->next =NULL; r->next = p; // 将新结点*p 插入结点*r 之后
        r = p;// r 指向新的尾结点 *p;
    }
    return head;
}

// 查找
Lnode *Findkey(Lnode *head,int key)
{   // 从带头结点的单链表 head 中查找值为 key 的元素
    Lnode *p = head->next;  // 初始化，p 指向首元结点
    while(p!=NULL&&p->data != key) // p 为空或 p 所指结点的数据域等于 key 跳出
        p = p->next;    // p 指向下一个结点
    return p; // 查找成功返回值为 key 的结点地址 p,查找失败返回 NULL;
}

// 插入
void Insertkey(Lnode *head,int key,int i)// 在 i 位置，插入 key
{
    Lnode *p = head;int j =0;
    while(p&&j<i-1){// 查找第 i-1 个结点，p 指向该结点
        p = p->next;++j;// 看不懂的话，可以用 i 等于 1，进行检查程序。
    }
    if(!p||j>i-1) cout<<"ERROR"<<endl;// 没有找到指定的位置
    Lnode *s = new Lnode;       // 生成新结点 *s
    s->data = key;  //
    s->next = p->next; // 将结点将结点 *s 的数据域值置为 key; *s 的指针域指向结点位置 i+1
    p->next = s;    // 将结点 *p 的指针域指向结点 *s
    n++;
    cout<< "Insert success" <<endl; // 成功
}

/* 合并循环单链表
void *Connect(Lnode *tail1,Lnode *tail2){
    Lnode *p = tail1->next; //  p 存表头结点
    tail1->next = tail2->next->next; //表1尾 连结表 2 首元结点；
    delete tail2->next; // 释放表 2 的头结点
    tail2->next = p; // 表 2 尾指向 表 1 头结点。

}
*/

// 删除
void Deletekey(Lnode *head,int key)
{
    if(head->next == NULL) // 空表
    {
        printf("empty list!\n");
        return;
    }
    Lnode *p = head,*r; // r 用来表示目标位置前一个地址，前驱
    while(p&&p->data!=key)
    {
        r = p;
        p = p->next;
    }
    if(p==NULL) {cout<<"Not Have This key"<<endl;return;}
    r->next = p->next; // 相当于跳过 p ，指向 p 的下一个结点。
    delete p; n--;// 释放内存。
    cout<< "Delete success" <<endl; // 成功
}
int main()
{
    Lnode *head;
   // head = Initlist(head);// 初始化
    cin>> n;
    head = Createlist(head,n);
    Lnode *p = Findkey(head,2);
    if(p==NULL)
        cout<< "Not Find key!"<<endl;
    else
        cout<<"Find success!"<<endl;
    Insertkey(head,3,1);
    Deletekey(head,2);
    for(int i=0;i<n;i++)
    {
        cout<<head->next->data<<endl;;
        head = head->next;
    }
    return 0;
}
