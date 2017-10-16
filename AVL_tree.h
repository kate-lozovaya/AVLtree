#include<iostream>
//#include <stdexcept>

template<typename T>
struct Node
{
	Node<T> * left;
	Node<T> * right;
	T key;
	unsigned char height;
	Node(T const& value)
	{
		left = nullptr;
		right = nullptr;
		key = value;
		height = 1;
	}
};

template<typename T>
class AVL_tree
{
private:
	Node<T> * root;
public:
	AVL_tree();
	~AVL_tree();
	void deleteNode(Node<T> * node);

	unsigned char height_(Node<T> * node);
	char bfactor(Node<T> * node);
	void fixheight(Node<T> * node);

	Node<T> * rotate_left(Node<T> * node);
	Node<T> * rotate_right(Node<T> * node);

	Node<T> * balance(Node<T> * node);

	void insert(const T& value);
	void insert(Node<T>* & node, const T& value);

	Node<T> * find_min(Node<T> * node);
	Node<T> * remove_min(Node<T> * node);

	void remove(const T& value);
	Node<T> * remove(Node<T>* & node, const T& value);
	
	Node<T> * search(const T& value)const;

	void print(std::ostream & stream);
	void print(Node<T> * node, std::ostream & stream, size_t level)const;
	/*friend std::ostream & operator << (std::ostream & stream, AVL_tree<T> & tree)
	{
		return tree.print(cout);
	}*/
};

template<typename T>
AVL_tree<T>::AVL_tree()
{
	root = nullptr;
}
template<typename T>
AVL_tree<T>::~AVL_tree()
{
	deleteNode(root);
}
template<typename T>
void AVL_tree<T>::deleteNode(Node<T> * node)
{
	if (node == nullptr) return;
	deleteNode(node->left);
	deleteNode(node->right);
	delete node;
}
template<typename T>
unsigned char AVL_tree<T>::height_(Node<T> * node)
{
	return node->height;
}
template<typename T>
char AVL_tree<T>::bfactor(Node<T> * node)
{
	return height_(node->right) - height_(node->left);
}
template<typename T>
void AVL_tree<T>::fixheight(Node<T> * node)
{
	unsigned char hl = height_(node->left);
	unsigned char hr = height_(node->right);
	node->height = (hl>hr ? hl : hr) + 1;
}
template<typename T>
Node<T> * AVL_tree<T>::rotate_left(Node<T> * node)
{
	Node<T> * p = node->right;
	node->right = p->left;
	p->left = node;
	fixheight(node);
	fixheight(p);
	return p;
}
template<typename T>
Node<T> * AVL_tree<T>::rotate_right(Node<T> * node)
{
	Node<T> * q = node->left;
	node->left = q->right;
	q->right = node;
	fixheight(node);
	fixheight(q);
	return q;
}
template<typename T>
Node<T> * AVL_tree<T>::balance(Node<T> * node)
{
	if (node->right || node->left)
	{
		fixheight(node);
		if (bfactor(node) == 2)
		{
			if (bfactor(node->right) < 0)
				node->right = rotate_right(node->right);
			return rotate_left(node);
		}
		if (bfactor(node) == -2)
		{
			if (bfactor(node->left) > 0)
				node->left = rotate_left(node->left);
			return rotate_right(node);
		}
	}
	return node;
}
template<typename T>
void AVL_tree<T>::insert(const T& value)
{
	insert(root, value);
}
template<typename T>
void AVL_tree<T>::insert(Node<T> * & node, const T& value)
{
	if (node)
	{
		if (value == node->key)
			throw std::logic_error("There is this element in the tree\n");
		if (value < node->key)
			insert(node->left, value);
		else
			insert(node->right, value);
	}
	else node = new Node<T>(value);
	
	balance(node);
}
template<typename T>
Node<T> * AVL_tree<T>::find_min(Node<T> * node)
{
	return node->left ? find_min(node->left) : p;
}
template<typename T>
Node<T> * AVL_tree<T>::remove_min(Node<T> * node)
{
	if (node->left == 0)
		return node->right;
	node->left = remove_min(node->left);
	return balance(node);
}
template<typename T>
void AVL_tree<T>::remove(const T& value)
{
	remove(root, value);
}
template<typename T>
Node<T> * AVL_tree<T>::remove(Node<T>* & node, const T& value)
{
	if (!node) return 0;
	if (value < node->key)
		node->left = remove(node->left, value);
	else if (value > node->key)
		node->right = remove(node->right, value);
	else
	{
		Node<T> * l = node->left;
		Node<T> * r = node->right;
		delete node;
		if (!r) return l;
		Node<T> * min = find_min(r);
		min->right = remove_min(r);
		min->left = l;
		return balance(min);
	}
	return balance(node);
}
template<typename T>
Node<T> * AVL_tree<T>::search(const T& value)const
{
	Node<T> * curEl = root;
	while (curEl != nullptr)
	{
		if (curEl->key == value)
			break;
		else
		{
			if (value > curEl->value)
				curEl = curEl->right;
			else curEl = curEl->left;
		}
	}
	return curEl;
}
template<typename T>
void AVL_tree<T>::print(std::ostream & stream)
{
	print(root, stream, 0);
}
template<typename T>
void AVL_tree<T>::print(Node<T> * node, std::ostream & stream, size_t level)const
{
	Node<T> * curEl = node;
	if (curEl != nullptr)
	{
		print(curEl->right, stream, level + 1);
		for (unsigned int i = 0; i < level; ++i)
			stream << '-';
		stream << curEl->key << std::endl;
		print(curEl->left, stream, level + 1);
	}
}