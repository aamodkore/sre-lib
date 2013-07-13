The following is a C++ implementation of SRE(Simple Regular Expressions) 
with elements as instances of memory with boolean variables(bits). This 
is usefull in the implementation of the EEC algorithm on the WSTS(Well 
Structured Ordering System) formed by the reduction of TSO to a Lossy 
Channel System.

-- Aamod Kore

--------------------------------------------------

FOR BULDING THIS LIBRARY YOU NEED TO HAVE INSTALLED "BuDDy" package.
You can ge it from :
http://vlsicad.eecs.umich.edu/BK/Slots/cache/www.itu.dk/research/buddy/

For building untar (uncompress) the contents of the tgz file into a 
folder preferably in the HOME folder. 

For building run 'make'. This compiles the files and places them in the 
respective directories in the place itself.

If the BuDDy package is installed in place and not in /usr, you will 
first have to set the the variable BDD_ROOT in the Makefile accordingly 
to the directory where BuDDy is compiled.
------------------------------

Then run 'make install' (This requires root access, so you would need to
 log in as root or simply run 'sudo make install')
 
This installs the library files to the /usr folder as required. The 
include path for GCC is mostly so for Linux systems, however if it is 
different you can change the INCLUDE_PATH and INSTALL_PATH variables in 
the make file accordingly.
If you don't have root access, even then you can use the library. 
However while compiling you would need to add flags for the paths 
appropriately.

If installed correctly, the library is called 'libsre.a' and thus to 
compile a C++ code you would have to include "sre.h" and the command for 
compiling would be:
'g++ path/to/code -o path/to/executable -lsre'
------------------------------

'make doc' creates the HTML documentation (not really helpful, although) 
and requires doxygen to be installed. You can also read about the 
classes and their use from the "doc/synopsis.txt" and header (H and HPP)
 files in the source.
------------------------------

'make examples' compiles the files in "examples" directory and places 
the executables to the "bin" directory
------------------------------

'make clean' cleans up unneccessary files. 
'make distclean' restores the package to the original state, keeping the
 library installed in /usr directories intact. 
'make bundle' creates a tgz archive of the package (again in the 
original state). 
'make uninstall' uninstalls the library from the /usr folder.
------------------------------
