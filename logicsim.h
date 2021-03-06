#ifndef LOGICSIM_H
#define LOGICSIM_H

#include <iostream>
#include "design.h"

using namespace std;

class LogicSim {
	public:
		LogicSim();
		~LogicSim();
		bool readParse(char* infile, Design* circuit);
		void simDump(char* infile, Design* circuit, char* outfile);

	private:
		int numLines;
		int numInputs;
		bool eOne;
		bool eTwo;
		bool eThree;
		vector<string> tempPIs;
		vector<char> tempVals;
		vector<char> PIVals;
		vector<string> tempPOs;
		vector<Net *>* PONets;
		vector<char> POVals;
		vector<int> PODelays;
		vector<Net *>* topoNets;
};

#endif
