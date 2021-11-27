# High-Performance-Computing-Experiments
Experimental and Comparative Performance Measurements of High Performance Computing Based on OpenMP and MPI
## 实验结果
本次实验记录了串行和并行的函数在数组大小分别为：10，50，100，500，1000，5000，10000，50000，100000，1000000时的运行时间。
结果如下（线程数为2，时间单位为ms）:
![image](https://user-images.githubusercontent.com/54580404/143666161-096e9965-1dd2-4da7-9d93-4922d842d9b7.png)
![image](https://user-images.githubusercontent.com/54580404/143666208-7ae6f6ef-208b-4794-abb3-9ce5f12d9f97.png)

#### 测试在线程数下的计算时间，并得出不同的结果。 

此处测试了线程数分别为1（串行），2，3，4，8的计算时间。
其中线程数为1和2的函数已经在上面给出。增加线程数，区别体现在quiksort函数中，将数组分割为更多子数组，并让不同的线程去处理子数组的排序。

测试结果（单位为毫秒，数组元素数为1，000，000）：
![image](https://user-images.githubusercontent.com/54580404/143666176-8792d086-ad27-4f2d-a9b7-62d5cc8d812b.png)![image](https://user-images.githubusercontent.com/54580404/143666216-f9571953-ace1-4bcb-a033-fc2646b6c3fc.png)

（3）对实验结果进行详细分析，将实验结果画成图表。 
本次实验利用pyecharts画出了串行与并行程序在不同大小的数组上分别运行的时间。
和在数组大小为10000时，线程数分别为1，2，4，8时程序运行的时间。

## 实验数据：
串行与并行的openMP实验结果如下图所示。
可以看出，随着数组元素的增加，无论是并行还是串行程序，运行的时间都会增加，尤其当数组元素数量非常多甚至达到百万级时，显然串行程序的运行时间已经超过了一秒，但是并行程序仅用了0.2s，可以看到，当数组元素达到一定的数量级时，并行算法的优势是极大的。
![image](https://user-images.githubusercontent.com/54580404/143666183-308cb914-58ea-4087-a101-c8789bde82cf.png)
不同线程运行时间结果如下图所示，由此可见，在选用合适线程数的情况下，线程越多，快速排序使用的时间越少。按概念来说，线程数越多，运行的时间应该更少，但是由于自身硬件的束缚，在线程增多到一定的数量时，若线程切换的过于频繁，也会影响程序的运行时间。所以说在运行多线程程序的时候还要考虑自己的cpu核心，来安排合适的线程数。
![image](https://user-images.githubusercontent.com/54580404/143666190-1e18edfd-d776-449a-bbf8-608aee724786.png)
![image](https://user-images.githubusercontent.com/54580404/143666219-c2dd54e1-0d26-40d5-a72d-8fe2cf1edc5d.png)
![image](https://user-images.githubusercontent.com/54580404/143666223-6eaf769b-0186-4eab-8471-f89647aa0ebb.png)
