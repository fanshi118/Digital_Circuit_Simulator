#include <iostream>
#include <cmath>
#include "gates.h"
using namespace std;

Gate::Gate()
{
	delay = 1; // if not provided
	inputs = new vector<Net *>;
	output = new Net;
}

Gate::Gate(string n)
{
	inst_name = n;
	delay = 1; // if not provided
	inputs = new vector<Net *>;
	output = new Net;
}

Gate::Gate(string n, int d)
{
	inst_name = n;
	delay = d;
	inputs = new vector<Net *>;
	output = new Net;
}

Gate::~Gate()
{
	while(!inputs->empty()){
		delete inputs->back();
		inputs->pop_back();
	}
	delete inputs;
	delete output;
}

string Gate::name() const
{ return inst_name; }

int Gate::getDelay() const
{ return delay; }

void Gate::addInput(Net *n)
{	inputs->push_back(n); }

vector<Net *> *Gate::getInputs()
{	return inputs; }

void Gate::addOutput(Net *n)
{ output = n; }

Net* Gate::getOutput() const
{ return output; }

int Gate::getNumInputs() const
{	return inputs->size(); }

// And Gate

And::And():Gate::Gate()
{ gtype = AND; }

And::And(string n):Gate::Gate(n)
{ gtype = AND; }

And::And(string n, int d):Gate::Gate(n,d)
{	gtype = AND; }

And::~And()
{
	while(!inputs->empty()){
		delete inputs->back();
		inputs->pop_back();
	}
	delete inputs;
	delete output;
}

char And::eval()
{
	bool flag = false;
	for(vector<Net *>::iterator it = inputs->begin();
		it != inputs->end();
		++it)
	{
		if((*it)->getVal() == '0')
			return '0';
		if((*it)->getVal() == 'X')
			flag = true;
	}
	if(flag)
		return 'X';
	return '1';
}

void And::dump(ostream &os)
{
	os << "	and ";
	if(delay != 1)
		os << "#" << delay << " ";
	os << inst_name << "(";
	os << output->name() << ", ";
	for(vector<Net *>::iterator it = inputs->begin();
		it != inputs->end();
		++it)
	{
		if(it == inputs->end()-1)
			os << (*it)->name() << ");" << endl;
		else
			os << (*it)->name() << ", ";
	}
}

// Or Gate
Or::Or():Gate::Gate()
{ gtype = OR; }

Or::Or(string n):Gate::Gate(n)
{ gtype = OR; }

Or::Or(string n, int d):Gate::Gate(n,d)
{ gtype = OR; }

Or::~Or()
{
	while(!inputs->empty()){
		delete inputs->back();
		inputs->pop_back();
	}
	delete inputs;
	delete output;
}

char Or::eval()
{
	bool flag = false;
	for(vector<Net *>::iterator it = inputs->begin();
		it != inputs->end();
		++it)
	{
		if((*it)->getVal() == '1')
			return '1';
		if((*it)->getVal() == 'X')
			flag = true;
	}
	if(flag)
		return 'X';
	return '0'; 
}

void Or::dump(ostream &os)
{
	os << "	or ";
	if(delay != 1)
		os << "#" << delay << " ";
	os << inst_name << "(";
	os << output->name() << ", ";
	for(vector<Net *>::iterator it = inputs->begin();
		it != inputs->end();
		++it)
	{
		if(it == inputs->end()-1)
			os << (*it)->name() << ");" << endl;
		else
			os << (*it)->name() << ", ";
	}
}

// Nor Gate
Nor::Nor():Gate::Gate()
{ gtype = NOR; }

Nor::Nor(string n):Gate::Gate(n)
{ gtype = NOR; }

Nor::Nor(string n, int d):Gate::Gate(n,d)
{ gtype = NOR; }

Nor::~Nor()
{
	while(!inputs->empty()){
		delete inputs->back();
		inputs->pop_back();
	}
	delete inputs;
	delete output;
}

char Nor::eval()
{
	bool flag = false;
	for(vector<Net *>::iterator it = inputs->begin();
		it != inputs->end();
		++it)
	{
		if((*it)->getVal() == '1')
			return '0';
		if((*it)->getVal() == 'X')
			flag = true;
	}
	if(flag)
		return 'X';
	return '1';
}


void Nor::dump(ostream &os)
{
	os << "	nor ";
	if(delay != 1)
		os << "#" << delay << " ";
	os << inst_name << "(";
	os << output->name() << ", ";
	for(vector<Net *>::iterator it = inputs->begin();
		it != inputs->end();
		++it)
	{
		if(it == inputs->end()-1)
			os << (*it)->name() << ");" << endl;
		else
			os << (*it)->name() << ", ";
	}
}

// Nand Gate
Nand::Nand():Gate::Gate()
{ gtype = NAND; }

Nand::Nand(string n):Gate::Gate(n)
{ gtype = NAND; }

Nand::Nand(string n, int d):Gate::Gate(n,d)
{ gtype = NAND; }

Nand::~Nand()
{
	while(!inputs->empty()){
		delete inputs->back();
		inputs->pop_back();
	}
	delete inputs;
	delete output;
}

char Nand::eval()
{
	bool flag = false;
	for(vector<Net *>::iterator it = inputs->begin();
		it != inputs->end();
		++it)
	{
		if((*it)->getVal() == '0')
			return '1';
		if((*it)->getVal() == 'X')
			flag = true;
	}
	if(flag)
		return 'X';
	return '0';
}

void Nand::dump(ostream &os)
{
	os << "	nand ";
	if(delay != 1)
		os << "#" << delay << " ";
	os << inst_name << "(";
	os << output->name() << ", ";
	for(vector<Net *>::iterator it = inputs->begin();
		it != inputs->end();
		++it)
	{
		if(it == inputs->end()-1)
			os << (*it)->name() << ");" << endl;
		else
			os << (*it)->name() << ", ";
	}
}

// Xor Gate
Xor::Xor():Gate::Gate()
{ gtype = XOR; }

Xor::Xor(string n):Gate::Gate(n)
{ gtype = XOR; }

Xor::Xor(string n, int d):Gate::Gate(n,d)
{ gtype = XOR; }

Xor::~Xor()
{
	while(!inputs->empty()){
		delete inputs->back();
		inputs->pop_back();
	}
	delete inputs;
	delete output;
}

char Xor::eval()
{
	int ones = 0;
	for(vector<Net *>::iterator it = inputs->begin();
		it != inputs->end();
		++it)
	{
		if((*it)->getVal() == 'X')
			return 'X';
		else if((*it)->getVal() == '1')
			ones++;
	}
	// if there's only one input
	if(inputs->size() == 1)
		return 'X';
	// if there's an odd number of ones
	if(ones%2 == 1)
		return '1';
	return '0';
}

void Xor::dump(ostream &os)
{
	os << "	xor ";
	if(delay != 1)
		os << "#" << delay << " ";
	os << inst_name << "(";
	os << output->name() << ", ";
	for(vector<Net *>::iterator it = inputs->begin();
		it != inputs->end();
		++it)
	{
		if(it == inputs->end()-1)
			os << (*it)->name() << ");" << endl;
		else
			os << (*it)->name() << ", ";
	}
}

// Not Gate
Not::Not():Gate::Gate()
{ gtype = NOT; }

Not::Not(string n):Gate::Gate(n)
{ gtype = NOT; }

Not::Not(string n, int d):Gate::Gate(n,d)
{ gtype = NOT; }

Not::~Not()
{
	while(!inputs->empty()){
		delete inputs->back();
		inputs->pop_back();
	}
	delete inputs;
	delete output;
}

char Not::eval()
{
	char tempV = inputs->back()->getVal();
	for(vector<Net *>::iterator it = inputs->begin();
		it != inputs->end();
		++it)
	{
		if((*it)->getVal() == 'X')
			return 'X';
		else if((*it)->getVal() != tempV)
			return 'X';
	}
	if(tempV == '0')
		return '1';
	return '0';
}

void Not::dump(ostream &os)
{
	os << "	not ";
	if(delay != 1)
		os << "#" << delay << " ";
	os << inst_name << "(";
	os << output->name() << ", ";
	for(vector<Net *>::iterator it = inputs->begin();
		it != inputs->end();
		++it)
	{
		if(it == inputs->end()-1)
			os << (*it)->name() << ");" << endl;
		else
			os << (*it)->name() << ", ";
	}
}
