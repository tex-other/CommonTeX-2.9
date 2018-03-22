
/*
 * @(#)io.c 2.5 EPA
 *
 * Copyright 1987,1988 Pat J Monardo
 *
 * Redistribution of this file is permitted through
 * the specifications in the file COPYING.
 *
 * 
 */

#include "tex.h"
#include "tokenstack.h"
#include "file.h"

int     last;
ascii   buffer[BUF_SIZE];
int     first;
int     max_buf_stack;

FILE *
a_open_in ()
{
    if (test_access(READ_ACCESS, INPUT_FILE_PATH))
        return (fopen(name_of_file, "r"));
    return NULL;
}

FILE *
a_open_out ()
{
    if (test_access(WRITE_ACCESS, NO_FILE_PATH))
        return (fopen(name_of_file, "w"));
    return NULL;
}

FILE *
b_open_in ()
{
    if (test_access(READ_ACCESS, FONT_FILE_PATH))
#ifdef __STDC__
        return (fopen(name_of_file, "rb"));
#else !__STDC__
        return (fopen(name_of_file, "r"));
#endif __STDC__
    return NULL;
}

FILE *
b_open_out ()
{
    if (test_access(WRITE_ACCESS, NO_FILE_PATH))
#ifdef __STDC__
        return (fopen(name_of_file, "wb"));
#else !__STDC__
        return (fopen(name_of_file, "w"));
#endif __STDC__
    return NULL;
}

FILE *
w_open_in ()
{
    if (test_access(READ_ACCESS, FORMAT_FILE_PATH))
#ifdef __STDC__
        return (fopen(name_of_file, "rb"));
#else !__STDC__
        return (fopen(name_of_file, "r"));
#endif __STDC__
    return NULL;
}

FILE *
w_open_out ()
{
    if (test_access(WRITE_ACCESS, NO_FILE_PATH))
#ifdef __STDC__
        return (fopen(name_of_file, "wb"));
#else !__STDC__
        return (fopen(name_of_file, "w"));
#endif __STDC__
    return NULL;
}

bool 
input_ln (f, bypass_eoln)
    alpha_file  f;
    bool        bypass_eoln;
{
    int         c;

    last = first;
    loop {
        c = getc(f);
        if (c == EOLN)
            break;
        if (c == EOF) {
            if (last == first)
                return FALSE;
            else
                break;
        }
        if (last > max_buf_stack) {
            max_buf_stack = last + 1;
            if (max_buf_stack == BUF_SIZE - 1)
                overflow("buffer size", BUF_SIZE);
        }
        buffer[last] = c;
        incr(last);
    }
    loop {
        if (last == first)
            break;  
        else if (buffer[last - 1] != ' ')
            break;
        else decr(last);
    }
    return TRUE;
}

term_input ()
{
    int     k;

    update_terminal();
    if (!input_ln(term_in, FALSE)) 
        fatal_error("! End of file on the terminal");
    term_offset = 0;
    decr(selector);
    if (last != first)
        for (k = first; k < last; incr(k))
            print_char(buffer[k]);
    print_ln();
    incr(selector);
}

bool
init_terminal ()
{
    loop {
        fputs("**", stdout);
        update_terminal();
        if (!input_ln(term_in, FALSE)) {
            puts("\n! End of file on the terminal...why?");
            return FALSE;
        }
        loc = first;
        while (loc < last && buffer[loc] == ' ')
            incr(loc);
        if (loc < last)
            return TRUE;
        puts("Please type the name of your input file.");
    }
}
