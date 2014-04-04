#include <iostream>
#include <string>

#include "Mesh.h"
#include "ObjLoader.h"
#include "AlphaShape.h"

using namespace std;

// Program entry point - SDL manages the actual WinMain entry point for us
int main(int argc, char *argv[])
{
	/*TPMain &TP = TPMain::getInstance();
	TP.init();
	TP.run();*/

	std::string filename;
	if(argc >= 2)
		filename = argv[1];
	else
	{
		cout << "Entrez un nom de fichier à convertir :" << std::endl;
		std::cin >> filename;
	}
	Mesh mesh, alphaShape, enveloppeConvexe;
	mesh.loadFromObjFile(filename.c_str());
	AlphaShape alpha;
	alpha.getAlphaShape(mesh, alphaShape);
	saveMesh(std::string(std::string("Alpha")+filename).c_str(), alphaShape);

    return 0;
}