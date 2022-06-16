#pragma once


#include <string>
#include <functional>
#include <type_traits>





// double ended single linked list
template <typename t>
class List
{
	static_assert(std::is_default_constructible_v<t>, "Template argument error, t must be integral.");

public:
	using value_type = t;



	List();
	List(List<t> const& l) = delete;
	List(List<t> && l) = delete;
	List<t>& operator=(List<t> const& l) = delete;
	List<t>& operator=(List<t> && l) = delete;
	~List();

	bool empty() const;
	size_t size() const;

	void prepend(value_type const & value);
	void append(value_type const & value);
	//void insert(value_type const & value, int pos);
	//void insert(value_type const & value, Iterator it);

	void clear();
	void removeFirst();
	void removeLast();
	//void remove(value_type const& value, int pos);
	//void remove(value_type const& value, Iterator it);

	value_type front() const;
	value_type& front();
	value_type back() const;
	value_type& back();

	//void traverse(void(*task)(std::string &));
	void traverse(std::function<void(value_type&)> task);



private:
	struct Node {
		Node(value_type v = "", Node* n = nullptr);
		value_type value;
		Node * next;
	};
	Node* _head;
	Node* _tail;
	size_t _size;

public:
	class Iterator {
		Node * _cur;

	public:
		Iterator(Node* cur = nullptr) : _cur{cur} {}
		~Iterator() = default;

		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = value_type;
		using pointer = value_type*;
		using reference = value_type&;

		Iterator& operator++() { 
			_cur = _cur->next; 
			return *this; 
		}
		Iterator operator++(int) {
			Iterator i(_cur);
			this->operator++();
			return i;
		}
		pointer operator*() { return &_cur->value; }
		pointer operator->() { return &_cur->value; }

		bool operator!=(Iterator const & other) const {
			return _cur != other._cur;
		}
		bool operator==(Iterator const & other) const {
			return !operator!=(other);
			return !(*this != other);
		}
	};

	Iterator begin() { return Iterator(_head); }
	Iterator end() { return Iterator(); }
};












#include <iostream>
#include <stdexcept>
#include <cassert>

template <typename t>
List<t>::List()
	: _head{}
	, _tail{}
	, _size{}
{
}

template <typename t>
List<t>::~List()
{
	clear();
}

template <typename t>
bool List<t>::empty() const
{
	return !size();
}

template <typename t>
size_t List<t>::size() const
{
	return _size;
}

template <typename t>
void List<t>::prepend(value_type const& value)
{
	Node* newNode{ new Node(value, _head) };
	_head = newNode;
	if (empty()) {
		_tail = _head;
	}
	++_size;
}

template <typename t>
void List<t>::append(value_type const& value)
{
	Node* newNode{ new Node(value, nullptr) };
	if (empty()) {
		_head = _tail = newNode;
	}
	else {
		_tail->next = newNode;
		_tail = newNode;
	}
	++_size;
}


template <typename t>
void List<t>::clear()
{
	while (_head) {
		Node* temp{ _head };
		_head = _head->next;
		delete temp;
	}
	_tail = nullptr;
	_size = 0;
}


template <typename t>
void List<t>::removeFirst()
{
	// 
}

template <typename t>
void List<t>::removeLast()
{
	//
}


template <typename t>
typename List<t>::value_type List<t>::front() const
{
	if (empty()) {
		throw std::logic_error("blablabla");
	}
	return _head->value;
}

template <typename t>
typename List<t>::value_type& List<t>::front()
{
	if (empty()) {
		throw std::logic_error("blablabla");
	}
	return _head->value;
}

template <typename t>
typename List<t>::value_type List<t>::List::back() const
{
	return const_cast<List<t> * > (this)->back();
	//assert(!empty());
	//return _tail->value;
}

template <typename t>
typename List<t>::value_type& List<t>::List::back()
{
	assert(!empty());
	return _tail->value;
}

template <typename t>
void List<t>::traverse(std::function<void(value_type&)> task)
{
	Node* cur{ _head };
	while (cur) {
		task(cur->value);
		cur = cur->next;
	}
}

template <typename t>
List<t>::Node::Node(value_type v, Node* n)
	: value(v), next{ n }
{
}






