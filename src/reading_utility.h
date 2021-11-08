#ifndef READING_UTILITY_H_
#define READING_UTILITY_H_

// Função que retorna uma cópia do nome de um arquivo em um path
char *copy_file_name(char *origin);

// Função que copia uma ‘string’ e retorna a cópia
char *copy(char *origin);

// Função qeu concatena um nome de arquivo com um caminho
char *concat_path_file(char *path, char *fileName);

// Função que retorna o nome de um arquivo em um path
char *get_file_name(char *path);

#endif

