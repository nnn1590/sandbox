CXXFLAGS = -O3

.PHONY: all
all: get-color-xlib  get-screenshot-xlib-libpng

get-color-xlib: get-color-xlib.cpp
	$(CXX) $(CXXFLAGS) get-color-xlib.cpp -lX11 -o get-color-xlib

get-screenshot-xlib-libpng: get-screenshot-xlib-libpng.cpp
	$(CXX) $(CXXFLAGS) get-screenshot-xlib-libpng.cpp -lX11 -lpng -o get-screenshot-xlib-libpng

.PHONY: clean
clean:
	rm -f get-color-xlib get-screenshot-xlib-libpng
