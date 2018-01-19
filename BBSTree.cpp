//
// Created by Administrator on 2017/12/21.
//
#include <stdio.h>
#include <cstdlib>
#include "BBSTree.h"
#define LH 1        //左高右低
#define EH 0        //等高
#define RH -1       //左低右高

//前序遍历平衡二叉树
void PreOrderTraverse(BBSTree tree){
    if (NULL == tree){
        //平衡二叉树为空
        return;
    } else{
        printf("%c ",tree->data);
        PreOrderTraverse(tree->lchild);
        PreOrderTraverse(tree->rchild);
    }
}

//中序遍历平衡二叉树
void InOrderTraverse(BBSTree tree , int size){
    if (NULL == tree){
        return;
    } else{
        InOrderTraverse(tree->lchild,size+1);
        printf("%c ",tree->data);
        InOrderTraverse(tree->rchild,size+1);
    }
}

//后序遍历平衡二叉树
void PosOrderTraverse(BBSTree tree){
    if (NULL == tree){
        return;
    } else{
        PosOrderTraverse(tree->lchild);
        PosOrderTraverse(tree->rchild);
        printf("%c ",tree->data);
    }
}

//平衡二叉树的查找
BBSTree SearchBBSTree(BBSTree T , CharType c){
    if (NULL == T) return NULL;     //空树查找失败
    if (T->data == c) return T;     //找到了这个节点
    else{
        if (T->data > c)
            return SearchBBSTree(T->lchild , c);
        else
            return SearchBBSTree(T->rchild , c);
    }
}

//右旋调整
void R_Rotate(BBSTree &p){
    BBSTree lc = p->lchild;
    p->lchild = lc->rchild;
    lc->rchild = p;
    p = lc;
}

//左旋调整
void L_Rotate(BBSTree &p){
    BBSTree rc =  p->rchild;
    p->rchild = rc->lchild;
    rc->lchild = p;
    p = rc;
}

//左平衡处理操作
void LeftBalance(BBSTree &T){
    BBSTree lc , rc;
    lc = T->lchild;
    switch (lc->bf){
        //属于LL型
        case LH:
            T->bf = EH;
            lc->bf = EH;
            R_Rotate(T);
            break;
        //属于LR型
        case RH:
            rc = lc->rchild;
            switch (rc->bf){
                case RH:
                    T->bf = EH;
                    rc->bf = EH;
                    lc->bf = LH;
                    break;
                case LH:
                    T->bf = RH;
                    lc->bf = EH;
                    rc->bf = EH;
                    break;
                case EH:
                    T->bf = lc->bf = EH;
                    break;
            }
            L_Rotate(T->lchild);
            R_Rotate(T);
            break;
        case EH:
            lc->bf = RH;
            T->bf = EH;
            R_Rotate(T);
            break;

    }
}

//右平衡处理操作
void RightBalance(BBSTree &T){
    if (NULL == T)
        return;
    BBSTree rc,lc;
    rc = T->rchild; //根节点的右子树
    switch (rc->bf){
        case RH:
            //RR型的情况
            T->bf = EH;
            rc->bf = EH;
            L_Rotate(T);
            break;
        case LH:
            //RL型的情况
            lc = rc->lchild;
            switch (lc->bf){
                case LH:
                    //左边大于右边的情况
                    T->bf = EH;
                    rc->bf = RH;
                    lc->bf = EH;
                    break;
                case RH:
                    //右边大于左边的情况
                    T->bf = LH;
                    lc->bf = EH;
                    rc->bf = EH;
                    break;
                case EH:
                    T->bf = rc->bf = EH;
                    break;
            }
            R_Rotate(T->rchild);
            L_Rotate(T);
            break;
        case EH:
            T->bf = RH;
            rc->bf = LH;
            L_Rotate(T);
            break;
    }
}

//平衡二叉树插入操作
Status InsertAVL(BBSTree &T , CharType e , Status &taller){
    //判断是否为空
    if (NULL == T){
        T = (BBSTNode *)malloc(sizeof(BBSTNode));
        T->data = e;
        T->bf = EH;
        T->rchild = NULL;
        T->lchild = NULL;
        taller = SUCCESS;
    } else if (T->data == e){
        //说明这个数已经存在，不需要再次插入
        taller = ERROR;
        return ERROR;
    } else if (T->data > e){
        //根节点的数大于插入的数，到数的左边插入
        int result = InsertAVL(T->lchild , e , taller);
        if (result == ERROR) return ERROR;
            //递归中的每一层都需要调整
        if (SUCCESS == taller){
            //表示已经插入成功，检查平衡因子
            switch (T->bf){
                case LH:
                    //本来左边比右边高
                    LeftBalance(T);
                    taller = ERROR;
                    break;
                case RH:
                    //原来右边比左边高，现在变成等高
                    T->bf = EH;
                    taller = ERROR;
                    break;
                case EH:
                    //原来两边等高，现在左边比右边高，不需要旋转
                    T->bf = LH;
                    taller = SUCCESS;
                    break;
            }
        }
    } else{
        //插入的数比根节点的大
        int result = InsertAVL(T->rchild , e , taller);
        if (ERROR == result) return ERROR;
        if (SUCCESS == taller){
            switch (T->bf){
                case LH:
                    //本来左边比右边高
                    T->bf = EH;
                    taller = ERROR;
                    break;
                case EH:
                    T->bf = RH;
                    taller = SUCCESS;
                    break;
                case RH:
                    //本来就右边比左边高，需要旋转调整
                    T->bf = EH;
                    RightBalance(T);
                    taller = ERROR;
                    break;
            }
        }
    }
    return SUCCESS;
}


//平衡二叉树的删除操作
Status DeleteAVL(BBSTree &T , CharType e , Status &shorter){
    BBSTree p , pre;
    Status position;
    if (NULL == T)      //空的则删除失败
        return ERROR;
    else if (T->data == e){
        shorter = SUCCESS;
        if (T->lchild == NULL && T->rchild == NULL){
            //表明这是叶子节点，将T置为空
            p = T;
            T = NULL;
            free(p);
        } else if (T->rchild == NULL){
            //右子树为空
            p = T;
            T = T->lchild;
            free(p);
        } else if (T->lchild == NULL){
            //左子树为空
            p = T;
            T = T->rchild;
            free(p);
        } else {
            //既有左子树又有右子树
                //使用T节点的前驱，也就是中序遍历的前一个
                //找到这个节点左孩子节点最右边的节点
                pre = T->lchild;
                while (pre->rchild != NULL){
                    pre = pre->rchild;
                }
                T->data = pre->data;
                DeleteAVL(T->lchild,pre->data,shorter);
                position = 0;
        }
    } else if (T->data > e){
        //删除的数在根节点的左子树上
        Status  result = DeleteAVL(T->lchild,e,shorter);
        if (result == ERROR)
            return ERROR;
        else position = 0;
        //对左子树做操作则标记为0，之后需要对左子树的高度进行调整
    } else if (T->data < e){
        Status result = DeleteAVL(T->rchild,e,shorter);
        if (result == ERROR)
            return ERROR;
        else position = 1;
    }
    //递归的每一层都需要判断并做处理
    if (shorter == SUCCESS) {
        if (position == 0){
                switch (T->bf){
                    case LH:
                        T->bf = EH;
                        shorter = SUCCESS;
                        break;
                    case EH:
                        T->bf = RH;
                        shorter = ERROR;
                        break;
                    case RH:
                        RightBalance(T);
                        if (T->rchild->bf == EH)
                            shorter = ERROR;
                        else
                        shorter = SUCCESS;
                        break;
                }
        }
        //调整树的高度
        if (position == 1) {
                switch (T->bf) {
                    case LH:
                        LeftBalance(T);     //左平衡处理
                        if(T->lchild->bf == EH)
                            shorter = ERROR;
                        else
                            //因为进行了平衡处理，树的高度会改变
                        shorter = SUCCESS;
                        break;
                    case EH:
                        T->bf = LH;
                        shorter = ERROR;
                        break;
                    case RH:
                        T->bf = EH;
                        //改变了树的高度，树变矮了
                        shorter = SUCCESS;
                        break;
                }
        }
    }
    return SUCCESS;
}

//凹表显示
void PrintBBSTree(BBSTree &T , int lev){
    if (NULL == T)  return;
    int i;
    if (T->rchild)
        PrintBBSTree(T->rchild,lev+1);
    for (i = 0; i < lev; i++) {
        printf("   ");
    }
    printf("%c(%d)\n",T->data,T->bf);
    if (T->lchild)
        PrintBBSTree(T->lchild,lev+1);
}

//合并两棵树
void Merge(BBSTree &T1 , BBSTree &T2){
    Status taller = ERROR;
    if (NULL == T2) return;
    //其实类似于中序遍历，将一棵树的内容插入到另一树上即可
    Merge(T1,T2->lchild);
    InsertAVL(T1,T2->data,taller);
    Merge(T1,T2->rchild);
    //之后要将T2这棵树销毁
    DestroyBBSTree(T2);
}

//销毁平衡二叉树
void DestroyBBSTree(BBSTree &T){
    if (T != NULL){
        DestroyBBSTree(T->lchild);
        DestroyBBSTree(T->rchild);
        BBSTree p = T;
        T = NULL;
        free(p);
    }
}

/**
 * 将一个平衡二叉树分裂为两棵
 * @param T
 * @param e 分裂的依据，比e大的为一棵，小的为一棵
 */
void Split(BBSTree T , CharType e ,BBSTree &T1 , BBSTree &T2){
    Status taller = ERROR;
    if (NULL == T) return;
    Split(T->lchild,e,T1,T2);
    if (e < T->data)
        InsertAVL(T1,T->data,taller);
    else
        InsertAVL(T2,T->data,taller);
    Split(T->rchild,e,T1,T2);
}

void SplitBBSTree(BBSTree T,CharType e,BBSTree &T1,BBSTree &T2){
    BBSTree t1 = NULL,t2 = NULL;
    Split(T,e,t1,t2);
    T1 = t1;
    T2 = t2;
    return;
}