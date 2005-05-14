#warning! this Makefile requied installed NSIS ( see http://nullsoft.com for detail)
#unix users should just ignore this file

NSIS="C:/Program Files/NSIS/makensis.exe"
CPP=cpp
configway=WINDOWS

all: avinfo.nsi ../src/avinfo.exe
	$(NSIS) avinfo.nsi >nsislog
	mv *.exe ..

avinfo.nsi: avinfo.nsi.p
	$(CPP) avinfo.nsi.p >avinfo.nsi

