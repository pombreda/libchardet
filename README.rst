##################################################
libchardet, a Character Encoding Detection Library
##################################################


As of 2014, not all text files are yet in UTF-8 (best thing since the wheel),
and character encoding detection is necessary.
This library is a reimplementation of universal character detection,
AFAICT pioneered by Netscape in their ``nsUniversalDetector`` piece of code,
which has been widely reused.
The goal is to make it more transparent and hackable, with less dependencies,
a clear API, and available to the world.


License
#######

libchardet uses the Mozilla Public License v2.0 (see ``LICENSE`` file which is
attached with the sources or the more readable https://www.mozilla.org/MPL/2.0/).
The goal is to permit any use, but making sure that distributed modifications
are back upstream.
The Exhibit A (source code form license notice) is deliberately not put
in each file in the sources, to save bytes, and all upstreamed contributions
are to be tracked with the VCS system.


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


References
##########

A well known library that does character encoding detection is gecko
(Netscape/Mozilla):
http://lxr.mozilla.org/seamonkey/source/extensions/universalchardet/
The algorithm is described at:
http://www-archive.mozilla.org/projects/intl/UniversalCharsetDetection.html

The Netscape code is forked at:
https://code.google.com/p/uchardet/
(https://github.com/BYVoid/uchardet)


Another library is libenca:
https://github.com/nijel/enca/
This library uses recode / iconv to try and parse text.

