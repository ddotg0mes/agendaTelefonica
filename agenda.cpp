#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

struct Agenda
{
    char Nome[30];
    char Telefone[11];
};

#define limit 1992
#define FILE_NAME "telefonica.ccf"

Agenda Telefonica[limit];
int Contador = 0;
void carregaContato()
{
    FILE *file = fopen(FILE_NAME, "r");
    if (!file == NULL)
    {
        Contador = 0;

        while (!feof(file))
        {
            fgets(Telefonica[Contador].Nome, 30, file);
            if (strcmp(Telefonica[Contador].Nome, "") > 0)
            {
                fgets(Telefonica[Contador].Telefone, 12, file);
                Contador++;
            }
            else
            {
                cout << "Erro ao carregadar contato" << endl;
            }
        }
    }

    fclose(file);
}
void salvaContato(Agenda Contato, FILE *file)
{
    fputs(Contato.Nome, file);
    fputs(Contato.Telefone, file);
}
bool inserirContato(Agenda Contato)
{
    bool r = false;
    FILE *file = fopen(FILE_NAME, "a+");
    if (!file == NULL)
    {
        r = true;
        salvaContato(Contato, file);
        Telefonica[Contador] = Contato;
        Contador++;
    }
    else
    {
    }
    fclose(file);
    return r;
}

void Cadastro()
{
    cout << "########CADASTRAR CONTATO########" << endl;
    Agenda Contato;

    cout << "Nome e sobrenome: " << endl;
    fflush(stdin);
    fgets(Contato.Nome, 30, stdin);

    cout << "Telefone: " << endl;
    fflush(stdin);
    fgets(Contato.Telefone, 12, stdin);

    if (inserirContato(Contato))
    {
        cout << "Contato salvo";
        cout << endl;
    }
    else
    {
        cout << "Erro ao salvar contato";
        cout << endl;
    }
}
void exibeLista(int i)
{
    cout << "Usuario(a): " << Telefonica[i].Nome;
    cout << "Telefone: " << Telefonica[i].Telefone;
    cout << endl
         << "-------------------------------------" << endl
         << endl;
}
void Lista()
{
    cout << "########LISTA DE CONTATO########" << endl;
    for (int i = 0; i < Contador; i++)
    {
        exibeLista(i);
    }
}
bool buscarContato(char *a, char *b, int i, int LIMIT)
{
    if (a[i] == b[i])
    {
        i++;
        if (i < LIMIT)
        {
            return buscarContato(a, b, i, LIMIT);
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}
void Busca()
{
    cout << "########BUSCAR CONTATO########" << endl;
    char Nome[30] = {""};
    cout << "Digite o nome: " << endl;
    fflush(stdin);
    fgets(Nome, 30, stdin);

    int LIMIT = strlen(Nome);
    LIMIT--;

    for (int i = 0; i < Contador; i++)
    {
        if (strlen(Telefonica[i].Nome) >= LIMIT)
        {
            if (buscarContato(Nome, Telefonica[i].Nome, 0, LIMIT))
            {
                exibeLista(i);
            }
        }
    }
}
void menuDefault()
{
    int OP = 0;
    do
    {
        cout << "########AGENDA TELEFONICA########" << endl
             << endl;
        cout << "Selecione a opcao desejada:" << endl;
        cout << "1 - Cadastrar contato" << endl;
        cout << "2 - Lista de contatos" << endl;
        cout << "3 - Buscar contato" << endl;
        cout << "0 - Sair" << endl
             << endl;

        cin >> ("%i", OP);
        if (OP != 0)
        {
            switch (OP)
            {
            case 1:
                Cadastro();
                break;
            case 2:
                Lista();
                break;
            case 3:
                Busca();
                break;
            default:
                cout << "Opção invalida!" << endl;
                break;
            }
        }
        else
        {
            cout << "Sistema encerrado!" << endl;
        }
    } while (OP != 0);
}
int main()
{
    menuDefault();
    carregaContato();
    return 0;
}
