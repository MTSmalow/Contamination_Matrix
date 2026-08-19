# Matriz Contaminatória

Simulação de propagação de contaminação em uma população representada por uma matriz NxN. Cada célula é uma pessoa: `0` para não contaminada, `1` para contaminada. A cada ciclo, uma pessoa não contaminada pode ser infectada com base no número de vizinhos contaminados (8 vizinhos, incluindo diagonais) e em uma taxa de contaminação informada pelo usuário.

## Como funciona

1. O programa solicita o tamanho da matriz, a taxa de contaminação (0 a 1) e o número máximo de ciclos
2. Um "paciente zero" é sorteado aleatoriamente e marcado como contaminado
3. A cada ciclo, cada pessoa não contaminada é avaliada: quanto mais vizinhos contaminados, maior a chance de ser infectada
   - **Fórmula**: `probabilidade = vizinhos_contaminados × taxa`
4. A simulação para quando toda a população é contaminada ou quando o número máximo de ciclos é atingido

## Arquitetura

| Arquivo            | Responsabilidade                                          | Funções |
|---------------------|------------------------------------------------------------|---------|
| `matrix.h`          | Structs `t_grid`/`t_sim` e protótipos                      | —       |
| `grid.c`            | Alocação, liberação, inicialização e cópia da matriz        | 4       |
| `display.c`         | Exibição da matriz e contagem de contaminados                | 3       |
| `contamination.c`   | Paciente zero, vizinhos infectados e propagação do contágio | 4       |
| `simulation.c`      | Loop principal da simulação e relatórios de progresso        | 3       |
| `main.c`             | Leitura de parâmetros e ponto de entrada (`main`)            | 2       |

**Nota sobre estruturas**: As structs `t_grid` (matriz + tamanho) e `t_sim` (duas matrizes + taxa + ciclos) mantêm todas as funções dentro do limite de 4 parâmetros — sem elas, `update_cell` precisaria de 6 argumentos.

## Instalação e Compilação

### Clone e compile

```bash
git clone <url-do-repositorio>
cd Contamination_Matrix
make
```

### Regras do Makefile

```bash
make          # Compila o projeto
make clean    # Remove os arquivos .o
make fclean   # Remove .o e o executável
make re       # fclean + make
```

## Uso

### Comando básico

```bash
./contamination_matrix
```

Depois, insira os parâmetros solicitados:
```
Enter matrix size (n for an nxn matrix): 5
Enter contamination rate (value between 0 and 1): 0.3
Enter maximum number of cycles: 10
```

### Flags disponíveis

| Flag | Descrição | Exemplo |
|------|-----------|---------|
| `--help` | Mostra ajuda com todas as opções | `./programa --help` |
| `--color` | Saída com cores ANSI (vermelho=contaminado, verde=saudável) | `./programa --color` |
| `--text` | Mostra apenas estatísticas sem o grid | `./programa --text` |
| `--final` | Mostra apenas o estado final | `./programa --final` |

### Combinações de flags

```bash
# Todos os ciclos com grid colorido
./programa --color

# Todos os ciclos mostrando apenas estatísticas (sem grid)
./programa --text

# Apenas o estado final com cores
./programa --final --color

# Apenas o estado final com somente estatísticas
./programa --final --text

# Apenas o estado final
./programa --final

# Ver todas as opções
./programa --help
```

## Exemplo de execução

```bash
$ ./programa --color --final

Enter matrix size (n for an nxn matrix): 8
Enter contamination rate (value between 0 and 1): 0.4
Enter maximum number of cycles: 20

Entire population contaminated after 12 cycles.

Final state:
[grid colorido exibido aqui]
Contaminated people: 64 of 64 (100.00%)
```

## Cores utilizadas

- **Vermelho intenso** (`RGB: 255, 70, 70`): Células contaminadas
- **Verde claro** (`RGB: 100, 255, 120`): Células saudáveis

As cores utilizam ANSI 24-bit True Color para melhor compatibilidade e visual em terminais modernos.

## Detalhes técnicos

- **Alocação dinâmica**: Matriz e buffers alocados em tempo de execução
- **Validação de entrada**: Verifica limites e tipos de dados
- **Tratamento de memória**: Liberação correta em todos os caminhos de execução
- **Vizinhança**: Moore neighborhood (8 vizinhos incluindo diagonais)
- **Probabilidade**: Cálculo linear baseado no número de vizinhos contaminados