
%module vcfreader
%include "std_string.i"
%include "std_map.i"
%include "std_vector.i"
using namespace std;

%template(StringVector) vector<string>;

%{

#include "vcfreader.h"
#include "zstr.hpp"

%}


%include  "vcfreader.h"