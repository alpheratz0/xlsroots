#include <stdio.h>
#include <xcb/xcb.h>
#include <xcb/xproto.h>

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
	xlsroots();
	return 0;
}
