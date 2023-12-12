from setuptools import setup, Extension
from Cython.Build import cythonize
import sysconfig
import os

# Define include and library directories
include_dirs = [
    '/usr/lib/include',
    '/opt/homebrew/include',
    sysconfig.get_paths()['include'],
]
lib_dirs = ['/opt/homebrew/lib']

# Compiler and linker flags
ccflags = []
ldflags = ["-pthread","-lkj","-lcapnp"]

# Sanitizer flags configuration
if 'UBSAN' in os.environ:
    ubsan_flags = [
        "-fsanitize=undefined",
        "-fno-sanitize-recover=undefined",
    ]
    ccflags += ubsan_flags
    ldflags += ubsan_flags
elif 'ASAN' in os.environ:
    asan_flags = [
        "-fsanitize=address",
        "-fno-omit-frame-pointer"
    ]
    ccflags += asan_flags
    ldflags += ["-fsanitize=address"]

extensions = [
    Extension(
        name="messaging_pyx",
        sources=["messaging_pyx.pyx", "messaging.cc", "impl_msgq.cc","msgq.cc","socketmaster.cc"],  # Add all necessary source files
        language="c++",
        include_dirs=include_dirs,
        library_dirs=lib_dirs,
        extra_compile_args=ccflags,
        extra_link_args=ldflags,
    )
]

setup(
    name='YourMessagingModule',
    ext_modules=cythonize(extensions,language_level='3')
)
