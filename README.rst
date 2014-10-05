##################################################
libchardet, a Character Encoding Detection Library
##################################################


As of 2014, not all text files are yet in UTF-8 (best thing since the wheel),
and character encoding detection is necessary.
This library is a reimplementation of universal character encoding detection
(aka charset sniffing), AFAICT pioneered by Netscape/Mozilla in their browser
via the ``nsUniversalDetector`` library, which has been widely reused.
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


Design Notes
############

This library assumes that Unicode is a super-set of all code pages and other
character encodings.
Thus, a first pass of eliminating the potentially incompatible encodings
is performed using Unicode libraries.
If available on the system, ``iconv`` and ``ICU`` will be used.

Then, to guess which encoding is used, between the potential results obtained
on the first pass, an analysis is performed, determining what is the
probability of the text being something else than random characters which
happen to be valid in the candidate encoding.
Strategies are used, such as frequency analysis, and result in the refinement
of the score of the candidate encodings.

Tables of probabilities are used to perform the second pass; a design goal
of this library is to have the tables generated during compile-time instead
of hard-coded in the sources.


Limitations
***********

It is sometimes found in e-mails that parts of a text are in an encoding,
and other ones are not, and this library doesn't handle that.
If the two encodings are incompatible, then the library will decide that
the result is none of the two.

As of v0.1, the whole text needs to be fed in the library, and the detector
cannot be reset. It's not that expensive anyway, given the purpose of the
library. But this limitation is only due to lack of development resources and
motivation, so don't hesitate to contribute, discuss the API, etc.


References
##########


Other Character Encoding Detection Implementations
**************************************************

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


Character Encodings and Unicode
*******************************

Here's a short intro to Unicode:
http://www.w3.org/International/articles/definitions-characters/


