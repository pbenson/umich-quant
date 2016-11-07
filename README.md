# University of Michigan Financial Quant Analytics project

This C++ project is being developed by students in the [Quantitative program](https://lsa.umich.edu/math/people/quant.html) at the U of M. More information on the project is available [here](https://pbenson.github.io/quant-projects/index.html).

## how to contribute to the project
First, you'll need to get the project up and running on your machine. And for that, you need to be properly installed, so check out [Getting Started](http://pbenson.github.io/cpp/getting-started.html). Now, since you've followed the instructions carefully, you've installed an IDE and the [boost library](http://boost.org), and configured your IDE to find the boost libraries.

<pre>
 #ifdef _WIN32 //For VisualStudio
#include "stdafx.h"
#endif

#include &lt;iostream&gt;
#include &lt;boost/date_time.hpp&gt;

int main(int argc, const char * argv[]) {
    std::cout << boost::gregorian::date_from_iso_string("20160930") << std::endl;
    return 0;
}
</pre>
and compile and run it successfully, with a return code of 0.
