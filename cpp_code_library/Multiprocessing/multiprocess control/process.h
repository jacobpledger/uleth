//author: Jacob Pledger, 001136676
#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

class process
{
 public:
  process();
  ~process();
  process(const process&);
  int getpid(); //returns the PID
  void setpid(int id); //sets the PID

  string getstate(); //returns the state the process is in
  void setstate(string newState); //sets the state to newState

  void makeready(); //sets the process state to ready and awaitingEvent to 0
  void block(int whichEvent); //sets the process state to blocked and awaitingEvent to whichEvent

  int timeRun(); //returns how long the process has run
  void RunTimeUp(); //increments the runtime
  int getTotalRuntime(); //returns the total runtime of the process
  
  int getEvent(); //returns the waiting event #
  void request(int e); //sets the event the process is waiting for

  void operator=(process newprocess);
  void run(); //outputs the process

  
 private:
  int pid; //ID of the process (aka, processlist index)
  string state; //which state the process is in
  int runtime; //counter for how long the process has been running at once
  int totalruntime; //counter for how long the process has run total
  int awaitingEvent; //indicator for which event # the process is waiting for, 0 means not waiting
};

#endif