#include "TaskContainer.h"
#include "Arduino.h"

namespace CleanAIR {
TaskContainer::TaskContainer() : mTasks(), mPerformedLastTimestep(0) {}

void TaskContainer::AddTask(std::function<bool()> task) { mTasks.push_back(task); }

unsigned long TaskContainer::GetPerformedLastTimestep() { return mPerformedLastTimestep; }

void TaskContainer::PerformTasks() {
  for (auto& task : mTasks) {
    mPerformedLastTimestep = millis();
    if (!task()) {
      Serial.println("Task failed!");
    }
  }
}
}  // namespace CleanAIR
