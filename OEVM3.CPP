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

	// printf("max mode: %s\n", getmodename(getmaxmode()));
	// printf("cur mode: %s\n", getmodename(getgraphmode()));
	// printf("max x: %d, max y: %d\n", getmaxx(), getmaxy());

	int screen_center_x, screen_center_y;
	screen_center_x = (getmaxx() + 1) / 2;
	screen_center_y = (getmaxy() + 1) / 2;

	struct windowParams {
		int x1, y1, x2, y2;
	} window;
	window.x1 = 0;
	window.y1 = 0;
	window.x2 = getmaxx();
	window.y2 = getmaxy();
	
	setviewport (window.x1, window.y1, window.x2, window.y2, 1);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 0);

	int pixelspery = 40, pixelsperx = 20;
	int graphic_zero_x, graphic_zero_y, graphic_end_x, graphic_end_y;
	graphic_zero_x = window.x1 + 15;
	graphic_zero_y = window.y2 - 75;
	graphic_end_x = window.x2 - 15;
	graphic_end_y = window.y1 + 15;

	// lines
	setlinestyle (SOLID_LINE, 0, NORM_WIDTH);
	setwritemode(0);
	line(graphic_zero_x, graphic_zero_y, graphic_end_x, graphic_zero_y);
	line(graphic_zero_x, graphic_zero_y, graphic_zero_x, graphic_end_y);


	float dx = M_PI_2/pixelsperx;
	float maxx, maxy = 0;
	
	int x_ = graphic_zero_x;
	float y = 0;
	for (float x = 3*M_PI_2; x <= 16*M_PI; x=x+dx, ++x_)
	{
		y = f(x);
		putpixel(x_,graphic_zero_y-int(y*pixelspery),4);
		if (y>maxy) {
			maxy = y;
			maxx = x;
		}
	}

	char str[12];
	for (int i = 0; i*pixelspery < (graphic_zero_y - graphic_end_y); ++i)
	{
		line(graphic_zero_x, graphic_zero_y-i*pixelspery, graphic_zero_x-2, graphic_zero_y-i*pixelspery);
		sprintf(str, "%d", i);
		outtextxy(graphic_zero_x-10, graphic_zero_y-2-i*pixelspery, str);
	}
	for (int j = 0; j*pixelsperx < (graphic_end_x - graphic_zero_x); ++j)
	{
		if (j % 2) {
			line(graphic_zero_x+j*pixelsperx, graphic_zero_y, graphic_zero_x+j*pixelsperx, graphic_zero_y+2);
			sprintf(str, "%dpi", (3+j)/2);
			outtextxy(graphic_zero_x-10+j*pixelsperx, graphic_zero_y+5, str);
		}
		else {
			line(graphic_zero_x+j*pixelsperx, graphic_zero_y, graphic_zero_x+j*pixelsperx, graphic_zero_y+12);
			sprintf(str, "%dpi", 3+j);
			outtextxy(graphic_zero_x-12+j*pixelsperx, graphic_zero_y+15, str);
			outtextxy(graphic_zero_x-10+j*pixelsperx, graphic_zero_y+23, "/2");
		}		
	}
	sprintf(str, "y = %.5f", maxy);
	int maxx_ = int((maxx-3*M_PI_2)/M_PI_2*pixelsperx), maxy_ = int(maxy*pixelspery);
	circle(graphic_zero_x+maxx_,graphic_zero_y-maxy_,1);
	outtextxy(graphic_zero_x+maxx_,graphic_zero_y-maxy_-15,str);

	getch();
	setfillstyle(SOLID_FILL, 5);
	setviewport (screen_center_x - 100, screen_center_y - 20, screen_center_x + 100, screen_center_y + 20, 1);
	rectangle(0,0,200,40);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	outtextxy(100,20,str);



	getch();
	closegraph();
	return 0;
}
