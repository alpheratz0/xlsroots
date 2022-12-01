/*
	Copyright (C) 2022 <alpheratz99@protonmail.com>

	This program is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License version 2 as published by the
	Free Software Foundation.

	This program is distributed in the hope that it will be useful, but WITHOUT ANY
	WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
	FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along with
	this program; if not, write to the Free Software Foundation, Inc., 59 Temple
	Place, Suite 330, Boston, MA 02111-1307 USA

*/

#include <stdio.h>
#include <stdlib.h>
#include <xcb/xcb.h>
#include <xcb/xproto.h>
#include <stdarg.h>

static void
die(const char *fmt, ...)
{
	va_list args;

	fputs("xlsroots: ", stderr);
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	fputc('\n', stderr);
	exit(1);
}

static void
version(void)
{
	puts("xlsroots version "VERSION);
	exit(0);
}

static void
xlsroots(void)
{
	xcb_connection_t *conn;
	const xcb_setup_t *setup;
	xcb_screen_iterator_t iter;

	conn = xcb_connect(NULL, NULL);
	setup = xcb_get_setup(conn);
	iter = xcb_setup_roots_iterator(setup);

	for (; iter.rem > 0; xcb_screen_next(&iter))
		printf("0x%x\n", iter.data->root);

	xcb_disconnect(conn);
}

int
main(int argc, char **argv)
{
	while (++argv, --argc > 0) {
		if ((*argv)[0] == '-' && (*argv)[1] != '\0' && (*argv)[2] == '\0') {
			switch ((*argv)[1]) {
				case 'v': version(); break;
				default: die("invalid option %s", *argv); break;
			}
		} else {
			die("unexpected argument: %s", *argv);
		}
	}

	xlsroots();

	return 0;
}
