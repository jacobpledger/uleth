# For Makefiles, lines preceded with # are comment lines
# Remember, Makefiles are your friends. You do not want to be compiling
# files individually.

# some settings...
# use the gnu C++ compiler
CCC= g++
# list all warnings
CCCFLAGS = -Wall

# all is called a target, after the colon you have dependencies
# ie. "the target all is dependent on the executables
all : testMatrix

# the target <excecutable1> is dependent on the list of dependencies
# the line following  is the required executable (don't need to adjust it)
# Note: executable lines, ie. $(CCC) ..., always begin with a tab.
# $^ = this target
# $@ = this/these dependencies
testMatrix : testMatrix.o bandMatrix.o
	$(CCC) $(CCCFLAGS) $^ -o $@

# default rule compiling .cc to .o
# all .o file targets are dependent on the corresponding .cc files
# $< = the corresponding .cc file
%.o : %.cc
	$(CCC) -c $(CCCFLAGS) $<

# Don't need next lines b/c of the above default rule but no harm including them
# In the following lines, make knows that the .cc file is required in the
# current dependency so you can leave it out.  You can also leave out the
# corresponding executable line
bandMatrix.o : bandMatrix.h
bandMatrix.o : bandMatrix.cc

clean:
	rm -f *.o *~ *% *# .#*

clean-all: clean
	rm -f matrixTest
