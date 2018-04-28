#ifndef DICTIONARY_H
#define DICTIONARY_H

#define MAX_WORD_SIZE   40
#define MAX_DESC_SIZE  200

void dictionary_initialise();

int dictionary_read_from_file(const char * filename);

int dictionary_lookup(const char * word, char * meaning);



#endif
