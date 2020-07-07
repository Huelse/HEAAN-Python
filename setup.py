import os, sys
from distutils.core import setup, Extension
from distutils import sysconfig

cfg_vars = sysconfig.get_config_vars()
for key, value in cfg_vars.items():
    if type(value) == str:
        cfg_vars[key] = value.replace('-Wstrict-prototypes', '')

cpp_args = ['-std=c++11']

ext_modules = [
    Extension(
        'HEAAN',
        ['src/base64.cpp', 'src/wrapper.cpp'],
        include_dirs=['/usr/include/python3.6', 'pybind11/include', '/usr/local/include', 'HEAAN/src'],
        language='c++',
        extra_compile_args = cpp_args,
        extra_objects=['/usr/local/lib/libntl.so', 'HEAAN/lib/libHEAAN.a'], # both lib need compiled with -fPIC
    ),
]

setup(
    name='HEAAN',
    version='2.1.0',
    author='Huelse', 
    author_email='Huelse@oini.top',
    description='Python wrapper for HEAAN',
    ext_modules=ext_modules,
)
