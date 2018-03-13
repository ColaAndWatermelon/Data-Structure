#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;
typedef struct AVLNode *Position;
typedef Position AVLTree; /* AVL������ */
struct AVLNode {
	ElementType Data; /* ������� */
	AVLTree Left;     /* ָ�������� */
	AVLTree Right;    /* ָ�������� */
	int Height;       /* ���� */
};
static AVLTree Tree;

int Max(int a, int b)
{
	return a > b ? a : b;
}

int GetHeight(AVLTree A)
{
	int HR, HL, MaxH;
	if (A)
	{
		HL = GetHeight(A->Left);
		HR = GetHeight(A->Right);
		MaxH = (HR > HL) ? HR : HL;
		return (MaxH + 1);
	}
	else return 0;
}

AVLTree SingleLeftRotation(AVLTree A)
{ /* ע�⣺A������һ�����ӽ��B */
  /* ��A��B������������A��B�ĸ߶ȣ������µĸ����B */

	AVLTree B = A->Left;
	A->Left = B->Right;
	B->Right = A;
	A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
	B->Height = Max(GetHeight(B->Left), A->Height) + 1;
	return B;
}

AVLTree SingleRightRotation(AVLTree A)
{
	AVLTree B = A->Right;
	A->Right = B->Left;
	B->Left = A;
	A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
	B->Height = Max(GetHeight(B->Left), A->Height) + 1;
	return B;
}

AVLTree DoubleLeftRightRotation(AVLTree A)
{ /* ע�⣺A������һ�����ӽ��B����B������һ�����ӽ��C */
  /* ��A��B��C�����ε����������µĸ����C */

  /* ��B��C���ҵ�����C������ */
	A->Left = SingleRightRotation(A->Left);
	/* ��A��C��������C������ */
	return SingleLeftRotation(A);
}

AVLTree DoubleRightLeftRotation(AVLTree A)
{
	A->Right = SingleLeftRotation(A->Right);
	return SingleRightRotation(A);
}

AVLTree Insert(AVLTree T, ElementType X)
{ /* ��X����AVL��T�У����ҷ��ص������AVL�� */
	if (!T) { /* ��������������½�����һ�������� */
		T = (AVLTree)malloc(sizeof(struct AVLNode));
		T->Data = X;
		T->Height = 0;
		T->Left = T->Right = NULL;
	} /* if (�������) ���� */

	else if (X < T->Data) {
		/* ����T�������� */
		T->Left = Insert(T->Left, X);
		/* �����Ҫ���� */
		if (GetHeight(T->Left) - GetHeight(T->Right) == 2)
			if (X < T->Left->Data)
				T = SingleLeftRotation(T);      /* ���� */
			else
				T = DoubleLeftRightRotation(T); /* ��-��˫�� */
	} /* else if (����������) ���� */

	else if (X > T->Data) {
		/* ����T�������� */
		T->Right = Insert(T->Right, X);
		/* �����Ҫ���� */
		if (GetHeight(T->Left) - GetHeight(T->Right) == -2)
			if (X > T->Right->Data)
				T = SingleRightRotation(T);     /* �ҵ��� */
			else
				T = DoubleRightLeftRotation(T); /* ��-��˫�� */
	} /* else if (����������) ���� */

	  /* else X == T->Data��������� */

	  /* �����˸������� */
	T->Height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1;
	return T;
}


void InorderTraversal(AVLTree BT)
{

	if (BT) {
		InorderTraversal(BT->Left);
		/* �˴������BT���ķ��ʾ��Ǵ�ӡ���� */
		printf("%d ", BT->Data); /* ��������Ϊ���� */
		InorderTraversal(BT->Right);
	}
}

void PreorderTraversal(AVLTree BT)
{
	if (BT) {
		printf("%d ", BT->Data);
		PreorderTraversal(BT->Left);
		PreorderTraversal(BT->Right);
	}
}

void PostorderTraversal(AVLTree BT)
{
	if (BT) {
		PostorderTraversal(BT->Left);
		PostorderTraversal(BT->Right);
		printf("%d ", BT->Data);
	}
}


void Create()
{
	Tree = NULL;
}

int main()
{
	int a[8] = { 12,6,8,5,4,7,14,96 };
	int i;
	Create();

	for (i = 0; i <= 7; i++)
	{
		Tree=Insert(Tree, a[i]);
	}

	PreorderTraversal(Tree);
	printf("\n");
	InorderTraversal(Tree);
	printf("\n");
	PostorderTraversal(Tree);
	printf("\n");

	system("pause");
}