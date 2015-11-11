#ifndef VLGPARSERMAN_H
#define VLGPARSERMAN_H

#include "design.h"
#include "vlg_parser.h"

class VlgParserMan : public VlgParser {
 public:
  VlgParserMan();
  Design *parse(char *filename);
 private:
  vector<string> parsePortList(istream &mystream, string &parsemsg, bool &parse_err);

};

#endif
