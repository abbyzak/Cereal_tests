#include "messaging.h"
#include <iostream>

struct can_frame {
  long address;
  std::string dat;
  long busTime;
  long src;
};

void receive_can_frames(SubMaster& sm) {
  sm.update(1000); // Wait for up to 1000 ms for new data

  if (sm.updated("can")) {
    auto can_msg = sm["can"].getCan(); 

    for (const auto& frame : can_msg) {
      // Process each CAN frame
      std::cout << "Received CAN Frame - Address: " << frame.getAddress()
                << ", Bus Time: " << frame.getBusTime()
                << ", Data: " << std::string(reinterpret_cast<const char*>(frame.getDat().begin()), frame.getDat().size())
                << ", Source: " << frame.getSrc()
                << std::endl;
    }
  }
}

int main() {
  SubMaster sm({"can"});

  while (true) {
    receive_can_frames(sm);
  }

  return 0;
}
