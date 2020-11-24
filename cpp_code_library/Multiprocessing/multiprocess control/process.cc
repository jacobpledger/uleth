//author: Jacob Pledger, 001136676
#include "process.h"

process::process()
{
  makeready();
}

process::~process()
{}

process::process(const process&)
{}



int process::getpid()
{
  return pid;
}

void process::setpid(int id)
{
  pid = id;
}



string process::getstate()
{
  return state;
}

void process::setstate(string newstate)
{
  state = newstate;
}

//moves a process to the ready queue
void process::makeready()
{
  state = "ready";
  awaitingEvent = 0;
  cout << "Process " << getpid() << " is ready" << endl;
}

//moves a process to the correct event wait queue
void process::block(int whichEvent)
{
  state = "blocked";
  awaitingEvent = whichEvent;
  cout << "Process " << getpid() << " is blocked" << endl;
  if(awaitingEvent != 0)
    cout << "Awaiting event: " << getEvent() << endl;
  else if (awaitingEvent == 0)
    cout << "It was taking too long" << endl;
}

int process::timeRun()
{
  return runtime;
}

void process::RunTimeUp()
{
  runtime++;
}

int process::getEvent()
{
  return awaitingEvent;
}

void process::request(int e)
{
  awaitingEvent = e;
}

void process::operator=(process newprocess)
{
  newprocess.pid = this->pid;
  newprocess.state = this->state;
  newprocess.awaitingEvent = this->awaitingEvent;
  newprocess.runtime = this->runtime;
}

void process::run()
{
  cout << "Process " << getpid() << " is running" << endl;
}

int process::getTotalRuntime()
{
  return totalruntime;
}