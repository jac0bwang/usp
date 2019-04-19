This file contains information about compiling the programs from Chapter 4
of UNIX Systems Programming.

Under Solaris: no changes needed.

Under Linux:
   Compiling the programs under Linux typically requires that the constant
   _GNU_SOURCE be defined.  Run the convertlinux program once to modify the
   makefile use this constant.

Under Mac OS X:
   The poll function is not implemented in this version of Mac OS.
   Under Mac OS X, the sys/select include file needs the fcntl.h include
   file.  Run the convertmac program once to modify the makefile to remove
   the default compilarion of monitorpolltest and to modify whichisready.c and
   waitfdtimes.c to include fcntl.h before sys/select.h.

If you run the programs on another system and need to make modifications to
make them work, please send email to authors@usp.cs.utsa.edu to let us know
what you did.
