# This file was automatically generated by SWIG (http://www.swig.org).
# Version 4.0.2
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.

from sys import version_info as _swig_python_version_info
if _swig_python_version_info < (2, 7, 0):
    raise RuntimeError("Python 2.7 or later required")

# Import the low-level C/C++ module
if __package__ or "." in __name__:
    from . import _vcfreader
else:
    import _vcfreader

try:
    import builtins as __builtin__
except ImportError:
    import __builtin__

def _swig_repr(self):
    try:
        strthis = "proxy of " + self.this.__repr__()
    except __builtin__.Exception:
        strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)


def _swig_setattr_nondynamic_instance_variable(set):
    def set_instance_attr(self, name, value):
        if name == "thisown":
            self.this.own(value)
        elif name == "this":
            set(self, name, value)
        elif hasattr(self, name) and isinstance(getattr(type(self), name), property):
            set(self, name, value)
        else:
            raise AttributeError("You cannot add instance attributes to %s" % self)
    return set_instance_attr


def _swig_setattr_nondynamic_class_variable(set):
    def set_class_attr(cls, name, value):
        if hasattr(cls, name) and not isinstance(getattr(cls, name), property):
            set(cls, name, value)
        else:
            raise AttributeError("You cannot add class attributes to %s" % cls)
    return set_class_attr


def _swig_add_metaclass(metaclass):
    """Class decorator for adding a metaclass to a SWIG wrapped class - a slimmed down version of six.add_metaclass"""
    def wrapper(cls):
        return metaclass(cls.__name__, cls.__bases__, cls.__dict__.copy())
    return wrapper


class _SwigNonDynamicMeta(type):
    """Meta class to enforce nondynamic attributes (no new attributes) for a class"""
    __setattr__ = _swig_setattr_nondynamic_class_variable(type.__setattr__)


class SwigPyIterator(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")

    def __init__(self, *args, **kwargs):
        raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    __swig_destroy__ = _vcfreader.delete_SwigPyIterator

    def value(self):
        return _vcfreader.SwigPyIterator_value(self)

    def incr(self, n=1):
        return _vcfreader.SwigPyIterator_incr(self, n)

    def decr(self, n=1):
        return _vcfreader.SwigPyIterator_decr(self, n)

    def distance(self, x):
        return _vcfreader.SwigPyIterator_distance(self, x)

    def equal(self, x):
        return _vcfreader.SwigPyIterator_equal(self, x)

    def copy(self):
        return _vcfreader.SwigPyIterator_copy(self)

    def next(self):
        return _vcfreader.SwigPyIterator_next(self)

    def __next__(self):
        return _vcfreader.SwigPyIterator___next__(self)

    def previous(self):
        return _vcfreader.SwigPyIterator_previous(self)

    def advance(self, n):
        return _vcfreader.SwigPyIterator_advance(self, n)

    def __eq__(self, x):
        return _vcfreader.SwigPyIterator___eq__(self, x)

    def __ne__(self, x):
        return _vcfreader.SwigPyIterator___ne__(self, x)

    def __iadd__(self, n):
        return _vcfreader.SwigPyIterator___iadd__(self, n)

    def __isub__(self, n):
        return _vcfreader.SwigPyIterator___isub__(self, n)

    def __add__(self, n):
        return _vcfreader.SwigPyIterator___add__(self, n)

    def __sub__(self, *args):
        return _vcfreader.SwigPyIterator___sub__(self, *args)
    def __iter__(self):
        return self

# Register SwigPyIterator in _vcfreader:
_vcfreader.SwigPyIterator_swigregister(SwigPyIterator)

class StringVector(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def iterator(self):
        return _vcfreader.StringVector_iterator(self)
    def __iter__(self):
        return self.iterator()

    def __nonzero__(self):
        return _vcfreader.StringVector___nonzero__(self)

    def __bool__(self):
        return _vcfreader.StringVector___bool__(self)

    def __len__(self):
        return _vcfreader.StringVector___len__(self)

    def __getslice__(self, i, j):
        return _vcfreader.StringVector___getslice__(self, i, j)

    def __setslice__(self, *args):
        return _vcfreader.StringVector___setslice__(self, *args)

    def __delslice__(self, i, j):
        return _vcfreader.StringVector___delslice__(self, i, j)

    def __delitem__(self, *args):
        return _vcfreader.StringVector___delitem__(self, *args)

    def __getitem__(self, *args):
        return _vcfreader.StringVector___getitem__(self, *args)

    def __setitem__(self, *args):
        return _vcfreader.StringVector___setitem__(self, *args)

    def pop(self):
        return _vcfreader.StringVector_pop(self)

    def append(self, x):
        return _vcfreader.StringVector_append(self, x)

    def empty(self):
        return _vcfreader.StringVector_empty(self)

    def size(self):
        return _vcfreader.StringVector_size(self)

    def swap(self, v):
        return _vcfreader.StringVector_swap(self, v)

    def begin(self):
        return _vcfreader.StringVector_begin(self)

    def end(self):
        return _vcfreader.StringVector_end(self)

    def rbegin(self):
        return _vcfreader.StringVector_rbegin(self)

    def rend(self):
        return _vcfreader.StringVector_rend(self)

    def clear(self):
        return _vcfreader.StringVector_clear(self)

    def get_allocator(self):
        return _vcfreader.StringVector_get_allocator(self)

    def pop_back(self):
        return _vcfreader.StringVector_pop_back(self)

    def erase(self, *args):
        return _vcfreader.StringVector_erase(self, *args)

    def __init__(self, *args):
        _vcfreader.StringVector_swiginit(self, _vcfreader.new_StringVector(*args))

    def push_back(self, x):
        return _vcfreader.StringVector_push_back(self, x)

    def front(self):
        return _vcfreader.StringVector_front(self)

    def back(self):
        return _vcfreader.StringVector_back(self)

    def assign(self, n, x):
        return _vcfreader.StringVector_assign(self, n, x)

    def resize(self, *args):
        return _vcfreader.StringVector_resize(self, *args)

    def insert(self, *args):
        return _vcfreader.StringVector_insert(self, *args)

    def reserve(self, n):
        return _vcfreader.StringVector_reserve(self, n)

    def capacity(self):
        return _vcfreader.StringVector_capacity(self)
    __swig_destroy__ = _vcfreader.delete_StringVector

# Register StringVector in _vcfreader:
_vcfreader.StringVector_swigregister(StringVector)


def is_digit(str):
    return _vcfreader.is_digit(str)
Int = _vcfreader.Int
Float = _vcfreader.Float
Str = _vcfreader.Str
Bool = _vcfreader.Bool
List = _vcfreader.List
class Header(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr
    HeaderType = property(_vcfreader.Header_HeaderType_get, _vcfreader.Header_HeaderType_set)
    id = property(_vcfreader.Header_id_get, _vcfreader.Header_id_set)
    dim = property(_vcfreader.Header_dim_get, _vcfreader.Header_dim_set)
    type = property(_vcfreader.Header_type_get, _vcfreader.Header_type_set)
    description = property(_vcfreader.Header_description_get, _vcfreader.Header_description_set)

    def __init__(self):
        _vcfreader.Header_swiginit(self, _vcfreader.new_Header())
    __swig_destroy__ = _vcfreader.delete_Header

# Register Header in _vcfreader:
_vcfreader.Header_swigregister(Header)

class Record(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr
    chrom = property(_vcfreader.Record_chrom_get, _vcfreader.Record_chrom_set)
    pos = property(_vcfreader.Record_pos_get, _vcfreader.Record_pos_set)
    id = property(_vcfreader.Record_id_get, _vcfreader.Record_id_set)
    ref = property(_vcfreader.Record_ref_get, _vcfreader.Record_ref_set)
    alt = property(_vcfreader.Record_alt_get, _vcfreader.Record_alt_set)
    qual = property(_vcfreader.Record_qual_get, _vcfreader.Record_qual_set)
    filter = property(_vcfreader.Record_filter_get, _vcfreader.Record_filter_set)
    infos = property(_vcfreader.Record_infos_get, _vcfreader.Record_infos_set)
    formats = property(_vcfreader.Record_formats_get, _vcfreader.Record_formats_set)
    format_names = property(_vcfreader.Record_format_names_get, _vcfreader.Record_format_names_set)

    def get_info_keys(self):
        return _vcfreader.Record_get_info_keys(self)

    def get_format_keys(self):
        return _vcfreader.Record_get_format_keys(self)

    def get_info(self, key):
        return _vcfreader.Record_get_info(self, key)

    def get_format(self, index, key):
        return _vcfreader.Record_get_format(self, index, key)

    def __init__(self):
        _vcfreader.Record_swiginit(self, _vcfreader.new_Record())
    __swig_destroy__ = _vcfreader.delete_Record

# Register Record in _vcfreader:
_vcfreader.Record_swigregister(Record)

class Value(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr
    dim = property(_vcfreader.Value_dim_get, _vcfreader.Value_dim_set)
    type = property(_vcfreader.Value_type_get, _vcfreader.Value_type_set)
    key = property(_vcfreader.Value_key_get, _vcfreader.Value_key_set)
    value = property(_vcfreader.Value_value_get, _vcfreader.Value_value_set)

    def __init__(self):
        _vcfreader.Value_swiginit(self, _vcfreader.new_Value())
    __swig_destroy__ = _vcfreader.delete_Value

# Register Value in _vcfreader:
_vcfreader.Value_swigregister(Value)

class VcfReader(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def __init__(self, filename):
        _vcfreader.VcfReader_swiginit(self, _vcfreader.new_VcfReader(filename))

    def get_info(self, key):
        return _vcfreader.VcfReader_get_info(self, key)

    def get_format(self, key):
        return _vcfreader.VcfReader_get_format(self, key)

    def get_samples(self):
        return _vcfreader.VcfReader_get_samples(self)

    def infos(self):
        return _vcfreader.VcfReader_infos(self)

    def formats(self):
        return _vcfreader.VcfReader_formats(self)

    def next(self):
        return _vcfreader.VcfReader_next(self)

    def record(self):
        return _vcfreader.VcfReader_record(self)

    def __iter__(self):
        return _vcfreader.VcfReader___iter__(self)

    def __next__(self):
        return _vcfreader.VcfReader___next__(self)
    __swig_destroy__ = _vcfreader.delete_VcfReader

# Register VcfReader in _vcfreader:
_vcfreader.VcfReader_swigregister(VcfReader)



