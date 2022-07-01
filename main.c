#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool checkaVencedor(char t[3][3], char aux)
//Recebe uma matriz (tabuleiro) e um caracter (X ou O), verifica as
//posi��es e com o aux�lio de um contador  diz se h� ou n�o vencedor,
//se sim retorna true, caso contrario retorna false.
{
  int contador=0;
  for (int i=0;i<=2;i+=2) {
    if (t[i][0] == aux && t[i][1] == aux && t[1][2] == aux) {
      contador++;
    } else if (t[1][i] == aux && t[2][i] == aux && t[0][1] == aux) {
      contador++;
    } else if (t[0][i] == aux && t[1][i] == aux && t[2][1] == aux) {
      contador++;
    } else if (t[0][1] == aux && t[1][1] == aux && t[2][i] == aux) {
      contador++;
    } else if (t[1][1] == aux && t[2][1] == aux && t[0][i] == aux) {
      contador++;
    }
  }
  for (int j=1;j<=2;j++) {
    if (t[j][1] == aux && t[j][2] == aux && t[1][0] == aux) {
      contador++;
    }
  }
  if (contador == 1) {
    return true;
  } else {
    return false;
  }
}

bool converte_jogada(char jogada[100], int *lin, int *col)
//Recebe a string da jogada e dois ponteiros de linha e coluna, verifica se
//a jogada � valida (linha A at� C e coluna 1 at� 2), caso seja v�lida
//a fun��o altera as refer�ncias do ponteiro e retorna true, do contr�rio
//somente retorna false.
{
  int i=0, linha=0, coluna=0, contador=0, checarL=0, checarC=0;;
  for (i=0;;i++) {
    if (jogada[i] >= 65 && jogada[i] <= 67 && checarL != 0) {
      linha=jogada[i]-65;
      contador++;
      checarL++;
    } else if (jogada[i] >= 97 && jogada[i] <= 99 && checarL != 1) {
      linha=jogada[i]-97;
      contador++;
      checarL++;
    } else if (jogada[i] >= 49 && jogada[i] <= 51 && checarC != 1) {
      coluna=jogada[i]- 49;
      contador++;
      checarC++;
    } else if (contador > 1 || jogada[i] == '\0' || jogada[i+1] == '\0') {
      break;
    }
  }
  if (contador > 1 && checarL == 1 && checarC == 1) {
    *lin=linha;
    *col=coluna;
    return true;
  } else {
    return false;
  }
}

char proxJog(int v)
//Recebe o valor do contador e aplica "mod", caso seja par
//retornar� 'X' e 'O' se for impar.
{
  if (v%2==0) {
    return 'X';
  } else {
    return 'O';
  }
}

void ZeraTabuleiro(char a[3][3])
//Recebe uma matriz e "Zera" ela colocando '-' em todas as suas posi��es.
{
  for (int i=0; i<=2; i++) {
    for (int j=0; j<=2; j++) {
      a[i][j]='-';
    }
  }
}

void imprime (char v[3][3], int t)
//Recebe uma matriz e seu tamanho e roda um la�o imprimindo-a.
{
  printf("\n");
  printf(" � TABULEIRO � \n\n");
  for(int i=0; i<t;i++) {
    for (int j=0;j<t;j++) {
      printf("  %c  ",v[i][j]);
    }
    printf("\n\n");
  }
}

bool checkaPos(char jogo[3][3], int xlinhas, int xcolunas)
//Recebe uma matriz e valores de linha e coluna, verifica se o espa�o est�
//disponivel naqueles valores, se sim retorna true, caso contr�rio falso.
{
  if (jogo[xlinhas][xcolunas]=='-') {
    return true;
  } else {
    return false;
  }
}

int main(void)
//Recebe os nomes e a jogada e armazena em Strings, ap�s isso chama
//as fun��es de zerar e imprimir o tabuleiro entrando em um la�o
//que pede as jogadas e verifica se � v�lida ou n�o, saindo apenas
//quando houver um vencedor ou empate.
{
  char nome1[20], nome2[20], tabuleiro[3][3], jogadaStr[100];
  char XO=2, marcador = 'X';
  int maxjogadas=0, xlinhas=0, xcolunas=0;
  int *linha = &xlinhas, *coluna = &xcolunas;
  bool flag3=true;
  bool flag1=true;
  bool flag2=true;
  printf("Digite o nome do jogador 1: ");
  scanf(" %[^\n]", nome1);
  printf("Digite o nome do jogador 2: ");
  scanf(" %[^\n]", nome2);
  printf("\nPor conven��o, %s ser� o 'X' e o %s a 'O'.\n", nome1, nome2);
  ZeraTabuleiro(tabuleiro);
  imprime(tabuleiro, 3);
  do {
    if (marcador == 'X') {
      printf("� a vez do jogador %s de pe�a %c. \n", nome1, marcador);
    } else if (marcador == 'O') {
      printf("� a vez do jogador %s de pe�a %c. \n", nome2, marcador);
    }
    printf("Por favor, indique a sua jogada: \n");
    scanf(" %[^\n]", jogadaStr);
    flag1=converte_jogada(jogadaStr,linha,coluna);
    flag2=checkaPos(tabuleiro, xlinhas, xcolunas);
    if (flag1 == true && flag2 == true) {
      tabuleiro[xlinhas][xcolunas] = marcador;
      maxjogadas++;
      XO++;
      imprime(tabuleiro, 3);
      flag3=checkaVencedor(tabuleiro, marcador);
      if (flag3 == 1 && marcador == 'X') {
        printf("O jogador %s venceu. \n", nome1);
        break;
      } else if (flag3 == 1 && marcador == 'O') {
        printf("O jogador %s venceu. \n", nome2);
        break;
      }
      marcador=proxJog(XO);
    } else if (flag1 == false || flag2 == false) {
      printf("Jogada inv�lida, tente novamente. \n");
      imprime(tabuleiro, 3);
    }
  } while (maxjogadas<=8);
  if (maxjogadas >= 8) {
    imprime(tabuleiro, 3);
    printf("O jogo empatou! \n");
  }
  return 0;
}
