
%module vcfreader
%include "std_string.i"
%include "std_map.i"
%include "std_vector.i"
%include "exception.i"

using namespace std;

%{

#include "record.h"
#include "value.h"
#include "vcfreader.h"
#include "zstr.hpp"

	PyObject * value_to_py(Value* value)
	{
		PyObject * result = Py_None;

		switch (value->type())
		{
			case Value::Double:
			result = PyFloat_FromDouble(value->to_double());	
			break;

			case Value::Integer:
			result = PyInt_FromLong(value->to_int());	
			break;

			case Value::Bool:
			result = value->to_bool() ? Py_True : Py_False;	
			break;

			case Value::Invalid:
			result = Py_None;
			break;

			case Value::String:
			result = PyString_FromString(value->to_string().c_str());
		}

		return result;
	}

	%}


	%typemap(out) Value& {

		
		if ($1->dim() == 1)
			$result = value_to_py($1);

		else
		{
			vector<Value> value_list = $1->to_list();
			PyObject *pylist = PyTuple_New(value_list.size());

			for (auto i=0; i< value_list.size(); ++i)
				PyTuple_SetItem(pylist, i, value_to_py(&value_list[i]));

			$result = pylist;
		}
	}


	%include "record.h"
	%include "value.h"
	%include  "vcfreader.h"
  %attribute(Value, string, test, type_name,type_name);


	%extend VcfReader {
	%pythoncode %{

		def __iter__(self):
			return self 

		def __next__(self):
			if self.next():
				return self.record()
			else:
				raise StopIteration;
	%}
}
	



	%exception {
		try {
			$action
		} catch (const std::exception& e) {
			SWIG_exception(SWIG_RuntimeError, e.what());
		}
	}





	%template(StringVector) vector<string>;
	%template(ListValue) vector<Value>;
