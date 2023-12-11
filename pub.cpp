#include "messaging.h"
#include <vector>
#include <string>
#include <chrono>
#include <thread>

struct can_frame {
  long address;
  std::string dat;
  long busTime;
  long src;
};

void send_can_frames(PubMaster& pm, const std::vector<can_frame>& frames) {
  MessageBuilder msg;
  auto evt = msg.initEvent();
  auto canData = evt.initCan(frames.size());

  for (size_t i = 0; i < frames.size(); ++i) {
    canData[i].setAddress(frames[i].address);
    canData[i].setBusTime(frames[i].busTime);
    canData[i].setDat(kj::arrayPtr((const uint8_t*)frames[i].dat.data(), frames[i].dat.size()));
    canData[i].setSrc(frames[i].src);
  }

  pm.send("can", msg);
}

int main() {
  PubMaster pm({"can"});

  while (true) {
    can_frame frame;
    frame.address = 0x123;      
    frame.busTime = 1577836800;  
    frame.src = 12451;             
    frame.dat = "01AB3F";       

    std::vector<can_frame> frames;
    frames.push_back(frame);

    send_can_frames(pm, frames);

    // Sleep for a short duration to avoid overwhelming the subscriber
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  return 0;
}
