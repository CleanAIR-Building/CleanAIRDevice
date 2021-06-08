#pragma once
#include <functional>
#include <map>
#include "TaskContainer.h"

namespace CleanAIR {
class TaskScheduler {
 public:
  void AddTask(unsigned long timestep, std::function<bool()> task);
  void Loop();

 private:
  std::map<unsigned long, TaskContainer> mTaskContainers;
};
}  // namespace CleanAIR
