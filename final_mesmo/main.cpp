#include "bib.hpp"
//g++ cgr-main.cpp -lGLU -lGL -lglut -o ray

struct RGBType
{
	double r;
	double g;
	double b;
};
void savebmp(int w, int h, RGBType *data)
{
	FILE *f;
	int k = w * h;
	int s = 4 * k;
	int filesize = 54 + s;

	double factor = 39.375;
	int m = static_cast<int>(factor);

	int ppm = dpi * m;

	unsigned char bmpfileheader[14] = {'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0};
	unsigned char bmpinfoheader[40] = {40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0};

	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[5] = (unsigned char)(filesize >> 24);

	bmpinfoheader[4] = (unsigned char)(w);
	bmpinfoheader[5] = (unsigned char)(w >> 8);
	bmpinfoheader[6] = (unsigned char)(w >> 16);
	bmpinfoheader[7] = (unsigned char)(w >> 24);

	bmpinfoheader[8] = (unsigned char)(h);
	bmpinfoheader[9] = (unsigned char)(h >> 8);
	bmpinfoheader[10] = (unsigned char)(h >> 16);
	bmpinfoheader[11] = (unsigned char)(h >> 24);

	bmpinfoheader[21] = (unsigned char)(s);
	bmpinfoheader[22] = (unsigned char)(s >> 8);
	bmpinfoheader[23] = (unsigned char)(s >> 16);
	bmpinfoheader[24] = (unsigned char)(s >> 24);

	bmpinfoheader[25] = (unsigned char)(ppm);
	bmpinfoheader[26] = (unsigned char)(ppm >> 8);
	bmpinfoheader[27] = (unsigned char)(ppm >> 16);
	bmpinfoheader[28] = (unsigned char)(ppm >> 24);

	bmpinfoheader[29] = (unsigned char)(ppm);
	bmpinfoheader[30] = (unsigned char)(ppm >> 8);
	bmpinfoheader[31] = (unsigned char)(ppm >> 16);
	bmpinfoheader[32] = (unsigned char)(ppm >> 24);

	string pathName = "result/";
	string fileName = "/rayTracing.bmp";
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	pathName.append(asctime(timeinfo));
	pathName.append("rayTracing.bmp");
	// pathName = pathName + fileName;
	std::cout << pathName << endl;

	f = fopen(pathName.c_str(), "wb");

	fwrite(bmpfileheader, 1, 14, f);
	fwrite(bmpinfoheader, 1, 40, f);

	for (int i = 0; i < k; i++)
	{
		RGBType rgb = data[i];

		double red = (data[i].r) * 255;
		double green = (data[i].g) * 255;
		double blue = (data[i].b) * 255;

		unsigned char color[3] = {static_cast<unsigned char>((int)floor(blue)), static_cast<unsigned char>((int)floor(green)), static_cast<unsigned char>((int)floor(red))};

		fwrite(color, 1, 3, f);
	}

	fclose(f);
}

int winningObjectIndex(vector<double> objIntersec)
{

	// prevent unnessary calculations
	if (objIntersec.size() == 0)
	{
		// if there are no intersections
		return -1;
	}
	else if (objIntersec.size() == 1)
	{
		if (objIntersec[0] > 0)
		{
			// if that intersection is greater than zero then its our index of minimum value
			return 0;
		}
		else
		{
			// otherwise the only intersection value is negative
			return -1;
		}
	}
	else
	{

		//Percorre todo o vetor para encontrar o valor maximo de interseção
		double max = 0;
		for (int i = 0; i < objIntersec.size(); i++)
		{
			if (max < objIntersec[i])
			{
				max = objIntersec[i];
			}
		}

		// then starting from the maximum value find the minimum positive value
		if (max > 0)
		{

			// return the index of the winning intersection
			int idx = 0;

			// we only want positive intersections
			for (int i = 0; i < objIntersec.size(); i++)
			{
				if (objIntersec[i] > 0 && objIntersec[i] <= max)
				{
					max = objIntersec[i];
					idx = i;
				}
			}

			return idx;
		}
		else
		{
			// all the intersections were negative
			return -1;
		}
	}
}

Color getColorAt(Vect posIntersec, Vect rayDirIntersec, vector<Object *> objCena, int indice, vector<Light *> fonteLuz)
{

	Color winning_object_color = objCena[indice]->getColor();
	Vect winning_object_normal = objCena[indice]->getNormalAt(posIntersec);

	Color corFinal = winning_object_color.colorScalar(luzAmbiente);

	//Se a cor especial (quantidade de reflexo) for maior que zero e menor que 1
	if (winning_object_color.getColorSpecial() > 0 && winning_object_color.getColorSpecial() <= 1)
	{
		// reflection from objects with specular intensity
		double dot1 = winning_object_normal.dotProduct(rayDirIntersec.negative());
		Vect scalar1 = winning_object_normal.vectMult(dot1);
		Vect add1 = scalar1.vectAdd(rayDirIntersec);
		Vect scalar2 = add1.vectMult(2);
		Vect add2 = rayDirIntersec.negative().vectAdd(scalar2);
		Vect reflection_direction = add2.normalize();

		Ray reflection_ray(posIntersec, reflection_direction);

		// determine what the ray intersects with first
		vector<double> intersecReflexao;
		//Adiciona no vetor todos os objetos que tem interseção com o raio refletido
		for (int i = 0; i < objCena.size(); i++)
		{
			intersecReflexao.push_back(objCena[i]->findIntersection(reflection_ray));
		}

		int indiceObjReflexo = winningObjectIndex(intersecReflexao);

		//faz o cálculo recursivo para criar uma reflexão entre os objetos, semelhante ao espelho
		if (indiceObjReflexo != -1)
		{
			// reflection ray missed everthing else
			if (intersecReflexao[indiceObjReflexo] > acuracia)
			{
				// determine the position and direction at the point of intersection with the reflection ray
				// the ray only affects the color if it reflected off something

				Vect posIntersecReflete = posIntersec.vectAdd(reflection_direction.vectMult(intersecReflexao.at(indiceObjReflexo)));
				Vect dirRayReflete = reflection_direction;

				Color corRefletido = getColorAt(posIntersecReflete, dirRayReflete, objCena, indiceObjReflexo, fonteLuz);

				corFinal = corFinal.colorAdd(corRefletido.colorScalar(winning_object_color.getColorSpecial()));
			}
		}
	}

	//Percorre o vetor de luzes no cenário
	for (int i = 0; i < fonteLuz.size(); i++)
	{
		Vect dirLuz = fonteLuz[i]->posLuz.vectAdd(posIntersec.negative()).normalize();

		float cos = winning_object_normal.dotProduct(dirLuz);

		if (cos > 0)
		{
			bool sombra = false;

			Vect distance_to_light = fonteLuz[i]->posLuz.vectAdd(posIntersec.negative()).normalize();
			float distance_to_light_magnitude = distance_to_light.magnitude();

			//Cria o ray da sombra, onde a origem é a interseção entre os objetos
			// e a direção é o sentido da fonte luminosa
			Ray raySombra(posIntersec, fonteLuz[i]->posLuz.vectAdd(posIntersec.negative()).normalize());

			vector<double> intersecAux;

			for (int i = 0; i < objCena.size() && !sombra; i++)
			{
				intersecAux.push_back(objCena[i]->findIntersection(raySombra));
			}

			//Faz o cálculo da sombra
			for (int c = 0; c < intersecAux.size(); c++)
			{
				if (intersecAux[c] > acuracia)
				{
					if (intersecAux[c] <= distance_to_light_magnitude)
					{
						sombra = true;
					}
				}
			}

			if (!sombra)
			{
				corFinal = corFinal.colorAdd(winning_object_color.colorMultiply(fonteLuz[i]->corLuz).colorScalar(cos));

				if (winning_object_color.getColorSpecial() > 0 && winning_object_color.getColorSpecial() <= 1)
				{
					// special [0-1]
					double dot1 = winning_object_normal.dotProduct(rayDirIntersec.negative());
					Vect scalar1 = winning_object_normal.vectMult(dot1);
					Vect add1 = scalar1.vectAdd(rayDirIntersec);
					Vect scalar2 = add1.vectMult(2);
					Vect add2 = rayDirIntersec.negative().vectAdd(scalar2);
					Vect reflection_direction = add2.normalize();

					double specular = reflection_direction.dotProduct(dirLuz);
					if (specular > 0)
					{
						specular = pow(specular, 10);
						corFinal = corFinal.colorAdd(fonteLuz[i]->corLuz.colorScalar(specular * winning_object_color.getColorSpecial()));
					}
				}
			}
		}
	}

	return corFinal.clip();
}

int main(int argc, char *argv[])
{
	cout << "rendering ..." << endl;

	clock_t t1, t2;

	int width = atoi(argv[1]);
	int height = atoi(argv[2]);
	int n = width * height;

	RGBType *pixels = new RGBType[n];

	//Buga quando campo.getVectX() é menor que 3
	//if (posCam.getVectX() < 3)
	//{
	//	posCam.setVectX(3);
	//}

	// Diferença entre a posição da camera e o ponto de look at, isto é a direção em que a câmera olha:
	// 	Dir = P_cam - L_at
	Vect diferenca(posCam.getVectX() - look_at.getVectX(), posCam.getVectY() - look_at.getVectY(), posCam.getVectZ() - look_at.getVectZ());

	// Normalizando Dir:
	Vect dirCam = diferenca.negative().normalize();
	// Vetor que aponta para a lateral do plano da câmera:
	Vect camright = Y.crossProduct(dirCam).normalize();
	// Note que o plano da cãmera sempre tem a aresta de cima paralela ao plano xz, a aparencia de estar inclinado ocorre devido a direção dos raios...
	// ... que saem dos pixels neste plano (os raios podem sair inclinados pra baixo ou pra cima)

	// Vetor que aponta para baixo do plano da câmera:
	Vect camdown = camright.crossProduct(dirCam);

	// Lembrar que a câmera é um plano (é infinito).

	Camera camera(posCam, dirCam, camright, camdown);

	Light luzCena(posLuz, white_light);
	Light luzTeste(Vect(0, 0, 0), Color(0.8, 0, 1, 0));

	vector<Light *> fonteLuz;

	// Obs.: https://en.cppreference.com/w/cpp/language/dynamic_cast

	//fonteLuz.push_back(dynamic_cast<Light *>(&luzCena));
	fonteLuz.push_back(dynamic_cast<Light *>(&luzTeste));

	vector<Object *> objCena;
	objCena.push_back(dynamic_cast<Object *>(&sphere_1));
	objCena.push_back(dynamic_cast<Object *>(&sphere_2));
	//objCena.push_back(dynamic_cast<Object *>(&sphere_3));
	objCena.push_back(dynamic_cast<Object *>(&sphere_4));
	objCena.push_back(dynamic_cast<Object *>(&sphere_4));
	objCena.push_back(dynamic_cast<Object *>(&sphere_6));
	objCena.push_back(dynamic_cast<Object *>(&sphere_7));
	objCena.push_back(dynamic_cast<Object *>(&sphere_8));
	objCena.push_back(dynamic_cast<Object *>(&sphere_9));
	objCena.push_back(dynamic_cast<Object *>(&sphere_10));
	objCena.push_back(dynamic_cast<Object *>(&sphere_11));

	//objCena.push_back(dynamic_cast<Object *>(&sphere_5));
	objCena.push_back(dynamic_cast<Object *>(&ground));
	objCena.push_back(dynamic_cast<Object *>(&wall));
	objCena.push_back(dynamic_cast<Object*>(&wall_2));
	objCena.push_back(dynamic_cast<Object*>(&wall_3));

	int thisone, aa_index;
	double xamnt, yamnt;

	string entrada;
	bool exit = false;

	t1 = clock();

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			// Cálcula o índice do pixel no vetor de pixels:
			thisone = y * width + x;

			// Começa com pixel branco:
			double tempRed;
			double tempGreen;
			double tempBlue;

			// Criar um raio da câmera para este pixel:

			// Faz a modificação da imagem, quando redimensiona a janela (redimensior para proporção 1:1):
			if (width > height)
			{
				// the image is wider than it is tall
				// A imagem é mais larga portanto é alta: 
				
				// x_amnt = ceil( x/h ) - (w-h)/(2h)
				xamnt = (x + 0.5) / (double)height - (((width - height) / (double)height) / 2);
				
				// y_amnt = ceil( (h-y)/h )
				yamnt = ((height - y) + 0.5) / height;
			}
			else if (height > width)
			{
				// the imager is taller than it is wider
				// A imagem é mais larga portanto é larga:
				xamnt = (x + 0.5) / width;
				yamnt = (height - y + 0.5) / (double)width - ((height - width) / (double)width) / 2;
			}
			else
			{
				// the image is square
				xamnt = (x + 0.5) / width;
				yamnt = ((height - y) + 0.5) / height;
			}


			//Origem dos raios de luz da câmera e a direção
			Vect rayOrigem = camera.posCam;
			
			// Equação do vetor diretor do raio que sai do pixel:
			// R = dir + [ (xamnt - 0.5) * camright + (yamnt - 0.5) * camdown]
			Vect rayDirecao = dirCam.vectAdd(camright.vectMult(xamnt - 0.5).vectAdd(camdown.vectMult(yamnt - 0.5))).normalize();
			
			// Obs. 1: este raio deve ser normalizado (os cálculos no código consideram o vetor de direção como unitário); 
			// Obs. 2: a direção do raio é movida para ser direcionado para os pixels diferentes, pois o vetor dir é a direção em relação...
			// ... ao pixel central.

			Ray rayCamera(rayOrigem, rayDirecao);

			// Vetor de cada parâmetro que indica uma intersecção, isto é, se a reta do raio é dada por R = t*v + o, estes serão...
			// ... os valores de t para os quais há intersecção com algum objeto: 
			vector<double> intersections;

			// Encontra a interseção dos raios da câmera com os objetos em cena...
			// ...e salvo no vetor:
			for (int index = 0; index < objCena.size(); index++)
			{
				intersections.push_back(objCena[index]->findIntersection(rayCamera));
			}

			int indice = winningObjectIndex(intersections);

			//Se nao houver interseção do ray com o objeto, o pixel é marcado como preto
			if (indice == -1)
			{
				// set the backgroung black
				tempRed = 0;
				tempGreen = 0;
				tempBlue = 0;

				//Se houver, é calculado na função getColorAt a cor (preto (sombra), branco (reflexo da luz)
				// ou a propria cod do objeto)
			}
			else
			{
				// index coresponds to an object in our scene
				if (intersections[indice] > acuracia)
				{
					// determine the position and direction vectors at the point of intersection

					Vect posIntersec = rayOrigem.vectAdd(rayDirecao.vectMult(intersections[indice]));
					Vect rayDirIntersec = rayDirecao;

					Color corIntersec = getColorAt(posIntersec, rayDirIntersec, objCena, indice, fonteLuz);

					tempRed = corIntersec.getColorRed();
					tempGreen = corIntersec.getColorGreen();
					tempBlue = corIntersec.getColorBlue();
				}
			}

			pixels[thisone].r = tempRed;
			pixels[thisone].g = tempGreen;
			pixels[thisone].b = tempBlue;
		}
	}

	savebmp(width, height, pixels);

	return 0;
}
