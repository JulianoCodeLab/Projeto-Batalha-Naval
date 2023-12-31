#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <locale.h>
#include <time.h>            //para usar srand e gerar numeros aleatorios

using namespace std;


//cabeçalho de funções
void menu_inicial();


//funções de manutenção

//funcao limpa tela
void limpa_tela(){

    system("CLS");
}


//--------------------JOGO--------------------------
//funcao 1.0 que cria e exibe e mostra o tabuleiro com 'A' (agua)
void inicia_tabuleiro(char tabuleiro [10][10], char mascara[10][10]){

    //popula o tabuleiro com 'A' (agua)
    int linha, coluna;

    for(linha = 0; linha < 10; linha++){
        for(coluna = 0; coluna < 10; coluna++){
            tabuleiro[linha][coluna] = 'A';
            mascara[linha][coluna] = '*';
        }
    }
}

//função que mostra indicadores do mapa
void exibe_mapa(){

    //mapa indicadores de colunas
    int cont;
    for(cont = 0; cont < 10; cont++){
        if(cont == 0){
            cout << "     ";
        }
        cout << cont << " ";
    }
    cout << "\n";
    for(cont = 0; cont < 10; cont++){
        if(cont == 0){
            cout << "     ";
        }
        cout << "| ";
    }
    cout << "\n";
}
//funcao 2.0 que cria e exibe e mostra o tabuleiro com 'A' (agua)
void exibe_tabuleiro(char tabuleiro [10][10],char mascara[10][10], bool mostraGabarito){

    //codico que modifica as cores do tabuleiro.

    //muda as cores da água para Azul quando o tiro for direcionado a ela
    char blue[] = { 0x1b, '[', '1', ';', '3', '4', 'm', 0};

    //muda as cores do barco pequeno para verde quando o tiro for direcionado a ela
    char green[] = { 0x1b, '[', '1', ';', '3', '2', 'm', 0};

    //cor natural da água
    char normal[] = { 0x1b, '[', '1', ';', '3', '9', 'm', 0};



    //popula o tabuleiro com 'A' (agua)
    int linha, coluna;
     //exibe o tabuleiro com 'A' (agua)
    for(linha = 0; linha < 10; linha++){
            cout << linha << " - ";
        for(coluna = 0; coluna < 10; coluna++){

            switch(mascara[linha][coluna]){
            case 'A':
                cout << blue << " " << mascara[linha][coluna] << normal;
                break;
            case 'P':
                cout << green << " " << mascara[linha][coluna] << normal;
                break;
            default:
                cout << " " << mascara[linha][coluna];
                break;
            }
        }
        //pula uma linha a cada 10 opções.
        cout << "\n";
    }

        if(mostraGabarito == false){
         //exibe o tabuleiro com 'A' (agua
        for(linha = 0; linha < 10; linha++){
            for(coluna = 0; coluna < 10; coluna++){
                cout << " " << tabuleiro[linha][coluna];
            }
            //pula uma linha a cada 10 opções.
            cout << "\n";
        }
    }


}

void   posiciona_barcos(char tabuleiro[10][10]){

    int cont, quantidade = 10, quantidadePosicionada = 0;

    //verifica se já posicionou todos os barcos
    while(quantidadePosicionada < quantidade){

        int linhaAleatoria = rand() % 10;       //Gera um numero aleatorio de 0 - 9
        int colunaAleatoria = rand() % 10;      //Gera um numero aleatorio de 0 - 9

        if( tabuleiro[linhaAleatoria][colunaAleatoria] == 'A'){

            //posciona barcos aleatoriamente.
            tabuleiro[linhaAleatoria][colunaAleatoria] = 'P';

            //aumenta a aquantidade de barcos posicionada
            quantidadePosicionada++;
        }
    }
}

void verifica_Tiro(char tabuleiro [10][10], int linhaJogada, int colunaJogada, int *pontos, string *mensagem){

    switch(tabuleiro[linhaJogada][colunaJogada]){
        case 'A':
            *mensagem = "VOCÊ ACERTOU A ÁGUA!";
            break;
        case 'P':
            *pontos = *pontos + 10;
            *mensagem = "BOM TRABALHO! VOCÊ ACERTOU UM PEQUENO BARCO";
            break;

            }
}

//função do jogo
void jogo(string nomeDoJogador){

    //variaveis Gerais
    char tabuleiro [10][10], mascara[10][10];           //tabuleiro do jogo
    int linha, coluna;                                  //auxiliares de navegação
    int linhaJogada, colunaJogada;                      //posicao escolhida pelo jogador
    //int estadoDeJogo = 1;                             // 1 = jogo acontecendo | 0 = fim de jogo
    int pontos = 0;                                     //pontuação do jogo
    int tentativas = 0, maximoTentativas = 5;           // tentativas do jogador
    int opcao;                                          //opcoes de fim de jogo
    string mensagem;                                    //mensagem de feedback para o jogador

    //inicia o tabuleiro com a 'A' (agua)
    inicia_tabuleiro(tabuleiro, mascara);

    //posiciona barcos aleatoriamente
    posiciona_barcos(tabuleiro);

    cout << "\n";

        while(tentativas < maximoTentativas){

            //limpa a tela do usuario
            limpa_tela();

            cout << "\n\t\t " << mensagem;
            cout << "\nPontos: " << pontos;
            cout <<"\nTentativas restantes : " << maximoTentativas - tentativas;
            cout << "\n------------------------\n\n";

            //mostra indicadores do mapa
            exibe_mapa();

            //exibe o tabuleiro com a mascara
            exibe_tabuleiro(tabuleiro, mascara, true);

            cout << "\n------------------------\n";


            //validação de dados
            linhaJogada = -1;
            colunaJogada = -1;

            while ((linhaJogada < 0 || colunaJogada < 0) || (linhaJogada > 9 || colunaJogada > 9) ){

                //pede ao usuario que digite uma posicao a ser jogada
            cout<< "\n" << nomeDoJogador << ", digite uma linha: \n";
            cout << ">> ";
            cin >> linhaJogada;

             cout<< "\n" << nomeDoJogador << ", digite uma coluna: \n";
            cout << ">> ";
            cin >> colunaJogada;

            }



            verifica_Tiro(tabuleiro, linhaJogada, colunaJogada, &pontos, &mensagem);

            //tira a mascara na posicao que o usuario escolheu
            mascara[linhaJogada][colunaJogada] = tabuleiro[linhaJogada][colunaJogada];

        tentativas++;
    }

    limpa_tela();

    cout << "\n\t    PARABENS!! VOCE FEZ: " << pontos << " PONTOS";

    cout << "\n\n\t\t* * * FIM DE JOGO * * *\n";
    cout << "\n\t\t1 - Jogar novamente\n";
    cout << "\n\t\t2 - Voltar ao Menu Principal\n";
    cout << "\n\t\t3 - Sair\n";
    cout << ">> ";
    cin >> opcao;

        switch(opcao){
    case 1:
        limpa_tela();
        jogo(nomeDoJogador);
        break;
    case 2:
        limpa_tela();
        menu_inicial();
        break;
    case 3:
        limpa_tela();
        cout << " \n\t\t* * * * ATÉ MAIS * * *\n\n";
        break;
        }

}


//opções de configuração do jogo
int opcoes(){

    int opcaojogo;
     //interface de menu de opcoes
    cout << "\n\t    ******** OPÇÕES ******** \n\n";

    cout << "\t\t  1 - SOBRE \n";
    cout << "\t\t---------------\n";
    cout << "\t\t  3 - VOLTAR \n";
    cout << "\t\t---------------\n";
    cout << "\n      Escolha uma opção e precione |ENTER|\n\n";
    cout << ">> ";

    //faz leitura da opcao escolhida pelo usuario.
    cin >> opcaojogo;

    //executa acao de acordo com a opcao escolhida pelo usuario
    switch(opcaojogo){
        case 1:
            limpa_tela();

            int opcaoSobre;

            cout << "\n\n\tEste programa tem como finalidade por em pratica e testar\n\t\tos conhecimentosem linguagem C++\n\t\t     ass: JULIANO SILVA\n\n";
            cout << "\n\t    ******** VOLTAR AO MENU PRINCIPAL ******** \n\n";
            cout << "\t\t\t  1 - VOLTAR \n\n";
            cout << "\t\t\t  2 - Sair \n\n";
            cout << ">> ";
            cin >> opcaoSobre;
            cout << "\n\n";
                if(opcaoSobre == 1){
                        limpa_tela();
                     menu_inicial();
                }
            break;
        case 2:
             limpa_tela();

            //Volta ao menu principal
             menu_inicial();
            break;


        }

}

//menu do jogo
void menu_inicial(){


    int opcao;                                          //opcao escolhida pelo user
    string nomeDoJogador;                               //nome do usuario
    //permite usar potuação nas palavras
    setlocale(LC_ALL,"");

    //laco de repeticao que da ao usuario apenas opcoes validas, e notifica caso a opcao seja invalida
    while(opcao < 1 || opcao > 3){

    //interface de menu inicial
    cout << "\n  ******** BEM VINDO A BATALHA NAVAL ******** \n\n";

    cout << "\t\t  1 - JOGAR \n";
    cout << "\t\t---------------\n";
    cout << "\t\t  2 - OPÇÕES \n";
    cout << "\t\t---------------\n";
    cout << "\t\t  3 - SAÍR \n";
    cout << "\t\t---------------\n";
    cout << "\n      Escolha uma opção e precione |ENTER|\n\n";
    cout << ">> ";

    //faz leitura da opcao escolhida pelo usuario.
    cin >> opcao;

    //executa acao de acordo com a opcao escolhida pelo usuario
    switch(opcao){
        case 1:
            limpa_tela();

        //solicita ao usuario que digite o nome
        cout << "\n\n\t* * * * Digite seu nome * * * *\n";
        cout << "\t>> ";
        cin >> nomeDoJogador;

            //iniciando o jogo
            jogo(nomeDoJogador);

            break;
        case 2:
            //opções do jogo
            limpa_tela();

            opcoes();

            break;
        case 3:
             limpa_tela();
            //sair do jogo
            cout << "\n\n  ******** ATÉ MAIS ******** \n\n";
            break;


        }
    }
}

int sair (){
}



//função principal
int main(){

    //para gerar numeros aleatórios toda vez que iniciar o programa
    srand(  (unsigned)time(NULL));

    //funcao menu inicial
    menu_inicial();

return 0;
}



