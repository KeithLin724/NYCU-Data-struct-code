# Data Structure Homework Template
### Written By KYLiN

---

This is code for the Data Structure Homework Template

It can support ```-std=c++11``` or upper version

### Design
- ```void print_class_data() const```: this function is for debug . Design for check the class member data.

- READ_FILE WRITE_FILE : This two marco is using ```__read_file_stream``` and  ```__to_file_stream``` to make it. Mainly using the stream buffer to control the data flow 

### HOW TO USE
#### *!!!Write your code in //TODO:!!!*

- DEBUG: 
    You can use the ```DEBUG``` mode to open the debug mode 

    If you close the ```DEBUG``` mode .You can not use the ```std::cout and std::cin```

> You can easily to control the ```cin cout``` , It will auto to compiler the cin and cout


- READ_FILE WRITE_FILE :
    You can use these two command to read file.
    
    The read file and write file in this template is already make it.
> Using  ```READ_FILE``` and ```WRITE_FILE``` to do it.
>
- ```solutionTools```: This is a Solution class object using in the main function  



---

### Main function example 

```cpp
/*
Title:This is code for the Data Structure Homework Template
Written By KYLiN
using Template example
Date: 6/12/2022
*/

// open the debug mode 
#define DEBUG 

#include <iostream>
#include "Solution.h"
using namespace std;

int main(int argc, char* argv[]) {

    try {
        // reading file 
        solutionTools.read_file(argv[1]);

        // check member function 
        solutionTools.print_class_data();

        // run solution
        solutionTools.run_solution(argv[2]);
    }
    catch (const std::exception& e) {
        cerr << e.what() << '\n';
        exit(-1);
    }
    return 0 ; 
}
```