#pragma once
#define NULL 0
#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <boost/concept_check.hpp>
#include <string>
#include <vector>


class node {
private:
	node ** _prev;
	node ** _next;
	bool end;

public:
	
	node() {};

	virtual node& GoToNext() {
		return **_next;
	}
	virtual void RaiseExcp() {
		throw std::exception("ERROR!");
	}
	virtual node& Exit(std::vector<node*>& c) {
		std::cout << "Exit.." << std::endl;
		return *c[0];
	}

	virtual void DoSmth() {

	}


	//virtual ~node() = 0;
};

template<typename T>
class var : public node {
private:
	
	
public:
	node * next;
	std::string _name;
	T _data;
	// Empty constructor
	var() : _data(NULL), _name(NULL) {}

	// Constructor
	var(T data, std::string name) : _data(data), _name(name) {}

	// Implicit conversion
	explicit var(T data) : _data(data) {}

	// Copy constructor
	var(var & other) : _data(other._data), _name(other._name) {  }

	// Move constructor
	var(var&& other) : _data(NULL), _name(NULL) {
		_data = other._data;
		_name = other._name;

		other._data = NULL;
		other._name = NULL;
	}

	void RaiseExcp() {
		throw std::exception("Wrong type!");
	}

	// Copy assignment
	var& operator=(var&& other) {
		_data = NULL;
		_name = NULL;

		_data = other._data;
		_name = other._name;

		other._data = NULL;
		other._data = NULL;

		return *this;
	}

	void DoSmth() {
		std::cout << "var " << _name << " := " << _data << ";" << std::endl;
	}

	// Move assignment
	var& operator=(var& other) {
		_data = other._data;
		_name = other._name;
		return *this;
	}

	// Output override
	friend std::ostream& operator<<(std::ostream& os, var<T>& v) {
		return os << v._data;
	}

	// Input override
	friend std::istream& operator>>(std::istream& is, var<T>& v) {
		T data;
		is >> data;
		v._data = data;
		return is;
	}
};

template<typename T>
class CaseStat : public node {
private:
	
	node ** _prev;
	var<T> * firstOp;
	var<T> * secondOp;
	bool res;
	bool inverse;
	char op;
public:
	node * _next0;
	node * _next1;
	// Execute an expression
	void DoSmth() {
		switch (op)
		{
		case '=':
			if (firstOp->_data == secondOp->_data)
				res = 1;
			else res = 0;
			break;
		case '<':
			if ((firstOp->_data) < (secondOp->_data))
				res = 1;
			else
				res = 0;
			break;
		case '>':
			if ((firstOp->_data) > (secondOp->_data))
				res = 1;
			else
				res = 0;
			break;
		default:
			res = 0;
		}
		if (inverse) {
			res = !res;
		}

		std::cout << "if " << firstOp->_name << " " << op << " " << secondOp->_name << " then" << endl;
		(*_next1).DoSmth();
		cout << endl;
		std::cout << "else" << std::endl;
		(*_next0).DoSmth();
		cout << ";" << endl;

	}

	// Constructor
	CaseStat(var<T>* fOp, std::string stmnt, var<T>* sOp): firstOp(fOp), secondOp(sOp), inverse(0) {
		if (stmnt.find("!") != std::string::npos) {// Turn to 1 inverse if denial was used
			inverse = 1;
			op = stmnt[1];
		}
		else op = stmnt[0];
	}


	// Go to next step of algorithm
	node& GoToNext() {
		if (res) 
			return *_next1;
		else
			return *_next0;
	}

	//Ostream override
	friend std::ostream& operator<<(std::ostream& os, CaseStat<T>& cs) {
		return os <<cs.res;
	}
};
template<typename T>
class output : public node {
private:
	std::string msg;
	var<T> * _var;
public:
	output(std::string mesg, var<T> * varbl) :msg(mesg),_var(nullptr) {
		if (varbl)
			_var = varbl;
	}

	void DoSmth() {
		std::cout << "println(" << msg <<")";
	}
};
