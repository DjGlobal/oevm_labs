#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>

struct plotParams {
	int zero_x, zero_y, end_x, end_y, pixelspery, pixelsperx;
};

float f(float x) {
	return pow(sin(x/2),3)+sqrt(x);
}

void drawPlotBase(struct plotParams &plot) {
	// lines
	setlinestyle (SOLID_LINE, 0, NORM_WIDTH);
	setwritemode(0);
	line(plot.zero_x, plot.zero_y, plot.end_x, plot.zero_y);
	line(plot.zero_x, plot.zero_y, plot.zero_x, plot.end_y);

	// numbers
	settextjustify(RIGHT_TEXT, CENTER_TEXT);
	char str[12];
	for (int i = 0; i*plot.pixelspery < (plot.zero_y - plot.end_y); ++i)
	{
		line(plot.zero_x, plot.zero_y-i*plot.pixelspery, plot.zero_x-2, plot.zero_y-i*plot.pixelspery);
		sprintf(str, "%d", i);
		outtextxy(plot.zero_x-2, plot.zero_y-i*plot.pixelspery, str);
	}
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	for (int j = 0; j*plot.pixelsperx < (plot.end_x - plot.zero_x); ++j)
	{
		if (j % 2) {
			// если нечетноё количество j*pi/2 (а вместе с ещё 3*pi/2 чётное), сокращаем до (j+3)/2*pi
			line(plot.zero_x+j*plot.pixelsperx, plot.zero_y, plot.zero_x+j*plot.pixelsperx, plot.zero_y+2);
			sprintf(str, "%dpi", (3+j)/2);
			outtextxy(plot.zero_x+j*plot.pixelsperx, plot.zero_y+6, str);
		}
		else {
			line(plot.zero_x+j*plot.pixelsperx, plot.zero_y, plot.zero_x+j*plot.pixelsperx, plot.zero_y+12);
			sprintf(str, "%dpi", 3+j);
			outtextxy(plot.zero_x+j*plot.pixelsperx, plot.zero_y+16, str);
			outtextxy(plot.zero_x+j*plot.pixelsperx, plot.zero_y+24, "/2");
		}		
	}
}

int main()
{
	int graph_driver;
	int graph_mode;
	int graph_error_code;
	graph_driver = DETECT;
	// инициализация граф. интерфейса. Драйвер определить автоматически
	initgraph(&graph_driver, &graph_mode, "c:\\a\\bc" ); 

	graph_error_code = graphresult( ); 
	// получаем статус работы графического режима
	if(graph_error_code != grOk)
	{
		// если произошла ошибка, выведем её описание на экран
		printf("%s\n", grapherrormsg(graph_error_code));
		getch();
		// дождёмся нажатия клавиши и закроем программу с кодом ошибки
		return 255;
	}

	int screen_center_x, screen_center_y;
	screen_center_x = (getmaxx() + 1) / 2;
	screen_center_y = (getmaxy() + 1) / 2;
	// Середина экрана: получаем значение последнего пикселя (количество пикселей - 1)
	// Прибавляем 1, получаем чётное число, делим, получаем пиксель чуть правее и ниже центра

	// структура для хранения координат окна. Можно и просто четыре переменных ввести, на практике пользы не было

	struct windowParams {
		int x1, y1, x2, y2;
	} window;
	window.x1 = 0;
	window.y1 = 0;
	window.x2 = getmaxx();
	window.y2 = getmaxy();
	// делаем окно на весь экран
	
	setviewport (window.x1, window.y1, window.x2, window.y2, 1);
	// последний параметр — обрезать ли то, что не вмещается в окно
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 0);
	// шрифт — беззасечковый, направление текста горизонтальное, а размер не помню как и что

	
	int graphic_zero_x, graphic_zero_y, graphic_end_x, graphic_end_y;
	
	plotParams plot;
	// устанавливаем координаты и масштаб графика
	// pixelspery пикселей на экране занимает один шаг по y (1), pixelsperx — один шаг по x (pi/2)
	plot.zero_x = window.x1 + 20;
	plot.zero_y = window.y2 - 30;
	plot.end_x = window.x2 - 20;
	plot.end_y = window.y1 + 20;
	plot.pixelspery = 40;
	plot.pixelsperx = 20;

	drawPlotBase(plot);
	float dx = M_PI_2/plot.pixelsperx;
	float maxx, maxy = 0;
	
	int x_ = plot.zero_x;
	float y = 0;
	for (float x = 3*M_PI_2; x <= 16*M_PI; x=x+dx, ++x_)
	{
		y = f(x);
		putpixel(x_,plot.zero_y-int(y*plot.pixelspery),4);
		if (y>maxy) {
			maxy = y;
			maxx = x;
		}
	}

	// выводим наибольшее значение функции
	char str[12];
	sprintf(str, "y = %.5f", maxy);
	// ищём точку на графике, соотв-ю максимум функции
	int maxx_ = int((maxx-3*M_PI_2)/M_PI_2*plot.pixelsperx), maxy_ = int(maxy*plot.pixelspery);
	// рисуем в ней белую окружность с радиусом в пиксель
	circle(plot.zero_x+maxx_,plot.zero_y-maxy_,1);
	// текст по левому краю
	settextjustify(LEFT_TEXT, CENTER_TEXT);
	// выводим над точкой значение ф-ии
	outtextxy(plot.zero_x+maxx_,plot.zero_y-maxy_-15,str);

	getch();

	// новое окно
	setfillstyle(SOLID_FILL, 5);
	setviewport (screen_center_x - 100, screen_center_y - 20, screen_center_x + 100, screen_center_y + 20, 1);
	// прямоугольник по периметру
	rectangle(0,0,200,40);
	// текст по центру
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	// выводим значение ф-ии посередине
	outtextxy(100,20,str);

	getch();
	// выходим из графического режима
	closegraph();
	return 0;
}