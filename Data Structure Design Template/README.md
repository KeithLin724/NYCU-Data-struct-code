# Data Structure Homework Template
### Written By KYLiN

---

This is code for the Data Structure Homework Template

It can support ```-std=c++11``` or upper version

### Design
- mainly using the `streambuff` to change the output stream

### HOW TO USE
#### *!!!Write your code in //TODO:!!!*
- `Mode run_your_design()` 
    
    Is a function for you to design the algorithm, you can start your code in there.  

- DEBUG: 
    
    You can use the ```DEBUG``` mode to open the debug mode 

    If you want to check the output , please use the ```debug()``` to replace the ```std::cout```

    It will output a `Log.txt` file to check you debug output

- Mode
    
    Mode is a mode of output place . There have 3 Mode , `Mode::file` `Mode::console` , and `Mode::both`, This 3 mode you can choose it in the 

    ```run_your_design``` return 
---

### Where I start to use 

In here 
``` cpp
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////Start your design//////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
    /* DATA: data */
public:
    Mode run_your_design(const std::string& fileNameIn) {
        auto inFileData = Solution::read_file(fileNameIn);

        /*TODO: */
        debug(<<"output Log file : Hello world");
        std::cout << "output file Hello world\n";
         
        // chose your output mode
        return Mode::file;
    }

    /*TODO: some design*/

```


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

int main() {
    try {
        // run solution
        solutionTools.run_solution("test.txt", "output.txt");
    }
    catch (const std::exception& e) {
        cerr << e.what() << '\n';
        exit(-1);
    }
    return 0;
}
```