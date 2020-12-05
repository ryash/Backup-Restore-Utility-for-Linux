all:
	g++ -o backup backup.cpp
	g++ -o restore restore.cpp

backup:
	g++ -o backup backup.cpp

restore:
	g++ -o restore restore.cpp

clean:
	rm -f backup restore
