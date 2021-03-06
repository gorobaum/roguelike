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
            fp, pathname, description = imp.find_module('_ugdk_base', [dirname(__file__)])
        except ImportError:
            import _ugdk_base
            return _ugdk_base
        if fp is not None:
            try:
                _mod = imp.load_module('_ugdk_base', fp, pathname, description)
            finally:
                fp.close()
            return _mod
    _ugdk_base = swig_import_helper()
    del swig_import_helper
else:
    import _ugdk_base
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


class SwigPyIterator(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, SwigPyIterator, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, SwigPyIterator, name)
    def __init__(self, *args, **kwargs): raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    __swig_destroy__ = _ugdk_base.delete_SwigPyIterator
    __del__ = lambda self : None;
    def value(self): return _ugdk_base.SwigPyIterator_value(self)
    def incr(self, n = 1): return _ugdk_base.SwigPyIterator_incr(self, n)
    def decr(self, n = 1): return _ugdk_base.SwigPyIterator_decr(self, n)
    def distance(self, *args): return _ugdk_base.SwigPyIterator_distance(self, *args)
    def equal(self, *args): return _ugdk_base.SwigPyIterator_equal(self, *args)
    def copy(self): return _ugdk_base.SwigPyIterator_copy(self)
    def next(self): return _ugdk_base.SwigPyIterator_next(self)
    def __next__(self): return _ugdk_base.SwigPyIterator___next__(self)
    def previous(self): return _ugdk_base.SwigPyIterator_previous(self)
    def advance(self, *args): return _ugdk_base.SwigPyIterator_advance(self, *args)
    def __eq__(self, *args): return _ugdk_base.SwigPyIterator___eq__(self, *args)
    def __ne__(self, *args): return _ugdk_base.SwigPyIterator___ne__(self, *args)
    def __iadd__(self, *args): return _ugdk_base.SwigPyIterator___iadd__(self, *args)
    def __isub__(self, *args): return _ugdk_base.SwigPyIterator___isub__(self, *args)
    def __add__(self, *args): return _ugdk_base.SwigPyIterator___add__(self, *args)
    def __sub__(self, *args): return _ugdk_base.SwigPyIterator___sub__(self, *args)
    def __iter__(self): return self
SwigPyIterator_swigregister = _ugdk_base.SwigPyIterator_swigregister
SwigPyIterator_swigregister(SwigPyIterator)
cvar = _ugdk_base.cvar
LuaLang = cvar.LuaLang
PythonLang = cvar.PythonLang

class ResourceContainerBase(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, ResourceContainerBase, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, ResourceContainerBase, name)
    def __init__(self, *args, **kwargs): raise AttributeError("No constructor defined")
    __repr__ = _swig_repr
    __swig_destroy__ = _ugdk_base.delete_ResourceContainerBase
    __del__ = lambda self : None;
ResourceContainerBase_swigregister = _ugdk_base.ResourceContainerBase_swigregister
ResourceContainerBase_swigregister(ResourceContainerBase)

class ResourceContainer_Texture(ResourceContainerBase):
    __swig_setmethods__ = {}
    for _s in [ResourceContainerBase]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, ResourceContainer_Texture, name, value)
    __swig_getmethods__ = {}
    for _s in [ResourceContainerBase]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, ResourceContainer_Texture, name)
    def __init__(self, *args, **kwargs): raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    __swig_destroy__ = _ugdk_base.delete_ResourceContainer_Texture
    __del__ = lambda self : None;
    def Insert(self, *args): return _ugdk_base.ResourceContainer_Texture_Insert(self, *args)
    def Replace(self, *args): return _ugdk_base.ResourceContainer_Texture_Replace(self, *args)
    def Exists(self, *args): return _ugdk_base.ResourceContainer_Texture_Exists(self, *args)
    def Find(self, *args): return _ugdk_base.ResourceContainer_Texture_Find(self, *args)
    def Load(self, *args): return _ugdk_base.ResourceContainer_Texture_Load(self, *args)
ResourceContainer_Texture_swigregister = _ugdk_base.ResourceContainer_Texture_swigregister
ResourceContainer_Texture_swigregister(ResourceContainer_Texture)

class ResourceContainer_AnimationSet(ResourceContainerBase):
    __swig_setmethods__ = {}
    for _s in [ResourceContainerBase]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, ResourceContainer_AnimationSet, name, value)
    __swig_getmethods__ = {}
    for _s in [ResourceContainerBase]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, ResourceContainer_AnimationSet, name)
    def __init__(self, *args, **kwargs): raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    __swig_destroy__ = _ugdk_base.delete_ResourceContainer_AnimationSet
    __del__ = lambda self : None;
    def Insert(self, *args): return _ugdk_base.ResourceContainer_AnimationSet_Insert(self, *args)
    def Replace(self, *args): return _ugdk_base.ResourceContainer_AnimationSet_Replace(self, *args)
    def Exists(self, *args): return _ugdk_base.ResourceContainer_AnimationSet_Exists(self, *args)
    def Find(self, *args): return _ugdk_base.ResourceContainer_AnimationSet_Find(self, *args)
    def Load(self, *args): return _ugdk_base.ResourceContainer_AnimationSet_Load(self, *args)
ResourceContainer_AnimationSet_swigregister = _ugdk_base.ResourceContainer_AnimationSet_swigregister
ResourceContainer_AnimationSet_swigregister(ResourceContainer_AnimationSet)

class ResourceContainer_Spritesheet(ResourceContainerBase):
    __swig_setmethods__ = {}
    for _s in [ResourceContainerBase]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, ResourceContainer_Spritesheet, name, value)
    __swig_getmethods__ = {}
    for _s in [ResourceContainerBase]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, ResourceContainer_Spritesheet, name)
    def __init__(self, *args, **kwargs): raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    __swig_destroy__ = _ugdk_base.delete_ResourceContainer_Spritesheet
    __del__ = lambda self : None;
    def Insert(self, *args): return _ugdk_base.ResourceContainer_Spritesheet_Insert(self, *args)
    def Replace(self, *args): return _ugdk_base.ResourceContainer_Spritesheet_Replace(self, *args)
    def Exists(self, *args): return _ugdk_base.ResourceContainer_Spritesheet_Exists(self, *args)
    def Find(self, *args): return _ugdk_base.ResourceContainer_Spritesheet_Find(self, *args)
    def Load(self, *args): return _ugdk_base.ResourceContainer_Spritesheet_Load(self, *args)
ResourceContainer_Spritesheet_swigregister = _ugdk_base.ResourceContainer_Spritesheet_swigregister
ResourceContainer_Spritesheet_swigregister(ResourceContainer_Spritesheet)

class ResourceContainer_LanguageWord(ResourceContainerBase):
    __swig_setmethods__ = {}
    for _s in [ResourceContainerBase]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, ResourceContainer_LanguageWord, name, value)
    __swig_getmethods__ = {}
    for _s in [ResourceContainerBase]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, ResourceContainer_LanguageWord, name)
    def __init__(self, *args, **kwargs): raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    __swig_destroy__ = _ugdk_base.delete_ResourceContainer_LanguageWord
    __del__ = lambda self : None;
    def Insert(self, *args): return _ugdk_base.ResourceContainer_LanguageWord_Insert(self, *args)
    def Replace(self, *args): return _ugdk_base.ResourceContainer_LanguageWord_Replace(self, *args)
    def Exists(self, *args): return _ugdk_base.ResourceContainer_LanguageWord_Exists(self, *args)
    def Find(self, *args): return _ugdk_base.ResourceContainer_LanguageWord_Find(self, *args)
    def Load(self, *args): return _ugdk_base.ResourceContainer_LanguageWord_Load(self, *args)
ResourceContainer_LanguageWord_swigregister = _ugdk_base.ResourceContainer_LanguageWord_swigregister
ResourceContainer_LanguageWord_swigregister(ResourceContainer_LanguageWord)

import ugdk_math
import ugdk_input
import ugdk_time
import ugdk_audio
import ugdk_action
import ugdk_graphic
import ugdk_util
class Color(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Color, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Color, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _ugdk_base.new_Color(*args)
        try: self.this.append(this)
        except: self.this = this
    def get_r(self): return _ugdk_base.Color_get_r(self)
    def get_g(self): return _ugdk_base.Color_get_g(self)
    def get_b(self): return _ugdk_base.Color_get_b(self)
    def get_a(self): return _ugdk_base.Color_get_a(self)
    def set_r(self, *args): return _ugdk_base.Color_set_r(self, *args)
    def set_g(self, *args): return _ugdk_base.Color_set_g(self, *args)
    def set_b(self, *args): return _ugdk_base.Color_set_b(self, *args)
    def set_a(self, *args): return _ugdk_base.Color_set_a(self, *args)
    __swig_destroy__ = _ugdk_base.delete_Color
    __del__ = lambda self : None;
Color_swigregister = _ugdk_base.Color_swigregister
Color_swigregister(Color)
MIRROR_NONE = cvar.MIRROR_NONE
MIRROR_HFLIP = cvar.MIRROR_HFLIP
MIRROR_VFLIP = cvar.MIRROR_VFLIP
MIRROR_HVFLIP = cvar.MIRROR_HVFLIP

class Configuration(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Configuration, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Configuration, name)
    __repr__ = _swig_repr
    __swig_setmethods__["base_path"] = _ugdk_base.Configuration_base_path_set
    __swig_getmethods__["base_path"] = _ugdk_base.Configuration_base_path_get
    if _newclass:base_path = _swig_property(_ugdk_base.Configuration_base_path_get, _ugdk_base.Configuration_base_path_set)
    __swig_setmethods__["window_icon"] = _ugdk_base.Configuration_window_icon_set
    __swig_getmethods__["window_icon"] = _ugdk_base.Configuration_window_icon_get
    if _newclass:window_icon = _swig_property(_ugdk_base.Configuration_window_icon_get, _ugdk_base.Configuration_window_icon_set)
    __swig_setmethods__["window_title"] = _ugdk_base.Configuration_window_title_set
    __swig_getmethods__["window_title"] = _ugdk_base.Configuration_window_title_get
    if _newclass:window_title = _swig_property(_ugdk_base.Configuration_window_title_get, _ugdk_base.Configuration_window_title_set)
    __swig_setmethods__["window_size"] = _ugdk_base.Configuration_window_size_set
    __swig_getmethods__["window_size"] = _ugdk_base.Configuration_window_size_get
    if _newclass:window_size = _swig_property(_ugdk_base.Configuration_window_size_get, _ugdk_base.Configuration_window_size_set)
    __swig_setmethods__["fullscreen"] = _ugdk_base.Configuration_fullscreen_set
    __swig_getmethods__["fullscreen"] = _ugdk_base.Configuration_fullscreen_get
    if _newclass:fullscreen = _swig_property(_ugdk_base.Configuration_fullscreen_get, _ugdk_base.Configuration_fullscreen_set)
    __swig_setmethods__["default_language"] = _ugdk_base.Configuration_default_language_set
    __swig_getmethods__["default_language"] = _ugdk_base.Configuration_default_language_get
    if _newclass:default_language = _swig_property(_ugdk_base.Configuration_default_language_get, _ugdk_base.Configuration_default_language_set)
    def __init__(self): 
        this = _ugdk_base.new_Configuration()
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _ugdk_base.delete_Configuration
    __del__ = lambda self : None;
Configuration_swigregister = _ugdk_base.Configuration_swigregister
Configuration_swigregister(Configuration)

class Engine(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Engine, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Engine, name)
    def __init__(self, *args, **kwargs): raise AttributeError("No constructor defined")
    __repr__ = _swig_repr
    __swig_getmethods__["reference"] = lambda x: _ugdk_base.Engine_reference
    if _newclass:reference = staticmethod(_ugdk_base.Engine_reference)
    def audio_manager(self): return _ugdk_base.Engine_audio_manager(self)
    def video_manager(self): return _ugdk_base.Engine_video_manager(self)
    def text_manager(self): return _ugdk_base.Engine_text_manager(self)
    def input_manager(self): return _ugdk_base.Engine_input_manager(self)
    def time_handler(self): return _ugdk_base.Engine_time_handler(self)
    def path_manager(self): return _ugdk_base.Engine_path_manager(self)
    def resource_manager(self): return _ugdk_base.Engine_resource_manager(self)
    def language_manager(self): return _ugdk_base.Engine_language_manager(self)
    def window_size(self): return _ugdk_base.Engine_window_size(self)
    def Initialize(self, *args): return _ugdk_base.Engine_Initialize(self, *args)
    def Run(self): return _ugdk_base.Engine_Run(self)
    def Release(self): return _ugdk_base.Engine_Release(self)
    def PushScene(self, *args): return _ugdk_base.Engine_PushScene(self, *args)
    def CurrentScene(self): return _ugdk_base.Engine_CurrentScene(self)
    def PopScene(self): return _ugdk_base.Engine_PopScene(self)
    def current_fps(self): return _ugdk_base.Engine_current_fps(self)
    def quit(self): return _ugdk_base.Engine_quit(self)
    __swig_destroy__ = _ugdk_base.delete_Engine
    __del__ = lambda self : None;
Engine_swigregister = _ugdk_base.Engine_swigregister
Engine_swigregister(Engine)

def Engine_reference():
  return _ugdk_base.Engine_reference()
Engine_reference = _ugdk_base.Engine_reference

class ResourceManager(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, ResourceManager, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, ResourceManager, name)
    __repr__ = _swig_repr
    def __init__(self): 
        this = _ugdk_base.new_ResourceManager()
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _ugdk_base.delete_ResourceManager
    __del__ = lambda self : None;
    __swig_getmethods__["GetTextureFromTag"] = lambda x: _ugdk_base.ResourceManager_GetTextureFromTag
    if _newclass:GetTextureFromTag = staticmethod(_ugdk_base.ResourceManager_GetTextureFromTag)
    __swig_getmethods__["GetTextureFromFile"] = lambda x: _ugdk_base.ResourceManager_GetTextureFromFile
    if _newclass:GetTextureFromFile = staticmethod(_ugdk_base.ResourceManager_GetTextureFromFile)
    __swig_getmethods__["GetSpritesheetFromTag"] = lambda x: _ugdk_base.ResourceManager_GetSpritesheetFromTag
    if _newclass:GetSpritesheetFromTag = staticmethod(_ugdk_base.ResourceManager_GetSpritesheetFromTag)
    __swig_getmethods__["GetAnimationSetFromFile"] = lambda x: _ugdk_base.ResourceManager_GetAnimationSetFromFile
    if _newclass:GetAnimationSetFromFile = staticmethod(_ugdk_base.ResourceManager_GetAnimationSetFromFile)
    __swig_getmethods__["CreateTextFromLanguageTag"] = lambda x: _ugdk_base.ResourceManager_CreateTextFromLanguageTag
    if _newclass:CreateTextFromLanguageTag = staticmethod(_ugdk_base.ResourceManager_CreateTextFromLanguageTag)
    def texture_container(self): return _ugdk_base.ResourceManager_texture_container(self)
    def spritesheet_container(self): return _ugdk_base.ResourceManager_spritesheet_container(self)
    def animation_loader(self): return _ugdk_base.ResourceManager_animation_loader(self)
    def word_container(self): return _ugdk_base.ResourceManager_word_container(self)
ResourceManager_swigregister = _ugdk_base.ResourceManager_swigregister
ResourceManager_swigregister(ResourceManager)

def ResourceManager_GetTextureFromTag(*args):
  return _ugdk_base.ResourceManager_GetTextureFromTag(*args)
ResourceManager_GetTextureFromTag = _ugdk_base.ResourceManager_GetTextureFromTag

def ResourceManager_GetTextureFromFile(*args):
  return _ugdk_base.ResourceManager_GetTextureFromFile(*args)
ResourceManager_GetTextureFromFile = _ugdk_base.ResourceManager_GetTextureFromFile

def ResourceManager_GetSpritesheetFromTag(*args):
  return _ugdk_base.ResourceManager_GetSpritesheetFromTag(*args)
ResourceManager_GetSpritesheetFromTag = _ugdk_base.ResourceManager_GetSpritesheetFromTag

def ResourceManager_GetAnimationSetFromFile(*args):
  return _ugdk_base.ResourceManager_GetAnimationSetFromFile(*args)
ResourceManager_GetAnimationSetFromFile = _ugdk_base.ResourceManager_GetAnimationSetFromFile

def ResourceManager_CreateTextFromLanguageTag(*args):
  return _ugdk_base.ResourceManager_CreateTextFromLanguageTag(*args)
ResourceManager_CreateTextFromLanguageTag = _ugdk_base.ResourceManager_CreateTextFromLanguageTag


def RegisterType_Color(*args):
  return _ugdk_base.RegisterType_Color(*args)
RegisterType_Color = _ugdk_base.RegisterType_Color

def GetNull_Color():
  return _ugdk_base.GetNull_Color()
GetNull_Color = _ugdk_base.GetNull_Color

def RegisterType_Configuration(*args):
  return _ugdk_base.RegisterType_Configuration(*args)
RegisterType_Configuration = _ugdk_base.RegisterType_Configuration

def GetNull_Configuration():
  return _ugdk_base.GetNull_Configuration()
GetNull_Configuration = _ugdk_base.GetNull_Configuration

def RegisterType_Engine(*args):
  return _ugdk_base.RegisterType_Engine(*args)
RegisterType_Engine = _ugdk_base.RegisterType_Engine

def GetNull_Engine():
  return _ugdk_base.GetNull_Engine()
GetNull_Engine = _ugdk_base.GetNull_Engine

def RegisterType_ResourceManager(*args):
  return _ugdk_base.RegisterType_ResourceManager(*args)
RegisterType_ResourceManager = _ugdk_base.RegisterType_ResourceManager

def GetNull_ResourceManager():
  return _ugdk_base.GetNull_ResourceManager()
GetNull_ResourceManager = _ugdk_base.GetNull_ResourceManager
print "Python ugdk_base confirm exports!"
module = __import__(__name__)
for key,value in module.__dict__.items():
	if key.startswith("RegisterType_"):
		arg = module.__dict__["GetNull_"+key[13:] ]()
		value(arg)

# This file is compatible with both classic and new-style classes.


