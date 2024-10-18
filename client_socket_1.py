import socket

HOST = '192.168.0.103'
PORT = 10000


def send_to_esp(num):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        num = str(num)
        s.sendall(b'' + num.encode())
        data = s.recv(1024)
    return data


for i in range(100):
    print(i)
    print(send_to_esp(i))

# print(f"Received {str(data)}")
