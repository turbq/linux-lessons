exe: solution.c 
	gcc solution.c -fPIC -ldl -o solution
lib: secret.c secret.h
	gcc -shared secret.c -fPIC -o secret.so
clean:
	-rm solution 2>/dev/null
