#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

namespace Points {
	struct Point {
		int x;
		int y;
	};
	void readPoint(Point& p) {
		cin >> p.x >> p.y;
	}
	void printPoint(const Point& p) {
		cout <<"(" << p.x<<", " << p.y<< ") ";
	}
	double getDist(const Point& p1, const Point& p2) {
		int dx = p1.x - p2.x;
		int dy = p1.y - p2.y;
		return sqrt(dx * dx + dy * dy);
	}
}
namespace Figures {
	using namespace Points;
	struct Sides {
		int a;
		int b;
		int c;
	};
	constexpr int NAME_LENGTH = 20;
	struct Triangle {
		char name[NAME_LENGTH];
		Point p1;
		Point p2;
		Point p3;
		Sides side;
	};
	double getPer(const Triangle& tr) {

		return tr.side.a + tr.side.b + tr.side.c;
	}
	double getArea(const Triangle& tr) {

		double halfPer = getPer(tr) / 2;
		return sqrt(halfPer * (halfPer - tr.side.a) * (halfPer - tr.side.b) *(halfPer - tr.side.c));
	}
	void sort(Triangle* triangle, int size, double (*calcMetric)(const Triangle&)) {
		double* areas = new double[size];
		for (int i = 0; i < size; i++) {
			areas[i] = calcMetric(triangle[i]);
		}
		for (int i = 0; i < size - 1; i++) {
			int minIndex = i;
			for (int j = i + 1; j < size; j++) {
				if (areas[j] > areas[minIndex]) {
					minIndex = j;
				}
			}
			if (minIndex != i) {
				std::swap(areas[i], areas[minIndex]);
				std::swap(triangle[i], triangle[minIndex]);
			}
		}
		delete[] areas;
	}
	void computeSides(Triangle& tr) {
		tr.side.a = getDist(tr.p1, tr.p2);
		tr.side.b = getDist(tr.p2, tr.p3);
		tr.side.c = getDist(tr.p1, tr.p3);
	}
	void readTriangle(Triangle& tr) {
		readPoint(tr.p1);
		readPoint(tr.p2);
		readPoint(tr.p3);
		computeSides(tr);
	}
	void printTriangle(const Triangle& tr) {
		cout << tr.name << " ";
		printPoint(tr.p1);
		printPoint(tr.p2);
		printPoint(tr.p3);
		cout << endl;
	}
}
/*
3
0 0 5 0 2 4
0 0 3 0 0 2
0 0 10 0 0 1
*/
/*
3
0 0 5 0 2 4  - Triangle 1 per=14.47, area = 10
0 0 3 0 0 2  - Triangle 2 per=8.61, area = 3
0 0 10 0 0 1 - Triangle 3 per=21.05, area = 5
*/

int main() {
	
	int n;
	cin >> n;
	Figures::Triangle* triangle = new Figures::Triangle[n];
	for (int i = 0; i < n; i++) {
		Figures::readTriangle(triangle[i]);
		char id[20];
		_itoa(i + 1, id, 10);
		strcpy(triangle[i].name, "Triangle ");
		strcat(triangle[i].name, id);
	}
	Figures::sort(triangle, n,Figures::getPer);
	for (size_t i = 0; i < n; i++)
	{
		Figures::printTriangle(triangle[i]);
	}
	delete[] triangle;
}