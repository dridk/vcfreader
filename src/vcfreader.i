
%module vcfreader
%include "std_string.i"
%include "std_map.i"
using namespace std;

%template(map_string_string) map<string, string>;


%typemap(out) Variant {
  
    if ($1.type == 0)
        $result = PyString_FromString($1.value);


    if ($1.type == 1){

        $result = PyInt_FromLong(atoi($1.value));
         
        }




}



%{

#include "vcfreader.h"
#include "zstr.hpp"

%}


%include  "vcfreader.h"