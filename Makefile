
all: build # build2 build3

time:
	/usr/bin/ntpdate -b -s -u pool.ntp.org

publish: clean
	python setup.py sdist upload

clean: cpp-clean
	rm -rf Adafruit_BBIO.* build dist
	rm -f *.pyo
	rm -f *.egg
	rm -f overlays/*.pyo overlays/*.pyc

tests:
	py.test

build:
	python setup.py build --force

install: build
	python setup.py install --force

build2:
	python2 setup.py build --force

install2: build2
	python2 setup.py install --force

build3:
	python3 setup.py build --force

install3: build3
	python3 setup.py install --force

configure: configure.ac
	rm -f configure && \
	autoreconf --install -I m4

build/Makefile: configure
	mkdir -p build && \
	cd build && \
	../configure

cpp: build/Makefile
	cd build && \
	$(MAKE)

cpp-clean:
	rm -rf \
	 aclocal.m4 \
	 autom4te.cache/ \
	 build/ \
	 config.h.in \
	 configure \
	 Makefile.in \
	 source/Makefile.in \
	 m4/libtool.m4 \
	 m4/lt~obsolete.m4 \
	 m4/ltoptions.m4 \
	 m4/ltsugar.m4 \
	 m4/ltversion.m4

format:
	for mask in '*.h' '*.c' '*.cpp'; do find . -name $$mask -exec clang-format -i {} \+; done

.PHONY: all clean
.PHONY: tests
.PHONY: build  install
.PHONY: build2 install2
.PHONY: build3 install3
.PHONY: cpp cpp-clean
