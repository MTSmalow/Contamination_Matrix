# Matriz Contaminatória

Simulação de propagação de contaminação em uma população representada por
uma matriz NxN. Cada célula é uma pessoa: `0` para não contaminada, `1`
para contaminada. A cada ciclo, uma pessoa não contaminada pode ser
infectada com base no número de vizinhos contaminados (8 vizinhos, incluindo
diagonais) e em uma taxa de contaminação informada pelo usuário.

## Como funciona

1. O programa pede o tamanho da matriz, a taxa de contaminação (0 a 1) e o
   número máximo de ciclos.
2. Um "paciente zero" é sorteado e marcado como contaminado.
3. A cada ciclo, cada pessoa não contaminada é avaliada: quanto mais
   vizinhos contaminados ela tem, maior a chance de ser infectada
   (`probabilidade = vizinhos_contaminados * taxa`).
4. A simulação para quando toda a população é contaminada ou quando o
   número máximo de ciclos é atingido.

## Estrutura dos arquivos

| Arquivo            | Responsabilidade                                          | Funções |
|---------------------|------------------------------------------------------------|---------|
| `matrix.h`          | Structs `t_grid`/`t_sim` e protótipos                      | —       |
| `grid.c`            | Alocação, liberação, inicialização e cópia da matriz        | 4       |
| `display.c`         | Exibição da matriz e contagem de contaminados                | 3       |
| `contamination.c`   | Paciente zero, vizinhos infectados e propagação do contágio | 4       |
| `simulation.c`      | Loop principal da simulação e relatórios de progresso        | 3       |
| `main.c`             | Leitura de parâmetros e ponto de entrada (`main`)            | 2       |

As structs `t_grid` (matriz + tamanho) e `t_sim` (as duas matrizes + taxa +
ciclos) existem para manter todas as funções dentro do limite de 4
parâmetros — sem elas, funções como `update_cell` precisariam de 6
argumentos.

## Instruções

### Compilação

```bash
git clone <url-do-repositorio>
cd Contamination_Matrix
make
```


### Regras do Makefile

```
make          compila o projeto
make clean    remove os arquivos .o
make fclean   remove os .o e o libftprintf.a
make re       fclean + make
```


### Exemplo de entrada:

```
Enter matrix size (n for an nxn matrix): 5
Enter contamination rate (value between 0 and 1): 0.3
Enter maximum number of cycles: 10
```