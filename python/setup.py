#!/usr/bin/env python
# -*- coding: utf-8 -*-

try:
	from setuptools import setup, Extension
except ImportError:
	from distutils.core import setup, Extension

from Cython.Build import cythonize

extensions = [
 Extension("libchardet._libchardet", ["libchardet/_libchardet.pyx"],
  include_dirs = ["../src"],
  libraries = ["chardet"],
  library_dirs = ["../build/src"],
 ),
]

setup(
 name = 'libchardet',
 author = 'Jérôme Carretero (zougloub)',
 author_email = 'cJ-libchardet@zougloub.eu',
 url = r"https://github.com/zougloub/libchardet",
 description = "Character Encoding Detector",
 long_description= "libchardet detects the most probable character" \
  " encodings in a string.\n" \
  "It doesn't give the best results but the goal is for the library to be" \
  " expandable and clear.\n",
 version = '0.1',
 license = 'MPL 2.0',
 classifiers = [
  # http://pypi.python.org/pypi?:action=list_classifiers
  'Development Status :: 4 - Beta',
  'License :: OSI Approved :: MPL License',
  'Programming Language :: Cython',
  'Programming Language :: Python',
  'Topic :: Software Development :: Libraries',
  'Programming Language :: Python :: 2',
  'Programming Language :: Python :: 3',
 ],
 keywords = [
  'cython',
  'libchardet', 'chardet', 'encoding',
 ],
 packages = ['libchardet'],
 ext_modules = cythonize(extensions),
)

