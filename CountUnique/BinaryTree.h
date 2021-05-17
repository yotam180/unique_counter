#pragma once

#include <memory>

template <class T>
class BinaryTreeNode
{
public:
	template <class ... Args>
	explicit BinaryTreeNode(Args&& ... args)
		: inner_value(std::forward<Args>(args)...), left(nullptr), right(nullptr) {}

public:
	T& value() { return inner_value; }
	const T& value() const { return inner_value; }

	template <class J>
	BinaryTreeNode* search(J&& value)
	{
		if (value == inner_value) return this;
		if (value < inner_value)
		{
			if (left == nullptr)
			{
				return nullptr;
			}
			return left->search(std::forward<J>(value));
		}
		else
		{
			if (right == nullptr)
			{
				return nullptr;
			}
			return right->search(std::forward<J>(value));
		}
	}

	template <class J>
	void insert(J&& value)
	{
		if (value <= inner_value)
		{
			if (left != nullptr)
			{
				left->insert(std::forward<J>(value));
			}
			else
			{
				left = std::unique_ptr<BinaryTreeNode>(new BinaryTreeNode(std::forward<J>(value)));
			}
		}
		else
		{
			if (right != nullptr)
			{
				right->insert(std::forward<J>(value));
			}
			else
			{
				right = std::unique_ptr<BinaryTreeNode>(new BinaryTreeNode(std::forward<J>(value)));
			}
		}
	}

private:
	T inner_value;
	std::unique_ptr<BinaryTreeNode> left, right;
};

template <class T>
class BinaryTree final
{
public:
	explicit BinaryTree() : root(nullptr) {}

public:

	template <class J>
	void insert(J&& value)
	{
		if (root == nullptr)
		{
			root = std::unique_ptr<BinaryTreeNode<T>>(new BinaryTreeNode<T>(std::forward<J>(value)));
		}
		else
		{
			root->insert(std::forward<J>(value));
		}
	}

	template <class J>
	bool contains(J&& value)
	{
		return root != nullptr && root->search(std::forward<J>(value)) != nullptr;
	}

private:
	std::unique_ptr<BinaryTreeNode<T>> root;
};