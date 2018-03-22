LOG		= ../util/log

MODEL		= BIG/

INITEX_DIR	= code/${MODEL}INIT
VIRTEX_DIR	= code/${MODEL}VIR
INITEX		= ${INITEX_DIR}/initex
VIRTEX		= ${VIRTEX_DIR}/virtex

LATEX_DIR	= latex.stuff
LATEX_INPUT	= lplain.tex
LATEX_FORMAT	= ${LATEX_DIR}/lplain.fmt
LATEX_PIECES	= ${VIRTEX} ${LATEX_FORMAT}
LATEX_RUN	= ${VIRTEX} "'&${LATEX_DIR}/lplain'"
#				^ ----------------

ROOT		= draft

bench-doit: bench-prepare ${ROOT}.tex
	@rm -f ${ROOT}.aux
	${LOG} . 'TeX run 1' ${LATEX_RUN} ${ROOT}.tex
	${LOG} . 'TeX run 2' ${LATEX_RUN} ${ROOT}.tex

bench-prepare: ${LATEX_PIECES}

${INITEX}:
	cd ${INITEX_DIR} ; make ${MFLAGS}

${VIRTEX}:
	cd ${VIRTEX_DIR} ; make ${MFLAGS}
#	${LOG} ${VIRTEX_DIR} 'Make virtex' make ${MFLAGS}

${LATEX_FORMAT}: ${INITEX} ${LATEX_DIR}/${LATEX_INPUT}	# And *.tfm, various .tex
	cd ${LATEX_DIR} ; ../${INITEX} ${LATEX_INPUT} \\dump

clean:
	@rm -f ${LATEX_FORMAT}	\
		${ROOT}.aux ${ROOT}.dvi ${ROOT}.log
	cd ${INITEX_DIR} ; make ${MFLAGS} clean
	cd ${VIRTEX_DIR} ; make ${MFLAGS} clean
