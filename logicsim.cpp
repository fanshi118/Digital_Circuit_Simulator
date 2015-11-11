#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "logicsim.h"

using namespace std;

// check inputs on the first line (a, b, c)
// run toposort() once on all the designNets()
// use setVal() to set each primary input
// run computeVal() & computeDelay()
// iterate thru all the PONets()
// print out the values and delays

LogicSim::LogicSim()
{
	numLines = 0;
	numInputs = 0;
	eOne = false;
	eTwo = false;
	eThree = false;
}

LogicSim::~LogicSim()
{ }

bool LogicSim::readParse(char* infile, Design* circuit)
{
	ifstream myfile(infile);
	string lineOne;
	getline(myfile, lineOne);
	stringstream ss(lineOne);
	string PI;
	numLines++;
	/***Error 1 check***/
	while(ss >> PI){
		if(circuit->findNet(PI) == NULL){
			cout << "At line " << numLines << ", PI: " << PI << "does not exist in the design." << endl;
			eOne = true;
		}
		else{
			numInputs++;
			tempPIs.push_back(PI);
		}
	}

	string nextLine;
	getline(myfile, nextLine);
	while(!myfile.fail()){
		numLines++;
		stringstream ssnl(nextLine);
		char val;
		/***Error 3 check***/
		while(ssnl >> val){
			if(val!='0' && val!='1' && val!='X'){
				cout << "At line " << numLines << ", an input has invalid value." << endl;
				eThree = true;
			}
			else{
				tempVals.push_back(val);
				PIVals.push_back(val);
			}
		}
		/***Error 2 check***/
		//cout << "PI size is " << tempPIs.size() << endl;
		//cout << "val size is " << PIVals.size() << endl;
		if(tempPIs.size() != tempVals.size()){
			cout << "At line " << numLines << ", # of input values mismatches # of PIs." << endl;
			eTwo = true;
		}
		getline(myfile, nextLine);
		tempVals.clear();
	}

	if(eOne || eTwo || eThree){
		myfile.close();
		return false;
	}
	myfile.close();
	return true;
}

void LogicSim::simDump(char* infile, Design* circuit, char* outfile)
{
	topoNets = circuit->toposort();
	ofstream ofile(outfile);

	// Print out the first line
	for(vector<Net *>::iterator it = topoNets->begin();
		it != topoNets->end();
		++it)
	{
		if(circuit->isPI(*it))
			ofile << setw(4) << (*it)->name();
	}
	ofile << setw(4) << "=>";
	for(vector<Net *>::iterator it = topoNets->begin();
		it != topoNets->end();
		++it)
	{
		if(circuit->isPO(*it))
			ofile << setw(6) << (*it)->name();
	}
	ofile << endl;

	// Get all names of the output
	PONets = circuit->getPONets();
	for(vector<Net *>::iterator it = PONets->begin();
		it != PONets->end();
		++it)
	{
		tempPOs.push_back((*it)->name());
	}
	delete PONets;
	
	// Set values for all primary inputs
	int col = tempPIs.size();
	int row = PIVals.size()/tempPIs.size();
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			Net* temp = circuit->findNet(tempPIs[j]);
			temp->setVal(PIVals[i*col+j]);
		}
		for(vector<Net *>::iterator it = topoNets->begin();
			it != topoNets->end();
			++it)
		{
			(*it)->computeVal();
			(*it)->computeDelay();
		}
		for(vector<string>::iterator jt = tempPOs.begin();
			jt != tempPOs.end();
			++jt)
		{
			Net* temp = circuit->findNet(*jt);
			POVals.push_back(temp->getVal());
			PODelays.push_back(temp->getDelay());
		}
	}
	//cout << POVals.size() << endl << PODelays.size() << endl;
	delete topoNets;

	// Print out the simulation result
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			ofile << setw(4) << PIVals[i*col+j];
		}
		ofile << setw(4) << "=>";
		for(unsigned int k=0; k<tempPOs.size(); k++){
			int index = i*tempPOs.size()+k;
			ofile << setw(4) << POVals[index] << "@" << PODelays[index];
		}
		ofile << endl;
	}
	ofile.close();
}
