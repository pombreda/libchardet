#! /usr/bin/env python
# -*- coding: utf-8 -*-

def options(opt):
	opt.recurse('src')

def configure(conf):
	conf.recurse('src')

def build(bld):
	bld.recurse('src')

	bld.install_files("${PREFIX}/share/doc/chardet",
	 ['README.rst'])

	bld(
	 source='chardet-0.1.pc.in',
	 install_path='${LIBDIR}/pkgconfig/',
	)

