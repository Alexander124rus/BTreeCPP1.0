#include <iostream>;
using namespace std;

template <class T>
class BTree
{
public:
	// Узел бинарного дерева
	template <class DATA>
	struct BTreeNode
	{
		BTreeNode<DATA>* parent; // Указатель на родительский
		// узел
		BTreeNode<DATA>* left; // Указатель на узел-корень
		// левого поддерева


		BTreeNode<DATA>* right; // Указатель на узел-корень
// правого поддерева
		DATA data; // Объект данных, хранящихся в узле дерева
		BTreeNode(const DATA& _data,
			BTreeNode<DATA>* _parent = NULL,
			BTreeNode<DATA>* _left = NULL,
			BTreeNode<DATA>* _right = NULL
		)
		{
			data = _data;
			parent = _parent;
			left = _left;
			right = _right;
		}
	};


	BTreeNode<T>* root; // Корень дерева
public:
	BTree()
	{
		root = NULL;
	}

	BTreeNode<T>* InsertNode(T data) {
		BTreeNode<T>* newItem;
		BTreeNode<T>* current;
		BTreeNode<T>* parent;

		current = root;
		parent = NULL;


		while (current != NULL)
		{
			if (data == current->data) return current;

			parent = current;
			if (data < current->data) current = current->left;
			else current = current->right;
		}
		// Создание нового узла
		newItem = new BTreeNode<T>(data, parent);
		// Привязка нового узла к дереву
		if (parent == NULL)
		{
			root = newItem;
		}
		else
		{
			// Здесь: новый элемент не является корнем дерева
			if (newItem->data < parent->data)
			{
				parent->left = newItem;
			}
			else {
				parent->right = newItem;
			}
		}
		return newItem;

	}

	BTreeNode<T>* FindNode(const T& data)
	{
		BTreeNode<T>* current = root;
		for (; ; )
		{
			if (current == NULL) return NULL;
			if (current->data == data) return current;
			if (data < current->data) current = current->left;
			else current = current->right;
		}
	}

	void DeleteNode(const T& data) {
		BTreeNode<T>* toDelete = FindNode(data);
		DeleteNode(toDelete);
	}

	void DeleteNode(BTreeNode<T>* toDelete) {
		BTreeNode<T>* x, * y; // Указатели на узлы в ходе
		// спусков влево-вправо
		if (toDelete == NULL) return;
		if (toDelete->left == NULL || toDelete->right == NULL)
		{
			// Хотя бы одно из поддеревьев отсутствует
			y = toDelete;
		}
		else
		{
			// Есть оба поддерева
			y = toDelete->right;
			while (y->left != NULL) {
				y = y->left;
			}
		}

		// Обрабатываем случай, когда у узла "y" только один потомок
		if (y->left != NULL) {
			x = y->left;
		}
		else {
			x = y->right;
		}
		// Исключаем узел "y" из "родительской" цепочки
		if (x != NULL) {
			x->parent = y->parent;
		}
		if (y->parent != NULL)
		{
			if (y == y->parent->left) {
				y->parent->left = x;
			}
			else {
				y->parent->right = x;
			}
		}
		else {
			root = x;
		}
		if (y != toDelete)
		{
			toDelete->data = y->data;
		}
		delete y;
	}

	//Вывод дерева
	void printTree(BTreeNode<T>* node, int level) {

		if (node != NULL) {

			printTree(node->right, level + 2);
			for (int i = 0; i < level; i++)
				printf(" ");
			printf("%4ld", node->data);
			printTree(node->left, level + 2);
		}
		else printf("\n");
	}

	/*while (node != NULL)
	{
		node = node->right;
		level += 2;
	}

	for (int i = 0; i < level; i++)
		printf(" ");
	printf("%4ld", node->data);

	while (node != NULL)
	{
		node = node->left;
		level += 2;
	}*/
};







//Node<T>* Add(Node<T>* _node, T _key) {
//	Node<T>* l;
//	Node<T>* r;
//	if (_node == nullptr)
//	{
//		Node<T>* current = new Node<T>(_key);
//		current->key = _key;
//		current->left = NULL;
//		current->right = NULL;
//		return (Node<T> *)current;
//	}
//	else
//	{
//		if (_key < _node->key) {
//			
//			//l = (Node<T> *)_node->left;
//			_node->left = Add(_node->left, _key);
//		}
//		else {
//			
//			r = (Node<T> *)_node->right;
//			r = (Node<T> *)Add(r, _key);
//		}
//	}
//	return _node;
//}




//void Print(T current, int indent) {
//
//
//	int i;
//	if (current != NULL) {
//		Print(current->right, indent + 2);
//		for (i = 0; i < indent; i++)
//			printf(" ");
//		printf("%4ld", current->key);
//		Print(current->left, indent + 2);
//	}
//	else printf("\n");
//
//}


int main(int args, const char* argv[]) {
	setlocale(LC_ALL, "Russian");
	BTree<int> tree;
	//BTree<int> Root = NULL;
	int mas[10] = { 8,1,9,4,7,3,2,4,9,10 };
	/*tree.InsertNode(8);
	tree.InsertNode(1);
	tree.InsertNode(9);*/
	for (int i = 0; i < 10; i++)
	{
		tree.InsertNode(mas[i]);


	}
	tree.printTree(tree.root, 0);
}