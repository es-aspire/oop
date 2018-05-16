#pragma once
#include "stdafx.h"
#include <cassert>
#include <iterator>
#include <memory>
#include <utility>

template <class T>
class CList
{
public:
	using value_type = T;
	struct Node
	{
		Node(const value_type& data, Node* prev, std::unique_ptr<Node>&& next)
			: data(data)
			, prev(prev)
			, next(std::move(next))
		{
		}
		value_type data;
		Node* prev;
		std::unique_ptr<Node> next;
	};

	size_t size() const;
	bool empty() const;

	void push_front(value_type const& data);
	void push_back(value_type const& data);
	value_type& front();
	value_type const& front() const;
	value_type& back();
	value_type const& back() const;

	template <typename Type>
	class CIterator
	{
		friend CList;
		CIterator(Node* node, bool isReverse = false)
			: m_node(node)
			, m_isReverse(isReverse)
		{
		}

	public:
		using value_type = Type;
		using reference = Type&;
		using pointer = Type*;
		using iterator_category = std::bidirectional_iterator_tag;
		using self_type = CIterator;
		using difference_type = std::ptrdiff_t;

		CIterator(CIterator<Type> const& it)
			: m_node(it.m_node)
		{
		}

		reference operator*() const
		{
			return m_node->data;
		}

		self_type operator++()
		{
			m_node = (!m_isReverse) ? m_node->next.get() : m_node->prev;
			return *this;
		}

		self_type operator++(int)
		{
			self_type tmp = *this;
			(!m_isReverse) ? ++*this : --*this;
			return tmp;
		}

		self_type operator--()
		{
			m_node = (!m_isReverse) ? m_node->prev : m_node->next.get();
			return *this;
		}

		self_type operator--(int)
		{
			self_type tmp = *this;
			(!m_isReverse) ? --*this : ++*this;
			return tmp;
		}

		template <typename OtherType>
		bool operator==(CIterator<OtherType> const& other) const
		{
			return m_node == other.m_node;
		}

		template <typename OtherType>
		bool operator!=(CIterator<OtherType> const& other) const
		{
			return !(m_node == other.m_node);
		}

	private:
		pointer operator->() const
		{
			return *m_node;
		}

	private:
		Node* m_node = nullptr;
		bool m_isReverse;
	};

	using Iterator = CIterator<value_type>;
	using ConstIterator = CIterator<const value_type>;

	Iterator begin() const;
	Iterator end() const;
	ConstIterator cbegin() const;
	ConstIterator cend() const;
	Iterator rbegin();
	Iterator rend();
	ConstIterator crbegin();
	ConstIterator crend();

	Iterator insert(Iterator const& wherePosition, value_type const& data);
	Iterator erase(Iterator const& wherePosition);
	void clear();

private:
	size_t m_size;
	std::unique_ptr<Node> m_firstNode;
	Node* m_lastNode = nullptr;
};

template <typename value_type>
size_t CList<value_type>::size() const
{
	return m_size;
}

template <typename value_type>
bool CList<value_type>::empty() const
{
	return m_size == 0;
}

template <typename value_type>
void CList<value_type>::push_back(value_type const& data)
{
	auto newNode = std::make_unique<Node>(data, m_lastNode, nullptr);
	Node* newLastNode = newNode.get();
	((m_lastNode) ? m_lastNode->next : m_firstNode) = std::move(newNode);

	m_lastNode = newLastNode;
	++m_size;
}

template <typename value_type>
void CList<value_type>::push_front(value_type const& data)
{
	auto newNode = std::make_unique<Node>(data, nullptr, std::move(m_firstNode));

	((newNode->next) ? newNode->next->prev : m_lastNode) = newNode.get();
	m_firstNode = std::move(newNode);
	m_firstNode->prev = nullptr;
	++m_size;
}

template <typename value_type>
typename CList<value_type>::Iterator CList<value_type>::insert(const typename CList<value_type>::Iterator& wherePosition, value_type const& data)
{
	if (wherePosition == end())
	{
		push_back(data);
		return Iterator(end());
	}
	else if (wherePosition == begin())
	{
		push_front(data);
		return Iterator(begin());
	}

	auto newNode = std::make_unique<Node>(data, wherePosition.m_node->prev, std::move(wherePosition.m_node->prev->next));
	wherePosition.m_node->prev = newNode.get();
	newNode->prev->next = std::move(newNode);
	++m_size;
	return Iterator(wherePosition.m_node->prev);
}

template <typename value_type>
value_type& CList<value_type>::front()
{
	assert(m_firstNode);
	return m_firstNode->data;
}

template <typename value_type>
value_type const& CList<value_type>::front() const
{
	assert(m_firstNode);
	return m_firstNode->data;
}

template <typename value_type>
value_type& CList<value_type>::back()
{
	assert(m_lastNode);
	return m_lastNode->data;
}

template <typename value_type>
value_type const& CList<value_type>::back() const
{
	assert(m_lastNode);
	return m_lastNode->data;
}

template <typename value_type>
void CList<value_type>::clear()
{
	while (m_lastNode)
	{
		m_lastNode->next = nullptr;
		m_lastNode = m_lastNode->prev;
	}

	m_firstNode = nullptr;
	m_lastNode = nullptr;
	m_size = 0;
}

template <typename value_type>
typename CList<value_type>::Iterator CList<value_type>::begin() const
{
	return Iterator(m_firstNode.get());
}

template <typename value_type>
typename CList<value_type>::Iterator CList<value_type>::end() const
{
	return Iterator(m_lastNode->next.get());
}

template <typename value_type>
typename CList<value_type>::ConstIterator CList<value_type>::cbegin() const
{
	return ConstIterator(m_firstNode.get());
}

template <typename value_type>
typename CList<value_type>::ConstIterator CList<value_type>::cend() const
{
	return ConstIterator(m_lastNode->next.get());
}

template <typename value_type>
typename CList<value_type>::Iterator CList<value_type>::rbegin()
{
	return (Iterator(m_lastNode, true));
}

template <typename value_type>
typename CList<value_type>::Iterator CList<value_type>::rend()
{
	return (Iterator(m_firstNode->prev, true));
}

template <typename value_type>
typename CList<value_type>::ConstIterator CList<value_type>::crbegin()
{
	return (ConstIterator(m_lastNode, true));
}

template <typename value_type>
typename CList<value_type>::ConstIterator CList<value_type>::crend()
{
	return (ConstIterator(m_firstNode->prev, true));
}