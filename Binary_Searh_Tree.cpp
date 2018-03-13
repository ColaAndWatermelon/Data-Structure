#include <stdio.h>  
#include <stdlib.h>  
#include <assert.h>  

typedef struct TNode *Position;
typedef Position BinTree; /* ���������� */
struct TNode { /* ����㶨�� */
	int Data; /* ������� */
	BinTree Left;     /* ָ�������� */
	BinTree Right;    /* ָ�������� */
};
static Position root;
/**��ʼ����*/
void create_tree()
{
	root = NULL;
}

Position Find(int x, BinTree BST)
{
	while (BST)
	{
		if (x > BST->Data)
			BST = BST->Right;
		else if (x < BST->Data)
		{
			BST = BST->Left;
		}
		else
		{
			return BST;
		}
		return NULL;
	}
}

Position FindMax(BinTree BST)
{
	if(BST)
		while (BST->Right)
		{
			BST = BST->Right;
		}
	return BST;
}

Position FindMin(BinTree BST)
{
	if (BST)
		while (BST->Left)
		{
			BST = BST->Left;
		}
	return BST;
}



BinTree Insert(BinTree BST, int X)
{
	if (!BST) { /* ��ԭ��Ϊ�գ����ɲ�����һ�����Ķ��������� */
		BST = (BinTree)malloc(sizeof(struct TNode));
		BST->Data = X;
		BST->Left = BST->Right = NULL;
		if (root == NULL) //���Ϊ���ڵ�  
			root = BST;
	}
	else { /* ��ʼ��Ҫ����Ԫ�ص�λ�� */
		if (X < BST->Data)
			BST->Left = Insert(BST->Left, X);   /*�ݹ����������*/
		else  if (X > BST->Data)
			BST->Right = Insert(BST->Right, X); /*�ݹ����������*/
												/* else X�Ѿ����ڣ�ʲô������ */
	}
	return BST;
}

BinTree Delete(BinTree BST, int X)
{
	Position Tmp;

	if (!BST)
		printf("Ҫɾ����Ԫ��δ�ҵ�");
	else {
		if (X < BST->Data)
			BST->Left = Delete(BST->Left, X);   /* ���������ݹ�ɾ�� */
		else if (X > BST->Data)
			BST->Right = Delete(BST->Right, X); /* ���������ݹ�ɾ�� */
		else { /* BST����Ҫɾ���Ľ�� */
			   /* �����ɾ����������������ӽ�� */
			if (BST->Left && BST->Right) {
				/* ��������������С��Ԫ�����ɾ����� */
				Tmp = FindMin(BST->Right);
				BST->Data = Tmp->Data;
				/* ����������ɾ����СԪ�� */
				BST->Right = Delete(BST->Right, BST->Data);
			}
			else { /* ��ɾ�������һ�������ӽ�� */
				Tmp = BST;
				if (!BST->Left)       /* ֻ���Һ��ӻ����ӽ�� */
					BST = BST->Right;
				else                   /* ֻ������ */
					BST = BST->Left;
				free(Tmp);
			}
		}
	}
	return BST;
}

void show_all(Position node)
{
	if (node)
	{
		show_all(node->Left);
		printf("%d ", node->Data);
		show_all(node->Right);
	}
}

int main()
{
	/**��ʼ��*/
	create_tree();

	/**����*/
	int list[15] = { 8,4,11,2,6,10,13,1,3,5,7,9,15,14,16 };
	int i;
	for (i = 0; i < 15; i++)
		Insert(root, list[i]);

	/**��ʾȫ��*/
	show_all(root);

	Delete(root, 10);
	show_all(root);
	system("pause");
	return 0;
}
