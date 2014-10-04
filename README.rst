##################################################
libchardet, a Character Encoding Detection Library
##################################################


Usage
#####

Check the ``chardet.h`` header and have fun.

Installation
############

libchardet uses the `waf <https://code.google.com/p/waf/>`_ build tool,
which also embeds Python scripts used to generate sources.

It is chosen not to embed the packaged waf here, but rather, tell users
and distro maintainers to get waf >= 1.7 from git or its distribution,
and call waf or waf-light from here.
So ``${waf}`` in what follows will mean either ``/path/to/waf/waf-light``
or a ``waf`` single-file package.

To build, run:

- configuration (will check for build dependencies)::

    ${waf} configure [regular waf options]

- build::

    ${waf}

- install::

    ${waf} install [regular waf intall options]


Development
###########

While character encoding detection is not expected to be used at large,
there are consumers for this, and also most of them I guess are interested
in the inner workings of such a library, so the goal is to be very clear
regarding what happens in this library, and keep the sources what they are,
source code.

It is chosen not to keep generated code in the sources, but rather to manage
to produce intermediate files during the build process.


