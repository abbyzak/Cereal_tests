#include <cassert>
#include <iostream>

#include "messaging.h"
#include "impl_msgq.h"




bool messaging_use_fake(){
  char* fake_enabled = std::getenv("CEREAL_FAKE");
  return fake_enabled != NULL;
}

Context * Context::create(){
  Context * c;
    c = new MSGQContext();
  return c;
}

SubSocket * SubSocket::create(){
  SubSocket * s;
      s = new MSGQSubSocket();
  return s;
}

SubSocket * SubSocket::create(Context * context, std::string endpoint, std::string address, bool conflate, bool check_endpoint){
  SubSocket *s = SubSocket::create();
  int r = s->connect(context, endpoint, address, conflate, check_endpoint);

  if (r == 0) {
    return s;
  } else {
    std::cerr << "Error, failed to connect SubSocket to " << endpoint << ": " << strerror(errno) << std::endl;

    delete s;
    return nullptr;
  }
}

PubSocket * PubSocket::create(){
  PubSocket * s;
  s = new MSGQPubSocket();
  return s;
}

PubSocket * PubSocket::create(Context * context, std::string endpoint, bool check_endpoint){
  PubSocket *s = PubSocket::create();
  int r = s->connect(context, endpoint, check_endpoint);

  if (r == 0) {
    return s;
  } else {
    std::cerr << "Error, failed to bind PubSocket to " << endpoint << ": " << strerror(errno) << std::endl;

    delete s;
    return nullptr;
  }
}

Poller * Poller::create(){
  Poller * p;
      p = new MSGQPoller();
  return p;
}

Poller * Poller::create(std::vector<SubSocket*> sockets){
  Poller * p = Poller::create();

  for (auto s : sockets){
    p->registerSocket(s);
  }
  return p;
}
