//			PROBLEM 1 CODE  
//
//#include <iostream>
//#include <string>
//
//template<class num>
//void print(const num& i)
//{
//	std::cout << i << std::endl;
//} 
//int main()
//{
//	print(1);
//	print(2.345f);
//	print("Hello World");
//
//	return 0;
//}


//							PROBLEM 2 CODE
//#include <iostream>
//#include <string>
//
//template<class m_vec>
//class vector2D
//{
//public:
//
//	m_vec x, y;
//
//	vector2D(const m_vec& xi, const m_vec& yi) : x(xi), y(yi)
//	{}
//
//	void print()
//
//	{
//
//		std::cout << x << " " << y << std::endl;
//
//	}
//
//};
//
//
//int main()
//{
//
//	vector2D<int> i_vec(1, 3);
//	vector2D<float> f_vec(1.5f, 3.5f); 
//
//	i_vec.print();
//	f_vec.print();
//
//	return 0;
//}


#include <GLFW/glfw3.h>
#include <cstring> 
#include <algorithm>
#include <math.h>
#include <vector>

const int width = 640;   const int height = 480;

float* pixels = new float[width*height * 3];

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(i, j, red, green, blue);
	}
} 

bool isInsideCircleCorsmall(double xcor, double ycor, double x, const double y)
{
	const double r = 20;
	const double f = (x - xcor)*(x - xcor) + (y - ycor)*(y - ycor) - r * r;
	if (f < 60 && f > -60) return true;
	else return false;
}



void drawrec(int a, int b, int c, int d)
{

	drawLine(a, d, b, d, 1.0f, 0.0f, 0.0f);
	drawLine(a, c, b, c, 1.0f, 0.0f, 0.0f);
	for (int i = c; i < d; i++)
	{
		drawPixel(a, i, 1.0f, 0.0f, 0.0f );
	}
	for (int i = c; i < d; i++)
	{
		drawPixel(b, i, 1.0f, 0.0f, 0.0f );
	}
}


class Box // NO PARENT
{
public:
	int a, b, c, d; 
	void draw()
	{
		a = 50; b = 100; c = 100; d = 200;
		drawrec(a, b, c, d);
	} 
};

class Circle // NO PARENT
{
public:
	int cx, cy;
	void draw()
	{
		cx = 210; cy = 350;
		for (int x = 0; x < 640; x++) for (int y = 0; y < 480; y++)
		{
			if (isInsideCircleCorsmall(cx, cy, x, y) == true)
			{
				drawPixel(x, y, 1.0f, 0.0f, 0.0f);
			}
		}
	}
};
 

class GeometricObjectInterface
{
public:
	virtual void draw() = 0;

};

template <class operation>
class GeometricObject : public GeometricObjectInterface
{
public:
	void draw()
	{
	operation op_object;
	op_object.draw();
	}
};

int main(void)
{
	GLFWwindow* window;
	if (!glfwInit())return -1; window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	std::fill_n(pixels, width*height * 3, 1.0f);

	double xpos, ypos;

	 
		std::vector<GeometricObjectInterface*> obj_list;
		obj_list.push_back(new GeometricObject<Box>);
		obj_list.push_back(new GeometricObject<Circle>);
		 

	 
	while (!glfwWindowShouldClose(window))
	{
		


		for (auto itr : obj_list)
			itr->draw();

		 

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	delete[] pixels;
	return 0;
}
