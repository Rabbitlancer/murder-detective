#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#ifndef __HEADER_H__
#define __HEADER_H__

typedef enum {
	ARDESIAN,
	SLEBRIAN,
	TOTNAN,
	WALLARISH,
	USSAIRIC,
	SINPOURI
} t_nation;

typedef enum {
	MALE,
	FEMALE
} t_gender;

typedef struct {
	unsigned char flat_id;
} flat;

typedef struct {
	unsigned char flat_number, house_id;
	flat *flats;
} house;

typedef struct strt {
	char street_name[20];
	unsigned char house_number;
	unsigned char street_id;
	house *houses;	
	struct strt **intersects;
} street;

typedef struct {
	unsigned char flat_id;
	unsigned char house_id;
	unsigned char street_id;
	char street_name[20];
} address;

typedef struct {
	char first_name[20];
	char last_name[20];
	t_nation nation;
	t_gender gender;
	unsigned char age;
	address home_address;
} person;

#define LIST_FIRST_MALE_ARD "lists/first_males_ardesian.lst"
#define LIST_FIRST_FEMALE_ARD "lists/first_females_ardesian.lst"
#define LIST_LAST_ARD "lists/last_ardesian.lst"
#define LIST_FIRST_MALE_SLE "lists/first_males_slebrian.lst"
#define LIST_FIRST_FEMALE_SLE "lists/first_females_slebrian.lst"
#define LIST_LAST_SLE "lists/last_slebrian.lst"
#define LIST_FIRST_MALE_TOT "lists/first_males_totnan.lst"
#define LIST_FIRST_FEMALE_TOT "lists/first_females_totnan.lst"
#define LIST_LAST_TOT "lists/last_totnan.lst"
#define LIST_FIRST_MALE_WAL "lists/first_males_wallarish.lst"
#define LIST_FIRST_FEMALE_WAL "lists/first_females_wallarish.lst"
#define LIST_LAST_WAL "lists/last_wallarish.lst"
#define LIST_FIRST_MALE_USS "lists/first_males_ussairic.lst"
#define LIST_FIRST_FEMALE_USS "lists/first_females_ussairic.lst"
#define LIST_LAST_USS "lists/last_ussairic.lst"
#define LIST_FIRST_MALE_SIN "lists/first_males_sinpouri.lst"
#define LIST_FIRST_FEMALE_SIN "lists/first_females_sinpouri.lst"
#define LIST_LAST_SIN "lists/last_sinpouri.lst"

#define FLAG_NAMERULE_COMMON 1
#define FLAG_NAMERULE_LASTNAME 2
#define FLAG_NAMERULE_SLEBRIAN 4
#define FLAG_NAMERULE_TOTNAN 8
#define FLAG_NAMERULE_USSAIRIC 16
#define FLAG_NAMERULE_SINPOURI 32
#define FULLFLAG 255

#define STREETS 10
#define PEOPLE 100

#endif