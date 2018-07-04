//
//  main.c
//  balance_binarytree
//
//  Created by 耿瑜 on 2018/6/25.
//  Copyright © 2018年 德玛西亚的耿宝宝的mac. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define size 1000

typedef enum
{
    false,
    true
}bool;

struct treenode {
    bool sign;
    int data;
    int bf;
    struct treenode* leftchild;
    struct treenode* rightchild;
    struct treenode* parent;
};

void init_treenode(struct treenode *newnode,int num){
    newnode->data=num;
    newnode->bf=0;
    newnode->leftchild=NULL;
    newnode->rightchild=NULL;
    newnode->parent=NULL;
    newnode->sign=true;
}//新的树节点初始化。

void balance_factor_delnode(struct treenode *p){
    struct treenode *N,*M;
    M=p;
    while(M->parent!=NULL){
        N=M->parent;
        if(M==N->leftchild)N->bf=N->bf+1;
        else N->bf=N->bf-1;
        if(N->bf==0)break;
        M=N;
    }
}//delnode操作更新平衡系数。

void balance_factor_addnode(struct treenode *p){
    struct treenode *N,*M;
    M=p;
    while(M->parent!=NULL){
        N=M->parent;
        if(M==N->leftchild)N->bf=N->bf-1;
        else N->bf=N->bf+1;
        if(N->bf==0)break;
        M=N;
    }
}//add操作更新平衡系数

void balance_factor_R_Rotate(struct treenode *p){
    p->bf=p->bf+1;
    p->rightchild->bf += 2;
    balance_factor_delnode(p);
}//R_Rotate操作更新平衡系数

void balance_factor_L_Rotate(struct treenode *p){
    p->bf=p->bf-1;
    p->leftchild->bf -= 2;
    balance_factor_delnode(p);
}//L_Rotate操作更新平衡系数

void balance_factor_LR_Rotate(struct treenode *p){
    int c;
    c=p->bf;
    if(c<0){
        p->bf = p->rightchild->bf + 2;
        p->leftchild->bf -= 1;
        p->rightchild->bf = p->rightchild->bf - c + 2;
    }
    else{
        p->bf=p->leftchild->bf-1;
        p->leftchild->bf = p->leftchild->bf - c -1;
        p->rightchild->bf += 2;
    }
    balance_factor_delnode(p);
}//LR_Rotate操作更新平衡系数

void balance_factor_RL_Rotate(struct treenode *p){
    int c;
    c=p->bf;
    if(c<0){
        p->bf=p->leftchild->bf-2;
        p->leftchild->bf = p->rightchild->bf + 1;
        p->rightchild->bf = p->rightchild->bf-c +1;
    }
    else{
        p->bf = p->leftchild->bf-2;
        p->leftchild->bf = p->leftchild->bf-c -2;
        p->rightchild->bf += 1;
    }
    balance_factor_delnode(p);
}//RL_Rotate操作更新平衡系数

void R_Rotate(struct treenode **p){
    struct treenode *lc;
    lc = (*p)->leftchild;
    (*p)->leftchild = lc->rightchild;
    lc->parent = (*p)->parent;
    (*p)->parent = lc;
    lc->rightchild = (*p);
    (*p)=lc;
} // 右单旋转

void L_Rotate(struct treenode **p) {
    struct treenode *rc;
    rc = (*p)->rightchild;
    (*p)->rightchild = rc->leftchild;
    rc->parent = (*p)->parent;
    (*p)->parent = rc;
    rc->leftchild = (*p);
    (*p)=rc;
} //左单旋转

void LR_Rotate (struct treenode **p) {
    struct treenode *lc,*rc;
    rc =(*p);
    lc =rc->leftchild;
    (*p)=lc->rightchild;
    lc->rightchild=(*p)->leftchild;
    (*p)->leftchild=lc;
    rc->leftchild=(*p)->rightchild;
    (*p)->rightchild=rc;
    (*p)->parent=rc->parent;
    rc->parent=(*p);
    lc->parent=(*p);
} // 先左后右双旋转

void RL_Rotate (struct treenode **p) {
    struct treenode *lc,*rc;
    lc =(*p);
    rc =lc->rightchild;
    (*p)=rc->leftchild;
    rc->leftchild=(*p)->rightchild;
    (*p)->rightchild=rc;
    lc->rightchild=(*p)->leftchild;
    (*p)->leftchild=lc;
    (*p)->parent=lc->parent;
    rc->parent=(*p);
    lc->parent=(*p);
} // 先右后左双旋转

void balancing_tree(struct treenode *p){
    struct treenode *L, *N, *M;
    L=p;
    N=p->parent;
    M=N;
    while(M->parent!=NULL){
        M=M->parent;
        if(M->bf>1||M->bf<-1){
            if(N==M->leftchild){
                if(L==N->leftchild){
                    R_Rotate(&M);
                    balance_factor_R_Rotate(M);
                }
                else{
                    LR_Rotate(&M);
                    balance_factor_LR_Rotate(M);
                }
            }
            else{
                if(L==N->rightchild){
                    L_Rotate(&M);
                    balance_factor_L_Rotate(M);
                }
                else{
                    RL_Rotate(&M);
                    balance_factor_RL_Rotate(M);
                }
            }
            break;
        }
        L=N;
        N=M;
    }
}//更新平衡树。

int search(struct treenode* start,int num, struct treenode **p){
    struct treenode *N;
    N=start;
    while(1){
        if(num>N->data){
            if(N->rightchild!=NULL)N=N->rightchild;
            else{
                (*p)=N;
                return 2;
            }
        }
        else if(num<N->data){
            if(N->leftchild!=NULL)N=N->leftchild;
            else{
                (*p)=N;
                return 1;
            }
        }
        else{
            (*p)=N;
            return 0;
        }
    }
}//查找节点：返回2表示在此节点右侧；返回1表示在此节点左侧；返回0表示找到此节点。

int addnode(struct treenode* start, struct treenode* newnode){//1表示成功，0表示失败。
    struct treenode *N=NULL;
    int i=0;
    i=search(start,newnode->data,&N);
    //添加新的节点
    if(i==2){
        N->rightchild=newnode;
        newnode->parent=N;
    }
    else if(i==1){
        N->leftchild=newnode;
        newnode->parent=N;
    }
    else{
        printf("节点已存在\n");
        return 0;
    }
    //使树重新平衡。
    balance_factor_addnode(newnode);
    balancing_tree(newnode);
    return 1;
}//增加节点；

int delnode(struct treenode* start, int data){
    struct treenode *N=NULL;
    int i=0;
    i=search(start,data,&N);
    if(i==0){
    }
    else{
        printf("节点不存在\n");
        return 0;
    }
    return 1;
}//删除数据为data的节点；

void tree_printf(struct treenode *start){
    int i=0,t=0,m=0;
    struct treenode *N;
    N=start;
    while(N->leftchild!=NULL)i++;
    i=2*i;//计算树的深度至多为左路的两倍加一；考虑根节点记为深度为0；
    N=start;
    t=0;
    while(N->rightchild!=NULL){
        while(N->leftchild!=NULL){
            for(m=0;m<(2^(i-t));m++){
                printf(" ");
                //写到这了
            }
        }
    }
    printf("%d\n",start->data);
}//树的图形化显示

int main() {
    struct treenode *AVL_tree,*start,*N=NULL;
    char m;
    int i=0,num,t,k;//i用来指示tree中的可用空节点，num储存数据，t储存状态，k表示AVL_tree申请了k*size个节点
    AVL_tree=(struct treenode * )malloc(size*sizeof(struct treenode));
    k=1;
    for(i=0;i<1000;i++)AVL_tree[i].sign=false;
    i=0;
    printf("产生根结点，输入根结点数值：");
    scanf("%d",&num);
    getchar();
    init_treenode(&AVL_tree[i],num);
    start=&AVL_tree[i];
    i++;
    printf("输入格式：\noperator,data\\n\noperator:a=add node,del=delete node, s=search, q=quit(data=0)\n");
    scanf("%c,%d",&m,&num);
    getchar();
    while(m!='q'){
        if(m=='a'){
            init_treenode(&AVL_tree[i], num);
            t=addnode(start,&AVL_tree[i]);
            if(t!=1)printf("add fail\n");
            else printf("add success\n");
            i++;
        }
        else if(m=='d'){
            t=delnode(start,num);
            if(t!=1)printf("delet fail\n");
            else printf("delet success\n");
        }
        else if(m=='s'){
            t=search(start,num,&N);
            if(t==2)printf("节点不存在，新节点在%d的右侧\n",N->bf);
            else if(t==1)printf("节点不存在，新节点在%d的左侧\n",N->bf);
            else printf("节点存在，其父节点为%d\n",N->parent->data);
        }
        else printf("input erro\n");
        tree_printf(start);
        scanf("%c,%d",&m,&num);
        getchar();
        if(i==k*size){
            t=0;
            for(i=0;i<k*size;i++){
                if(AVL_tree[i].sign==true){
                    AVL_tree[t]=AVL_tree[i];
                    t++;
                }
            }
            if(t==k*size){
                printf("内存溢出，需申请更多空间\n");
                AVL_tree=(struct treenode * )malloc(size*sizeof(struct treenode));
                for(i=k*size;i<(k+1)*size;i++)AVL_tree[i].sign=false;
                k++;
            }
            i=t;
        }//清理内存，释放没储存数据的节点。
    }
    free(AVL_tree);
    return 0;
}
