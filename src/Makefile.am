## Makefile.am -- process this file with automake to produce Makefile.in
bin_PROGRAMS = avinfo
avinfo_SOURCES = avinfo.c common.c filecach.c mkv.c ogm.c readtpl.c riff.c statisti.c var.c\
                 codec.c confset.c ifo.c mpeg.c print.c report.c scan.c text.c ass.tab.c
CLEANFILES = ass.tab.c ass.tab.h ass.output

if NOBISON
ass.tab.c: ass.y
	cp ./nobison/ass.tab.c ./nobison/ass.tab.h .
else
ass.tab.c: ass.y
	$(BISON) -d -v ass.y && cp ./ass.tab.c ./ass.tab.h ./nobison
endif
