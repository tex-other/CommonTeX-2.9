#
#  Pehong Chen, University of California, Berkeley (phc@renoir.berkeley.edu)
#
#      modified for distribution, monardo@renoir.berkeley.edu
#
#      hacked for benchmarking, maslen@lurch.stanford.edu.  Result is awful
#	 for development but fine for a complete build.
#

CC	= $(C_COMPILE)

# 16-bit word
#CFLAGS	= $(OPTIMIZE)
# 32-bit word
CFLAGS	= $(OPTIMIZE) -DBIG
# 64-bit word
#CFLAGS	= $(OPTIMIZE) -DBIGG

SRCS	= align.c arith.c box.c boxlists.c char.c cmds.c cond.c def.c dvi.c \
	  eq.c eqstack.c error.c eval.c evalstack.c expand.c file.c fmt.c \
	  hash.c heap.c hyph.c io.c math.c mathlists.c mlst-hlst.c pack.c \
	  page.c par.c print.c scan.c str.c tex.c texext.c tfm.c token.c \
	  tokenlists.c tokenstack.c

HDRS	= align.h arith.h box.h boxlists.h char.h cmds.h cond.h def.h dvi.h \
	  eq.h eqstack.h error.h eval.h evalstack.h expand.h file.h fmt.h \
	  hash.h heap.h hyph.h io.h math.h mathlists.h mlst-hlst.h pack.h \
	  page.h par.h print.h scan.h str.h tex.h texext.h tfm.h token.h \
	  tokenlists.h tokenstack.h
# Yup, there's a .h for every .c; such structuring...

all: initex virtex

initex: $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) -DINIT -o initex $(SRCS)

virtex: $(SRCS) $(HDRS)
	$(CC) $(CFLAGS)        -o virtex $(SRCS)

clean:
	rm -f *.o *.u initex virtex *.out
