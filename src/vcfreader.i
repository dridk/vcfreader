
%module vcfreader
%include "std_string.i"
%include "std_map.i"
%include "std_vector.i"
%include "exception.i"

using namespace std;

%template(StringVector) vector<string>;

%exception {
  try {
    $action
  } catch (const std::exception& e) {
    SWIG_exception(SWIG_RuntimeError, e.what());
  }
}


%typemap(out) Value& {
	
	$result = PyString_FromString($1->value.c_str());

	if ($1->dim == 1)
	{
		if ($1->type == "Integer")
			$result = PyInt_FromLong(stoi($1->value));

		if ($1->type == "Float")
			$result = PyFloat_FromDouble(stod($1->value));
	}

	if ($1->dim > 1)
	{
		auto tmp = PyList_New($1->dim);

		for (uint i=0; i< $1->dim; ++i)
		{
			if ($1->type == "Integer")
				PyList_SET_ITEM(tmp,i,PyInt_FromLong(stoi($1->value)));

			if ($1->type == "Float")
				PyList_SET_ITEM(tmp,i,PyFloat_FromDouble(stod($1->value)));
		}

    $result = SWIG_Python_AppendOutput($result,tmp);
	}

}



%{

#include "vcfreader.h"
#include "zstr.hpp"

	%}


	%include  "vcfreader.h"
