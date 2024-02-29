#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>

#define dataBase "database.dat"
#define tempdata "temp.dat"

struct Pessoas
{
    int id;
    char nome[50];
    char idade[3];
};

void menu()
{
    printf("\n\t\t=================== MENU ====================\n");
    printf("\t\t(1) Cadastrar Pessoas\n ");
    printf("\t\t(2) Vizualizar Cadastros\n ");
    printf("\t\t(3) Editar Cadastros \n");
    printf("\t\t(4) Excluir Cadastros \n");
    printf("\t\t(0) Sair do programa \n");
    printf("\t\t=============================================\n");
}

void cadastra_pessoas()
{
    FILE *file= fopen(dataBase,"ab");
    Pessoas novo ;
    if (file != NULL)
    {
       printf("\t\t insira o nome do usuario: ");
       scanf("%s",&novo.nome);
       printf("\t\t insira a idade do usuario: ");
       scanf("%s",&novo.idade);
       fseek(file,0,SEEK_END);
       novo.id= (ftell(file)/sizeof(Pessoas))+1;
       fwrite(&novo,sizeof(Pessoas),1,file);
       fclose(file);
        
    }
    else
    {
        printf ("não foi possivel abrir o arquivo");
    }
}

void visualiza_cadastros()
{
    FILE *file= fopen(dataBase,"rb");
    Pessoas consulta;
    if (file != NULL)
    {
        while (fread(&consulta,sizeof(Pessoas),1,file)==1)
        {
            printf("\n\t\t Nome: %s \n",consulta.nome);
            printf("\t\t Idade: %s\n",consulta.idade);
        }
        fclose(file);
        
    }
    else
    {
        printf ("não foi possivel abrir o arquivo");
    }
}
void edita_cadastros()
{
    FILE *file= fopen(dataBase,"r+b");
    Pessoas edicao;
    int status;
    char pesquisa[50];
    if (file != NULL)
    {
        printf("\t\tInsira o nome da pessoa que deseja alterar:  ");
        scanf("%s",&pesquisa);
        while (fread(&edicao,sizeof(Pessoas),1,file)==1)
        {
            if(strcmp(edicao.nome,pesquisa)==0)
            {
                printf("\t\t insira o novo nome do usuario: ");
                scanf("%s",&edicao.nome);
                printf("\t\t insira a idade do usuario: ");
                scanf("%s",&edicao.idade);
                fseek(file,-sizeof(Pessoas),SEEK_CUR);
                fwrite(&edicao,sizeof(Pessoas),1,file);
                status=1;
                break;
            }
            
        }
        fclose(file);
        if (status==1)
        {
            printf("\t\tCadastro alterado com sucesso !!");
        }
        else
        {
            printf("\t\tnao foi possivel encontrar o usuario");
        }
    }   
        
    
    else
    {
        printf ("\t\tnao foi possivel abrir o arquivo");
    }
}
void exclui_cadastros()
{
    char pesquisa[50];
    FILE *file= fopen(dataBase,"rb");
    if (file == NULL)
    {
    printf("Erro ao abrir o arquivo");
    exit(1);
    }  
    FILE *tempfile = fopen("temp.dat","wb");
    if(tempfile == NULL)
    {
    printf("Erro ao criar arquivo temporario");
    exit(1);
    }  

    
    printf("\n\t\tdigite o nome que deseja excluir : ");
    scanf("%s",&pesquisa);
    Pessoas lista;
    int encontrado;

    while (fread(&lista,sizeof(Pessoas),1 , file)==1)
    {
        if(strcmp(lista.nome,pesquisa)==0)
        {
            encontrado = 1;
        }
        else
        {
            fwrite(&lista,sizeof(Pessoas),1,tempfile);
        }
    }
    fclose(file);
    fclose(tempfile);
    remove(dataBase);
    rename(tempdata,dataBase);   
    if (encontrado==1)
    {
        printf("\t\tCliente excluido com sucesso");
    }
    else
    {
        printf("\t\t\ncliente não encontrado\n");
    }
}
int main()
{
    
    int op;
    do
    {
        menu();   
        printf("\t\t Selecione umas das opcoes: ");
        scanf("%d",&op);

        switch (op)
        {
        case 1:
            cadastra_pessoas();
            break;
        case 2:
            visualiza_cadastros();
            break;    
        case 3:
            edita_cadastros();
            break;
        case 4:
            exclui_cadastros();
            break;
        case 0:
            printf("saindo do programa");
            break;
        
        default:
                printf("opção invalida");
            break;
        }
    } while ( op != 0);
    
}