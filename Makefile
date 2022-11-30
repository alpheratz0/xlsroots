.POSIX:
.PHONY: clean install uninstall

xlsroots: xlsroots.c
	cc xlsroots.c -o xlsroots -lxcb

clean:
	rm -f xlsroots

install: xlsroots
	cp xlsroots /usr/local/bin

uninstall:
	rm -f /usr/local/bin/xlsroots
