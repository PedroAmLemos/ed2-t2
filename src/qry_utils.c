#include <string.h>
#include <stdlib.h>
#include "qry_utils.h"

int is_name_in_list(List_t _list, char *name){
    for(ListNode_t node = get_list_first(_list); node != NULL; node = get_list_next(node)){
        if(strcmp(name, get_list_info(node))==0){
            return 1;
        }
    }
    return 0;
}
