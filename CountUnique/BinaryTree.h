#pragma once

#include <memory>

template <class T>
class BinaryTreeNode
{
public:
	explicit BinaryTreeNode(T&& value)
		: inner_value(value), left(nullptr), right(nullptr) {}

public:
	T& value() { return inner_value; }
	const T& value() const { return inner_value; }

	bool has_left_child() const { return left != nullptr; }
	bool has_right_child() const { return right != nullptr; }

	BinaryTreeNode& left_child() const { return left; }
	BinaryTreeNode& right_child() const { return right; }

	void add_left(std::unique_ptr<BinaryTreeNode>& child) { left = std::forward(child); }
	void add_right(std::unique_ptr<BinaryTreeNode>& child) { right = std::forward(child); }

	BinaryTreeNode* search(T&& value)
	{
		if (value == inner_value) return this;
		if (value < inner_value)
		{
			if (left == nullptr)
			{
				return nullptr;
			}
			return left->search(std::forward<T&&>(value));
		}
		else
		{
			if (right == nullptr)
			{
				return nullptr;
			}
			return right->search(std::forward<T&&>(value));
		}
	}

	void insert(T&& value)
	{
		if (value <= inner_value)
		{
			if (left != nullptr)
			{
				left->insert(std::forward<T&&>(value));
			}
			else
			{
				left = std::unique_ptr<BinaryTreeNode>(new BinaryTreeNode(std::forward<T&&>(value)));
			}
		}
		else
		{
			if (right != nullptr)
			{
				right->insert(std::forward<T&&>(value));
			}
			else
			{
				right = std::unique_ptr<BinaryTreeNode>(new BinaryTreeNode(std::forward<T&&>(value)));
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
	void insert(T&& value)
	{
		if (root == nullptr)
		{
			root = std::unique_ptr<BinaryTreeNode<T>>(new BinaryTreeNode<T>(std::forward<T&&>(value)));
		}
		else
		{
			root->insert(std::forward<T&&>(value));
		}
	}

	bool search(T&& value)
	{
		return root != nullptr && root->search(std::forward<T&&>(value)) != nullptr;
	}

private:
	std::unique_ptr<BinaryTreeNode<T>> root;
};