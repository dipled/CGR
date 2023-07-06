#include "bib.hpp"
#include <cmath>
// g++ cgr-main.cpp -lGLU -lGL -lglut -o ray

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

	// Se o tamanho do objeto for zero ele vai retornar -1
	if (objIntersec.size() == 0)
	{
		return -1;
	}
	else if (objIntersec.size() == 1)
	{
		if (objIntersec[0] > 0)
		{
			
			return 0;
		}
		else
		{
			return -1;
		}
	}
	else
	{

		// Percorre todo o vetor para encontrar o valor maximo de interseção
		double max = 0;
		for (int i = 0; i < objIntersec.size(); i++)
		{
			if (max < objIntersec[i])
			{
				max = objIntersec[i];
			}
		}

		// Comecando do maximo, vamos achar o minimo positivo
		if (max > 0)
		{

			int idx = 0;

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
			// Caso todas as interseções tenham sido negativas, ele vai retornar -1, indicando que o raio missou o objeto
			return -1;
		}
	}
}

Color getColorAt(Vect posIntersec, Vect rayDirIntersec, vector<Object *> objCena, int indice, vector<Light *> fonteLuz)
{

	Color winning_object_color = objCena[indice]->getColor();
	Vect winning_object_normal = objCena[indice]->getNormalAt(posIntersec);

	Color corFinal = winning_object_color.colorScalar(luzAmbiente);

	//Se a cor especial (quantidade de reflexo) for maior que zero e menor que 1:
	if (winning_object_color.getColorSpecial() > 0 && winning_object_color.getColorSpecial() <= 1)
	{
		// Reflexão de objetos com intensidade especular:
		double dot1 = winning_object_normal.dotProduct(rayDirIntersec.negative());

		Vect scalar1 = winning_object_normal.vectMult(dot1);
		Vect add1 = scalar1.vectAdd(rayDirIntersec);
		Vect scalar2 = add1.vectMult(2);
		Vect add2 = rayDirIntersec.negative().vectAdd(scalar2);
		Vect reflection_direction = add2.normalize();

		// Sendo L: direção do raio, N: normal a superfície de intersecção, R: direção do raio de reflexão, R é...
		// ... dado por:
		// R = L - 2.(L ⋅ N)⋅ N

		Ray reflection_ray(posIntersec, reflection_direction);
		// A reta Re do raio de reflexão, sendo Pin o ponto de intersecção é dada por:
		// Re = R.t + Pin


		// Determina qual é a primeira interseção do raio
		vector<double> intersecReflexao;
		// Adiciona no vetor todos os objetos que tem interseção com o raio refletido
		for (int i = 0; i < objCena.size(); i++)
		{
			intersecReflexao.push_back(objCena[i]->findIntersection(reflection_ray));
		}
		// Pega o índice do objeto que foi refletido
		int indiceObjReflexo = winningObjectIndex(intersecReflexao);

		// faz o cálculo recursivo para criar uma reflexão entre os objetos, semelhante ao espelho
		// Caso o índice seja diferente de -1, o raio acertou algum objeto
		if (indiceObjReflexo != -1)
		{
			// Verifica se a interção está acima da nossa acurácia para otimizar as interseções 
			if (intersecReflexao[indiceObjReflexo] > acuracia)
			{
				// Determina qual será a posição e direção do raio refletido a partir da interseção
				Vect posIntersecReflete = posIntersec.vectAdd(reflection_direction.vectMult(intersecReflexao.at(indiceObjReflexo)));
				Vect dirRayReflete = reflection_direction;

				// Pega a cor final que será refletida, chamando recursivamente esta fução para continuar refletindo até o raio missar tudo
				Color corRefletido = getColorAt(posIntersecReflete, dirRayReflete, objCena, indiceObjReflexo, fonteLuz);

				corFinal = corFinal.colorAdd(corRefletido.colorScalar(winning_object_color.getColorSpecial()));
			}
		}
	}

	// Percorre o vetor de luzes no cenário
	for (int i = 0; i < fonteLuz.size(); i++)
	{
		Vect dirLuz = fonteLuz[i]->posLuz.vectAdd(posIntersec.negative()).normalize();

		float cos = winning_object_normal.dotProduct(dirLuz);

		if (cos > 0)
		{
			bool sombra = false;

			Vect distance_to_light = fonteLuz[i]->posLuz.vectAdd(posIntersec.negative()).normalize();
			float distance_to_light_magnitude = distance_to_light.magnitude();

			// Cria o ray da sombra, onde a origem é a interseção entre os objetos
			// e a direção é o sentido da fonte luminosa
			Ray raySombra(posIntersec, fonteLuz[i]->posLuz.vectAdd(posIntersec.negative()).normalize());

			vector<double> intersecAux;

			for (int i = 0; i < objCena.size() && !sombra; i++)
			{
				intersecAux.push_back(objCena[i]->findIntersection(raySombra));
			}

			// Faz o cálculo da sombra
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
			// Se o objeto tiver sombra, precisamos ainda somar no vetor de cores a cor da fonte de luz
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
	// No final, vai retornar a resultade da cor, capada para valores dentro dos limites RGB
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

	// Diferença entre a posição da camera e o ponto de look at, isto é a direção em que a câmera olha:
	// 	Dir = P_cam - L_at
	Vect diferenca = look_at.vectAdd(posCam.negative());

	// Normalizando Dir:
	Vect dirCam = diferenca.normalize();
	// Vetor que aponta para a lateral do plano da câmera:
	Vect camright = Y.crossProduct(dirCam).normalize();
	// Note que o plano da cãmera sempre tem a aresta de cima paralela ao plano xz, a aparencia de... 
	// ... estar inclinado ocorre devido a direção dos raios que saem dos pixels...
	// ... neste plano (os raios podem sair inclinados pra baixo ou pra cima)
	// Note que este produto vetorial é normalizado;

	// Vetor que aponta para baixo do plano da câmera:
	Vect camdown = camright.crossProduct(dirCam).normalize();

	// Lembrar que a câmera é um plano (é infinito).

	Camera camera(posCam, dirCam, camright, camdown);

	Light luzCena(posLuz, white_light);
	// Light luzTeste(Vect(0, 0, 0), Color(0.8, 0, 1, 0));

	vector<Light *> fonteLuz;

	// Obs.: https://en.cppreference.com/w/cpp/language/dynamic_cast

	fonteLuz.push_back(dynamic_cast<Light *>(&luzCena));
	// fonteLuz.push_back(dynamic_cast<Light *>(&luzTeste));

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

	objCena.push_back(dynamic_cast<Object *>(&sphere_5));
	objCena.push_back(dynamic_cast<Object *>(&ground));
	objCena.push_back(dynamic_cast<Object *>(&wall));
	objCena.push_back(dynamic_cast<Object*>(&wall_2));
	objCena.push_back(dynamic_cast<Object*>(&wall_3));

	int thisone;
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
				
				// x_amnt = ( (x + 0.5) /h ) - (w-h)/(2h)
				// xamnt = ((x + 0.5) / (double)height) - ((width - height) / (double)height) / 2; 
				xamnt = ((x + 0.5) / (double)height) - ((width - height) / ((double) 2*height)) - 0.5; 

				// Note que:
				// (a) para imagem não ficar esticada em alguma direção, a variação de uma unidade em x deve ser igual...
				// ... a variação de uma unidade em y por isto se divide x + 0.5 pelo height;
				// 
				// (b)  entretando como width > heigth quando x é maior que o height ele x/height > 1, portanto deve-se...
				// ... ajustar para que o valor máximo da "normalização" seja 1, para isso note que quando x = w-1,
				// ... x_amnt = ( (x + 0.5) /h ) - (w-h)/(h)
				// ... x_amnt = ( (w - 1 + 0.5) /h ) - (w-h)/(h)
				// ... x_amnt = (w - 0.5 - w + h)/h
				// ... x_amnt = (h - 0.5)/h
				
				// y_amnt = ceil( (h-y)/h )
				yamnt = ((height - y) + 0.5) / height - 0.5;

				// Note que a primeira para 


			}
			else if (height > width)
			{
				// the imager is taller than it is wider
				// A imagem é mais alta portanto deve ser larga:
				
				xamnt = (x + 0.5) / width - 0.5;
				yamnt = (height - y + 0.5) / (double)width - ((height - width) / (double)width) / 2 - 0.5;
				
				// Com x note que o que ocorre aqui é que x é normalizado entre 0 e 1 somado mas se soma 0.5 pois queremos...
				// ... o centro do pixel, então se subtrai 0.5 para que fique no intervalo [-0.5, 0.5];

				// Com y note que o que ocorre aqui é que y é normalizado entre 0 e 1 somado mas se soma 0.5 pois queremos...
				// ... o centro do pixel, então se subtrai 0.5 para que fique no intervalo [-0.5, 0.5], entretanto como...
				// ... neste caso existem mais pixels na vertical deve-se subtrair a porcentagem de pixels a mais dividida...
				// ... por 2 pois ;

			}
			else
			{
				// Se a imagem é quadrada:
				xamnt = ((x + 0.5) / width) - 0.5;
				yamnt = (((height - y) + 0.5) / height) - 0.5;

			}


			// Origem dos raios de luz da câmera e a direção
			Vect rayOrigem = camera.posCam;
			
			// Equação do vetor diretor do raio que sai do pixel:
			// R = dir + [ (xamnt - 0.5) * camright + (yamnt - 0.5) * camdown]
			Vect rayDirecao = dirCam.vectAdd(camright.vectMult(xamnt).vectAdd(camdown.vectMult(yamnt))).normalize();
			
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

			// Indice do objeto com a menor intersecção positiva:
			int indice = winningObjectIndex(intersections);

			// Se nao houver interseção do ray com o objeto, o pixel é marcado como preto
			if (indice == -1)
			{
				// Define a cor de fundo (quando o raio de um pixel não intersect nenhum objeto) como preto:
				tempRed = 0;
				tempGreen = 0;
				tempBlue = 0;
				// Se houver, é calculado na função getColorAt a cor (preto (sombra), branco (reflexo da luz)...
				// ... ou a propria cor do objeto)
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
