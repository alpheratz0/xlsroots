.POSIX:
.PHONY: all clean install uninstall dist

include config.mk

all: xlsroots

xlsroots: xlsroots.o
	$(CC) $(LDFLAGS) -o xlsroots xlsroots.o $(LDLIBS)

clean:
	rm -f xlsroots xlsroots.o xlsroots-$(VERSION).tar.gz

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f xlsroots $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/xlsroots
	mkdir -p $(DESTDIR)$(MANPREFIX)/man1
	cp -f xlsroots.1 $(DESTDIR)$(MANPREFIX)/man1
	chmod 644 $(DESTDIR)$(MANPREFIX)/man1/xlsroots.1

dist: clean
	mkdir -p xlsroots-$(VERSION)
	cp -R COPYING config.mk Makefile README xlsroots.1 xlsroots.c xlsroots-$(VERSION)
	tar -cf xlsroots-$(VERSION).tar xlsroots-$(VERSION)
	gzip xlsroots-$(VERSION).tar
	rm -rf xlsroots-$(VERSION)

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/xlsroots
	rm -f $(DESTDIR)$(MANPREFIX)/man1/xlsroots.1
