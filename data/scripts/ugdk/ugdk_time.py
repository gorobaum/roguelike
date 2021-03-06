# This file was automatically generated by SWIG (http://www.swig.org).
# Version 2.0.4
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.



from sys import version_info
if version_info >= (2,6,0):
    def swig_import_helper():
        from os.path import dirname
        import imp
        fp = None
        try:
            fp, pathname, description = imp.find_module('_ugdk_time', [dirname(__file__)])
        except ImportError:
            import _ugdk_time
            return _ugdk_time
        if fp is not None:
            try:
                _mod = imp.load_module('_ugdk_time', fp, pathname, description)
            finally:
                fp.close()
            return _mod
    _ugdk_time = swig_import_helper()
    del swig_import_helper
else:
    import _ugdk_time
del version_info
try:
    _swig_property = property
except NameError:
    pass # Python < 2.2 doesn't have 'property'.
def _swig_setattr_nondynamic(self,class_type,name,value,static=1):
    if (name == "thisown"): return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'SwigPyObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name,None)
    if method: return method(self,value)
    if (not static):
        self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)

def _swig_setattr(self,class_type,name,value):
    return _swig_setattr_nondynamic(self,class_type,name,value,0)

def _swig_getattr(self,class_type,name):
    if (name == "thisown"): return self.this.own()
    method = class_type.__swig_getmethods__.get(name,None)
    if method: return method(self)
    raise AttributeError(name)

def _swig_repr(self):
    try: strthis = "proxy of " + self.this.__repr__()
    except: strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

try:
    _object = object
    _newclass = 1
except AttributeError:
    class _object : pass
    _newclass = 0


import ugdk_base
class TimeAccumulator(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TimeAccumulator, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TimeAccumulator, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _ugdk_time.new_TimeAccumulator(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _ugdk_time.delete_TimeAccumulator
    __del__ = lambda self : None;
    def TimeLeft(self): return _ugdk_time.TimeAccumulator_TimeLeft(self)
    def Expired(self): return _ugdk_time.TimeAccumulator_Expired(self)
    def Restart(self, *args): return _ugdk_time.TimeAccumulator_Restart(self, *args)
    def Pause(self): return _ugdk_time.TimeAccumulator_Pause(self)
    def Resume(self): return _ugdk_time.TimeAccumulator_Resume(self)
    def IsPaused(self): return _ugdk_time.TimeAccumulator_IsPaused(self)
TimeAccumulator_swigregister = _ugdk_time.TimeAccumulator_swigregister
TimeAccumulator_swigregister(TimeAccumulator)
cvar = _ugdk_time.cvar
LuaLang = cvar.LuaLang
PythonLang = cvar.PythonLang

class TimeManager(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TimeManager, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TimeManager, name)
    __repr__ = _swig_repr
    def __init__(self): 
        this = _ugdk_time.new_TimeManager()
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _ugdk_time.delete_TimeManager
    __del__ = lambda self : None;
    def Update(self): return _ugdk_time.TimeManager_Update(self)
    def TimeElapsed(self): return _ugdk_time.TimeManager_TimeElapsed(self)
    def TimeDifference(self): return _ugdk_time.TimeManager_TimeDifference(self)
    def TimeSince(self, *args): return _ugdk_time.TimeManager_TimeSince(self, *args)
TimeManager_swigregister = _ugdk_time.TimeManager_swigregister
TimeManager_swigregister(TimeManager)


def RegisterType_TimeAccumulator(*args):
  return _ugdk_time.RegisterType_TimeAccumulator(*args)
RegisterType_TimeAccumulator = _ugdk_time.RegisterType_TimeAccumulator

def GetNull_TimeAccumulator():
  return _ugdk_time.GetNull_TimeAccumulator()
GetNull_TimeAccumulator = _ugdk_time.GetNull_TimeAccumulator

def RegisterType_TimeManager(*args):
  return _ugdk_time.RegisterType_TimeManager(*args)
RegisterType_TimeManager = _ugdk_time.RegisterType_TimeManager

def GetNull_TimeManager():
  return _ugdk_time.GetNull_TimeManager()
GetNull_TimeManager = _ugdk_time.GetNull_TimeManager
print "Python ugdk_time confirm exports!"
module = __import__(__name__)
for key,value in module.__dict__.items():
	if key.startswith("RegisterType_"):
		arg = module.__dict__["GetNull_"+key[13:] ]()
		value(arg)

# This file is compatible with both classic and new-style classes.


