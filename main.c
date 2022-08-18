#include <iostream>
#include <vector>

using namespace std;

class Graph_vertices
{

	private:
		int color, number, number_of_paths;
		vector <int> paths;
	
	public:

		Graph_vertices()
		{
			number_of_paths = 0;
			color = 0;
		}

		void add_path(int numb, int path)
		{
			number = numb;
			number_of_paths++;
			paths.push_back(path);
		}


		void change_color(int a)
		{
			color = a;
		}

		void out()
		{
			int i;
			cout << number << color << "	" << number_of_paths << endl;
			for (i = 0; i < number_of_paths; i++)
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
		vertices[a].add_path(a, b);
		vertices[b].add_path(b, a);
	}

	return vertices;
}


int main()
{
	int n_vertices, n_paths, n_colors, i; //n_ = number_of_
	int *colors_of_verticies;
	Graph_vertices *vertices;

	cin >> n_paths;
	cin >> n_vertices;

	vertices = set_vertices(n_vertices, n_paths);

	for (i = 0; i < n_vertices; i++)
		vertices[i].out();

	return 0;
}
