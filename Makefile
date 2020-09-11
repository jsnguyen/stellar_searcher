CXX=gcc

SRCDIR=src
OBJDIR=build

_INCDIRS=include \
				 ../jsmn \
				 /Users/jsn/programs/sofa/20200721/c/include

INCDIRS=$(addprefix -I,$(_INCDIRS))

_LIBDIRS=lib \
				 /Users/jsn/programs/sofa/20200721/c/lib

LIBDIRS=$(addprefix -L,$(_LIBDIRS))

_LIBS=m sofa_c
LIBS=$(addprefix -l,$(_LIBS))

CXXFLAGS=-O3 -Wall $(INCDIRS) -fPIC
LDFLAGS=-O3 -shared $(INCDIRS) $(LIBDIRS) $(LIBS)

_SRCFILES=threeVector.c \
					matrix.c \
					celestialTime.c \
					dateTime.c \
					stellarCoordinate.c \
					constellation.c \
					interpolate.c \
					parser.c

SRCS=$(addprefix $(SRCDIR)/,$(_SRCFILES))

_OBJFILES=$(_SRCFILES:%.c=%.o)
OBJS=$(addprefix $(OBJDIR)/,$(_OBJFILES))

LIBDIR=lib
LIB=libss.so

DIRGUARD=@mkdir -p $(@D)

all: $(LIBDIR)/$(LIB)

$(LIBDIR)/$(LIB) : $(OBJS)
	$(DIRGUARD)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(DIRGUARD)
	$(CXX) $< -c -o $@ $(CXXFLAGS)

.SECONDARY: $(OBJS)
.PHONY: clean

clean:
	rm $(OBJDIR)/*.o
	rm $(LIBDIR)/*.so
	rmdir $(OBJDIR) $(LIBDIR)
