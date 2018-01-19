#include <cstdio>
#include <cstdlib>
#include "BBSTree.h"
#define ONE '1'
#define TWO '2'
#define THREE '3'
#define FOUR '4'
#define FIVE '5'
#define SIX '6'
#define SEVEN '7'
#define EIGHT '8'
int main() {
    BBSTree T = NULL;
    BBSTree T1  = NULL;
    BBSTree T3 = NULL , T4 = NULL;
    Status taller = ERROR;
    Status shorter = ERROR;
    int  resultIN , resultDel;
    int  num ;
    CharType chooseNum , insertChar , deleteChar;
    char *treeNumber;
    printf("==============请输入要生成的平衡二叉树的元素个数==============\n");
    scanf("%d",&num);
    getchar();
    treeNumber = (char *)malloc(sizeof(num));
    for (int i = 0; i < num; ++i) {
        printf("请输入第 %d 个字符\n",i+1);
        scanf("%c",&treeNumber[i]);
        getchar();
        InsertAVL(T,treeNumber[i],taller);
    }
    printf("============平衡二叉树成功生成==========\n ");
    PrintBBSTree(T,1);
    while (true){
        printf("\n========功能表========\n");
        printf("1、按 1 前序遍历平衡二叉树\t  2、按 2 中序遍历平衡二叉树\n");
        printf("3、按 3 后续遍历平衡二叉树\t  4、按 4 插入字符\n");
        printf("5、按 5 删除字符\t  6、按 6 合并平衡二叉树\n");
        printf("7、按 7 平衡二叉树分裂\t  8、退出程序\n请选择序号：");
        scanf("%c",&chooseNum);
        getchar();
        if (chooseNum < '1' || chooseNum > '8'){
            printf("您输入的指令有误，请重新输入\n");
            continue;
        }
        switch (chooseNum){
            case ONE:
                printf("前序遍历的结果为: \n");
                PreOrderTraverse(T);
                break;
            case TWO:
                printf("中序遍历的结果为:  \n");
                InOrderTraverse(T,1);
                break;
            case THREE:
                printf("后序遍历的结果为：  \n");
                PosOrderTraverse(T);
                break;
            case FOUR:
                printf("请输入你要插入的字符(输入多个只插入第一个字符)：  ");
                scanf("%c",&insertChar);
                getchar();
                resultIN = InsertAVL(T,insertChar,taller);
                if (resultIN == ERROR){
                    printf("插入失败，改字符已经存在\n");
                } else{
                    printf("插入成功，结果为 \n");
                    PrintBBSTree(T,1);
                }
                break;
            case FIVE:
                printf("请输入你要删除的字符(输入多个只插入第一个字符)");
                scanf("%c",&deleteChar);
                getchar();
                resultDel = DeleteAVL(T,deleteChar,shorter);
                if (resultDel == ERROR){
                    printf("删除失败，这个元素不存在或者这棵树为空\n");
                } else{
                    printf("删除成功\n中序遍历出的结果为\n");
                    PrintBBSTree(T,1);
                }
                break;
            case SIX:
                int size;
                char *treeList;
                printf("==============请输入新生成的平衡二叉树的元素个数==============\n");
                scanf("%d",&size);
                getchar();
                treeList = (char *)malloc(sizeof(size));
                for (int i = 0; i < size; ++i) {
                    printf("请输入第 %d 个字符\n",i+1);
                    scanf("%c",&treeList[i]);
                    getchar();
                    InsertAVL(T1,treeList[i],taller);
                }
                Merge(T,T1);
                printf("\n合并成功，结果为：\n");
                PrintBBSTree(T,1);
                break;
            case SEVEN:
                printf("请输入分裂的基准：");
                CharType pos;
                scanf("%c",&pos);
                getchar();
                if (SearchBBSTree(T,pos) == NULL) {
                    printf("结点不存在，分裂失败");
                } else {
                    SplitBBSTree(T,pos,T3,T4);
                    printf("分裂成功，结果为：\n");
                    PrintBBSTree(T3,1);
                    printf("\n==================================\n");
                    PrintBBSTree(T4,1);
                }
                break;
            case EIGHT:
                printf("再见\n");
                return 0;
            default:
                break;
        }
    }
}