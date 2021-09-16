/*
Caio Vinicius Rodrigues da Costa
Iorrana Maria do Nascimento
*/

#include <iostream>

using namespace std;

int qntCoresIguais;

int buscaCoresIguais(int mMatriz[][200], int i, int j, int numLinhas, int numColunas, int cor);

int main()
{
    //a altura e a largura da minha parede
    int numLinhas, numColunas, tamMenorArea;

    cin >> numLinhas >> numColunas;
    tamMenorArea = -1;

    //criando uma parede com o tamanho maximo dela
    int mMatriz[200][200];

    //pintando a minha parede de branco
    for (int i = 0; i < numLinhas; i++)
    {
        for (int j = 0; j < numColunas; j++)
        {
            mMatriz[i][j] = -1;
        }
    }

    //pintando a minha parede de colorido
    for (int i = 0; i < numLinhas; i++)
    {
        for (int j = 0; j < numColunas; j++)
        {
            cin >> mMatriz[i][j];
        }
    }

    //percorrendo a minha parede
    for (int i = 0; i < numLinhas; i++)
    {
        for (int j = 0; j < numColunas; j++)
        {
            //verifico se a parede esta colorida ou se ela ja foi visitada
            if (mMatriz[i][j] != -1)
            {
                qntCoresIguais = buscaCoresIguais(mMatriz, i, j, numLinhas, numColunas, mMatriz[i][j]);
                if (tamMenorArea == -1 || tamMenorArea > qntCoresIguais)
                {
                    tamMenorArea = qntCoresIguais;
                }
            }
        }
    }

    cout << tamMenorArea << endl;

    return 0;
}

int buscaCoresIguais(int mMatriz[][200], int i, int j, int numLinhas, int numColunas, int cor)
{
    //verifico se a cor que eu envie esta nos limites da matriz
    if (i < 0 || i >= numLinhas)
    {
        return 0;
    }
    if (j < 0 || j >= numColunas)
    {
        return 0;
    }

    if (mMatriz[i][j] == cor)
    {
        //sinalizo como visitada
        mMatriz[i][j] = -1;

        //chamo a funcao para os vertices vizinhos para checar se sao da mesma cor que eu
        return 1 + buscaCoresIguais(mMatriz, i + 1, j, numLinhas, numColunas, cor) + buscaCoresIguais(mMatriz, i - 1, j, numLinhas, numColunas, cor) + buscaCoresIguais(mMatriz, i, j + 1, numLinhas, numColunas, cor) + buscaCoresIguais(mMatriz, i, j - 1, numLinhas, numColunas, cor);
    }

    return 0;
}