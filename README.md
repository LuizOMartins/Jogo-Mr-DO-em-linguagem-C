# Jogo Mr DO feito em C

OBJETIVO DO JOGO
Mr Do deve colher todas as frutas do cenário ou eliminar todos os fantasmas nas duas fases do
jogo. O jogo acaba quando:
i) Não existem mais frutas para colher
ii) Não existem mais fantasmas para eliminar
iii) O Mr Do é eliminado por um dos fantasmas.

REGRAS DO JOGO
 Mr Do!:
o Inicialmente localiza-se na base do cenário.
o Pode mover-se para direita, esquerda, para cima ou para baixo, de acordo com
as setas do teclado, respectivamente.
o Efetua disparos para ‘frente’ quando o jogador pressiona ‘espaço’.
o Abre novos caminhos no labirinto quando passa por cima de uma parede.
o Para colher frutas, basta colidir com elas.
o Morre quando ocorre uma colisão com um fantasma.
 Ninho de fantasmas:
o Localizam-se no centro do labirinto.
o Não pode se mover nem ser destruído
o Todos os fantasmas nascem na posição do ninho.
 Conjunto de fantasmas:
o Inicialmente localizam-se no ‘ninho’.

o Movem-se aleatoriamente pelo labirinto.
o Não podem abrir novos caminhos no labirinto.
o Se um fantasma é destruído por um tiro do Mr Do!, o jogador ganha 10
pontos.
o Pode haver no máximo 10 fantasmas vivos ao mesmo tempo.
o Nasce um fantasma a cada 3 segundos.
o Nascem no máximo 10 fantasmas por fase.
o Podem comer as frutas do cenário, sem dar pontos ao jogador.
o Elimina o Mr Do! ao colidir com ele.
 Um conjunto de frutas:
o Deve haver 32 frutas no início de casa fase espalhadas pelo labirinto.
o Quando o jogador pega uma fruta, ele ganha 50 pontos.
o Quando um fantasma pega uma fruta, a fruta é destruída.
 Tiros:
o É disparado pelo Mr Do! quando o jogador pressiona ‘espaço’.
o O tiro explode quando colide com fantasmas, frutas ou paredes do labirinto.
o A direção do tiro será a ultima direção pressionada pelo jogador.
o Um novo tiro só pode ser dado se o anterior já atingiu algum alvo.
o Se o tiro colidir com um fantasma, ambos são destruídos.
o Não há número máximo de tiros.

DETALHES TÉCNICOS
 Cenário:
o Será composto por uma matriz M de char de tamanho fixo em 23x60.
o Toda a lógica do jogo será controlada na matriz M.
o Essa matriz M deverá ser lida de um arquivo texto, com a configuração inicial
da fase. O arquivo fase1.txt deve configurar a primeira fase. O arquivo fase2.txt
deve configurar a segunda fase do jogo. O formato do arquivo é descrito no tópico
‘Arquivo de Configuração Inicial’.
 Labirinto:
o É o conjunto de caracteres vazios (32 em ASCII) que formam um caminho no
cenário.
 Arquivo de Configuração Inicial:
o Um arquivo texto com o mesmo número de linhas e colunas da matriz M,
configura o início de cada fase.
o Cada caracter do arquivo será um char que indica a posição e o tipo de um
elemento do jogo que será carregado na matriz M.
o Você deve mapear os elementos do jogo de acordo com a seguinte estratégia:
 ‘p’ = parede
 ‘i’ = fantasma
 ‘f’ = fruta
 ‘d’ = Mr Do!
 ‘t’ = tiro
 ‘n’ = ninho dos fantasmas


High Scores:
o O jogo deverá ter uma lista com os 5 melhores pontuadores.
o Essa lista será atualizada ao final de cada jogo com a pontuação e o nome do
jogador, caso ele tenha entrada na lista de 5 melhores pontuações.
o A lista deverá ser armazenada num arquivo binário chamado ‘highscores.bin’,
definida como uma struct com os elementos ‘nome’ e ‘pontos’.
o Uma visualização da lista deverá estar disponível no menu inicial do jogo (a
exibição da lista deve ser ordenada).
 Sair do Jogo
o Quando o jogador digitar a tecla ‘ESC’, o jogo deve ser encerrado.
o O encerramento do jogo com ‘ESC’ deve também salvar todo o estado atual do
cenário. Mais detalhes na seção ‘Salvar Jogo’.
o Ao encerrar o jogo, o programa deve voltar ao menu inicial.
 Salvar Jogo
o Quando o jogador decidir sair do jogo, o programa deve salvar o cenário com
todos os seus elementos e o estado do jogo.
o Os elementos do cenário devem ser salvos num arquivo texto chamado
‘continuar.txt’, no mesmo formato especificado para a configuração das fases do
jogo (na seção Arquivo de Configuração Inicial).
o O estado do jogo será gravado num arquivo binário chamado ‘estado.bin’.
Uma struct deve ser criada para gravar as seguintes informações:
 Pontuação do jogador
 Quantidade de fantasmas que já nasceram

 Movimentação dos Fantasmas
o Cada fantasma terá movimentações independentes.
o O movimento de um fantasma é aleatório, porém obedece as seguintes regras:
 Se fantasma está num cruzamento, sorteia nova direção que não seja a
de onde ele veio e que não tenha obstáculo (parede).
 Se não, se a próxima posição não for obstáculo (parede), continua
caminhando no sentido da última direção.
 Se não for nenhum dos casos anteriores, sorteia uma nova direção que
não seja obstáculo (parede). Neste caso, pode escolher também a direção
de onde o fantasma veio.
o Na seção Dicas está disponível um pseudo-código que implementa as regras
acima.

JOGABILIDADE
O jogo do Mr Do! que será criado pelo grupo de alunos deve ser interativo, ou seja, será um
programa que recebe interações do jogador via teclado, e em tempo real, interage com os
personagens do jogo.
O fluxo normal do jogo deve iniciar na apresentação do menu, em seguida iniciar a fase 1, e
caso o jogador completar a tarefa, apresentar a fase 2. Terminada a fase 2 com sucesso, o jogo
é finalizado e retorna ao menu inicial.

REQUISITOS MÍNIMOS

O QUE SE ESPERA DO PROGRAMA
 O programa deve implementar todas as regras descritas até aqui.
 O código fonte deve compilar sem apresentar erros de compilação.
 O executável deve rodar sem mostrar erros de execução.
 Manipulação dos arquivos texto e binários:

 fase1.txt
 fase2.txt
 continuar.txt
 estado.bin
 highscores.bin

 Uso de struct.
 Carregamento de arquivo para configurar as fases.
 Duas fases para o jogo.
 Salvar e continuar um jogo.
 Atualização e exibição do High Scores.
 Algoritmo de movimentação dos fantasmas.
 Identação e documentação (comentários) do código fonte .
 Modularização do código (uso de funções e passagem de parâmetros).

RODADA DE TESTE NA APRESENTAÇÃO
Na apresentação do trabalho, além da demonstração do programa funcionando com os
arquivos auxiliares do próprio aluno, haverá um teste no qual os arquivos auxiliares (fase1.txt,
fase2.txt, continuar.txt, estado.bin, highscores.bin ) serão fornecidos pelo professor.

DICAS DE IMPLEMENTAÇÃO
Para escrever o jogo na tela é preciso controlar o cursor e definir onde devem ser escritos os
dados da matriz. Pode-se utilizar a função gotoxy() para definir a posição de impressão na tela.
