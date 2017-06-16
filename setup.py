#!/usr/bin/env python
try:
    from setuptools import setup, Extension
except ImportError:
    from distutils.core import setup, Extension
import os
os.environ["CC"] = "gcc"

CSP_PATH = '/opt/cprocsp'
CSP_INCLUDE = os.path.join(CSP_PATH, 'include')
CSP_LIB_PATH = os.path.join(CSP_PATH, 'lib')

import platform
if platform.system() == 'Linux':
    CSP_LIB_PATH = os.path.join(CSP_LIB_PATH, 'amd64')

module_libsignature = Extension(
    'libsignature',
    sources = [
        './src/cpcsp/cpcsp.c',
        './src/cpcsp/crl.c',
        './src/cpcsp/cert.c',
        './src/cpcsp/verify.c',
        './src/libsignature.c',
        './src/py_cpcsp.c',         
    ],
    include_dirs = [
        CSP_INCLUDE,
        os.path.join(CSP_INCLUDE, 'cpcsp'),
        os.path.join(CSP_INCLUDE, 'pki'),        
    ],
    library_dirs = [
        CSP_LIB_PATH,
    ],
    libraries = [
        'rdrsup',
        'capi20',
        'pthread',
    ],
    extra_compile_args = [
        '-DUNIX',
        '-DHAVE_LIMITS_H',
        '-DHAVE_STDIN_H',
        '-DSIZEOF_VOID_P=8',
    ],
)


setup(
    name='libsignature',
    version='0.2',
    description='Python lib for verify cryptopro csp signature',
    author='Igor Kuznetsov',
    author_email='kuznetsovin@gmail.com',
    ext_modules = [module_libsignature],
)
