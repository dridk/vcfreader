
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
	
	switch ($1->type())
	{

	case Value::Double:
		$result = PyFloat_FromDouble($1->toDouble());	
		break;

	case Value::Integer:
		$result = PyInt_FromLong($1->toInt());	
		break;

	case Value::Bool:
		$result = $1->toBool() ? Py_True : Py_False;	
		break;

	case Value::None:
		$result = Py_None;
		break;

	case Value::String:
		$result = PyString_FromString($1->toString().c_str());
	

	}

	




}



%{

#include "record.h"
#include "value.h"
#include "vcfreader.h"

#include "zstr.hpp"

	%}

%include "record.h"
%include "value.h"
%include  "vcfreader.h"
