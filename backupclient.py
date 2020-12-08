import socket
import os
import _thread
import time
s = socket.socket()
host = "192.168.0.5"
port = 9000


s.connect((host, port))
#directory = os.listdir(path)
List = open("out.txt").readlines()
List = map(lambda s: s.strip(), List)
#print(list(List))

for files in list(List):
    #print(files)
    if os.path.isfile(files):
        filename=files.replace("/", "-")
        print(filename)
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


# for files in directory:
#     print(files)
#     filename = path[1:4]+files
#     size = len(filename)
#     size = bin(size)[2:].zfill(16) # encode filename size as 16 bit binary
#     s.send(size.encode())
#     s.send(filename.encode())
#     filename=files
#     filename = os.path.join(path,filename)
#     filesize = os.path.getsize(filename)
#     filesize = bin(filesize)[2:].zfill(32) # encode filesize as 32 bit binary
#     s.send(filesize.encode())

#     file_to_send = open(filename, 'rb')
#     #time.sleep(10)
#     l = file_to_send.read()
#     s.sendall(l)
#     file_to_send.close()
#     #files=files.replace("a", "q")   have to generate another string.
#     #print(files)
    
#     print ('File Sent')

s.close()
