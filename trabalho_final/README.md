Descri��o do projeto:
	O projeto consiste em criar uma rede otimizada para a instala��o de fibra �ptica a partir de uma �rvore geradora m�nima, para isso adiciona-se o grafo em formato DOT em um arquivo .txt, com o nome "grafo", � pasta do diret�rio do programa.
	A raiz da nova �rvore ser� o primeiro v�rtice descrito no arquivo.
Exemplo:
graph {
	vertice1 -- vertice2 [label = 4];
	vertice2 -- vertice3 [label = 5];
        vertice2 -- vertice4 [label = 2];
}

	Por exemplo, a raiz da �rvore a partir do grafo exemplo seria 'vertice1', vertices esses que ser�o tipo char, e os valores de label ser�o tipo int.
	Ap�s feito, abrir o projeto (tipo 'projeto file') e pressionar 'compilar e executar' (ter� um desenho de uma engranagem com uma seta verde).
	A �rvore geradora minima estar� disponivel na paste diret�ria do projeto com o nome "minimum_spanning_tree".

Medi��es:

==13138==  Block was alloc'd at                                                 
==13138==    at 0x4C2DB8F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64
-linux.so)                                                                      
==13138==    by 0x4013ED: cria_sub_arvore (arvore.c:42)                         
==13138==    by 0x40148F: arvore_adicionar_subarvore (arvore.c:64)              
==13138==    by 0x4017D9: minimum_spannin_tree (arvore.c:174)                   
==13138==    by 0x401335: main (main.c:16)                                      
==13138==                                                                       
==13138==                                                                       
==13138== HEAP SUMMARY:                                                         
==13138==     in use at exit: 131 bytes in 13 blocks                            
==13138==   total heap usage: 97 allocs, 97 frees, 12,488 bytes allocated       
==13138==                                                                       
==13138== LEAK SUMMARY:                                                         
==13138==    definitely lost: 131 bytes in 13 blocks                            
==13138==    indirectly lost: 0 bytes in 0 blocks                               
==13138==      possibly lost: 0 bytes in 0 blocks                               
==13138==    still reachable: 0 bytes in 0 blocks                               
==13138==         suppressed: 0 bytes in 0 blocks                               
==13138== Rerun with --leak-check=full to see details of leaked memory  
	