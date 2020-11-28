/*
Последовательно вводятся вершины бинарного дерева.
По построенному дереву найти
1) сумму вершин дерева
2) количество вершин на нечетных уровнях

Автор : Метелев В.Р.
Дата  : 16.10.2020
*/

#include <iostream>
#include <iomanip>
#include <locale.h>

using namespace std;

struct TreeNode
{
	int info;
	int sum; //добавил сумму, как характеристику вершины
	TreeNode* left, * right;
};

// Прототипы функций
TreeNode* makeTree(int level);
void printTree(TreeNode*& root, const int level = 0);
int sumTree(TreeNode* root);
int countOddLevelNodes(TreeNode*& root, const int level = 0);
int oldSumm(TreeNode*& root); // объявление функции поиска суммы предков (она работает, но пока только для 1 элемента :DDD)

void main()
{
	setlocale(LC_ALL, "Russian");

	cout << "Введите дерево" << endl;
	TreeNode* root = makeTree(0);

	cout << "Введенное дерево:" << endl;
	printTree(root);

	cout << "Сумма вершин дерева = " << sumTree(root) << endl;

	cout << "Количество вершин на нечётных уровнях = " << countOddLevelNodes(root, 0) << endl;

	printTree(root->left);
	//cout << endl << oldSumm(root) << endl;

	system("pause");
	return;
}

// Создание бинарного дерева вводом с клавиатуры
TreeNode* makeTree(int level)
{
	char c;
	int b;
	cout << setw(4 * level) << "" << "Создать вершину? (y/n)";
	cin >> c;
	if (c == 'y')
	{
		TreeNode* p = new TreeNode;
		p->sum = 0;
		cout << setw(4 * level) << "" << "Введите значение вершины:";
		cin >> p->info;
		p->sum = p->sum + p->info; // на мой взгляд, можно считать сумму тут, но выводит кривые регистры, 
		// не аккуратная работа с памятью, скорее всего надо занулить p->sum, что я и сделал в 62 строчке, но получается каждый раз сумма обнуляться будет, тоже калич крч

		cout << setw(4 * level) << "" << "Левое поддерево вершины " << p->info << endl;
		p->left = makeTree(level + 1);

		cout << setw(4 * level) << "" << "Правое поддерево вершины " << p->info << endl;
		p->right = makeTree(level + 1);
		return p;
	}
	else
		return NULL;


}


// Вывод бинарного дерева на консоль
void printTree(TreeNode*& root, const int level)
{
	if (root)
	{
		printTree(root->left, level + 1);
		cout << setw(4 * level) << "" << root->info << root->sum << endl;
		printTree(root->right, level + 1);
	}
	return;
}

// Функция возвращает сумму вершин бинарного дерева
int sumTree(TreeNode* root)
{
	if (root)
		return root->info + sumTree(root->left) + sumTree(root->right);
	else
		return 0;
}

// Функция возвращает сумму количество вершин бинарного дерева на нечетных уровнях
int countOddLevelNodes(TreeNode*& root, const int level)
{
	if (root)
		return (level % 2 == 1 ? 1 : 0) + countOddLevelNodes(root->left, level + 1) + countOddLevelNodes(root->right, level + 1);
	else
		return 0;
}

// Функция поиска суммы предков
int oldSumm(TreeNode*& root)
{
	int rightSumm = 0;
	int leftSumm = 0;
	while ((root->left != NULL) and (root->right != NULL)) //пока у вершины есть корни делаем это:
	{
		if (root->left = NULL)
		root = root->left;
		leftSumm += root->info;
	}
	return leftSumm;
}
