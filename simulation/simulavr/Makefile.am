#
# $Id$
#

ACLOCAL_AMFLAGS = -I m4

if USE_AVR_CROSS
EXAMPLES = examples
endif

SUBDIRS = . src $(EXAMPLES) doc

EXTRA_DIST = bootstrap make_tarball README.gdb SUPPORT m4/README
 
doc_DATA = README README.gdb SUPPORT TODO AUTHORS ChangeLog COPYING INSTALL NEWS

CLEANFILES = simulavr-$(PACKAGE_VERSION).tar.gz

doxygen-doc:
if DX_COND_doc
	$(MAKE) -C doc doxygen-doc
else
	@echo "doxygen documentation not available! Sorry."
endif

sphinx-doc:
if PYTHON_CMD_USE
if HAVE_PYMOD_sphinx
	$(MAKE) -C doc sphinx-doc
else
	@echo "  Can't build documentation with Sphinx, python has no module sphinx!"
endif
else
	@echo "  Can't build documentation with Sphinx, python command not found!"
endif

web-html:
if PYTHON_CMD_USE
if HAVE_PYMOD_sphinx
	$(MAKE) -C doc web-html
else
	@echo "  Can't build web site with Sphinx, python has no module sphinx!"
endif
else
	@echo "  Can't build web site with Sphinx, python command not found!"
endif

install-doxygen:
if DX_COND_doc
	$(MAKE) -C doc install-doxygen
else
	@echo "install doxygen documentation not available! Sorry."
endif

install-vpi:
if USE_VERILOG
	$(MAKE) -C src install-vpi
else
	@echo "install vpi module not available! Sorry."
endif

check-versions.out: check-versions.sh
	./check-versions.sh > check-versions.out

all-local: check-versions.out

.PHONY: doxygen-doc sphinx-doc web-html install-doxygen install-vpi

