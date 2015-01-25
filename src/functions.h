#include "header.h"

#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

float return_rand ();
int take_chance (float chance);
float rand_weighted (int low_bound, int high_bound, int weight);
int rand_val ( int min, int max );
t_nation return_nation ();
char *nation_to_string( t_nation nat );
char *gender_to_string( t_gender gnd );
char *extract_from_list ( const char *list_path );
int check_flag ( char flags, const char sample );
char *expand_string( char *str, int pos );
void mess_up_with_name( char *name, const char flags );
void generate_person( person *target );
char *describe_person( person *guy );

#endif