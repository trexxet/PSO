#include "Window.h"


void Window::proceedGUI () {
	if (nk_begin (nk_ctx, "Main GUI", nk_rect (0, 0, 200, 600), NK_WINDOW_NO_SCROLLBAR)) {

	};
	nk_end (nk_ctx);
}
