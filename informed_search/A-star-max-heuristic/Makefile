 all: main.cpp Node.cpp Session.cpp AStar.cpp SessionOrganizer.cpp
	  g++ -std=c++11 -o main main.cpp Session.cpp Node.cpp AStar.cpp SessionOrganizer.cpp

 profile: main.cpp Node.cpp Session.cpp AStar.cpp SessionOrganizer.cpp
	  g++ -pg -o main main.cpp Session.cpp Node.cpp AStar.cpp SessionOrganizer.cpp
	  ./main inputfile3.txt out.txt
	  gprof ./main gmon.out