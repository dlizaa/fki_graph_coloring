//n_ = number_of_

#include <iostream>
#include <vector>
#include <stdlib.h>

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
		}

		void add_path(int numb, int path)
		{
			number = numb;
			n_paths++;
			paths.push_back(path);
		}

		void out()
		{
			int i;
			cout << number << color << "	" << n_paths << endl;
			for (i = 0; i < n_paths; i++)
				cout << paths[i];
			cout << endl;
		}
		
};

Graph_vertices *set_vertices(int n_v, int n_p)
{
	Graph_vertices *vertices;
	int i, a, b;

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
		vertices[a].add_path(a, b);
		vertices[b].add_path(b, a);
	}

	return vertices;
}

int vertix_with_max_n_paths(Graph_vertices *vertices, int number)
/*if number < 0 we choose vertix from all graph vertices, -number = number of all graph verices,
else from the list of paths number-vertix*/
{
	int i, n_paths, max = 0, max_number;
	vector <int> paths;
	if (number < 0)
	{
		for (i = 0; i < -number; i++)
		{
			if (vertices[i].get_n_paths() > max)
			{
				max = vertices[i].get_n_paths();
				max_number = i;
			}
		}
	}
	else
	{
		n_paths = vertices[number].get_n_paths();
		if (n_paths == 0)
			return -1;
		paths = vertices[number].get_paths();
		for (i = 0; i < n_paths; i++)
		{
			if (vertices[paths[i]].get_n_paths() > max)
			{
				max = vertices[paths[i]].get_n_paths();
				max_number = paths[i];
			}
		}
	}
	return max_number;
}

int main()
{
	int n_vertices, n_paths, n_colors, i;
	int *colors_of_verticies; Graph_vertices *vertices;

	cin >> n_paths;
	cin >> n_vertices;

	if (n_paths * n_vertices <= 0 || n_paths + n_vertices <= 0)
	{
		cout << "Wrong data" << endl;
		return 0;
	}

	vertices = set_vertices(n_vertices, n_paths);

	//**************
	
	for (i = 0; i < n_vertices; i++)
		vertices[i].out();

	cout << "\n\n" << vertix_with_max_n_paths(vertices, -n_vertices) << "\n\n";

	for (i = 0; i < n_vertices; i++)
		cout << vertix_with_max_n_paths(vertices, i) << endl;

	return 0;
}
