#ifndef __APPLICATION_MANAGER_H__
#define __APPLICATION_MANAGER_H__

#include <stdlib.h>

#include "RenderingManager.h"
#include "WindowManager.h"

// controls the main loop
namespace ApplicationManager
{
	Scene scene;
	
	Mesh loadMesh(std::string name, Mesh &myMesh)
	{
		char op; int v;
		std::string fileName = "ExternalFiles\\Objects\\" + name;
		std::string MTLname;

		FILE * obj = freopen(fileName.c_str(), "r", stdin); 

		if(obj != NULL)
		{
			while(scanf(" %c", &op) > 0 && !feof(obj))
			{
				if(op == 'v')
				{
					float x,y,z;

					scanf("%c", &op);

					if(op == ' ')
					{
						scanf("%f %f %f", &x, &y, &z);
						myMesh.addVertex(Vec3f(x,y,z));
					}
					else if(op == 't')
					{
						scanf("%f %f %f", &x, &y, &z);
						myMesh.addTexture(Vec3f(x,y,z));
					}
					else if(op == 'n')
					{
						scanf("%f %f %f", &x, &y, &z);
						myMesh.addNormals(Vec3f(x,y,z));
					}
				}
				else if(op == 'f')
				{ 
					scanf("%c", &op);

					std::vector<unsigned int> verticesIndicesAux;
					std::vector<unsigned int> normalsIndicesAux;
					std::vector<unsigned int> texturaIndicesAux;

					bool hasTexture = false,
						hasNormals = false;

					while(op == ' ' && !feof(obj))
					{
						if(scanf("%d", &v) > 0)
						{
							v--; verticesIndicesAux.push_back(v);

							scanf("%c", &op);
							if(op == '/')
							{
								if(scanf("%d", &v) > 0)
								{
									v--; texturaIndicesAux.push_back(v);
									scanf("%c", &op);
									scanf("%d", &v);

									v--; normalsIndicesAux.push_back(v);

									hasTexture = true;
									scanf("%c", &op);
								}
								else
								{
									scanf("%c", &op);
									scanf("%d", &v);

									v--;  normalsIndicesAux.push_back(v);
									scanf("%c", &op);
								}

								hasNormals = true;
							}
						}
						else break;
					}

					// faces triangulize
					int i = verticesIndicesAux.size() - 1;

					for(; i >= 2; --i)
					{
						myMesh.indices.push_back(verticesIndicesAux.at(i));
						myMesh.indices.push_back(verticesIndicesAux.at(i-1));
						myMesh.indices.push_back(verticesIndicesAux.at(0));

						if(hasNormals)
						{
							myMesh.normalIndices.push_back(normalsIndicesAux.at(i));
							myMesh.normalIndices.push_back(normalsIndicesAux.at(i-1));
							myMesh.normalIndices.push_back(normalsIndicesAux.at(0));
						}

						if(hasTexture)
						{
							myMesh.texturaIndices.push_back(texturaIndicesAux.at(i));
							myMesh.texturaIndices.push_back(texturaIndicesAux.at(i-1));
							myMesh.texturaIndices.push_back(texturaIndicesAux.at(0));
						}
					}
				}
				else if(op == 'm')
				{
					char w[10], c_name[100];
					std::string aux;

					scanf("%s %s", w, c_name);

					aux = c_name;
					MTLname = "ExternalFiles\\Objects\\" + aux;
				}
				else
				{
					op = fgetc(obj);
					while (op != '\n' && !feof(obj)) op = fgetc(obj); // comments
				}
			}

			fclose(obj);

			if(myMesh.getNormalsSize() == 0) // case there is not normals on file
			{
				std::cout << "Caculating vertices' normals " << std::endl;

				for(int i = 0; i < myMesh.getIndicesSize(); i += 3)
				{
					Vec3f a(myMesh.vertices.at(myMesh.indices.at(i+1)*3), myMesh.vertices.at(myMesh.indices.at(i+1)*3+1), myMesh.vertices.at(myMesh.indices.at(i+1)*3+2));
					Vec3f b(myMesh.vertices.at(myMesh.indices.at(i+2)*3), myMesh.vertices.at(myMesh.indices.at(i+2)*3+1), myMesh.vertices.at(myMesh.indices.at(i+2)*3+2));
					Vec3f c(myMesh.vertices.at(myMesh.indices.at(i)*3), myMesh.vertices.at(myMesh.indices.at(i)*3+1), myMesh.vertices.at(myMesh.indices.at(i)*3+2));

					a = a - c;
					b = b - c;

					int indice = myMesh.addNormals(b.cross(a).normalized());

					myMesh.normalIndices.push_back(indice);
					myMesh.normalIndices.push_back(indice);
					myMesh.normalIndices.push_back(indice);
				}
			}

			if(!MTLname.empty())
			{
				FILE * mtlFile = freopen(MTLname.c_str(), "r", stdin);

				if(mtlFile != NULL)
				{
					while(scanf("%c", &op) > 0 && !feof(mtlFile))
					{
						if(op == 'K')
						{
							float red, green, blue;
							scanf("%c", &op);

							scanf("%f %f %f", &red, &green, &blue);

							if(op == 'a')
								myMesh.setAmbiental(Color(red, green, blue));
							else if(op == 'd')
								myMesh.setDiffuse(Color(red, green, blue));
							else if(op == 's')
								myMesh.setSpecular(Color(red, green, blue));
						}
						else if(op == 'i')
						{
							int ilumSpecular;
							scanf("%d", &ilumSpecular);

							if(ilumSpecular == 1)
								myMesh.hasSpecular = false;
							else if(ilumSpecular == 2)
								myMesh.hasSpecular = true;
						}
						else if(op == 'd' || op == 'T')
						{
							float transparency;
							scanf("%f", &transparency);
							myMesh.setTransparency(transparency);
						}
						else if(op == 'N')
						{
							float shininess;
							scanf("%f", &shininess);
							myMesh.setShininess(shininess);
						}
						else if(op == 'm')
						{

						}
					}

					fclose(mtlFile);
				}
				else
				{
					std::cout << "There was an error on openning mdl file. Try again." << std::endl;
					std::cout << "Directory: " << "ExternalFiles\\Objects\\" + MTLname << std::endl;
				}
			}
		}
		else
		{
			std::cout << "There was an error on openning obj file. Try again." << std::endl;
			std::cout << "Directory: " << "ExternalFiles\\Objects\\" + fileName << std::endl;
		}

		return myMesh;
	}

	Mesh createMesh(std::string meshName,
		const Vec3f& position = Vec3f(),
		const Vec3f& orientation = Vec3f(0, 1, 0),
		const float scale = 1)
	{
		Mesh myMesh(position, orientation, scale);

		return loadMesh(meshName, myMesh);
	}


	void create(Scene& scene)
	{
		scene.setGravity(Vec3f(0, -9.8f, 0));
		/*scene.add(Cube(0.5, Vec3f(0, 1000, 1)));
		scene.add(Cube(0.5, Vec3f(0, 500, 1)));
		scene.add(Cube(0.5, Vec3f(0, 100, 1)));
		scene.add(Cube(0.5, Vec3f(0, 59, 1)));
		scene.add(Cube(0.5, Vec3f(1, 59, 1)));
		scene.add(Cube(0.5, Vec3f(2, 59, 1)));
		scene.add(Cube(0.5, Vec3f(3, 59, 1)));
		scene.add(Cube(0.5, Vec3f(4, 59, 1)));
		scene.add(Cube(0.5, Vec3f(5, 59, 1)));
		scene.add(Cube(0.5, Vec3f(6, 59, 1)));
		scene.add(Cube(0.5, Vec3f(7, 59, 1)));
		scene.add(Cube(0.5, Vec3f(8, 59, 1)));
		scene.add(Cube(0.5, Vec3f(9, 59, 1)));
		scene.add(Cube(0.5, Vec3f(10, 59, 1)));
		scene.add(Cube(0.5, Vec3f(11, 59, 1)));
		scene.add(Cube(0.5, Vec3f(12, 59, 1)));
		scene.add(Cube(0.5, Vec3f(13, 59, 1)));
		scene.add(Cube(0.5, Vec3f(14, 59, 1)));
		scene.add(Cube(0.5, Vec3f(0, 47, 1)));
		scene.add(Cube(0.5, Vec3f(0, 35, 1)));
		scene.add(Cube(0.5, Vec3f(0, 23, 1)));
		scene.add(Cube(0.5, Vec3f(0, 11, 1)));*/
		
		scene.add(LightScheme(1.0, Color(1.0, 0.0, 0.0)));
		scene.add(Light(0.5f, 1.0f, Vec3f(2.0, 2.0, 0.0), Color(0.9f, 0.9f, 0.9f)));
		scene.add(Plane(60, Color(0.6, 0.6, 0.6), Vec3f(-1, -1, -1), Vec3f(0.5, 4, -0.5)));

		Mesh mesh = createMesh("3.obj");
		mesh.setDiffuse(Color(0.0f, 1.0f, 1.0f));
		scene.add(mesh);

		//Mesh mesh(Vec3f(1,1,1), Vec3f(0,1,0),1); //TODO: ver o pq de por 1 no Y da rotaçao tem o mesmo efeito de por -1 no Z!!!
		//mesh.addVertex(Vec3f(2,0,0));
		//mesh.addVertex(Vec3f(-2,0,0));
		//mesh.addVertex(Vec3f(0,2,0));
		//mesh.addVertex(Vec3f(0,-2,0));
		//mesh.addVertex(Vec3f(2,0,1));
		//mesh.addVertex(Vec3f(-2,0,1));
		//mesh.addVertex(Vec3f(0,2,1));
		//mesh.addVertex(Vec3f(0,-2,1));

		//mesh.addTriangleIndices(Vec3i(0,1,2));
		//mesh.addTriangleIndices(Vec3i(0,3,1));
		//mesh.addTriangleIndices(Vec3i(4,5,7));
		//mesh.addTriangleIndices(Vec3i(4,6,5));
		//mesh.addTriangleIndices(Vec3i(1,3,5));
		//mesh.addTriangleIndices(Vec3i(3,7,5));
		//mesh.addTriangleIndices(Vec3i(2,6,0));
		//mesh.addTriangleIndices(Vec3i(0,6,4));
		//mesh.addTriangleIndices(Vec3i(1,5,2));
		//mesh.addTriangleIndices(Vec3i(2,5,6));
		//mesh.addTriangleIndices(Vec3i(3,0,7));
		//mesh.addTriangleIndices(Vec3i(0,4,7));

		//scene.add(mymesh);
	}

	void init()
	{
		int argc = 1;
		char *argv[1] = { (char*)"" };

		const int width = 640;
		const int height = 480;

		create(scene);
		RenderingManager::init(width, height);
	}

	void run()
	{
		init();
	}
};

#endif