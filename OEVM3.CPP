#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>

float f(float x) {
	return pow(sin(x/2),3)+sqrt(x);
}

int main()
{
	int graph_driver;
	int graph_mode;
	int graph_error_code;
	graph_driver = DETECT;
	initgraph(&graph_driver, &graph_mode, "c:\\a\\bc" ); 
	graph_error_code = graphresult( ); 
	if(graph_error_code != grOk)
	{
		printf("%s\n", grapherrormsg(graph_error_code));
		getch();
		return 255;
	}

	printf("max mode: %s\n", getmodename(getmaxmode()));
	printf("cur mode: %s\n", getmodename(getgraphmode()));
	printf("max x: %d, max y: %d\n", getmaxx(), getmaxy());

	int screen_center_x, screen_center_y;
	screen_center_x = (getmaxx() + 1) / 2;
	screen_center_y = (getmaxy() + 1) / 2;

	struct windowParams {
		int x1, y1, x2, y2;
	} window;
	window.x1 = 0;
	window.y1 = 0;
	// window.x2 = screen_center_x;
	window.x2 = getmaxx();
	// window.y2 = screen_center_y;
	window.y2 = getmaxy();
	
	setviewport (window.x1, window.y1, window.x2, window.y2, 1);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 0);
	// outtext ("ty pidor");


	int graphic_zero_x, graphic_zero_y;
	graphic_zero_x = window.x1 + 10;
	graphic_zero_y = window.y2 - 10;

	// lines
	setlinestyle (SOLID_LINE, 0, NORM_WIDTH);
	setwritemode(0);
	line(graphic_zero_x, graphic_zero_y, window.x2-10, graphic_zero_y);
	line(graphic_zero_x, graphic_zero_y, graphic_zero_x, window.y1+10);

	float dx = M_PI_2/20;
	int x_, y_;
	int pixelspery = 40;
	x_ = graphic_zero_x;
	for (float x = 3*M_PI_2; x <= 16*M_PI; x=x+dx, ++x_)
	{
		// putpixel(x_,round(f(x)/20),16);
		// printf("x: %f, y: %f, x_: %d, y_: %d\n",x, f(x), x_, graphic_zero_y-int(f(x)*pixelspery));
		// getch();
		putpixel(x_,graphic_zero_y-int(f(x)*pixelspery),4);
	}
	// float dy = M_PI_2/20;
	 // 32 * 20px — x
	// 16 * 30px — y




	getch();
	closegraph();
	return 0;
}
