#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <iomanip>
#include <climits>
#include <algorithm>

using namespace std;




struct Process {
  string processID;
  int burst, waiting = 0,turnaround = 0,remainingTmme;
};
queue<Process> processQueue;

// FCFS Scheduling 
void fcfsaddProcess(){//adding a process from user
  Process p;
  cout << "Enter Process ID: ";
  cin >> p.processID;
  cout << "Enter Burst Time: ";
  cin >> p.burst;
  processQueue.push(p);
  cout << "Process " << p.processID << " added.\n\n";
};

void fcfsviewProcesses() { //
  if (processQueue.empty()) { 
      cout << "No processes in the queue.\n\n";
      return;
  }

  queue<Process> temp = processQueue;
  cout << "Current Process Queue:\n";
  while (!temp.empty()) {
      Process p = temp.front();
      cout << "Process ID: " << p.processID << ", Burst Time: " << p.burst << endl;
      temp.pop();
  }
  cout << endl;
} 

void simulateFCFS() {
  if (processQueue.empty()) {
      cout << "No processes to schedule.\n\n";
      return;
  }

  queue<Process> temp = processQueue;
  int time = 0;
  float totalWaiting = 0, totalTurnaround = 0;

  cout << "\nGantt Chart:\n";
  while (!temp.empty()) {
      Process& p = temp.front();
      cout << "| " << p.processID << " ";
      p.waiting = time;
      time += p.burst;
      p.turnaround = time;
      temp.pop();
  }
  cout << "|\n\n";

  // Reset temp to refill from original queue
  temp = processQueue;
  time = 0;

  cout << left << setw(10) << "ProcessID" << setw(10) << "Burst"<< setw(12) << "Waiting" << setw(15) << "Turnaround" << endl;

  while (!temp.empty()) {
      Process p = temp.front();
      p.waiting = time;
      p.turnaround = p.waiting + p.burst;
      totalWaiting += p.waiting;
      totalTurnaround += p.turnaround;
      cout << left << setw(10) << p.processID<< setw(10) << p.burst << setw(12) << p.waiting << setw(15) << p.turnaround << endl;
      time += p.burst;
      temp.pop();
  }
  //cal the average wait and turnaroudn time
  int count = processQueue.size();
  cout << fixed;
  cout << "\nAverage Waiting Time: " << totalWaiting / count;
  cout << "\nAverage Turnaround Time: " << totalTurnaround / count << "\n\n";
}

void fcfsclearQueue() {
  while (!processQueue.empty())
      processQueue.pop();
  cout << "All processes cleared.\n\n";
}
//----------main menu for First-Come, First-Served (FCFS) Scheduling.
void fcfsMenu() {
  int choice;
  do {
      cout << "\n--- FCFS Scheduling ---\n";
      cout << "1. Add Process\n";
      cout << "2. View Queue\n";
      cout << "3. Simulate FCFS\n";
      cout << "4. Clear All Processes\n";
      cout << "5. Go Back to Main Menu\n";
      cout << "Enter your choice: ";
      cin >> choice;

      switch (choice) {
          case 1: fcfsaddProcess(); break;
          case 2: fcfsviewProcesses(); break;
          case 3: simulateFCFS(); break;
          case 4: fcfsclearQueue(); break;
          case 5: cout << "Returning to Main Menu...\n"; break;
          default: cout << "Invalid choice. Try again.\n";
      }
  } while (choice != 5);
}
//-------------------------END OF FCFS------------------------------------//

//
struct STRProcess {
  string processID;      
  int burst, waiting ,arrival, turnaround = 0, remainingTime;  
};

  vector<STRProcess> processVector;

void SRTaddProcess() {
    STRProcess pp;
    cout << "Enter Process ID: ";
    cin >> pp.processID;
    cout << "Enter Arrival Time: ";
    cin >> pp.arrival;
    cout << "Enter Burst Time: ";
    cin >> pp.burst;
    pp.remainingTime=pp.burst;
  processVector.push_back(pp);
  cout << "Process " << pp.processID << " added.\n\n";
}

void SRTviewProcess() { //
  if (processVector.empty()) { 
      cout << "No processes in the vector.\n\n";
      return;
  }
  cout << "Process ID | Arrical Time | BurstTime | Remaining Time\n";
  for (auto &pp : processVector) {
      cout << pp.processID << setw(13)<< pp.arrival << setw(14)<< pp.burst <<setw(14) << pp.remainingTime << endl;

}
}
void simulateSRT() {
  if (processVector.empty()) {
      cout << "No processes to simulate.\n";
      return;
  }
  //vector<STRProcess> processVector;
  int currentTime = 0;
  int completedProcess = 0;

  // While there are processes left to complete
  while (completedProcess < processVector.size()) {
      STRProcess* shortestProcess = nullptr;
      int minremainingTime = INT_MAX;

      // Find the process with the shortest remaining time
      for (auto &pp : processVector) {
          if (pp.arrival <= currentTime && pp.remainingTime  > 0 && pp.remainingTime < minremainingTime) {
              shortestProcess = &pp;
              minremainingTime = pp.remainingTime;
          }
      }

      // Execute the shortest process for 1 unit of time
      if (shortestProcess != nullptr) {
          shortestProcess->remainingTime--;  // Decrease remaining time
          currentTime++;

          // If process is finished2
          if (shortestProcess->remainingTime == 0) {
              completedProcess++;
              cout << "Process " << shortestProcess->processID << " completed at time " << currentTime << endl;
          }
      }
      else{
        currentTime++;
      }
  }
  cout << "All processes completed.\n";
}
void SRTclearQueue() {
  while (!processVector.empty())
      processVector.pop_back();
  cout << "All processes cleared.\n\n";
}
//-----------main menu for Shortest Remaining Time.
void srtMenu() {
  int choice;
  do {
      cout << "\n--- SRT Scheduling ---\n";
      cout << "1. Add Process\n";
      cout << "2. View Processes\n";
      cout << "3. Simulate SRT\n";
      cout << "4. Clear All Processes\n";
      cout << "5. Go Back to Main Menu\n";
      cout << "Enter your choice: ";
      cin >> choice;

      switch (choice) {
          case 1: SRTaddProcess(); break;
          case 2: SRTviewProcess(); break;
          case 3: simulateSRT(); break;
          case 4: processVector.clear(); cout << "Cleared all processes.\n"; break;
          case 5: cout << "Returning to main menu...\n"; break;
          default: cout << "Invalid choice. Try again.\n";
      }
  } while (choice != 5);
}
//-------------------------END OF SRT------------------------------------//

// shortest-job-next(SJN) Scheduling
struct SJNProcess {
  string processID;      
  int burst,arrivalTime;
};

vector<SJNProcess> processList;

void SJNaddProcess() {
  SJNProcess psjn;
  cout << "Enter Process ID: ";
  cin >> psjn.processID;
  cout << "Enter Arrival Time: ";
  cin >> psjn.arrivalTime;
  cout << "Enter Burst Time: ";
  cin >> psjn.burst;
  processList.push_back(psjn);
  cout << "Process " << psjn.processID << " added.\n\n";
}

void SJNviewProcess() { 
  if (processList.empty()) { 
      cout << "No processes in the vector.\n\n";
      return;
  }
    cout << "\nProcess List:\n";
    cout << "Process ID | Arrical Time | BurstTime\n";// "Process ID | Arrical Time | BurstTime\n"
    for (auto psjn : processList) {
        cout << psjn.processID << setw(13)  << psjn.burst <<setw(14)  << psjn.arrivalTime << endl;

  }
}
void simulateSJN() {
  // Sort by arrival time, then burst time
  vector<SJNProcess> processes = processList;

  sort(processes.begin(), processes.end(), [](SJNProcess a, SJNProcess b) {
      return a.arrivalTime < b.arrivalTime;
  });

  int currentTime = 0;
  vector<SJNProcess> completed;
  vector<bool> visited(processes.size(), false);

  while (completed.size() < processes.size()) {
      int shortestIdx = -1;
      int minBurst = INT_MAX;

      for (int i = 0; i < processes.size(); i++) {
          if (!visited[i] && processes[i].arrivalTime <= currentTime) {
              if (processes[i].burst < minBurst) {
                  minBurst = processes[i].burst;
                  shortestIdx = i;
              }
          }
      }

      if (shortestIdx == -1) {
          currentTime++;
      } else {
          visited[shortestIdx] = true;
          currentTime += processes[shortestIdx].burst;
          completed.push_back(processes[shortestIdx]);
      }
  }

  cout << "\nSJN Scheduling Result:\n";
  cout << "ProcessID | Burst | Arrival | Completion | Turnaround | Waiting\n";
  int completionTime = 0;
  for (auto &psjn : completed) {
    completionTime += psjn.burst;
      int turnaround = completionTime - psjn.arrivalTime;
      int waiting = turnaround - psjn.burst;
      cout << psjn.processID << setw(13) << psjn.burst << setw(9)  << psjn.arrivalTime << setw(9)  << completionTime<< setw(13)  << turnaround << setw(14)  << waiting << endl;
    }
  }
  /*void SJNclearQueue() {
    while (!processList.empty())
      processList.pop_back();
    cout << "All processes cleared.\n\n";
  }*/
//-----------main menu for Shortest Remaining Time.
void sjnMenu() {
  
  int choice;
  do {
      cout << "\n--- SJN Scheduling ---\n";
      cout << "1. Add Process\n";
      cout << "2. View Processes\n";
      cout << "3. Simulate SJN Scheduling\n";
      cout << "4. Clear All Processes\n";
      cout << "5. Go Back to Main Menu\n";
      cout << "Enter your choice: ";
      cin >> choice;

      switch (choice) {
          case 1: SJNaddProcess(); break;
          case 2: SJNviewProcess(); break;
          case 3: simulateSJN(); break;
          case 4: processList.clear(); cout << "Cleared all processes.\n"; break;
          case 5: cout << "Returning to main menu...\n"; break;
          default: cout << "Invalid choice. Try again.\n";
      }
  } while (choice != 5);
}

//-------------------------END OF SRT------------------------------------//
//------------------------MAIN------------------------------------//
int main(int argc, char const *argv[])
{
    int choice;
    do {
        cout << "\n====== CPU Scheduling Simulator ======\n";
        cout << "1. First-Come, First-Served (FCFS) Scheduling\n";
        cout << "2. Shortest Remaining Time (SRT)\n";
        cout << "3. Shortest-job-next(SJN) Scheduling\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
  
        switch (choice) {
            case 1: fcfsMenu(); break; // calls the submenu
            case 2: srtMenu(); break; // ""
            case 3: sjnMenu(); break; // ""
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);
  
    
    return 0;
}

