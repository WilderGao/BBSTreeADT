//
// Created by Administrator on 2017/12/21.
//

#ifndef BBSTREE_BBSTREE_H
#define BBSTREE_BBSTREE_H
#define SUCCESS 1       //成功
#define ERROR 0         //失败

#endif //BBSTREE_BBSTREE_H
typedef char CharType;  //结点元素类型
typedef int Status;     //状态类型
typedef struct BBSTNode{
    CharType data;  //结点值
    int bf;         //平衡节点因子
    struct BBSTNode *lchild , *rchild;  //左子树和右子树
}BBSTNode,*BBSTree;

void PreOrderTraverse(BBSTree tree);        //先序遍历
void InOrderTraverse(BBSTree tree,int size);    //中序遍历
void PosOrderTraverse(BBSTree tree);    //后续遍历
BBSTree SearchBBSTree(BBSTree T , CharType c);  //查找结点
void R_Rotate(BBSTree &p);  //右旋操作
void L_Rotate(BBSTree &p);  //左旋操作
void LeftBalance(BBSTree &T);   //左平衡调整
void RightBalance(BBSTree &T);  //右平衡调整
Status InsertAVL(BBSTree &T , CharType e , Status &taller); //插入结点
Status DeleteAVL(BBSTree &T , CharType e , Status &shorter);    //删除结点
void PrintBBSTree(BBSTree &T , int lev);    //凹表打印二叉树
void Merge(BBSTree &T1 , BBSTree &T2);  //合并
void DestroyBBSTree(BBSTree &T);    //销毁
void Split(BBSTree T , CharType e ,BBSTree &T1 , BBSTree &T2);  //分裂
void SplitBBSTree(BBSTree T,CharType e,BBSTree &T1,BBSTree &T2);    //分裂