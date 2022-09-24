//n_ = number_of_

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <malloc.h>
#include <algorithm>
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

		void set_sorted_paths(vector <int> p)
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
	int i, j, k, x, mn, mn_k;
	vector <int> n_paths, paths;
	for (i = 0; i < n_v; i++)
	{
		paths = vertices[i].get_paths();
		for (j = 0; j < vertices[i].get_n_paths(); j++)
			n_paths.push_back(vertices[paths[j]].get_n_paths());
		for (j = 0; j < vertices[i].get_n_paths(); j++)
		{
			mn_k = 0;
			mn = n_paths[mn_k];
			for (k = j; k < vertices[i].get_n_paths(); k++)
			{
				if (n_paths[k] > mn)
				{
					mn_k = k;
					mn = n_paths[mn_k];
				}
			}
			x = n_paths[j];
			n_paths[j] = n_paths[mn_k];
			n_paths[mn_k] = x;
			x = paths[j];
			paths[j] = paths[mn_k];
			paths[mn_k] = x;
		}
		vertices[i].set_sorted_paths(paths);
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
			max_number = -1;
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

vector <int> coloring(int *counter, Graph_vertices *vertices, int *colors_of_vertices, int cur_vert, int color, vector <int> seen_paths)
{
	//*cur_flag = 0;	//if flag == 0 at the end of function< then all neighboring vertices have color
	int i, j;
	vector <int> paths, next_paths;
	for (i = 0; i < seen_paths.size(); i++)
		if (seen_paths[i] == cur_vert)
			return seen_paths;
	if (colors_of_vertices[cur_vert] == 0)
	{
		if (possible_color(color, colors_of_vertices, vertices[cur_vert].get_paths()))
		{
			colors_of_vertices[cur_vert] = color;
			vertices[cur_vert].set_color(color);
			*counter++;
		}
	}
	paths = vertices[cur_vert].get_paths();
//	for (i = 0; i < paths.size(); i++)
//		seen_paths.push_back(paths[i]);
	seen_paths.push_back(cur_vert);
//	for (i = 0; i < seen_paths.size(); i++)
//		cout << seen_paths[i] << "!";
//	cout << endl;
	for (i = 0; i < paths.size(); i++)
	{
		if (paths[i] != cur_vert)
		{
			next_paths = vertices[paths[i]].get_paths();
			for (j = 0; j < next_paths.size(); j++)
			{
				seen_paths = coloring(counter, vertices, colors_of_vertices, next_paths[j], color, seen_paths);
			}
		}
	}
//	for (i = 0; i < seen_paths.size(); i++)
//		cout << seen_paths[i] << "!";
//	cout << endl;
	return seen_paths;
}

vector <int> unseen(vector <int> paths, int n)
{
	vector <int> p, p1;
	int i;
//	for (i = 0; i < p.size(); i++)
//		cout << p[i] << "  ";
//	cout << endl;
//	cout << "@@@@@@@" << endl;
	for (i = 0; i <= n; i++)
		p.push_back(i);
	for (i = 0; i < paths.size(); i++)
		p[paths[i]] = -1;
	for (i = 0; i < n; i++)
		if (p[i] != -1)
			p1.push_back(p[i]);
//	for (i = 0; i < p1.size(); i++)
//		cout << p1[i] << "  ";
//	cout << endl;
	return p1;
}

vector <int> remove_repeats(vector <int> paths)
{
	vector <int> p;
	int i, j = 0;
	sort(begin(paths), end(paths));
	p.push_back(paths[0]);
	for (i = 1; i < paths.size(); i++)
		if (paths[i] != p[j])
		{
			j++;
			p.push_back(paths[i]);
		}
//	for (i = 0; i < paths.size(); i++)
//		cout << paths[i] << "()";
//	cout << paths.size() << endl;
	return p;
}

void start_coloring(int n_vert, int n_paths, Graph_vertices *vertices, int *colors_of_vertices)
{
	int cur_vert, i, j, k, flag, counter = n_vert, c;
	vector <int> unseen_paths, paths, vert;
	cur_vert = vertix_with_max_n_paths(vertices, -n_vert);
	for (i = 0; i < n_vert; i++)
		unseen_paths.push_back(1);
	
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
//		cout << "!!!!!!!" << endl;
		if (j > 1)
		{
			k = 0;
			while (vert[k] == 0)
				k++;
			cur_vert = k;
		}
//		cout << cur_vert << "!!!!!!!" << endl;
		while (cur_vert < n_vert)
		{
			colors_of_vertices[cur_vert] = j;
			vert[cur_vert] = 0;
			paths = vertices[cur_vert].get_paths();
//			cout << "!!!!!!!" << endl;
			for (k = 0; k < vertices[cur_vert].get_n_paths(); k++)
				vert[paths[k]] = 0;
			k = 0;
			while (vert[k] == 0)
				k++;
			cur_vert = k;
		}
		cout << "%%%%%%" << endl;
		j++;
	}



	/*while (minimum(colors_of_vertices, n_vert) == 0)
	{
		i = 0;
		while (colors_of_vertices[cur_vert] != 0)
		{
			//paths = vertices[cur_vert].get_paths();
			cur_vert = i;
			i++;
		}
		c = 0;
		paths.clear();
		while (paths.size() < n_vert)
		{
			paths = coloring(&c, vertices, colors_of_vertices, cur_vert, j, paths);
//			for (i = 0; i < paths.size(); i++)
//				cout << paths[i] << "_";
//			cout << paths.size() << endl;
			paths = remove_repeats(paths);
			for (i = 0; i < paths.size(); i++)
				cout << paths[i] << "*";
			cout << paths.size() << endl;
			if (paths.size() < n_vert)
			{
				unseen_paths = unseen(paths, n_vert);
//			if (!unseen_paths.empty())
					cur_vert = unseen_paths[0];
			}
		}
		counter =- c;
		j++;
	}*/
	return;
}

int main()
{
	int n_vertices, n_paths, n_colors, i;
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

	/*colors_of_vertices = new int[n_vertices];
	memset(colors_of_vertices, 0, n_vertices * sizeof(*colors_of_vertices));
*/
//	cout << n_vertices;
	colors_of_vertices = (int*)calloc(n_vertices, sizeof(int));

	start_coloring(n_vertices, n_paths, vertices, colors_of_vertices);

	cout << maximum(colors_of_vertices, n_vertices) << "!!!" << endl;	


	//**************
	
//	for (i = 0; i < n_vertices; i++)
//		cout << colors_of_vertices[i] << endl;

//	cout << "%%%%%%%" << endl;

//	for (i = 0; i < n_vertices; i++)
//		vertices[i].out();

//	cout << "\n\n" << vertix_with_max_n_paths(vertices, -n_vertices) << "\n\n";

//	for (i = 0; i < n_vertices; i++)
//		cout << vertix_with_max_n_paths(vertices, i) << endl;

	delete(colors_of_vertices);

	return 0;
}
