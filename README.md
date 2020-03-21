# TrueRandomNumber
This is a C library based on Windows which can produce true random numbers, which are the random numbers that cannot be predicted.
//NOTICE: This source code can only be used on Windows!

How does it work?
First, the program will create 2 threads (RNGProc). Each of these 2 threads will do plus operation to 2 global variables repeatly. Interestiongly, because of the looting of processor slice, these two global veriables will eventually be different from each other.
Second, after a period of time (RNG_LOOPTIME), these 2 threads will be terminated to release the resources they hold. Then, we can get the difference between those 2 global variables.
The previous two steps we've done can generate numbers that cannot be predicted, but the numbers are not random enough mathmatically because actually they have a relatively high possibility to appear in a certain area. So, the next steps are to make them become more random.
