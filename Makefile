
libs = -lpython
objs = shorter.o utils.o

all: $(objs)
	g++ -fPic -shared -O3 $^ -o shorter.so $(libs)

%.o: %.cpp %.c
	g++ -O3 -c -o $@ $^
	
deploy:
	mv shorter.so ~/Development/venv/lib/python2.6/shorter.so

undeploy:
	rm ~/Development/venv/lib/python2.6/shorter.so

clean:
	rm *.o
	rm *.so





