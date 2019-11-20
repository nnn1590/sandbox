.PHONY: all
all: get-color-xlib  get-screenshot-xlib-libpng

get-color-xlib: get-color-xlib.cpp
	$(CXX) -o get-color-xlib get-color-xlib.cpp -lX11

get-screenshot-xlib-libpng: get-screenshot-xlib-libpng.cpp
	$(CXX) -o get-screenshot-xlib-libpng get-screenshot-xlib-libpng.cpp -lX11 -lpng

.PHONY: clean
clean:
	rm -f get-color-xlib get-screenshot-xlib-libpng
