//author: Jacob Pledger, 001136676
#include "process.h"
#include <fstream>
using namespace std;

void spawn(vector<process>&processlist);
void spawn(int numProcesses, vector<process>&processlist);
void getEventList(vector<int>&e);
void getProcessEvents(vector<int>&pe);
void getWhenEvents(vector<int>&when);

int main()
{
  //setup
  //********************************************************************
  int numprocesses; //how many processes there are
  cout << "How many processes are there? ";
  cin >> numprocesses;
  
  int processlength;
  cout << "How long does each process need to finish? ";
  cin >> processlength;

  int maxruntime;
  cout << "How long can each process run at a time? ";
  cin >> maxruntime;
  
  //Set up event queues
  int numEvents;
  cout << "How many events are there? ";
  cin >> numEvents;
  vector<queue<process> >eventqs; //resizable array of event wait queues
  queue<process>q;
  for (unsigned int i = 0; i < numEvents; ++i)
    eventqs.push_back(q);
  
  //set up which processes request events
  vector<int>whosEvents;
  getProcessEvents(whosEvents);

  //set up when each process requests the event
  vector<int>whenEvents;
  getWhenEvents(whenEvents);
  
  //set up when events occur
  vector<int>eventTimeline; //list of events in the order they occur
  getEventList(eventTimeline);
  
  //create processes
  vector<process>processlist; //vector of all processes
  queue<process> readyq; //queue of ready processes
  spawn(numprocesses, processlist);
  
  for (int i = 0; i < numprocesses; ++i)
    processlist[i].request(whosEvents[i]);
  
  //put all processes into the ready queue
  for (unsigned int i = 0; i < numprocesses; ++i)
    {
      processlist[i].makeready();
      readyq.push(processlist[i]);
    }
    
  bool runningProcess = false; //indicator for if a process is running
  bool done = false;
  //**********************************************************************
  
  int t = 0;
  while(!done)
    {
      //put all process waiting the event that occurs at this time into the ready queue
      while( !eventqs[eventTimeline[t]].empty() )
	{
	  eventqs.at(eventTimeline[t]).front().makeready();
	  readyq.push(eventqs.at(eventTimeline[t]).front());
	  eventqs.at(eventTimeline[t]).pop();
	}
      
      //if no processes are running, and there are processes in the ready queue run the next process in the ready queue
      if(!runningProcess && !readyq.empty())
	{
	  readyq.front().run();
	  runningProcess = true;
	}
      
      //if it's time to request an operation, do so.
      if(t == whenEvents[readyq.front().getpid()] )
	readyq.front().request(whosEvents[readyq.front().getpid()] );
      
      readyq.front().RunTimeUp();
            
      //if the process has completed, kill it.
      if(readyq.front().getTotalRuntime() == processlength)
	{
	  readyq.pop();
	}
      
      //if the current process has hit its max runtime...
      if(readyq.front().timeRun() == maxruntime)
	{
	  //if the process is waiting for an event, put it in the event queue
	  if(readyq.front().getEvent() != 0)
	    {
	      readyq.front().block(readyq.front().getEvent());
	      eventqs.at(readyq.front().getEvent()).front() = readyq.front();
	      readyq.pop();
	    }
	  //if the process is not waiting for an event, put it back into the ready queue
	  if(readyq.front().getEvent() == 0)
	    {
	      readyq.front().block(0);
	      readyq.front().makeready();
	      readyq.push(readyq.front());
	      readyq.pop();
	    }
	  
	}
      
      //if all the processes are done, exit
      if(readyq.empty())
	{
	  int c = 0;
	  for(unsigned int i = 0; i < numEvents; ++i)
	    if(eventqs[i].empty())
	      c++;
	  if(c = numEvents)
	    done = true;
	}
      
      t++;
    }
  
  
  return 0;
}

//adds a new process to the process list
void spawn(vector<process>&processlist)
{
  process newprocess;
  processlist.push_back(newprocess); //spawns a new process
  processlist.at(processlist.size()).setpid(processlist.size()); //sets the ID of the process
}

//spawns a specified number of processes
void spawn(int numprocesses, vector<process>&processlist)
{
  for (unsigned int i = 0; i < numprocesses; ++i)
    spawn(processlist);
}

//gets the list of events in the order they will occur
void getEventList(vector<int>&e)
{
  ifstream infile;
  string filename;
  cout << "Where is the list of when events occur?" << endl;
  cin >> filename;
  infile.open(filename.c_str() );
  int i = 0;
  while(!infile.eof())
    {
      infile >> e[i];
      ++i;
    }
}

void getProcessEvents(vector<int>&pe)
{
  ifstream infile;
  string filename;
  cout << "Where is the list of which processes request events?" << endl;
  cin >> filename;
  infile.open(filename.c_str() );
  int i = 0;
  while(!infile.eof())
    {
      infile >> pe[i];
      ++i;
    }
}

void getWhenEvents(vector<int>&when)
{
  ifstream infile;
  string filename;
  cout << "Where is the list of when processes request events?" << endl;
  cin >> filename;
  infile.open(filename.c_str() );
  int i = 0;
  while(!infile.eof())
    {
      infile >> when[i];
      ++i;
    }
}