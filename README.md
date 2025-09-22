# Stego

## Good resources

https://www.opencv-srf.com/2017/11/opencv-cpp-api.html

## Nice hack (idom)

you can slurp a whole file into a vector in one line

```language: c++ 
std::ifstream input_stream("./file", std::ios::binary);

std::vector<uint8_t> payload ( (std::istreambuf_iterator<char>(file)), 
	                           (std::istreambuf_iterator<char>()) );
```


### notes 

#### casts
 in c++, there are 4 types of casts:
 1. static_cast<type>(expr). you can only use it with rerlated types
 like double->int, Base*->Derived*. but it does not allow cast between
 unrelated pointer types like uint8_t* and char*

 2. reinterpret_cast<type>(expr). it's used with raw memory, so it can 
 be used in cases where statc_cast won't work.
 like from uint8_t* to char*
 
 3. const_cast<type>(expr). it's used when casting a const type to a non
 const type and vise versa.
 
 4. C-style cast. the c-style cast is discouraged to be used in c++ because
 it can perform any cast possible. it can do the job of all the above ones.


#### inheritance

private inheritance will porhibit polymorphysim
