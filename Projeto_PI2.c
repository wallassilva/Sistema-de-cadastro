// Walas Silva
// Projeto de PI

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Definicao do limite de cadastros
#define MAX 8

// Struct
typedef struct {
  int matricula;
  float notas[4];
  char nome_aluno[30];
  int turma;
  int faltas;
  float media;
  float frequencia;
} inf_cadastro;

// Variável globais
int posicao, qtde = 0;
inf_cadastro cad[MAX];
FILE *arq;

// Funcoes
int Validar_Matricula();
void Cadastrar_aluno();
void Remover_aluno();
void Atualizar_dados();
void Listar_Alunos_Cadastrados();
void Media_de_Notas(int w);
void Frequencia(int w);
void Listar_Alunos_Aprovados();
void Listar_Alunos_reprovado_media();
void Listar_Alunos_reprovado_falta();
void Listar_alunos_por_turma();
void Ordenacao_dos_dados();
void Sair();

// Funcoes de ordenacao
void selectionsort_matricula(inf_cadastro cad[], int r);
void selectionsort_nome(inf_cadastro cad[], int r);
void selectionsort_media(inf_cadastro cad[], int r);
void selectionsort_qfaltas(inf_cadastro cad[], int r);
void troca(inf_cadastro cad[], int pos_max, int pos2);

// Funcoes de arquivo
void escrever_novo_aluno(inf_cadastro a);
void ler_alunos(int *qtde, inf_cadastro cad[]);
void excluir(int remover);
void atualizar(int matricula, inf_cadastro atualiza);

// Menu
int main() {
  int op;

  do {
    printf(" 1 - Cadastrar aluno no arquivo\n 2 - Remover um aluno do arquivo\n 3 "
           "- Atualizar dados de um aluno do arquivo\n 4 - Listar alunos "
           "cadastrados no arquivo \n 5 - Listar alunos aprovados \n 6 - Listar "
           "alunos reprovados por média \n 7 - Listar alunos reprovados por "
           "faltas \n 8 - Listar alunos por turma \n 9- Ordenar os dados \n 0 "
           "- Sair \n\n");

    scanf("%d", &op);

    // Menu de opções
    switch (op) {
    case 0: {
      // Encerra programa
    } break;
    case 1: {
      // Cadastra um novo aluno no vetor
      Cadastrar_aluno();
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
      // Listar alunos por turma
      Listar_alunos_por_turma();
      // mostrar_cad();
    } break;
    case 9: {
      // Ordenação dos dados
      Ordenacao_dos_dados();
    } break;
    default: {
      // Erro caso o número inserido seja invalido
      printf("Número digitado incorreto, tente novamente:\n");
    }
    }

    getchar();
    printf("Pressione ENTER para continuar..\n");
    getchar();

  } while (op != 0);
  return 0;
}

// Analisa se a matrícula inserida já esá cadastrada
int Validar_Matricula() {
  int pos;
  int id;
  int repitido = 0, varia;
  ler_alunos(&qtde, cad);

  if (qtde < MAX) {

    printf("Digite o seu número de matrícula:\n");
    scanf("%d", &id);

    // Verifica se a matricula é valida
    if (id >= 2021000 && id < 2021100) {
      // Verifica se a matricula é repitida
      for (int i = 0; i < qtde; i++) {
        if (id == cad[i].matricula)
          repitido++;
      }

      if (repitido == 0) {
        ler_alunos(&qtde, cad);
        pos = qtde;

        cad[posicao].matricula = id;
        return 0;
      } else {
        printf("\nNº de matrícula já cadastrada!\n\n");
        return 1;
      }
    } else {
      printf("Nº de matrícula inválido, digite outro número!\n\n");
      return 1;
    }
  } else {
    printf("Nao ha vagas para cadastro\n\n");
    return 1;
  }
}
// Faz o cadastro das notas e faltas
void Cadastrar_aluno() {

  int falta;
  float nota;

  ler_alunos(&qtde, cad);

  if (Validar_Matricula() == 0) {
    // Faz o cadrastro das informacoes
    for (int i = posicao; i < posicao + 1; i++) {
      for (int j = 0; j < 4; j++) {

        printf("Digite a %d nota:\n", j + 1);
        scanf("%f%*c", &nota);
        if (nota >= 0 && nota <= 10) {
          cad[i].notas[j] = nota;
        } else {

          do {
            printf("Nota inválida!\n");
            printf("Digite novamente a %d nota:\n", j + 1);
            scanf("%f%*c", &nota);
          } while ((nota < 0) || (nota > 10));
          cad[i].notas[j] = nota;
        }
      }

      Media_de_Notas(i);

      printf("Digite o seu nome:\n");
      fgets(cad[i].nome_aluno, 30, stdin);
      cad[i].nome_aluno[strcspn(cad[i].nome_aluno, "\n")] = '\0';

      printf("Digite a sua turma\n");
      scanf("%d", &cad[i].turma);

      printf("Digite o seu número de faltas:\n");
      scanf("%d", &falta);

      if (falta >= 0 && falta <= 36) {
        cad[i].faltas = falta;
      } else {
        while ((falta < 0) || (falta > 36)) {
          printf("N° de faltas inválida\n");
          printf("Digite novamente o N° de faltas:\n");
          scanf("%d", &falta);
        }

        cad[i].faltas = falta;
      }
      Frequencia(i);

      escrever_novo_aluno(cad[i]);
    }
  }
}
// Remove aluno do vetor
void Remover_aluno() {

  int remover, cont = 0, ind;
  ler_alunos(&qtde, cad);

  printf("Informe o número de matrícula para ser apagado:\n");
  scanf("%d", &remover);
  // Verifica se a matricula é valida
  if (remover >= 2021000 && remover < 2021100) {
    for (int i = 0; i < qtde; i++) {
      // Verifica se existe a matricula
      if (remover == cad[i].matricula) {
        cont++;
        ind = i;
        // Remover o cadrastro do arquivo
        excluir(remover);
        printf("Removido com sucesso!\n\n");
      }
    }
    for (int q = ind + 1; q < qtde; q++) {
      cad[q - 1].matricula = cad[q].matricula;
      for (int j = 0; j < 4; j++) {
        cad[q - 1].notas[j] = cad[q].notas[j];
      }
      cad[q - 1].media = cad[q].media;
      cad[q - 1].frequencia = cad[q].frequencia;
      strcpy(cad[q - 1].nome_aluno, cad[q].nome_aluno);
      cad[q - 1].faltas = cad[q].faltas;
      cad[q - 1].turma = cad[q].turma;
    }

    if (cont != 0) {
      qtde--;
    } else {
      printf("Número de matrícula não encontrado.\n\n");
    }
  } else {
    printf("N° de matricula invalido!\n");
  }
}
// Atualiza notas e faltas do aluno selecionado
void Atualizar_dados() {

  int matr, contador = 0, falta;
  float nota;
  inf_cadastro atualiza;

  ler_alunos(&qtde, cad);

  printf("Digite o Nº de matrícula:\n");
  scanf("%d", &matr);
  // Verifica se a matricula é valida
  if (matr >= 2021000 && matr < 2021100) {
    for (int i = 0; i < qtde; i++) {
      // Verifica se a matricula existe
      if (matr == cad[i].matricula) {
        contador = 1;

        for (int j = 0; j < 4; j++) {
          printf("Digite a %d nota:\n", j + 1);
          scanf("%f%*c", &nota);
          if (nota >= 0 && nota <= 10) {
            cad[i].notas[j] = nota;
          } else {

            do {
              printf("Nota inválida!\n");
              printf("Digite novamente a %d nota:\n", j + 1);
              scanf("%f%*c", &nota);
            } while ((nota < 0) || (nota > 10));
            cad[i].notas[j] = nota;
          }
        }

        printf("Digite o seu número de faltas:\n");
        scanf("%d", &falta);

        if (falta >= 0 && falta <= 36) {
          cad[i].faltas = falta;
        } else {
          while ((falta < 0) || (falta > 36)) {
            printf("N° de faltas inválida\n");
            printf("Digite novamente o N° de faltas:\n");
            scanf("%d", &falta);
          }

          cad[i].faltas = falta;
        }

        Media_de_Notas(i);
        Frequencia(i);

        atualiza = cad[i];
        // Atualiza o arquivo
        atualizar(matr, atualiza);
      }
    }
    if (contador == 0 && qtde != 0) {
      printf("Número de matrícula não encontrado\n");
    } else if (contador == 0 && qtde == 0) {
      printf("Ainda não foi feito cadrastros\n");
    }
  } else {
    printf("Matricula inválida!\n");
  }
  if (contador == 1) {
    printf("Cadastro atualizado com sucesso!\n");
  }
}
// Lista todos os alunos cadastrados do vetor, com suas notas e faltas
void Listar_Alunos_Cadastrados() {
  int turmaa, cont = 0;
  printf("Informe a sua turma\n");
  scanf("%d", &turmaa);
  ler_alunos(&qtde, cad);

  for (int i = 0; i < qtde; i++) {

    if (turmaa == cad[i].turma) {
      cont++;
      if (cad[i].matricula != -1) {
        printf("[%d] Matrícula: %d \n", i + 1, cad[i].matricula);

        printf("Notas na disciplina: ");
        printf("%.2f %.2f %.2f %.2f\n", cad[i].notas[0], cad[i].notas[1],
               cad[i].notas[2], cad[i].notas[3]);
        printf("Faltas: %d\n", cad[i].faltas);
      }
    }
  }
  if (cont == 0) {
    printf("Nao ha alunos dessa turma cadrastrados\n\n");
  }
}
// Calcula a media das 4 notas de todos os alunos cadastrados
void Media_de_Notas(w) {
  float soma = 0;

  soma = soma + cad[w].notas[0] + cad[w].notas[1] + cad[w].notas[2] +
         cad[w].notas[3];
  cad[w].media = soma / 4;
}
// Calcula a frequência de cada aluno cadastrado em %
void Frequencia(w) {
  int aulas = 36;
  cad[w].frequencia = 100 - (cad[w].faltas * 100 / aulas);
}
// Lista alunos aprovados com notas >= 7 e frenquência >= 60%
void Listar_Alunos_Aprovados() {
  int turmaa, cont = 0;

  printf("Informe a sua turma\n");
  scanf("%d", &turmaa);

  ler_alunos(&qtde, cad);

  for (int i = 0; i < qtde; i++) {
    if (turmaa == cad[i].turma) {
      if (cad[i].media >= 7 && cad[i].frequencia >= 60) {
        cont++;
        printf("[%d] Matrícula: %d \n", i + 1, cad[i].matricula);

        printf("Médias: %.2f \n", cad[i].media);
        printf("Frequência: %.2f\n", cad[i].frequencia);
      }
    }
  }
  if (cont == 0) {
    printf("Nao ha alunos dessa turma cadrastrados\n\n");
  }
}
// Lista alunos reprovados com notas < 7
void Listar_Alunos_reprovado_media() {
  int cont = 0, contt = 0;
  int turmaa;
  printf("Informe a sua turma\n");
  scanf("%d", &turmaa);

  ler_alunos(&qtde, cad);
  for (int i = 0; i < qtde; i++) {
    if (turmaa == cad[i].turma) {
      contt++;
      if (cad[i].media < 7) {
        printf("Nº de matrícula: %d\n", cad[i].matricula);
        printf("Média: %.2f\n", cad[i].media);
        cont++;
      }
    }
  }

  if (cont == 0 && contt != 0) {
    printf("Nao ha alunos dessa turma reprovados por falta \n\n");
  }

  if (contt == 0) {
    printf("Nao ha alunos dessa turma cadrastrados \n\n");
  }
}
// Lista alunos reprovados com frenquência < 60%
void Listar_Alunos_reprovado_falta() {
  int cont = 0, contt = 0, turmaa;

  printf("Informe a sua turma\n");
  scanf("%d", &turmaa);

  ler_alunos(&qtde, cad);
  for (int i = 0; i < qtde; i++) {
    if (turmaa == cad[i].turma) {
      contt++;
      if (cad[i].frequencia < 60) {
        cont++;
        printf("Nº de matrícula: %d\n", cad[i].matricula);
        printf("Frenquência em %% : %.2f\n", cad[i].frequencia);
      }
    }
  }
  if (cont == 0 && contt != 0) {
    printf("Nao ha alunos dessa turma reprovados por falta \n\n");
  }

  if (contt == 0) {
    printf("Nao ha alunos dessa turma cadrastrados \n\n");
  }
}
// Listar alunos por turma
void Listar_alunos_por_turma() {
  int turmaa, cont;
  printf("Informe a turma:\n");
  scanf("%d", &turmaa);
  ler_alunos(&qtde, cad);

  for (int i = 0; i < qtde; i++) {
    if (turmaa == cad[i].turma) {
      printf("[%d] Matrícula: %d \n", i + 1, cad[i].matricula);
      printf("Médias: %.2f \n", cad[i].media);
      cont++;
    }
  }
  if (cont == 0) {
    printf("Nao ha alunos dessa turma cadrastrados\n\n");
  }
}

// Menu de ordenação de cadastros
void Ordenacao_dos_dados() {
  int opc;
  ler_alunos(&qtde, cad);

  while (opc != 0) {

    printf("******** Informe qual  forma de ordenação *******\n");
    printf("1 - Matricula\n2 - Nome \n3 - Média \n4 - Quantidade de "
           "faltas \n0 - Voltar ao menu principal\n");
    scanf("%d", &opc);

    switch (opc) {
    case 0: {
      continue;
    } break;
    case 1: {
      selectionsort_matricula(cad, qtde);
    } break;
    case 2: {
      selectionsort_nome(cad, qtde);
    } break;
    case 3: {
      selectionsort_media(cad, qtde);
    } break;
    case 4: {
      selectionsort_qfaltas(cad, qtde);
    } break;
    default: {
      printf("Opcao invalida!, tente novamente\n");
    }
    }
    getchar();
    printf("Pressione ENTER para continuar...\n");
    getchar();
  }
}
// Funcoes de ordenação
// De acordo com a matricula
void selectionsort_matricula(inf_cadastro cad[], int r) {

  int i, j;
  int pos_max, pos2;
  printf("\n");

  for (i = 0; i < r - 1; i++) {
    pos_max = 0;

    for (j = 1; j < r - i; j++) {
      if (cad[j].matricula > cad[pos_max].matricula) {
        pos_max = j;
      }
    }
    pos2 = r - 1 - i;
    troca(cad, pos_max, pos2);
  }

  for (i = 0; i < r; i++) {
    if (cad[i].matricula != -1) {
      printf("Matrícula: [%d]\n", cad[i].matricula);
      printf("Nome: %s\n", cad[i].nome_aluno);
      printf("Média: %.2f\n", cad[i].media);
      printf("Quantidade de faltas: %d\n", cad[i].faltas);
    }
  }
}
// De acordo com o nome
void selectionsort_nome(inf_cadastro cad[], int r) {

  int i, j;
  int pos_max, pos2;
  printf("\n");

  for (i = 0; i < r - 1; i++) {
    pos_max = 0;

    for (j = 1; j < r - i; j++) {

      if (strcmp(cad[j].nome_aluno, cad[pos_max].nome_aluno) > 0) {
        pos_max = j;
      }
    }
    pos2 = r - 1 - i;
    troca(cad, pos_max, pos2);
  }

  for (i = 0; i < r; i++) {
    if (cad[i].matricula != -1) {
      printf("Matrícula: [%d]\n", cad[i].matricula);
      printf("Nome: %s\n", cad[i].nome_aluno);
      printf("Média: %.2f\n", cad[i].media);
      printf("Quantidade de faltas: %d\n", cad[i].faltas);
    }
  }
}
// De acordo com a media
void selectionsort_media(inf_cadastro cad[], int r) {

  int i, j;
  int pos_max, pos2;
  printf("\n");

  for (i = 0; i < r - 1; i++) {
    pos_max = 0;

    for (j = 1; j < r - i; j++) {

      if (cad[j].media > cad[pos_max].media) {
        pos_max = j;
      }
    }
    pos2 = r - 1 - i;
    troca(cad, pos_max, pos2);
  }
  for (i = 0; i < r; i++) {
    if (cad[i].matricula != -1) {
      printf("Matrícula: [%d]\n", cad[i].matricula);
      printf("Nome: %s\n", cad[i].nome_aluno);
      printf("Média: %.2f\n", cad[i].media);
      printf("Quantidade de faltas: %d\n", cad[i].faltas);
    }
  }
}
// De acordo com as faltas
void selectionsort_qfaltas(inf_cadastro cad[], int r) {

  int i, j;
  int pos_max, pos2;
  printf("\n");

  for (i = 0; i < r - 1; i++) {
    pos_max = 0;

    for (j = 1; j < r - i; j++) {

      if (cad[j].faltas > cad[pos_max].faltas) {
        pos_max = j;
      }
    }
    pos2 = r - 1 - i;
    troca(cad, pos_max, pos2);
  }

  for (i = 0; i < r; i++) {
    if (cad[i].matricula != -1) {
      printf("Matrícula: [%d]\n", cad[i].matricula);
      printf("Nome: %s\n", cad[i].nome_aluno);
      printf("Média: %.2f\n", cad[i].media);
      printf("Quantidade de faltas: %d\n", cad[i].faltas);
    }
  }
}

// Funcao de troca para ordenar os cadrastros
void troca(inf_cadastro cad[], int pos_max, int pos2) {
  int i;
  inf_cadastro tmp;

  tmp.matricula = cad[pos_max].matricula;
  for (i = 0; i < 4; i++)
    tmp.notas[i] = cad[pos_max].notas[i];
  strcpy(tmp.nome_aluno, cad[pos_max].nome_aluno);
  tmp.turma = cad[pos_max].turma;
  tmp.faltas = cad[pos_max].faltas;
  tmp.media = cad[pos_max].media;
  tmp.frequencia = cad[pos_max].frequencia;

  cad[pos_max].matricula = cad[pos2].matricula;
  for (i = 0; i < 4; i++)
    cad[pos_max].notas[i] = cad[pos2].notas[i];
  strcpy(cad[pos_max].nome_aluno, cad[pos2].nome_aluno);
  cad[pos_max].turma = cad[pos2].turma;
  cad[pos_max].faltas = cad[pos2].faltas;
  cad[pos_max].media = cad[pos2].media;
  cad[pos_max].frequencia = cad[pos2].frequencia;

  cad[pos2].matricula = tmp.matricula;
  for (i = 0; i < 4; i++)
    cad[pos2].notas[i] = tmp.notas[i];
  strcpy(cad[pos2].nome_aluno, tmp.nome_aluno);
  cad[pos2].turma = tmp.turma;
  cad[pos2].faltas = tmp.faltas;
  cad[pos2].media = tmp.media;
  cad[pos2].frequencia = tmp.frequencia;
}

// Funções de arquivo

// Ler aluno
void ler_alunos(int *qtde, inf_cadastro cad[]) {

  FILE *arq;
  int i = 0;
  arq = fopen("arquivo-alunos.txt", "r");
  if (arq == NULL) {

  } else {
    // Ler cadastros ate o fim do arquivo
    while (fscanf(arq, "%d %f %f %f %f %d %d %f %f %[^\n]s", &cad[i].matricula,
                  &cad[i].notas[0], &cad[i].notas[1], &cad[i].notas[2],
                  &cad[i].notas[3], &cad[i].turma, &cad[i].faltas,
                  &cad[i].media, &cad[i].frequencia, cad[i].nome_aluno) != EOF)
      i++;

    fclose(arq);
  }
  *qtde = i;
}
// Inclui um novo aluno ao final do arquivo
void escrever_novo_aluno(inf_cadastro a) {

  FILE *arq;
  arq = fopen("arquivo-alunos.txt", "a");
  fprintf(arq, "%d  %.2f  %.2f  %.2f  %.2f  %d  %d  %.2f  %.2f  %s \n",
          a.matricula, a.notas[0], a.notas[1], a.notas[2], a.notas[3], a.turma,
          a.faltas, a.media, a.frequencia, a.nome_aluno);
  fclose(arq);
}
// Exlcuir um cadrastro escolhido pelo usuário no arquivo
void excluir(int remover) {

  int i = 0;
  FILE *arq, *temporario;
  arq = fopen("arquivo-alunos.txt", "r+");
  temporario = fopen("temp.txt", "w");

  while (fscanf(arq, "%d %f %f %f %f%*c %d %d %f %f %[^\n]s", &cad[i].matricula,
                &cad[i].notas[0], &cad[i].notas[1], &cad[i].notas[2],
                &cad[i].notas[3], &cad[i].turma, &cad[i].faltas, &cad[i].media,
                &cad[i].frequencia, cad[i].nome_aluno) != EOF) {
    // Cria um arquivo temporario com todos os cadrastro exceto o que o usuario
    // quer apagar
    if (cad[i].matricula != remover) {
      fprintf(temporario,
              "%d  %.2f  %.2f  %.2f  %.2f  %d  %d  %.2f  %.2f  %s \n",
              cad[i].matricula, cad[i].notas[0], cad[i].notas[1],
              cad[i].notas[2], cad[i].notas[3], cad[i].turma, cad[i].faltas,
              cad[i].media, cad[i].frequencia, cad[i].nome_aluno);
    }
    i++;
  }

  fclose(temporario);
  fclose(arq);
  // Apaga o arquivo original
  remove("arquivo-alunos.txt");
  // Renomeia o arquivo temporario com o mesmo nome do original
  rename("temp.txt", "arquivo-alunos.txt");
}
// Atualiza um cadrastro escolhido pelo usuário no arquivo
void atualizar(int matricula, inf_cadastro a) {

  int i = 0;
  FILE *arq, *temporario;
  arq = fopen("arquivo-alunos.txt", "r+");
  temporario = fopen("temp.txt", "w");

  while (fscanf(arq, "%d %f %f %f %f%*c %d %d %f %f %[^\n]s", &cad[i].matricula,
                &cad[i].notas[0], &cad[i].notas[1], &cad[i].notas[2],
                &cad[i].notas[3], &cad[i].turma, &cad[i].faltas, &cad[i].media,
                &cad[i].frequencia, cad[i].nome_aluno) != EOF) {
    // Cria um arquivo temporario com todos os cadrastro e faz a atualizacao dos
    // dados de acordo com a matricula inserida pelo usuario
    if (cad[i].matricula != matricula) {
      fprintf(temporario, "%d %.2f %.2f %.2f %.2f %d %d %.2f %.2f %s\n",
              cad[i].matricula, cad[i].notas[0], cad[i].notas[1],
              cad[i].notas[2], cad[i].notas[3], cad[i].turma, cad[i].faltas,
              cad[i].media, cad[i].frequencia, cad[i].nome_aluno);

    } else {
      fprintf(temporario, "%d %.2f %.2f %.2f %.2f %d %d %.2f %.2f %s\n",
              a.matricula, a.notas[0], a.notas[1], a.notas[2], a.notas[3],
              a.turma, a.faltas, a.media, a.frequencia, a.nome_aluno);
    }
    i++;
  }
  fclose(temporario);
  fclose(arq);
  // Apaga o arquivo original
  remove("arquivo-alunos.txt");
  // Renomeia o arquivo temporario com o mesmo nome do original
  rename("temp.txt", "arquivo-alunos.txt");
}