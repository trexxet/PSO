#include "Window.h"
#define _GNU_SOURCE
#include <cstdio>


void Window::proceedGUI () {
	if (nk_begin (nk_ctx, "Main GUI", nk_rect (0, 0, 200, 600), NK_WINDOW_NO_SCROLLBAR)) {
		// Function selector
		nk_layout_row_dynamic (nk_ctx, 30, 2);
		nk_label (nk_ctx, "Function:", NK_TEXT_LEFT);
		selectedFunction = (size_t) nk_combo (nk_ctx, (const char**) funcNameList, (int) Function::getListSize (),
		                                      (int) selectedFunction, 30, nk_vec2 (100, 80));

		nk_layout_row_dynamic (nk_ctx, 30, 1);
		nk_label_wrap (nk_ctx, functions[selectedFunction].str_repr.c_str ());
		if (nk_button_label (nk_ctx, "Calculate function"))
			changeFunction ();

		char *maxval_str = nullptr;
		asprintf (&maxval_str, "Visualized maximum: %.2f", canvas->max_val);
		nk_label (nk_ctx, maxval_str, NK_TEXT_LEFT);
		free (maxval_str);
		nk_slider_float (nk_ctx, 0.1f, &(canvas->max_val), 2.f, 0.01f);
	};
	nk_end (nk_ctx);
}
