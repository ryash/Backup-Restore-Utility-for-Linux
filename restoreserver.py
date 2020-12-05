import socket
import os
import _thread
import time


while True:
    HOST = '127.0.0.1'  # Standard loopback interface address (localhost)
    PORT = 65432        # Port to listen on (non-privileged ports are > 1023)
    data1=[]
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen()
        conn, addr = s.accept()
        with conn:
            print('Connected by', addr)
            while True:
                data = conn.recv(1024)
                data1.append(data)
                if not data:
                    break
                
        s.close()


    s = socket.socket()
    host = "127.0.0.1"
    port = 9000
    s.connect((host, port))
    data1[0]=data1[0].decode('utf-8')

    print(data1[0])


    files=data1[0]
    #files=files.decode('utf-8')
    #if os.path.isfile(files):
    filename=files.replace("/", "-")
    #filename=files
    size=len(filename)
    size = bin(size)[2:].zfill(16) 
    s.send(size.encode())
    s.send(filename.encode())
    filename=files
    filesize=os.path.getsize(filename)
    filesize = bin(filesize)[2:].zfill(32) # encode filesize as 32 bit binary
    s.send(filesize.encode())

    file_to_send = open(filename, 'rb')
    #time.sleep(10)
    l = file_to_send.read()
    s.sendall(l)
    file_to_send.close()
    #files=files.replace("a", "q")   have to generate another string.
    #print(files)

    print ('File Sent')



    s.close()
