#pragma once
#define CIRC_BUF_SIZE 64


typedef struct {
    char buf[CIRC_BUF_SIZE];
    unsigned char cur_elem;
} circ_buffer;


int circ_write(char val, circ_buffer* buffer);
int circmp(char* str, circ_buffer* buffer);




