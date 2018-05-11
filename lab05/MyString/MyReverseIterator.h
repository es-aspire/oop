#pragma once

class CMyString;

template <typename ValueType>
class CMyReverseIterator : public std::iterator<std::random_access_iterator_tag, ValueType>, 
	public std::iterator<std::output_iterator_tag, ValueType>
{
	friend CMyString;

public:
	typedef ValueType value_type;
	typedef value_type& reference;
	typedef value_type* pointer;
	typedef std::random_access_iterator_tag iterator_category;
	typedef ptrdiff_t difference_type;
	typedef CMyReverseIterator<ValueType> self_type;

	CMyReverseIterator(pointer pointer)
		: m_pointer(pointer)
	{
	}

	reference operator*()
	{
		return *m_pointer;
	}

	pointer operator->()
	{
		return m_pointer;
	}

	self_type operator++()
	{
		self_type prev = *this;

		m_pointer--;

		return prev;
	}

	self_type operator++(int)
	{
		m_pointer--;

		return *this;
	}

	self_type operator--()
	{
		self_type prev = *this;

		m_pointer++;

		return prev;
	}

	self_type operator--(int)
	{
		m_pointer++;

		return *this;
	}

	self_type& operator+=(difference_type offset)
	{
		m_pointer = m_pointer + offset;

		return *this;
	}

	self_type& operator-=(difference_type offset)
	{
		m_pointer = m_pointer - offset;

		return *this;
	}

	self_type& operator+(difference_type offset) const
	{
		self_type tmp = *this;

		return (tmp += offset);
	}

	self_type& operator-(difference_type offset) const
	{
		self_type tmp = *this;

		return (tmp -= offset);
	}

	difference_type operator-(self_type const& rhs) const
	{
		return m_pointer - rhs.m_pointer;
	}

	bool operator==(self_type const& rhs)
	{
		return m_pointer == rhs.m_pointer;
	}

	bool operator!=(self_type const& rhs)
	{
		return m_pointer != rhs.m_pointer;
	}

	bool operator<(self_type const& rhs)
	{
		return m_pointer < rhs.m_pointer;
	}

	bool operator>=(self_type const& rhs)
	{
		return !(*this < rhs);
	}

	bool operator>(self_type const& rhs)
	{
		return rhs.m_pointer < m_pointer;
	}

	bool operator<=(self_type const& rhs)
	{
		return !(*this > rhs);
	}

	value_type operator[](size_t index)const
	{
		return m_pointer[index];
	}

private:
	pointer m_pointer;
};

template<typename ValueType>
inline CMyReverseIterator<ValueType>& operator+(std::ptrdiff_t& offset, const CMyReverseIterator<ValueType>& rhs)
{
	CMyIterator<ValueType> tmp = rhs;

	return tmp + offset;
}