# I2C Communication


## Arcitectural decisions:

### Libraries

Main Library we build on top is [SerialTransfer](https://github.com/powerbroker2/SerialTransfer). This library has some known limitations that we still need to resolve.

### Data types:


#### Resources

1) [Bit bite important basics](https://web.stanford.edu/class/cs101/bits-bytes.html)
2) [Common sizes of Data Types](https://docs.oracle.com/cd/E19253-01/817-6223/chp-typeopexpr-2/index.html)
3) [Integer ranges and types in C++](https://sites.ualberta.ca/~jhoover/ConcreteComputing/section/bitexercise.htm)

Note: in C++ in int definition number of bits is encoded (not bytes!). E.g. uint32_t means this int has 32 bit == 4 bytes.  