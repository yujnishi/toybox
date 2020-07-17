srcs=$(wildcard src/*)

noext0=$(srcs)
noext1=$(noext0:.c=)
noext2=$(noext1:.sh=)
noext3=$(noext2:.pl=)
noext=$(noext3)

bins=$(patsubst src/%,bin/%,$(noext))


.PHONY: all clean

all: myutils.rpm

myutils.spec: $(bins)

bin/%: src/%.c
	$(CC) $(CFLAGS) -o $@ $^

bin/%: src/%.sh
	cp $^ $@
	chmod +x $@

bin/%: src/%.pl
	cp $^ $@
	chmod +x $@

%.rpm: %.spec
	rm -rf build
	rpmbuild --define="_topdir $(PWD)" --define="_builddir $(PWD)" --define="_buildrootdir $(PWD)/build" --define="_sourcedir ." --define="_specdir ." --define="_srcrpmdir ." --define="_rpmdir rpm" --define="debug_package %{nil}" -bb $^
	mv rpm/x86_64/*.rpm $@
	rmdir build
	rmdir rpm/x86_64
	rmdir rpm

clean:
	rm -f myutils.rpm $(bins)
