In this example, you have to run p1 first then p2. Since:
p1 will enter the critical section once p2 has finished its critical section.

Another note, to compile it: """ gcc -o run semaphore_p1.c -lpthread """