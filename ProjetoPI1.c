// Walas Silva
// Projeto de PI

//Link do Vídeo
// https://drive.google.com/file/d/1ye3C7DHfuXL_Wc4qpa3Asv4un6JhJAhn/view?usp=share_link

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Variável globais
int op, sair, vazio = 0, posicao;
int alunos[30], faltas[30], turma[30];
float media[30], frequencia[30], notas[30][4];

void inicializar_vetor();
void Analisar_vetor();
void Validar_Matricula();
void Cadastrar_aluno();
void Remover_aluno();
void Atualizar_dados();
void Listar_Alunos_Cadastrados();
void Media_de_Notas();
void Frequencia();
void Listar_Alunos_Aprovados();
void Listar_Alunos_reprovado_media();
void Listar_Alunos_reprovado_falta();
void Sair();

// Função principal
int main() {

  // Inicializa o vetor alunos com -1 em todas as suas posições
  inicializar_vetor();

  do {
    printf(" 1 - Cadastrar aluno no vetor\n 2 - Remover um aluno do vetor\n 3 "
           "- Atualizar dados de um aluno do vetor \n 4 - Listar alunos "
           "cadastrados no vetor \n 5 - Listar alunos aprovados \n 6 - Listar "
           "alunos reprovados por média \n 7 - Listar alunos reprovados por "
           "faltas \n 8 - Sair \n\n");

    scanf("%d", &op);

    // Menu de opções
    switch (op) {

    case 1: {
      // Verifica se a matrícula já está cadastrada
      // Se não, cadastra um novo aluno no vetor
      Validar_Matricula();
    } break;

    case 2: {
      // Remover um aluno do vetor
      Remover_aluno();
    } break;

    case 3: {
      // Atualizar dados de um aluno do vetor
      Atualizar_dados();
    } break;

    case 4: {
      // Listar alunos cadastrados no vetor
      Listar_Alunos_Cadastrados();
    } break;

    case 5: {
      // Listar alunos aprovados
      Listar_Alunos_Aprovados();
    } break;

    case 6: {
      // Listar alunos reprovados por média
      Listar_Alunos_reprovado_media();

    } break;

    case 7: {
      // Listar alunos reprovados por faltas
      Listar_Alunos_reprovado_falta();
    } break;

    case 8: {
      // Encerra programa
      Sair();
    } break;

    default: {
      // Erro caso o número inserido seja invalido
      printf("Número digitado incorreto, tente novamente:\n");
      break;
    }
    }
    printf("\n");

  } while (sair != -1);
  return 0;
}

// Inicializa o vetor alunos com -1 em todas as suas posições
void inicializar_vetor() {
  for (int i = 0; i < 30; i++) {
    alunos[i] = -1;
  }
}
// Avalia se existe posições vazias no vetor de alunos
void Analisar_vetor() {
  int analise = 0, vazia = 0;

  for (int i = 0; i < 30; i++) {
    if (alunos[i] == -1) {

      // Avalia se existe posições vazias no vetor de alunos
      vazia++;
      vazio = vazia;
      if (analise == 0) {

        // Armazena a primeria posição vazia do vetor
        posicao = i;
        analise++;
      }
    }
  }
  analise = 0;
  vazia = 0;
}
// Analisa se a matrícula inserida já esá cadastrada
void Validar_Matricula() {

  int id, repitido = 0;

  printf("Digite o seu número de matrícula:\n");
  // scanf("%7d", &id);
  scanf("%7d", &id);

  for (int i = 0; i < 30; i++) {
    if (id == alunos[i]) {
      repitido++;
    }
  }

  if (repitido == 0) {
    Analisar_vetor();
    if (vazio > 0) {
      alunos[posicao] = id;
      Cadastrar_aluno();
    } else {
      printf("Não há vagas para cadastro de alunos!");
    }
  } else {
    repitido = 0;
    printf("\nNº de matrícula já cadastrada!\n");
  }
}
// Faz o cadastro das notas e faltas
void Cadastrar_aluno() {

  printf("Digite as suas 4 notas da disciplina:\n");
  for (int i = posicao; i < posicao + 1; i++) {
    for (int j = 0; j < 4; j++) {
      scanf("%f", &notas[i][j]);
    }
  }

  printf("Digite o seu número de faltas:\n");
  scanf("%d", &faltas[posicao]);

  printf("Digite a sua turma:\n");
  scanf("%d", &turma[posicao]);

  printf("\n");
}
// Remove aluno do vetor
void Remover_aluno() {

  int remover, contador = 0;

  printf("Informe o número de matrícula para ser apagado;\n");
  scanf("%d", &remover);

  for (int i = 0; i < 30; i++) {
    if (remover == alunos[i]) {
      contador++;
      alunos[i] = -1;

      printf("Removido com sucesso! \n");
    }
  }
  Analisar_vetor();
  if (contador == 0 && vazio < 30) {
    printf("Número de matrícula não encontrado\n");
  }
  if (vazio == 30) {
    printf("Vetor vazio!\n");
  }
  contador = 0;
}
// Atualiza notas e faltas do aluno selecionado
void Atualizar_dados() {

  int matricula, contador = 0;

  printf("Digite o Nº de matrícula:\n");
  scanf("%d", &matricula);

  for (int i = 0; i < 30; i++) {
    if (matricula == alunos[i]) {
      contador++;
      printf("Digite as suas 4 notas da disciplina:\n");
      for (int j = 0; j < 4; j++) {
        scanf("%f", &notas[i][j]);
      }

      printf("Digite o seu número de faltas:\n");
      scanf("%d", &faltas[i]);
    }
  }
  Analisar_vetor();
  if (contador == 0 && vazio < 30) {
    printf("Número de matrícula não encontrado\n");
  }
  if (vazio == 30) {
    printf("Vetor vazio!\n");
  }
  contador = 0;
}
// Lista todos os alunos cadastrados do vetor, com suas notas e faltas
void Listar_Alunos_Cadastrados() {
  for (int w = 0; w < 30; w++) {

    if (alunos[w] != -1) {
      printf("[%d] Matrícula: %d \n", w, alunos[w]);

      printf("Notas:\n");

      for (int j = 0; j < 4; j++) {
        printf("%.2lf\n", notas[w][j]);
      }

      printf("Faltas:\n");
      printf("%d\n", faltas[w]);
    }
  }
}
// Calcula a media das 4 notas de todos os alunos cadastrados
void Media_de_Notas() {
  float soma = 0;

  for (int i = 0; i < 30; i++) {
    if (alunos[i] != -1) {
      for (int j = 0; j < 4; j++) {
        soma = soma + notas[i][j];
        media[i] = soma / 4;
      }

      soma = 0;
    }
  }
}
// Calcula a frequência de cada aluno cadastrado em %
void Frequencia() {
  int aulas = 36;

  for (int i = 0; i < 30; i++) {
    if (alunos[i] != -1) {
      frequencia[i] = 100 - (faltas[i] * 100 / aulas);
    }
  }
}
// Lista alunos aprovados com notas >= 7 e frenquência >= 60%
void Listar_Alunos_Aprovados() {
  for (int i = 0; i < 30; i++) {
    if (alunos[i] != -1) {
      Media_de_Notas();
      Frequencia();
      if (media[i] >= 7 && frequencia[i] >= 60) {

        printf("[%d] Matrícula: %d \n", i, alunos[i]);

        printf("Médias: %.2f \n", media[i]);

        printf("\n");
        printf("Frequência: %.2f\n", frequencia[i]);
      }
    }
  }
}
// Lista alunos reprovados com notas < 7
void Listar_Alunos_reprovado_media() {
  int cont = 0;
  for (int i = 0; i < 30; i++) {
    if (alunos[i] != -1) {
      Media_de_Notas();
      if (media[i] < 7) {
        printf("Nº de matrícula: %d\n", alunos[i]);
        printf("Média: %.2f\n5", media[i]);
        cont++;
      }
    }
  }
  if (cont == 0) {
    printf("Nenhum aluno reprovado!\n");
  }
}
// Lista alunos reprovados com frenquência < 60%
void Listar_Alunos_reprovado_falta() {
  int cont = 0;
  for (int i = 0; i < 30; i++) {
    if (alunos[i] != -1) {
      Frequencia();
      if (frequencia[i] < 60) {
        printf("Nº de matrícula: %d\n", alunos[i]);
        printf("Frenquência em %% : %.2f\n", frequencia[i]);
        cont++;
      }
    }
  }
  if (cont == 0) {
    printf("Nenhum aluno reprovado!\n");
  }
}
// Encerra o programa
void Sair() {
  sair = -1;
  }