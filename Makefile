files = SimulatedOS.cpp Disk.cpp PCB.cpp RAM.cpp
headers = SimulatedOS.h Disk.h PCB.h RAM.h

main: main.cpp ${files} ${headers}
	g++ -o main main.cpp ${files} 

mem: memory_test.cpp ${files} ${headers}
	g++ -o mem memory_test.cpp ${files}


clean:
	rm -f *.o main mem
	clear