CC=g++

# Optimized:
#CXXFLAGS=-Wall -Wextra -pedantic -Werror -std=c++17 -O3

# For debugging:
CXXFLAGS=-Wall -Wextra -pedantic -Werror -std=c++17 -g -O0

sources=$(wildcard src/*.cpp)
objects=$(sources:src/%.cpp=obj/%.o)
headers=$(wildcard src/*.hpp)
precompiledheader=obj/stdafx.h.gch
executable=output/neural
resourcesrc=$(shell find resources/ -type f)
resourcedest=$(resourcesrc:resources/%=output/%)

# "|" signals an order-only prerequisite: the prereq must exist, but
# it won't cause the target to be recreated.
$(executable): $(precompiledheader) $(objects) Makefile | obj output $(resourcedest)
	$(CC) $(CXXFLAGS) -o $(executable) \
	$(objects)

$(resourcedest) : output/% : resources/% | output
	mkdir -p $(dir $@);
	cp -r $< $@;

obj output:
	if [ ! -e $@ ]; then mkdir $@; fi;

reformat:
	for file in $(sources) $(headers); do \
		clang-format -i -style="$$(<style)" "$$file"; \
	done;

# Static pattern rules. Take each object in the targets, create a "base"
# with it specified by % (removing the literal part '.o'), then
# use that base to generate the prerequisite. This generates
# several rules.  For instance,  main.o : "main".o : "main".cpp
# then refer to the left-most prerequisite with $<, and the target
# with $@ like usual.
$(objects) : obj/%.o : src/%.cpp $(headers) $(precompiledheader) Makefile | obj
	$(CC) -c $(CXXFLAGS) \
	$< -o $@

$(precompiledheader) : src/stdafx.hpp Makefile | obj
	$(CC) $(CXXFLAGS) $< -o $@

clean :
	rm -rf obj output

echo :
	@echo sources $(sources)
	@echo objects $(objects)
	@echo headers $(headers) src/stdafx.hpp
	@echo executable $(executable)
	@echo resourcesrc $(resourcesrc)
	@echo resourcedest $(resourcedest)

.PHONY : echo clean reformat
