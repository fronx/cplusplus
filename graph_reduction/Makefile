BOOST_VERSION = 1_55_0
BOOST_DIR = boost_$(BOOST_VERSION)
BOOST_PKG = $(BOOST_DIR).tar.bz2
BOOST_URL = http://downloads.sourceforge.net/project/boost/boost/1.55.0/$(BOOST_PKG)

CC=g++

graph_reduction: graph_reduction.cpp deps
	$(CC) graph_reduction.cpp -o $@ -I./include -v

.PHONY: deps

deps: include/boost

include/boost: include/$(BOOST_DIR)
	cd include && ln -s $(BOOST_DIR)/boost boost

include/$(BOOST_DIR): include/$(BOOST_PKG)
	cd include && tar --bzip2 -xf $(BOOST_PKG)
	touch $@

include/$(BOOST_PKG):
	cd include && wget -O $(BOOST_PKG) $(BOOST_URL)

clean:
	rm -rf graph_reduction
