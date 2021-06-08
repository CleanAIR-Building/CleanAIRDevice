#include "TaskScheduler.h"
#include "Arduino.h"
#include "TaskContainer.h"

namespace CleanAIR {
void TaskScheduler::AddTask(unsigned long timestep, std::function<bool()> task) {
  auto search = mTaskContainers.find(timestep);
  if (search == mTaskContainers.end()) {
    search = mTaskContainers.emplace(timestep, TaskContainer()).first;
  }
  search->second.AddTask(task);
}

void TaskScheduler::Loop() {
  for (auto& pair : mTaskContainers) {
    const unsigned long period = pair.first;
    auto& taskContainer = pair.second;
    if ((millis() - taskContainer.GetPerformedLastTimestep()) > period) {
      taskContainer.PerformTasks();
    }
  }
}
}  // namespace CleanAIR
