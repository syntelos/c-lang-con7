Continuation

  A continuation code is found in [LEB128].  The high bit
  (0x80) in an ordered sequence of octets is high (1) to
  indicate another octet follows in sequence, and low (0) to
  indicate the final octet in the sequence.

Implementation

  This package defines a pair of functions to perform
  continuation coding.  A seven bit octet sequence
  translates with an eight bit octet sequence in encoding
  and decoding.

Notes

  The first most natural application is to seven bit ASCII
  text, because ASCII plain text is a seven bit binary.

  To pack seven bit sequence of M-N bits into N byte words
  one would choose a byte order and bit padding, which is
  beyond the scope of this package.

References

  [LEB128] https://en.wikipedia.org/wiki/LEB128
  [CPL] https://www.cs.princeton.edu/~bwk/cbook.html
  [CPL] https://www.bell-labs.com/usr/dmr/www/

See also

  https://github.com/syntelos/c-lang-bix
  https://github.com/syntelos/c-endian-bint
  https://github.com/syntelos/lang

Configuration

  Clone with submodule.

    git clone --recurse-submodules <github:syntelos/c-lang-con7>

  Build using "make" (clang SUSv3 POSIX.1-2001).
