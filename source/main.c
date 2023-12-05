#include <float.h>
#include <limits.h>
#include <GL/glew.h>

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION
#define NK_KEYSTATE_BASED_INPUT
#include "../external/nuklear.h"
#include "../external/nuklear_glfw_gl3.h"


static void error_callback(int e, const char *d)
{printf("Error %d: %s\n", e, d);}

/* ===============================================================
 *
 *                          CUSTOMER
 *
 * ===============================================================*/
struct date{
    int month;
    int day;
    int year;
};

struct account {
	int acct_no;
	char name[100];
	char mobile_no[30];
	char street[100];
	char city[100];
	float oldbalance;
	float newbalance;
	float payment;
	struct date paymentdate;
} customer;

static void customer_window(struct nk_context *ctx)
{
	if (nk_begin(ctx, "Create Customer", nk_rect(50, 50, 400, 400), NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_CLOSABLE)) {
		nk_layout_row_dynamic(ctx, 30, 2);
		
		nk_label(ctx, "Account No:", NK_TEXT_LEFT);
		nk_property_int(ctx, "#Account No:", INT_MIN, &customer.acct_no, INT_MAX, 1, 1);
		
        nk_label(ctx, "Name:", NK_TEXT_LEFT);
		nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, customer.name, sizeof(customer.name), nk_filter_default);
		
		nk_label(ctx, "Mobile No:", NK_TEXT_LEFT);
		nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, customer.mobile_no, sizeof(customer.mobile_no), nk_filter_default);
		
		nk_label(ctx, "Street:", NK_TEXT_LEFT);
		nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, customer.street, sizeof(customer.street), nk_filter_default);
		
		nk_label(ctx, "City:", NK_TEXT_LEFT);
		nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, customer.city, sizeof(customer.city), nk_filter_default);

        nk_label(ctx, "Old Balance:", NK_TEXT_LEFT);
        nk_property_float(ctx, "#Old Balance:", FLT_MIN, &customer.oldbalance, FLT_MAX, 1, 1);

        nk_label(ctx, "New Balance:", NK_TEXT_LEFT);
        nk_property_float(ctx, "#New Balance:", FLT_MIN, &customer.newbalance, FLT_MAX, 1, 1);

        nk_label(ctx, "Payment:", NK_TEXT_LEFT);
        nk_property_float(ctx, "#Payment:", FLT_MIN, &customer.payment, FLT_MAX, 1, 1);

		// Add more fields as needed...
		
		if (nk_button_label(ctx, "Submit")) {
			// Handle form submission...
			printf("Account No: %d\n", customer.acct_no);
			printf("Name: %s\n", customer.name);
			printf("Mobile No: %s\n", customer.mobile_no);
			printf("Street: %s\n", customer.street);
			printf("City: %s\n", customer.city);
            printf("Old Balance: %.2f\n", customer.oldbalance);
            printf("New Balance: %.2f\n", customer.newbalance);
            printf("Payment: %.2f\n", customer.payment);
			// Print more fields as needed...
		}
	}
	nk_end(ctx);
}

int main(void)
{
    /* GLFW */
    struct nk_glfw glfw = {0};
    static GLFWwindow *win;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) 
    {fprintf(stdout, "[GFLW] failed to init!\n");exit(1);}
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    /* Platform */
    /* Get screen size */
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    int win_width = mode->width;
    int win_height = mode->height;
    win = glfwCreateWindow(win_width, win_height, "BillHub", NULL, NULL);
    glfwMakeContextCurrent(win);

    /* Glew */
    glewExperimental = 1;
    if (glewInit() != GLEW_OK) 
    {fprintf(stderr, "Failed to setup GLEW\n");exit(1);}

	/* create context */
    struct nk_context *ctx = nk_glfw3_init(&glfw, win, NK_GLFW3_INSTALL_CALLBACKS);

    {struct nk_font_atlas *atlas;
    nk_glfw3_font_stash_begin(&glfw, &atlas);
    nk_glfw3_font_stash_end(&glfw);}

    while (!glfwWindowShouldClose(win))
    {
        /* Input */
        glfwPollEvents();
        nk_glfw3_new_frame(&glfw);

        /* GUI */
        customer_window(ctx);

        /* Draw */
        glViewport(0, 0, win_width, win_height);
        glClear(GL_COLOR_BUFFER_BIT);
        nk_glfw3_render(&glfw, NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
        glfwSwapBuffers(win);
    }
    nk_glfw3_shutdown(&glfw);
    glfwTerminate();
    return 0;
}