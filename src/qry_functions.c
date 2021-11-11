#include <stdio.h>
#include <stdlib.h>
#include "qry_functions.h"
#include "block.h"
#include "kdtree.h"
#include "linked_list.h"
#include "svg.h"

void catac(City_t _city, double x, double y, double w, double h, FILE *qrySVGFile, FILE *qryTXTFile){
    KDTree_t blocks_tree = get_blocks_tree(_city);
    Block_t block;
    print_rectangle(x, y, w, h, "#AB37C8", "#AA0044", qrySVGFile);


    // remover quadras
    List_t points_inside = get_info_inside_kd(blocks_tree, x, y, w, h);
    for(ListNode_t aux = get_list_first(points_inside); aux != NULL; aux = get_list_next(aux)){
        if(is_block_inside_rect(get_list_info(aux), x, y, w, h)){
            block = get_list_info(aux);
            double *key = get_block_point(get_list_info(aux));

            fprintf(qryTXTFile, "Quadra removida\n");
            print_block_txt(block, qryTXTFile);
            remove_kd_node(blocks_tree, key);
            free(get_list_info(aux));
        }
    }
    remove_list(points_inside, NULL);







}
