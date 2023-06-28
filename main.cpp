#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>


class point{
public:
	double x;
	double y;

	point(double a,double b){
		x = a;
		y = b;
	}
	~point(){
		free(this);
	}


};


int partition(int strt,int end,std::vector<point*> &v);
void quick_sort(int strt,int end,std::vector<point*> &v);

int num_points(std::vector<point*> &line,std::vector<point*> &graph_points);
std::vector<point*> best_line(std::vector<point*> &graph_points);

double doub_rand(int min,int max);

int main()
{
	 /* ?\n;||(or) e &&(and)*/

	srand(time(NULL));
	std::vector<point*> g;
	for(int i = 0;i < 30;i++){
		point *p = new point(i,doub_rand(0,100));
		g.push_back(p);
	}
	/*for(int i = 0;i < 30;i++){
		std::cout << g[i]->y << " ";
	}*/

	std::vector<point*> line = best_line(g);
	std::cout << line[0]->x << " " << line[0]->y << '\n';
	std::cout << line[1]->x << " " << line[1]->y << '\n';


	return 0;
}

double doub_rand(int min,int max){
	double r = (max-min)*((double)rand()/RAND_MAX) + min;
	return r;
}

int partition(int strt,int end,std::vector<point*> &v){

	int pivot = v[(strt+end)/2]->y;

	while(strt <= end){

		while(v[strt]->y < pivot){
			strt++;
		}
		while(v[end]->y > pivot){
			end--;
		}
		if(strt <= end){
			std::swap(v[strt],v[end]);
			//std::swap(v[strt]->x,v[end]->x);
			strt++;
			end--;
		}
	}
	return strt;
}

void quick_sort(int strt,int end,std::vector<point*> &v){

	int part = partition(strt,end,v);

	if(part-1 > strt){
		quick_sort(strt,part-1,v);
	}
	if(part < end){
		quick_sort(part+1,end,v);
	}

}

int num_points(std::vector<point*> &line,std::vector<point*> &graph_points){

	//given a line,count the quantity of points that intercepts this object in the graph

	//finding the equation:
	double m = (line[1]->y - line[0]->y)/line[1]->x - line[0]->x;
	double n = line[1]->y - m*line[1]->x;

	int c = 0;
	for(int i = 0;i < graph_points.size();i++){
		double x = graph_points[i]->x;
		double y = graph_points[i]->y;
		if(y == (m*y)+n){
			c++;
		}
	}
	return c;

}

std::vector<point*> best_line(std::vector<point*> &graph_points){

	/*The idea is to sort the points in terms of y,and then get both extremes until they converge to horizontal line
	 * or something close close to it,in each case i will count the number of points that each line cotains in teh graph
	 * the ideia here is that after those points match i will have covered all the possible directions.
	 */

	std::vector<point*> line;
	line.push_back(0);
	line.push_back(0);
	quick_sort(0,graph_points.size()-1,graph_points);

	int low = 0;
	int high = graph_points.size()-1;
	int max = 0;

	while(low < high){

		line.at(0) = graph_points[low];
		line.at(1) = graph_points[high];
		int curr = num_points(line,graph_points);
		if(curr > max){
			max = curr;
		}
		low++;
		high--;

	}

	return line;
}








