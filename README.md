# Backup-Restore-Utility-for-Linux
This a backup/restore utility for linux. A single command backup the listed directory and a deamon in background check for change in files and send them accordingly to the server. 

# Steps to run utility
make <br />
./backup  (for backup directory.) <br />
./restore (for restore file.) <br />

# Steps to run script
1. Run the restoreserver script(restoreserver.py) and backupserver script (backupserver.py) simultaneously in different windows.
2. Delete all the previous logs from the log file (maplog.txt).
3. Run 'make' command in a new window.
4. Run ./backup 
5. Make change in any file and kill the current task.
6. Run ./restore (enter the full path of the file to be restored).

# Demo of the Project
https://youtu.be/Y8wgtwjuG2Q

# Guide for Contributing:
https://www.dataschool.io/how-to-contribute-on-github/
