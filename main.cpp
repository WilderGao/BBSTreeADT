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
    printf("==============������Ҫ���ɵ�ƽ���������Ԫ�ظ���==============\n");
    scanf("%d",&num);
    getchar();
    treeNumber = (char *)malloc(sizeof(num));
    for (int i = 0; i < num; ++i) {
        printf("������� %d ���ַ�\n",i+1);
        scanf("%c",&treeNumber[i]);
        getchar();
        InsertAVL(T,treeNumber[i],taller);
    }
    printf("============ƽ��������ɹ�����==========\n ");
    PrintBBSTree(T,1);
    while (true){
        printf("\n========���ܱ�========\n");
        printf("1���� 1 ǰ�����ƽ�������\t  2���� 2 �������ƽ�������\n");
        printf("3���� 3 ��������ƽ�������\t  4���� 4 �����ַ�\n");
        printf("5���� 5 ɾ���ַ�\t  6���� 6 �ϲ�ƽ�������\n");
        printf("7���� 7 ƽ�����������\t  8���˳�����\n��ѡ����ţ�");
        scanf("%c",&chooseNum);
        getchar();
        if (chooseNum < '1' || chooseNum > '8'){
            printf("�������ָ����������������\n");
            continue;
        }
        switch (chooseNum){
            case ONE:
                printf("ǰ������Ľ��Ϊ: \n");
                PreOrderTraverse(T);
                break;
            case TWO:
                printf("��������Ľ��Ϊ:  \n");
                InOrderTraverse(T,1);
                break;
            case THREE:
                printf("��������Ľ��Ϊ��  \n");
                PosOrderTraverse(T);
                break;
            case FOUR:
                printf("��������Ҫ������ַ�(������ֻ�����һ���ַ�)��  ");
                scanf("%c",&insertChar);
                getchar();
                resultIN = InsertAVL(T,insertChar,taller);
                if (resultIN == ERROR){
                    printf("����ʧ�ܣ����ַ��Ѿ�����\n");
                } else{
                    printf("����ɹ������Ϊ \n");
                    PrintBBSTree(T,1);
                }
                break;
            case FIVE:
                printf("��������Ҫɾ�����ַ�(������ֻ�����һ���ַ�)");
                scanf("%c",&deleteChar);
                getchar();
                resultDel = DeleteAVL(T,deleteChar,shorter);
                if (resultDel == ERROR){
                    printf("ɾ��ʧ�ܣ����Ԫ�ز����ڻ��������Ϊ��\n");
                } else{
                    printf("ɾ���ɹ�\n����������Ľ��Ϊ\n");
                    PrintBBSTree(T,1);
                }
                break;
            case SIX:
                int size;
                char *treeList;
                printf("==============�����������ɵ�ƽ���������Ԫ�ظ���==============\n");
                scanf("%d",&size);
                getchar();
                treeList = (char *)malloc(sizeof(size));
                for (int i = 0; i < size; ++i) {
                    printf("������� %d ���ַ�\n",i+1);
                    scanf("%c",&treeList[i]);
                    getchar();
                    InsertAVL(T1,treeList[i],taller);
                }
                Merge(T,T1);
                printf("\n�ϲ��ɹ������Ϊ��\n");
                PrintBBSTree(T,1);
                break;
            case SEVEN:
                printf("��������ѵĻ�׼��");
                CharType pos;
                scanf("%c",&pos);
                getchar();
                if (SearchBBSTree(T,pos) == NULL) {
                    printf("��㲻���ڣ�����ʧ��");
                } else {
                    SplitBBSTree(T,pos,T3,T4);
                    printf("���ѳɹ������Ϊ��\n");
                    PrintBBSTree(T3,1);
                    printf("\n==================================\n");
                    PrintBBSTree(T4,1);
                }
                break;
            case EIGHT:
                printf("�ټ�\n");
                return 0;
            default:
                break;
        }
    }
}