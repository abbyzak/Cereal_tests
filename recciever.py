from messaging_pyx import Context, Poller, SubSocket
import time
if __name__ == "__main__":
    c = Context()
    sub_sock = SubSocket()
    sub_sock.connect(c, "controlsState")

    poller = Poller()
    poller.registerSocket(sub_sock)

    while True:
        for s in poller.poll(100):
            dat = s.receive()
            if dat:
                received_time = int.from_bytes(dat, 'little')
                current_time = int(time.time() * 1000)
                latency = current_time - received_time  # Calculate latency
                print(f"Received time: {received_time}, Latency: {latency}ms")
