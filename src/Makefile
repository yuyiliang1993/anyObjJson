cc = g++
output_dir=../bin
CPPFLAGS := -g -Wall -Werror
HPPFILES=../include/person.hpp
HPPFILES+=../include/serialize.hpp
CPPFLAGS += -std=c++17
MY_INCLUES = -I../include
CPPSRCS = $(wildcard *.cpp)
CPPOBJS = $(patsubst %.cpp,%.o,$(CPPSRCS))
TARGET= anyObjJson
all:$(TARGET)
$(TARGET):$(CPPOBJS) $(HPPFILES) 
	$(cc) $(CPPOBJS) -o $(output_dir)/$@ 
%.o:%.cpp
	$(cc) $(CPPFLAGS) $(MY_INCLUES) -c $< -o $@
./PHONY:clean
clean:
	rm -rf $(CPPOBJS) $(TARGET)
