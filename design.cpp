#include <iostream>
#include "design.h"
using namespace std;

Design::Design(string n):desname(n)
{ }

Design::~Design()
{
	for(map<string, Net *>::iterator it = designNets.begin();
		it != designNets.end();
		++it)
	{
		delete it->second; 
		designNets.erase(it);
	}
	for(map<string, Gate *>::iterator it = designGates.begin();
		it != designGates.end();
		++it)
	{
		delete it->second;
		designGates.erase(it);
	}
	vector<Net *> *allNets = this->allNets();
	delete allNets;
	vector<Gate *> *allGates = this->allGates();
	delete allGates;
	vector<Net *> *wireNets = this->getWireNets();
	delete wireNets;
	vector<Net *> *PINets = this->getPINets();
	delete PINets;
}

string Design::name()
{ return desname; }

void Design::addPI(string n)
{ pis.push_back(n); }

void Design::addPO(string n)
{	pos.push_back(n); }

Net *Design::findNet(string net_name)
{
	for(map<string, Net *>::iterator it = designNets.begin();
		it != designNets.end();
		++it)
	{
		if(it->first == net_name)
			return it->second;
	}
	return NULL;
}

Gate *Design::findGate(string inst_name)
{
	for(map<string, Gate *>::iterator it = designGates.begin();
		it != designGates.end();
		++it)
	{
		if(it->first == inst_name)
			return it->second;
	}
	return NULL;
}

Net* Design::addFindNet(string n)
{
	for(map<string, Net *>::iterator it = designNets.begin();
		it != designNets.end();
		++it)
	{
		if(designNets.find(n) != designNets.end())
			return designNets.find(n)->second;
	}
	Net* newNet = new Net(n);
	designNets.insert(make_pair(n,newNet));
	return newNet;
}

Gate* Design::addFindGate(int gtype, string g)
{
	for(map<string, Gate *>::iterator it = designGates.begin();
		it != designGates.end();
		++it)
	{
		if(designGates.find(g) != designGates.end())
			return designGates.find(g)->second;
	}
	Gate* newGate;
	if(gtype == 0)
		newGate = new And(g,1);
	else if(gtype == 1)
		newGate = new Or(g,1);
	else if(gtype == 2)
		newGate = new Nand(g,1);
	else if(gtype == 3)
		newGate = new Nor(g,1);
	else if(gtype == 4)
		newGate = new Xor(g,1);
	else if(gtype == 5)
		newGate = new Not(g,1);
	designGates.insert(make_pair(g,newGate));
	return newGate;
}

Gate* Design::addFindGate(int gtype, string g, int d)
{
	for(map<string, Gate *>::iterator it = designGates.begin();
		it != designGates.end();
		++it)
	{
		if(designGates.find(g) != designGates.end())
			return designGates.find(g)->second;
	}
	Gate* newGate;
	if(gtype == 0)
		newGate = new And(g,d);
	else if(gtype == 1)
		newGate = new Or(g,d);
	else if(gtype == 2)
		newGate = new Nand(g,d);
	else if(gtype == 3)
		newGate = new Nor(g,d);
	else if(gtype == 4)
		newGate = new Xor(g,d);
	else if(gtype == 5)
		newGate = new Not(g,d);
	designGates.insert(make_pair(g,newGate));
	return newGate;
}

vector<Net *> *Design::getPINets()
{
	vector<Net *> *newNet = new vector<Net *>;
	for(vector<string>::iterator it = pis.begin();
		it != pis.end();
		++it)
	{
		if(designNets.find(*it) != designNets.end())
			newNet->push_back(designNets.find(*it)->second);
	}
	return newNet;
}

vector<Net *> *Design::getPONets()
{
	vector<Net *> *newNet = new vector<Net *>;
	for(vector<string>::iterator it = pos.begin();
		it != pos.end();
		++it)
	{
		if(designNets.find(*it) != designNets.end())
			newNet->push_back(designNets.find(*it)->second);
	}
	return newNet;
}

vector<Net *> *Design::getWireNets()
{
	vector<Net *> *newNet = new vector<Net *>;
	bool flag1, flag2;
	for(map<string, Net *>::iterator it = designNets.begin();
		it != designNets.end();
		++it)
	{
		flag1 = false; flag2 = false;
		for(unsigned int i=0; i<pis.size(); i++)
			if(it->first == pis[i])
				flag1 = true;
		for(unsigned int j=0; j<pos.size(); j++)
			if(it->first == pos[j])
				flag2 = true;
		if(!flag1 && !flag2)
			newNet->push_back(it->second);
	}
	return newNet;
}

vector<Net *> *Design::allNets()
{
	vector<Net *> *newNet = new vector<Net *>;
	for(map<string, Net *>::iterator it = designNets.begin();
		it != designNets.end();
		++it)
	{
		newNet->push_back(it->second);
	}
	return newNet;
}

vector<Gate *> *Design::allGates()
{
	vector<Gate *> *newGate = new vector<Gate *>;
	for(map<string, Gate *>::iterator it = designGates.begin();
		it != designGates.end();
		++it)
	{
		newGate->push_back(it->second);
	}
	return newGate;
}

void Design::dump(ostream &os)
{
	os << "module " << desname << "(";
	for(vector<string>::iterator it = pis.begin();
		it != pis.end();
		++it)
	{		
		os << *it << ", ";
	}
	for(vector<string>::iterator jt = pos.begin();
		jt != pos.end();
		++jt)
	{		
		if(jt == pos.end()-1)
			os << *jt << ");" << endl;
		else
			os << *jt << ", ";
	}
	for(vector<string>::iterator it = pis.begin();
		it != pis.end();
		++it)
	{		
		os << "	input " << *it << ";" << endl;
	}
	for(vector<string>::iterator jt = pos.begin();
		jt != pos.end();
		++jt)
	{		
		os << "	output " << *jt << ";" << endl;
	}
	vector<Net *> *wires = getWireNets();
	for(vector<Net *>::iterator kt = wires->begin();
		kt != wires->end();
		++kt)
	{
		os << "	wire " << (*kt)->name() << ";" << endl;
	}
	for(map<string, Gate *>::iterator it = designGates.begin();
		it != designGates.end();
		++it)
	{
		it->second->dump(os);
	}
	os << "endmodule";
	// Clean up
	delete wires;
}

bool Design::isPI(Net *n)
{
	vector<Net *> *PIvec = getPINets();
	for(vector<Net *>::iterator it = PIvec->begin();
		it != PIvec->end(); 
		++it)
	{
		if(*it == n)
			return true;
	}
	return false;
}

bool Design::isPO(Net *n)
{
	vector<Net *> *POvec = getPONets();
	for(vector<Net *>::iterator it = POvec->begin();
		it != POvec->end(); 
		++it)
	{
		if(*it == n)
			return true;
	}
	return false;
}

/****Topological sort****/
vector<Net *> *Design::toposort()
{ // Let -1 denote white, 0 denote gray, and 1 denote black
	vector<Net *> *theList = new vector<Net *>;
	vector<Net *> *PONets = this->getPONets();
	map<string, int> colormap;
	for(map<string, Net *>::iterator it = designNets.begin();
		it != designNets.end();
		++it)
	{
		colormap.insert(make_pair(it->first,-1)); // initialize all nets to -1
	}
	theList->clear();
	for(vector<Net *>::iterator jt = PONets->begin();
		jt != PONets->end();
		++jt)
	{
		if(colormap[(*jt)->name()] == -1)
			dfs_visit(*jt, theList, colormap);
	}
	return theList;
}

void Design::dfs_visit(Net *n, vector<Net *> *flist, map<string, int> &colormap)
{
	colormap[n->name()]++; // it's 0 now
	for(vector<Gate *>::iterator it = n->getDrivers()->begin();
		it != n->getDrivers()->end();
		++it)
	{
		for(vector<Net *>::iterator jt = (*it)->getInputs()->begin();
			jt != (*it)->getInputs()->end();
			++jt)
		{
			if(colormap[(*jt)->name()] == -1)
				dfs_visit(*jt, flist, colormap);
		}
	}
	colormap[n->name()]++; // it's 1 now
	flist->push_back(n);
}
