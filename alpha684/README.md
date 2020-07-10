
==== Math

So if you want to efficiently encode a guid, with a minimum character set
beyond the alpha-numerics (ie ascii 85 is too encompassing), then the
next place to look is at 21 characters for 128 bits.

2 ^ 128 &#2245; 68.368 ^ 21

(This is easy to do on a calculator for any arbitrary bit size just by using logarithms.
`exp(ln(2)*128/21)=68.367468&#2026;`)

So an alphabet of 69?  Well, we can be a little more discriminating.  Our goal is
to create tokens that are more or less human recognizable, so we can trim some
of our terms to 68, having less spots that use that last element of the alphabet.

68.37 huh?

						68.3675 ^ 7 &#2245; 6981486380887
	68 * 69 * 68 * 69 * 68 * 69 * 68 = 7023974448384 

==== Alphabet

So we start with the obvious

    0-9
    A-Z
    a-z

that gets us to 62.  Then we add

    +-:%_=@

Why these characters.  Well, unlike base64 and base85 which are designed to be machine to machine,
we are attempting to design something better than hex for machine to human.  Which is to say,
guids will be encoded with this and output to logs.  Users could read those logs, select a guid
out of the line, and then paste it into a command line to grep for it in other places, or otherwise
process it.  So we want something that will read ok, select well, and not use any shell command characters.

So that last character will get used less than half as much as the others.  Then we throw
in one more short-cut.  We will replace double zeros with a dot, similar to ascii85's abbreviation.

We can also encode partial blocks into short strings, by tracking how many bits we have built
per digit.  Unfortunately for anything short of a full block, we only obtain an encoding
efficiency of three bytes to four characters (identical to base64).  But at least its no worse,
and of course for our primary use of sixteen bytes, base64 would actually require 22 characters
because sixteen is not evenly divisable by three.

==== Examples

So
0x00000000000000000000000000000000 = '...0...0...0'
0xffffffffffffffffffffffffffffffff = '=@=@=@==@=@=@==@=@=@='

other full blocks include:

0x0123456789abcdef0123456789abcdef =
0xdeadbeafdeadbeafdeadbeafdeadbeaf = 

partial blocks:

