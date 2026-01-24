#include "../include/cub3d.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	"check number of args? nao por causa do tamanho do mapa"
    'obrigar esta ordem 4 textures+ floor + ceiling + map'
	return (0);
}

" TO DO: estava a pensar que se pode gerar uma file temporaria (existe enquanto o programa corre com o mapa)
char *map_hadling(char **map_file)
{
    char *type;
    -> how to normalize various lengths of walls?
        * Flood fill OR Edge scanning (which its more efficient) 
        -> check all 1 on edges 
    return type # if empty no error 
}
"
void error_message(char *type)
{
    "!! como lidar com os frees so abrir files depois de verificar TUDO
    mais facil do que um clean_up backtracking, right... ?"
    "SE HOUVER TEMPO to do: organizar types codes numa lista/ tabela..."
    
    printf("Error\n");
    'then if code associated print'
    if  (strncmp(type, "MI", 3))
        printf("missing identifier: have to be the following 4: NO; SO; WE; EA\n")
    else if(strncmp(type, "WI", 3))
        printf("wrong identifier: must be NO; SO; WE ou EA (one each, no repetions)\n");
    else if (strncmp(type, DU, 3))
        printf("duplicated identifier\n"); 'TO DO specify duplicated'
    else if (strncmp(type, TF, 3))
        printf(" texture file doesnt exist\n"); 'TO DO specifie which one...'
    'os dois proximos vai ter de se abrir as files....'
    else if (strncmp(type, FW, 3))
        printf("invalid RGB values for the floor: number ∈ [0, 255]; format (eg: F 220,100,0)\n ");
    else if (strncmp (type, CW, 3))
        printf ("invalid RGB values for the ceiling: number ∈ [0, 255]; format (eg: C 255,255,255)\n ");
    else if (strncmp(type, IF, 3))
        printf("most have one floor and one ceiling file, (really one for each)\n")
    'missed something...?'
    else if (strncmp(type, MW, 3))'ter uma subfuncao para  tratar de char *type aqui: NECESSARIO LER A FILE, se der error aqui tem de fechar!!!'       
    {
        printf("map walls: must be enclosed by walls (1)\n");
        printf("example:\n1111111\n1000001\n10N0001\n");
    }
    else if (strncmp(type, MP, 3))
        printf("missing player: represent one (and one only) by:N, S, E or  W \n");
    printf("if your message error doesnt seems right, confirm that you inputed the arguments in the order:\n");
    pritnf("XX ./path_to_the_XX_texture\nXX ./path_to_the_XX_texture\n");
    printf("XX ./path_to_the_XX_texture\nXX ./path_to_the_XX_texture\nFloor\nCeiling\nMAP\n");
}