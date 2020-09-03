CXX=gcc

SRCDIR=.
OBJDIR=.

_INCDIRS=../include \
				 ../../wmmwrapper/include \
				 ../../wmmwrapper/wmm2015_src/src \
				 ../../jsmn \
				 ../../../include

INCDIRS=$(addprefix -I,$(_INCDIRS))

_LIBDIRS=../lib \
				 ../../wmmwrapper/lib \
				 ../../../lib

LIBDIRS=$(addprefix -L,$(_LIBDIRS))

_LIBS=ss ww m sofa_c
LIBS=$(addprefix -l,$(_LIBS))

CXXFLAGS=-O3 -Wall $(INCDIRS)

_COMMA=,
_RPATHS=$(addprefix -Wl$(_COMMA)-rpath$(_COMMA),$(_LIBDIRS))
LDFLAGS=-O3 $(INCDIRS) $(LIBDIRS) $(_RPATHS) $(LIBS)

_SRCFILES=matrixThreeVectorTest.c \
					stringParserTest.c

SRCS=$(addprefix $(SRCDIR)/,$(_SRCFILES))

_OBJFILES=$(_SRCFILES:%.c=%.o)
OBJS=$(addprefix $(OBJDIR)/,$(_OBJFILES))

EXES=$(_SRCFILES:%.c=%.exe)

all: $(EXES)

%.exe : $(OBJDIR)/%.o
	$(CXX) $< -o $@ $(LDFLAGS)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CXX) $< -c -o $@ $(CXXFLAGS)

.SECONDARY: $(OBJS)
.PHONY: clean

clean:
	rm $(OBJDIR)/*.o
	rm *.exe
