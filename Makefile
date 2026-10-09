all:
	g++ -Wall -g -O2 Sim.cpp Sim_Math.cpp TimeCode.cpp TimeCodeTests.cpp BigInteger.cpp -o traffic-simulation -lsqlite3 -I/usr/include


tests: Tests.cpp Sim_Math.cpp TimeCode.cpp TimeCodeTests.cpp BigInteger.cpp BigIntegerTests.cpp 
	g++ -Wall -g -O2 Tests.cpp Sim_Math.cpp TimeCode.cpp TimeCodeTests.cpp BigInteger.cpp BigIntegerTests.cpp -o tests -lsqlite3 -I/usr/include

	
clean:
	rm -rf tests traffic-simulation