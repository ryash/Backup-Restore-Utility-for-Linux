import socket
import _thread
import hashlib
import os
HOST = '192.168.0.5'  # The server's hostname or IP address
PORT = 9001       # The port used by the server

os.chdir("BackedupFiles")

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    temp=input()
    s.sendall(bytes(temp, 'utf-8'))
    s.close()



serversock = socket.socket()
host = "192.168.0.5"
port = 9002
serversock.bind((host,port))
filename = ""
serversock.listen(10)
print ("Waiting for a connection.....")
while True:
    clientsocket,addr = serversock.accept()
    print("Got a connection from %s" % str(addr))
    while True:
        size = clientsocket.recv(16) # Note that you limit your filename length to 255 bytes.
        if not size:
            break
        size = int(size, 2)
        filename = clientsocket.recv(size)
        filesize = clientsocket.recv(32)
        filesize = int(filesize, 2)
        file_to_write = open(filename, 'wb')
        chunksize = 4096
        while filesize > 0:
            if filesize < chunksize:
                chunksize = filesize
            data = clientsocket.recv(chunksize)
            file_to_write.write(data)
            filesize -= len(data)

        file_to_write.close()
        print ('File received successfully')
        break
    break

serversock.close()

