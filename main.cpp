//n_ = number_of_

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <malloc.h>
#include <algorithm>

using namespace std;

class Graph_vertices
{

	private:
		int color, number, n_paths;
		vector <int> paths;
	
	public:

		Graph_vertices()
		{
			n_paths = 0;
			color = 0;
		}

		int get_color()
		{
			return color;
		}

		int get_n_paths()
		{
			return n_paths;
		}

		vector <int> get_paths()
		{
			return paths;
		}

		void set_color(int a)
		{
			color = a;
			return;
		}

		int add_path(int numb, int path)
		{
			int i;
			number = numb;
			for (i = 0; i < n_paths; i++)
				if (paths[i] == path)
					return 1;
			n_paths++;
			paths.push_back(path);
			return 0;
		}

		void set_paths(vector <int> p)
		{
			paths = p;
			return;
		}

		void out()
		{
			int i;
			cout << number << color << "	" << n_paths << endl;
			for (i = 0; i < n_paths; i++)
				cout << paths[i];
			cout << endl;
			return;
		}
		
};

Graph_vertices *sort_vertices(Graph_vertices *vertices, int n_v)
{
	int i, j, x, mx, nmx;
	vector <int> p, vert, n_paths;
	Graph_vertices *new_vertices;
	for (i = 0; i < n_v; i++)
	{
		vert.push_back(i);
		n_paths.push_back(vertices[i].get_n_paths());
	}
	for (i = 0; i < n_v; i++)
	{
		nmx = i;
		mx = n_paths[nmx];
		for (j = i; j < n_v; j++)
		{
			if (n_paths[j] > mx)
			{
				nmx = j;
				mx = n_paths[nmx];
			}
		}
		x = n_paths[i];
		n_paths[i] = n_paths[nmx];
		n_paths[nmx] = x;
		x = vert[i];
		vert[i] = vert[nmx];
		vert[nmx] = x;
	}

	new_vertices = new Graph_vertices[n_v];
	for (i = 0; i < n_v; i++)
	{
		new_vertices[i] = vertices[vert[i]];
	}

	vertices = new_vertices;

	for (i = 0; i < n_v; i++)
	{
		p = vertices[i].get_paths();
		sort(begin(p), end(p));
		vertices[i].set_paths(p);
	}
	return vertices;

}


Graph_vertices *set_vertices(int n_v, int n_p)
{
	Graph_vertices *vertices;
	int i, a, b, flag;

	vertices = new Graph_vertices[n_v];
	
	for (i = 0; i < n_p; i++)
	{
		cin >> a;
		cin >> b;
		if (a < 0 || a >= n_v || b < 0 || b >= n_v)
		{
			cout << "Wrong data" << endl;
			exit(0);
		}
		flag = vertices[a].add_path(a, b);
		if (flag == 0)
			vertices[b].add_path(b, a);
	}

	vertices = sort_vertices(vertices, n_v);
	return vertices;
}

int minimum(int *colors_of_vertices, int n)
{
	int i, mn;
	mn = colors_of_vertices[0];
	for (i = 1; i < n; i++)
		if (colors_of_vertices[i] < mn)
			mn = colors_of_vertices[i];
	return mn;
}

int maximum(int *colors_of_vertices, int n)
{
	int i, mx;
	mx = colors_of_vertices[0];
	for (i = 1; i < n; i++)
		if (colors_of_vertices[i] > mx)
			mx = colors_of_vertices[i];
	return mx;
}

void start_coloring(int n_vert, int n_paths, Graph_vertices *vertices, int *colors_of_vertices)
{
	int cur_vert, i, j, k;
	vector <int> paths, vert;
	
	j = 1;
	while (minimum(colors_of_vertices, n_vert) == 0)
	{
		vert.clear();
		for (i = 0; i < n_vert; i++)
		{
			if (colors_of_vertices[i] == 0)
				vert.push_back(1);
			else
				vert.push_back(0);
		}
			k = 0;
			while (vert[k] == 0)
				k++;
			cur_vert = k;
		while (cur_vert < n_vert)
		{
			colors_of_vertices[cur_vert] = j;
			vert[cur_vert] = 0;
			paths = vertices[cur_vert].get_paths();
			for (k = 0; k < vertices[cur_vert].get_n_paths(); k++)
				vert[paths[k]] = 0;
			k = 0;
			while (vert[k] == 0)
				k++;
			cur_vert = k;
		}
		j++;
	}
	return;
}

int main()
{
	int n_vertices, n_paths;
	int *colors_of_vertices; 
	Graph_vertices *vertices;

	cin >> n_vertices;
	cin >> n_paths;

	if (n_paths * n_vertices <= 0 || n_paths + n_vertices <= 0)
	{
		cout << "Wrong data" << endl;
		return 0;
	}

	vertices = set_vertices(n_vertices, n_paths);

	colors_of_vertices = (int*)calloc(n_vertices, sizeof(int));

	start_coloring(n_vertices, n_paths, vertices, colors_of_vertices);

	cout << maximum(colors_of_vertices, n_vertices) << endl;	


	delete(colors_of_vertices);

	return 0;
}
