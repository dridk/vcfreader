
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
			result = PyFloat_FromDouble(value->toDouble());	
			break;

			case Value::Integer:
			result = PyInt_FromLong(value->toInt());	
			break;

			case Value::Bool:
			result = value->toBool() ? Py_True : Py_False;	
			break;

			case Value::Invalid:
			result = Py_None;
			break;

			case Value::String:
			result = PyString_FromString(value->toString().c_str());
		}

		return result;
	}

	%}


	%typemap(out) Value& {

		
		if ($1->dim() == 1)
			$result = value_to_py($1);

		else
		{
			vector<Value> value_list = $1->toList();
			PyObject *pylist = PyTuple_New(value_list.size());

			for (auto i=0; i< value_list.size(); ++i)
				PyTuple_SetItem(pylist, i, value_to_py(&value_list[i]));

			$result = pylist;
		}
	}


	%include "record.h"
	%include "value.h"
	%include  "vcfreader.h"

	%pythoncode %{

		def __next__(self):
			if self.next():
				return self.record()
			else:
				raise StopIteration;

		VcfReader.__iter__ = lambda self: self
		VcfReader.__next__ = __next__


	%}
	



	%exception {
		try {
			$action
		} catch (const std::exception& e) {
			SWIG_exception(SWIG_RuntimeError, e.what());
		}
	}





	%template(StringVector) vector<string>;
	%template(ListValue) vector<Value>;
