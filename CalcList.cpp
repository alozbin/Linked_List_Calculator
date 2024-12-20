#include "CalcList.hpp"
#include <iostream>

// constructor for new list
CalcList::CalcList() : head(nullptr), tail(nullptr), currTotal(0.0), operationCount(0) {}

// destructor
CalcList::~CalcList()
{
	Node* temp;
	while (head != nullptr)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
}

// returns current total of list
double CalcList::total() const
{
	return currTotal;
}

// adds new operation to list and creates new total
void CalcList::newOperation(const FUNCTIONS func, const double operand)
{
	double newTotal = currTotal;

	switch (func)		// determines operation to be performed on total from given func
	{
		case ADDITION:
			newTotal += operand;
			break;
		case SUBTRACTION:
			newTotal -= operand;
			break;
		case MULTIPLICATION:
			newTotal *= operand;
			break;
		case DIVISION:
			if (operand == 0)		// throws if division by zero is attempted
			{
				throw std::logic_error("Error: division by zero.");
			}
			newTotal /= operand;
			break;
		default:
			throw std::logic_error("Error: invalid operation.");
	}

	Node* newNode = new Node(currTotal, newTotal, func, operand);

	if (head == nullptr)		// new node added as only node if list is empty
	{
		head = tail = newNode;
	}
	else		// adds new node to end of list
	{
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
	}

	currTotal = newTotal;
	operationCount++;
}

// removes last operation from list and restores previous total
void CalcList::removeLastOperation()
{
	if (tail == nullptr)		// throws if list is empty
	{
		throw std::logic_error("Error: history already empty.");
	}

	currTotal = tail->totalBefore;
	operationCount--;

	Node* temp = tail;		// temp points to node to be deleted

	if (tail->prev != nullptr)		// tail points to previous operation if more than one node in list
	{
		tail = tail->prev;
		tail->next = nullptr;
	}
	else		// head and tail no longer point to only node in list
	{
		head = tail = nullptr;
	}

	delete temp;		// node pointing to last operation deleted
}

// returns string of completed operations formatted with fixed point precision
std::string CalcList::toString(unsigned short precision) const
{
	int step = operationCount;

	Node* curr = tail;
	if (curr == nullptr)		// throws if list is empty
	{
		throw std::logic_error("Error: list is empty.");
	}

	std::ostringstream string;

	while (curr != nullptr)			// starting from tail loops up list and stores each operation in string
	{
		char function = ' ';
		switch (curr->operation)		// determines char to be used in string from operation in each node
		{
		case ADDITION:
			function = '+';
			break;
		case SUBTRACTION:
			function = '-';
			break;
		case MULTIPLICATION:
			function = '*';
			break;
		case DIVISION:
			function = '/';
			break;
		}

		// each step accumulated as formatted output in string
		string << step << ": " << std::fixed << std::setprecision(precision) << curr->totalBefore << function << curr->operand << "=" << curr->totalAfter << "\n";

		curr = curr->prev;
		step--;
	}

	return string.str();
}