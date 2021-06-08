#pragma once
#include <functional>
#include <list>

namespace CleanAIR {
class TaskContainer {
 public:
  TaskContainer();
  void PerformTasks();
  void AddTask(std::function<bool()> task);
  unsigned long GetPerformedLastTimestep();

 private:
  std::list<std::function<bool()>> mTasks;
  unsigned long mPerformedLastTimestep;
};
}  // namespace CleanAIR
