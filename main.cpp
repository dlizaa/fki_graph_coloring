//n_ = number_of_

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <malloc.h>
//#include <cstring>

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
				
				//if (vertices[paths[i]].get_color() == 0)
				//{
					max = vertices[paths[i]].get_n_paths();
					max_number = paths[i];
				//}
			}
		}
		if (max == 0)
			max_number = paths[0];
	}
	return max_number;
}

int possible_color(int j, int *col_of_vert, vector <int> paths)
{
	int i;
	for (i = 0; i < paths.size(); i++)
	{
		if (j == col_of_vert[paths[i]])
			return 0;
	}
	return 1;
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
	int cur_vert, i, j, flag;
	vector <int> paths;
	cur_vert = vertix_with_max_n_paths(vertices, -n_vert);
	
	/*while (minimum(colors_of_vertices, n_vert) == 0)
	{
		if (vertices[cur_vert].get_color() == 0)
		{
			j = 1;
			while (possible_color(j, colors_of_vertices, vertices[cur_vert].get_paths()) == 0)
				j++;
			vertices[cur_vert].set_color(j);
			colors_of_vertices[cur_vert] = j;
		}
		cur_vert = vertix_with_max_n_paths(vertices, cur_vert);
	}*/

	vertices[cur_vert].set_color(1);
	colors_of_vertices[cur_vert] = 1;

	while (minimum(colors_of_vertices, n_vert) == 0)
	{
		j = 1;
		paths = vertices[cur_vert].get_paths();
		while (!paths.empty())
		{
			if (j == colors_of_vertices[cur_vert])
				j++;
			for (i = 0; i < paths.size(); i++)
			{
				if (possible_color(j, colors_of_vertices, vertices[paths[i]].get_paths()))
				{
					colors_of_vertices[paths[i]] = j;
					vertices[paths[i]].set_color(j);
					paths[i] = paths[paths.size() - 1];
					paths.pop_back();
				}
			}
			j++;
		}

		
		cur_vert = vertix_with_max_n_paths(vertices, cur_vert);



		/*j = 1;
		if (j == colors_of_vertices[cur_vert])
			j++;
		while (possible_color(j, colors_of_vertices, vertices[cur_vert].get_paths()) == 0)
		{
			j++;
			if (j == colors_of_vertices[cur_vert])
				j++;
		}
		for (i = 0; i < paths.size(); i++)
		{
			
		}*/
	}
	return;
}

int main()
{
	int n_vertices, n_paths, n_colors, i;
	int *colors_of_vertices; 
	Graph_vertices *vertices;

	cin >> n_paths;
	cin >> n_vertices;

	if (n_paths * n_vertices <= 0 || n_paths + n_vertices <= 0)
	{
		cout << "Wrong data" << endl;
		return 0;
	}

	vertices = set_vertices(n_vertices, n_paths);

	/*colors_of_vertices = new int[n_vertices];
	memset(colors_of_vertices, 0, n_vertices * sizeof(*colors_of_vertices));
*/
	colors_of_vertices = (int*)calloc(n_vertices, sizeof(int));

	start_coloring(n_vertices, n_paths, vertices, colors_of_vertices);

	cout << maximum(colors_of_vertices, n_vertices) << "!!!" << endl;	


	//**************
	
	for (i = 0; i < n_vertices; i++)
		cout << colors_of_vertices[i] << endl;

	for (i = 0; i < n_vertices; i++)
		vertices[i].out();

	cout << "\n\n" << vertix_with_max_n_paths(vertices, -n_vertices) << "\n\n";

	for (i = 0; i < n_vertices; i++)
		cout << vertix_with_max_n_paths(vertices, i) << endl;

	delete(colors_of_vertices);

	return 0;
}
