# Support library Makefile.am for building a BEEBS benchmark
#
# Copyright (C) 2018 Embecosm Limited
#
# Contributor: Jeremy Bennett <jeremy.bennett@embecosm.com>
#
# This file is part of the Bristol/Embecosm Embedded Benchmark Suite.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# SPDX-License-Identifier: GPL-3.0-or-later

ROOT = README
SRC = $(srcdir)/$(ROOT).adoc
SRC_STRIPPED = $(builddir)/$(ROOT)-stripped.adoc

.PHONY: all
all: pdf html docbook latex

.PHONY: pdf
pdf: $(builddir)/$(ROOT).pdf

$(builddir)/$(ROOT).pdf: sanity-check $(SRC)
	asciidoctor-pdf -a imagesdir=images -d article $(SRC) -o $@

.PHONY: html
html: $(builddir)/$(ROOT).html

$(builddir)/$(ROOT).html: sanity-check $(SRC)
	asciidoctor -a imagesdir=${srcdir}/images -d article -b html \
	    $(SRC) -o $@

.PHONY: docbook
docbook: $(builddir)/$(ROOT).docbook

$(builddir)/$(ROOT).docbook: sanity-check $(SRC)
	asciidoctor -a imagesdir=${srcdir}/images -d article -b docbook \
	    $(SRC) -o $@

$(builddir)/$(ROOT).latex: sanity-check $(SRC)
	asciidoctor -a imagesdir=${srcdir}/images -d article -b latex \
	    $(SRC) -o $@

# It is all too easy for the document history and title page to have diverging
# version numbers.  This target checks first.

.PHONY: sanity-check
sanity-check:
	@s=$$(sed -n < $(SRC) -e '3s/Issue //p') ; \
	t=$$(sed -n < $(SRC) -e "/== Document history/,/^$$/p" | \
	           grep -c "$${s}") ; \
	if [ $${t} -ne 1 ] ; \
	then \
	    echo "Version number of title and document history do not match" ; \
	    exit 1 ; \
	fi

$(builddir)/custom.dict: $(srcdir)/custom.wordlist
	aspell --lang=en create master ./$@ < $<

.PHONY: spell
spell: $(builddir)/custom.dict $(SRC)
	sed < $(SRC) > $(SRC_STRIPPED) -e 's/`[^`]\+`//gp' -e '/^----$$/,/^----$$/d'
	aspell --master=en_US --mode=none \
	    --add-extra-dicts=$(builddir)/custom.dict \
	    -c $(SRC_STRIPPED)
	$(RM) $(SRC_STRIPPED)

clean:
	$(RM) $(SRC_STRIPPED) $(builddir)/$(ROOT).pdf $(builddir)/$(ROOT).html \
	      $(builddir)/$(ROOT).docbook $(builddir)/$(ROOT).latex \
	      $(builddir)/custom.dict
