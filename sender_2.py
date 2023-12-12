import time
from messaging_pyx import Context, PubSocket

if __name__ == "__main__":
    c = Context()
    pub_sock = PubSocket()
    pub_sock.connect(c, "can")

    while True:
        current_time = int(time.time() * 1000)  # Current time in milliseconds
        bts = current_time.to_bytes(8, 'little')
        pub_sock.send(bts)
        print(f"Sent current time: {current_time}")
        time.sleep(1)  # Sleep for a second between sends
