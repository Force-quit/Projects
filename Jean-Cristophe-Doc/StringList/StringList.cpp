#include "StringList.h"

#include <iostream>
#include <stdexcept>

StringList::StringList()
	: _head{}
	, _tail{}
	, _size{}
{
}

StringList::~StringList()
{
	clear();
}

bool StringList::empty() const
{
	return !size();
}

size_t StringList::size() const
{
	return _size;
}

void StringList::prepend(value_type const & value)
{
	Node* newNode{ new Node(value, _head) };
	_head = newNode;
	if (empty()) {
		_tail = _head;
	}
	++_size;
}

void StringList::append(value_type const& value)
{
	Node* newNode{ new Node(value, nullptr) };
	if (empty()) {
		_head = _tail = newNode;
	} else {
		_tail->next = newNode;
		_tail = newNode;
	}
	++_size;
}

void StringList::clear()
{
	while (_head) {
		Node * temp{_head};
		_head = _head->next;
		delete temp;
	}
	_tail = nullptr;
	_size = 0;
}

void StringList::removeFirst()
{
	// 
}

void StringList::removeLast()
{
	//
}

StringList::value_type StringList::front() const
{
	if (empty()) {
		throw std::logic_error("blablabla");
	}
	return _head->value;
}

StringList::value_type& StringList::front()
{
	if (empty()) {
		throw std::logic_error("blablabla");
	}
	return _head->value;
}

void StringList::traverse(std::function<void(value_type&)> task)
{
	Node* cur{ _head };
	while (cur) {
		task(cur->value);
		cur = cur->next;
	}
}

StringList::Node::Node(value_type v, Node* n)
	: value(v), next{ n }
{
}
