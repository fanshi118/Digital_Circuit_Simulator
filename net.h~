#ifndef NET_H
#define NET_H
#include <vector>
#include <string>
using namespace std;

/* Forward Declaration */
class Gate;

/**
 * This class models a net in the design
 */
class Net {
 public:
  /**
   * Constructor to initialize Net with given name
   *
   * @param[in] n Name of the net
   */
  Net(string n);

  /**
   * Destructor
   */
  ~Net();

  /**
   * Returns the name of this Net
   *
   * @return String representing the name of the net
   */
  string name() const;

  /**
   * Adds the given gate to the list of drivers 
   *  for this net
   *
   * @param[in] g Driver gate
   */
  void addDriver(Gate *g);

  /**
   * Adds the given gate to the list of loads 
   *  for this net
   *
   * @param[in] g Load gate
   */
  void addLoad(Gate *g);

  /**
   * Returns the loads of this net
   *
   * @return Returns a new dynamically allocated
   *          list of the load gates
   */
  vector<Gate *> *getLoads();

  /**
   * Returns the drivers of this net
   *
   * @return Returns a new dynamically allocated
   *          list of the driver gates
   */
  vector<Gate *> *getDrivers();

  /**
   * Looks at the driver gates and input nets to those
   *  gates to compute and return the value on this net
   *
   * @return Value produced on this net: '0','1','X'
   */
  char computeVal();

  /**
   * Looks at the driver gates and input nets to those
   *  gates to compute and return the time when this
   *  net's value will be resolved
   *
   * @return Time when this net's value is resolved
   */
  int computeDelay();


  /**
   * Accessor to the val data member
   *
   * @return Value of the net '0','1','X'
   */
  char getVal() const { return val; }

  /**
   * Mutator for the val data member
   *
   * @param[in] Sets the value of the net '0','1','X'
   */
  void setVal(char v) { val = v; }

  /**
   * Accessor to the delay data member
   *
   * @return Current delay value
   */
  int getDelay() const { return delay; }

  /**
   * Mutator for the delay data member
   *
   * @param[in] Value to assign to the delay
   */
  void setDelay(int d) { delay = d; }

  /**
   * Debug function you can use to verify 
   * your code. Prints the drivers and loads.
   *
   */
  void printDriversLoads();

 private:
  vector<Gate *> *drivers;
  vector<Gate *> *loads;
  char val;
  string netname;
  int delay;
};
#endif
