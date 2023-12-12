@0xf3b1f17e25a4285b;

const logVersion :Int32 = 1;

struct CanData {
  address @0 :UInt32;
  busTime @1 :UInt16;
  dat     @2 :Data;
  src     @3 :UInt8;
}

struct Event {
  logMonoTime @0 :UInt64;  # nanoseconds
  valid @1 :Bool = true;
  can @2 :List(CanData);#if feild is initing list or array that does mean it init func in corrospondng headet will takes in size pram
}
