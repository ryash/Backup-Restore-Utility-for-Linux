# Backup-Restore-Utility-for-Linux
This a backup/restore utility for linux. A single command backup the listed directory and a deamon in background check for change in files and send them accordingly to the server. 

# Steps to run script
1. Run the restoreserver script(python3 restoreserver.py) and backupserver script (python3 backupserver.py) simultaneously in different windows.
2. Run 'make' command in a new window.
3. Run ./backup 
4. Make changes in any file (The changes will be detected and the changed files will be sent to the server).
5. Run ./restore (enter the full path of the file to be restored).
6. The config file contains the directory path which we want to backup.

# Demo of the Project
https://youtu.be/Y8wgtwjuG2Q

# Guide for Contributing:
https://www.dataschool.io/how-to-contribute-on-github/
