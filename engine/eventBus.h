#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <raylib.h>
#include "log.h"
#pragma once

enum kind { EXAMPLE_EVENT };
struct EventStruct {
  kind event;
  const std::shared_ptr<void> data;
  const std::shared_ptr<void> data2;
};

class EventBus {
  private:
  std::queue<EventStruct> q;
  // Static pointer to prevent copies
  static EventBus* instancePtr;
  // Mutex to ensure thread safety
  static std::mutex mtx;
  // Private Constructor
  EventBus() {}

  public:
  // Remove the copy constructor to prevent copies 
  EventBus(const EventBus& obj) = delete;
  // Static method to get class instance
  static EventBus* getInstance() {
    if (instancePtr == nullptr) {
      std::lock_guard<std::mutex> lock(mtx);
      if (instancePtr == nullptr) {
        instancePtr = new EventBus();
      }
    }
    return instancePtr;
  }

  void push(EventStruct event) {
    q.push(event);
  }

  void pop() {
    if (q.size() > 0) {
      q.pop();
    }
  }

  int size() { return q.size(); }

  EventStruct getFront() {
    if (q.size() == 0) { LOG_ERROR("Bus is empty"); }
    return q.front();
  }

  kind eventType() {
    if (q.size() == 0) { LOG_ERROR("Bus is empty"); }
    return q.front().event;
  } 
};

