#pragma once

#include "CMyArrayIterator.h"
#include <algorithm>
#include <exception>
#include <memory>
#include <new>

template <typename T>
class CMyArray
{
public:
	CMyArray();
	CMyArray(size_t size);
	CMyArray(const CMyArray& arr);
	CMyArray(CMyArray&& other);
	CMyArray& operator=(CMyArray&& other);
	CMyArray& operator=(CMyArray const& other);
	T* Data();
	const T* Data() const;
	void Resize(size_t size = 0);
	void Clear();
	void ResizeCapacity(size_t capacity);
	void Append(const T& value);
	const T& operator[](size_t index) const;
	T& operator[](size_t index);
	T& Front();
	const T& Front() const;
	const T& GetBack() const;
	T& Back();
	size_t GetSize() const;
	bool IsEmpty() const;
	size_t GetCapacity() const;

	using MyIterator = CMyArrayIterator<T>;
	using MyConstIterator = CMyArrayIterator<const T>;

	MyIterator Begin();
	MyIterator End();
	MyConstIterator CBegin() const;
	MyConstIterator CEnd() const;

	using MyReverseIterator = std::reverse_iterator<MyIterator>;
	using MyConstReverseIterator = std::reverse_iterator<MyConstIterator>;

	MyReverseIterator RBegin();
	MyReverseIterator REnd();
	MyConstReverseIterator CRBegin() const;
	MyConstReverseIterator CREnd() const;
	~CMyArray();

private:
	/*void SwitchToNewStorageBlock(T* newBegin, T* newEnd, T* newEndOfCapacity)
	{
		m_begin = newBegin;
		m_end = newEnd;
		m_endOfCapacity = newEndOfCapacity;
	}

	// Конструируем копию value по адресу newItemLocation
	static void NewItem(T* pos, T const& value)
	{
		new (pos) T(value);
	}

	void TryThrowOutOfRange(size_t index)
	{
		if (index >= GetSize())
		{
			throw std::out_of_range("out of range in in array");
		}
	}

	static void DeleteItems(T* begin, T* end)
	{
		// Разрушаем старые элементы
		DestroyItems(begin, end);
		// Освобождаем область памяти для их хранения
		RawDealloc(begin);
	}

	// Копирует элементы из текущего вектора в to, возвращает newEnd
	static void CopyItems(const T* srcBegin, T* srcEnd, T* const dstBegin, T*& dstEnd)
	{
		for (dstEnd = dstBegin; srcBegin != srcEnd; ++srcBegin, ++dstEnd)
		{
			// Construct "T" at "dstEnd" as a copy of "*begin"
			new (dstEnd) T(*srcBegin);
		}
	}

	static void DestroyItems(T* from, T* to)
	{
		// dst - адрес объект, при конструирование которого было выброшено исключение
		// to - первый скорнструированный объект
		while (to != from)
		{
			--to;
			// явно вызываем деструктор для шаблонного типа T
			to->~T();
		}
	}

	static T* RawAlloc(size_t n)
	{
		size_t memSize = n * sizeof(T);
		T* p = static_cast<T*>(malloc(memSize));
		if (!p)
		{
			throw std::bad_alloc();
		}
		return p;
	}

	static void RawDealloc(T* p)
	{
		free(p);
	}
	*/

	void SwitchToNewStorageBlock(T* newBegin, T* newEnd, T* newEndOfCapacity);

	// Конструируем копию value по адресу newItemLocation
	static void NewItem(T* pos, T const& value);
	void TryThrowOutOfRange(size_t index);
	static void DeleteItems(T* begin, T* end);

	// Копирует элементы из текущего вектора в to, возвращает newEnd
	static void CopyItems(const T* srcBegin, T* srcEnd, T* const dstBegin, T*& dstEnd);
	static void DestroyItems(T* from, T* to);
	static T* RawAlloc(size_t n);
	static void RawDealloc(T* p);

private:
	T* m_begin = nullptr;
	T* m_end = nullptr;
	T* m_endOfCapacity = nullptr;
};

template <typename T>
CMyArray<T>::CMyArray()
	: CMyArray(0)
{
}

template <typename T>
CMyArray<T>::CMyArray(size_t size)
{
	Resize(size);
}

template <typename T>
CMyArray<T>::CMyArray(const CMyArray<T>& arr)
{
	const auto size = arr.GetSize();
	if (size != 0)
	{
		m_begin = RawAlloc(size);
		try
		{
			CopyItems(arr.m_begin, arr.m_end, m_begin, m_end);
			m_endOfCapacity = m_end;
		}
		catch (...)
		{
			DeleteItems(m_begin, m_end);
			throw;
		}
	}
}

template <typename T>
CMyArray<T>::CMyArray(CMyArray<T>&& other)
	: m_begin(other.m_begin)
	, m_end(other.m_end)
	, m_endOfCapacity(other.m_endOfCapacity)
{
	other.Clear();
}

template <typename T>
CMyArray<T>& CMyArray<T>::operator=(CMyArray<T>&& other)
{
	if (this != std::addressof(other))
	{
		std::swap(m_begin, tmp.m_begin);
		std::swap(m_end, tmp.m_end);
		std::swap(m_endOfCapacity, tmp.m_endOfCapacity);
		other.Clear();
	}

	return *this;
}

template <typename T>
CMyArray<T>& CMyArray<T>::operator=(CMyArray<T> const& other)
{
	if (std::addressof(*this) != std::addressof(other))
	{
		CMyArray tmp(other);
		if (GetCapacity() < other.GetSize())
		{
			m_endOfCapacity = m_begin + other.GetSize();
		}
		std::swap(m_begin, tmp.m_begin);
		std::swap(m_end, tmp.m_end);
	}

	return *this;
}

template <typename T>
T* CMyArray<T>::Data()
{
	return m_begin;
}

template <typename T>
const T* CMyArray<T>::Data() const
{
	return m_begin;
}

template <typename T>
void CMyArray<T>::Resize(size_t size)
{
	if (size > GetCapacity())
	{
		ResizeCapacity(size);
	}
	if (size >= GetSize())
	{
		auto prevEnd = m_end;
		m_end = m_begin + size;

		for (auto current = prevEnd; current != m_end; ++current)
		{
			NewItem(current, T());
		}
	}
	else
	{
		auto tmpEnd = m_end;
		m_end = m_begin + size;
		DestroyItems(m_end, tmpEnd);
	}
}

template <typename T>
void CMyArray<T>::Clear()
{
	DestroyItems(m_begin, m_end);
	m_end = m_begin;
}

template <typename T>
void CMyArray<T>::ResizeCapacity(size_t capacity)
{
	auto newBegin = RawAlloc(capacity);
	T* newEnd = newBegin;
	try
	{
		CopyItems(m_begin, m_end, newBegin, newEnd);
	}
	catch (...)
	{
		DeleteItems(newBegin, newEnd);
		throw;
	}

	SwitchToNewStorageBlock(newBegin, newEnd, newEnd + capacity);
}

template <typename T>
void CMyArray<T>::Append(const T& value)
{
	if (m_end == m_endOfCapacity)
	{
		size_t newCapacity = std::max(size_t(1), GetCapacity() * 2);

		auto newBegin = RawAlloc(newCapacity);
		T* newEnd = newBegin;
		try
		{
			CopyItems(m_begin, m_end, newBegin, newEnd);
			NewItem(newEnd, value);
			++newEnd;
		}
		catch (...)
		{
			DeleteItems(newBegin, newEnd);
			throw;
		}
		DeleteItems(m_begin, m_end);

		// Переключаемся на использование нового хранилища элементов
		m_begin = newBegin;
		m_end = newEnd;
		m_endOfCapacity = m_begin + newCapacity;
	}
	else // has free space
	{
		new (m_end) T(value);
		++m_end;
	}
}

template <typename T>
const T& CMyArray<T>::operator[](size_t index) const
{
	if (IsEmpty())
	{
		throw std::out_of_range("CMyArray is empty");
	}
	if (index >= GetSize())
	{
		throw std::out_of_range("out of range inCMyArray");
	}

	return *(m_begin + index);
}

template <typename T>
T& CMyArray<T>::operator[](size_t index)
{
	if (IsEmpty())
	{
		throw std::out_of_range("CMyArray is empty");
	}
	if (index >= GetSize())
	{
		throw std::out_of_range("out of range in CMyArray");
	}

	return *(m_begin + index);
}

template <typename T>
T& CMyArray<T>::Front()
{
	if (IsEmpty())
	{
		throw std::out_of_range("CMyArray is empty");
	}

	return m_begin;
}

template <typename T>
const T& CMyArray<T>::Front() const
{
	if (IsEmpty())
	{
		throw std::out_of_range("CMyArray is empty");
	}

	return m_begin;
}

template <typename T>
const T& CMyArray<T>::GetBack() const
{
	if (GetSize() == 0u)
	{
		throw std::out_of_range("CMyArray is empty");
	}

	return m_end[-1];
}

template <typename T>
T& CMyArray<T>::Back()
{
	if (GetSize() == 0u)
	{
		throw std::out_of_range("CMyArray is empty");
	}

	return m_end;
}

template <typename T>
size_t CMyArray<T>::GetSize() const
{
	return m_end - m_begin;
}

template <typename T>
bool CMyArray<T>::IsEmpty() const
{
	return GetSize() == 0;
}

template <typename T>
size_t CMyArray<T>::GetCapacity() const
{
	return m_endOfCapacity - m_begin;
}

template <typename T>
typename CMyArray<T>::MyIterator CMyArray<T>::Begin()
{
	return MyIterator(m_begin);
}

template <typename T>
typename CMyArray<T>::MyIterator CMyArray<T>::End()
{
	return MyIterator(m_end);
}

template <typename T>
typename CMyArray<T>::MyConstIterator CMyArray<T>::CBegin() const
{
	return MyConstIterator(m_begin);
}

template <typename T>
typename CMyArray<T>::MyConstIterator CMyArray<T>::CEnd() const
{
	return MyConstIterator(m_end);
}

template <typename T>
typename CMyArray<T>::MyReverseIterator CMyArray<T>::RBegin()
{
	return MyReverseIterator(m_end - 1);
}

template <typename T>
typename CMyArray<T>::MyReverseIterator CMyArray<T>::REnd()
{
	return MyReverseIterator(m_begin - 1);
}

template <typename T>
typename CMyArray<T>::MyConstReverseIterator CMyArray<T>::CRBegin() const
{
	return MyConstReverseIterator(m_end - 1);
}

template <typename T>
typename CMyArray<T>::MyConstReverseIterator CMyArray<T>::CREnd() const
{
	return MyConstReverseIterator(m_begin - 1);
}

template <typename T>
CMyArray<T>::~CMyArray()
{
	DeleteItems(m_begin, m_end);
}

template <typename T>
void CMyArray<T>::SwitchToNewStorageBlock(T* newBegin, T* newEnd, T* newEndOfCapacity)
{
	m_begin = newBegin;
	m_end = newEnd;
	m_endOfCapacity = newEndOfCapacity;
}

// Конструируем копию value по адресу newItemLocation
template <typename T>
void CMyArray<T>::NewItem(T* pos, T const& value)
{
	new (pos) T(value);
}

template <typename T>
void CMyArray<T>::TryThrowOutOfRange(size_t index)
{
	if (index >= GetSize())
	{
		throw std::out_of_range("out of range in in array");
	}
}

template <typename T>
void CMyArray<T>::DeleteItems(T* begin, T* end)
{
	// Разрушаем старые элементы
	DestroyItems(begin, end);
	// Освобождаем область памяти для их хранения
	RawDealloc(begin);
}

// Копирует элементы из текущего вектора в to, возвращает newEnd
template <typename T>
void CMyArray<T>::CopyItems(const T* srcBegin, T* srcEnd, T* const dstBegin, T*& dstEnd)
{
	for (dstEnd = dstBegin; srcBegin != srcEnd; ++srcBegin, ++dstEnd)
	{
		// Construct "T" at "dstEnd" as a copy of "*begin"
		new (dstEnd) T(*srcBegin);
	}
}

template <typename T>
void CMyArray<T>::DestroyItems(T* from, T* to)
{
	// dst - адрес объект, при конструирование которого было выброшено исключение
	// to - первый скорнструированный объект
	while (to != from)
	{
		--to;
		// явно вызываем деструктор для шаблонного типа T
		to->~T();
	}
}

template <typename T>
T* CMyArray<T>::RawAlloc(size_t n)
{
	size_t memSize = n * sizeof(T);
	T* p = static_cast<T*>(malloc(memSize));
	if (!p)
	{
		throw std::bad_alloc();
	}
	return p;
}

template <typename T>
void CMyArray<T>::RawDealloc(T* p)
{
	free(p);
}
