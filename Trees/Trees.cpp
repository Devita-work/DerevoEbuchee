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
	TreeNode* left, * right, *back;
};

// Прототипы функций
TreeNode* makeTree(int level, int b);
void printTree(TreeNode*& root, const int level = 0);
int sumTree(TreeNode* root);
int countOddLevelNodes(TreeNode*& root, const int level = 0);
 // объявление функции поиска суммы предков (она работает, но пока только для 1 элемента :DDD)

void main()
{
	setlocale(LC_ALL, "Russian");

	int b = 0;

	cout << "Введите дерево" << endl;
	TreeNode* root = makeTree(0,b);

	cout << "Введенное дерево:" << endl;
	printTree(root);

	printTree(root->left);
	//cout << endl << oldSumm(root) << endl;dsd

	system("pause");
	return;
}

// Создание бинарного дерева вводом с клавиатуры
TreeNode* makeTree(int level, int b)
{
	char c;
	cout << setw(4 * level) << "" << "Создать вершину? (y/n)";
	cin >> c;
	if (c == 'y')
	{
		TreeNode* p = new TreeNode;
		
		cout << setw(4 * level) << "" << "Введите значение вершины:";
		cin >> p->info;
		b = b + p->info; // на мой взгляд, можно считать сумму тут, но выводит кривые регистры, 
		// не аккуратная работа с памятью, скорее всего надо занулить p->sum, что я и сделал в 62 строчке, но получается каждый раз сумма обнуляться будет, тоже калич крч
		p->sum = b;
		cout << setw(4 * level) << "" << "Левое поддерево вершины " << p->info << endl;
		p->left = makeTree(level + 1,b);

		cout << setw(4 * level) << "" << "Правое поддерево вершины " << p->info << endl;
		p->right = makeTree(level + 1,b);
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
		cout << setw(4 * level) << "" << root->info << "(" << root->sum - root->info << ")" << endl;
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
