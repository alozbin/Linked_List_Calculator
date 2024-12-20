#ifndef CALCLIST_HPP
#define CALCLIST_HPP

#include "CalcListInterface.hpp"
#include <string>
#include <sstream>
#include <iomanip>

// doubly linked list based arithmetic calculator
class CalcList : public CalcListInterface
{
private:
	struct Node
	{
		double totalBefore;
		double totalAfter;
		FUNCTIONS operation;
		double operand;
		Node* next;
		Node* prev;

		// constructor for new node
		Node(double before, double after, FUNCTIONS opn, double opd) : totalBefore(before), totalAfter(after), operation(opn), operand(opd), next(nullptr), prev(nullptr) {}
	};

	Node* head;
	Node* tail;
	double currTotal;
	int operationCount;

public:
	CalcList();		// constructor for new list
	~CalcList();		// destructor
	double total() const;		// view current total of list
	void newOperation(const FUNCTIONS func, const double operand);		// add new operation to list and create new total
	void removeLastOperation();		// remove last operation and restore previous total
	std::string toString(unsigned short precision) const;		// view formatted string of previous operations
};

#endif /* CALCLIST_HPP */