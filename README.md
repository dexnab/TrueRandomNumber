# TrueRandomNumber
This is a C library based on Windows which can produce true random numbers, which are the random numbers that cannot be predicted.
//NOTICE: This source code can only be used on Windows!

How does it work?
We know, the function rand() is a pseudo-random number generator, which means with the same seed, it can only generate the same random numbers. So how to produce an unpredictable random number? The solution is to generate unpredictable seeds each time when we use rand() to generate random numbers.

First, the program will create 2 threads (RNGProc). Each of these 2 threads will do plus operation to 2 global variables repeatly. Interestiongly, because of the looting of processor slice, these two global variables will eventually be different from each other.
Second, after a period of time (RNG_LOOPTIME), these 2 threads will be terminated to release the resources they hold. Then, we can get the difference between those 2 global variables.

The previous two steps we've done can generate numbers that cannot be predicted, but the numbers are not random enough mathmatically because actually they have a relatively high possibility to appear in a certain area. So, the next steps are to make them become more random.

First, we xor the number we get from the previous steps with the current time, and the result is the seed. This can reduce the possibility of same seeds significantly.
Then, we generate a pseudo-random number through the function rand() by using the seed produced in the last step. So the number produced will be dispersive enough.

Through these steps, we can generate a random number that cannot be predicted.
