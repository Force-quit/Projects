#pragma once

#include <string>
#include <functional>

// double ended single linked list
class StringList
{
public:
	using value_type = std::string;

	StringList();
	~StringList();

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
};

