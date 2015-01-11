#include "functions.h"

float return_rand () { //returns a float between 0 and 1
	uint8_t base_token = 0;
	RAND_bytes((unsigned char *)&base_token, sizeof(base_token));
	return (float)((float)base_token / 256);
}

int take_chance (float chance) { //takes a chance between 0 and 1
	if ((chance - return_rand()) < 0) {
		return 0;
	} else {
		return 1;
	}
}

float rand_weighted (int low_bound, int high_bound, int weight) {
	/*float res = 0.0;
	float delta = high_bound - low_bound;
	if (take_chance(weight)) {
		res = low_bound + return_rand()*delta;
	} else {
		if (take_chance(1-high_bound)) {
			res=high_bound + return_rand()*(1 - high_bound);
		} else {
			res=return_rand()*low_bound;
		}
	}
*/
	//return res;
	return 0.0;
} //not working weighted random

int rand_val ( int min, int max ) { //returns an integer between min and max
	int delta = ( max - min ), res = 0;
	res = return_rand()*delta+min;
	return res;
}

t_nation return_nation () { //returns a random nation.
	float tmp = return_rand();
	if (tmp<0.86) { //ardesian: 86%
		return ARDESIAN;
	} else if (tmp<0.91) { //slebrian: 5%
		return SLEBRIAN;     //temporarily limited functionality for the sake of missing name lists
	}/* else if (tmp<0.94) { //wallarish: 3%
		return WALLARISH;
	} else if (tmp<0.96) { //totnan: 2%
		return TOTNAN;
	} else if (tmp<0.98) { //ussairic: 2%
		return USSAIRIC;
	}*/ else { //sinpouri: 2%
		//return SINPOURI;
		return SLEBRIAN;
	}
}

char *nation_to_string( t_nation nat ) {
	if (nat == ARDESIAN) {
		return "Ardesian";
	} else if (nat == SLEBRIAN) {
		return "Slebrian";
	} else if (nat == TOTNAN) {
		return "Totnan";
	} else if (nat == WALLARISH) {
		return "Wallarish";
	} else if (nat == USSAIRIC) {
		return "Ussairic";
	} else if (nat == SINPOURI) {
		return "Sinpouri";
	}
}

char *gender_to_string( t_gender gnd ) {
	if (gnd == MALE) {
		return "male";
	} else return "female";
}

char *extract_from_list ( char *list_path ) { //chooses a random name from the list
	printf("TEST 3");
	FILE *fp;
	fp = fopen(list_path, "r");

	char *str = NULL;
	str=(char *)calloc(20, sizeof(char));

	char *lenstr = NULL;
	lenstr=(char *)calloc(10, sizeof(char));
	int len;
	fscanf(fp,"%d",&lenstr);
	len = atoi(lenstr);
	len = rand_val(0,len+1);
	for (int i = 0; i<len; i++) {
		fscanf(fp,"%s",&str);
	}

	fclose(fp);

	printf("TEST 4");
	return str;
}

void generate_person( person *target ) { //creates a random person
	printf("TEST 1");
	(*target).nation = return_nation();
	char *fname = NULL;
	fname=(char *)calloc(20,sizeof(char));
	char *lname = NULL;
	lname=(char *)calloc(20,sizeof(char));
	if (take_chance(0.5)) {
		(*target).gender = MALE;
		printf("TEST 2");
		if ((*target).nation == ARDESIAN) {
			strcpy(fname, extract_from_list(LIST_FIRST_MALE_ARD));
			strcpy(lname, extract_from_list(LIST_LAST_ARD));
		} else if ((*target).nation == SLEBRIAN) {
			strcpy(fname, extract_from_list(LIST_FIRST_MALE_SLE));
			strcpy(lname,  extract_from_list(LIST_LAST_SLE));
		} else if ((*target).nation == TOTNAN) {
			strcpy(fname, extract_from_list(LIST_FIRST_MALE_TOT));
			strcpy(lname,  extract_from_list(LIST_LAST_TOT));
		} else if ((*target).nation == WALLARISH) {
			strcpy(fname, extract_from_list(LIST_FIRST_MALE_WAL));
			strcpy(lname,  extract_from_list(LIST_LAST_WAL));
		} else if ((*target).nation == USSAIRIC) {
			strcpy(fname, extract_from_list(LIST_FIRST_MALE_USS));
			if (take_chance(0.4)) {
				strcpy(lname, "al-");
			} else strcpy(lname, "");
			strcat(lname, extract_from_list(LIST_LAST_USS));
		} else if ((*target).nation == SINPOURI) {
			strcpy(fname, extract_from_list(LIST_FIRST_MALE_SIN));
			strcpy(lname, extract_from_list(LIST_LAST_SIN));
		}
	} else {
		printf("TEST 2");
		(*target).gender = FEMALE;
		if ((*target).nation == ARDESIAN) {
			strcpy(fname, extract_from_list(LIST_FIRST_FEMALE_ARD));
			strcpy(lname, extract_from_list(LIST_LAST_ARD));
		} else if ((*target).nation == SLEBRIAN) {
			strcpy(fname, extract_from_list(LIST_FIRST_FEMALE_SLE));
			strcpy(lname,  extract_from_list(LIST_LAST_SLE));
			strcat(lname, "a");
		} else if ((*target).nation == TOTNAN) {
			strcpy(fname, extract_from_list(LIST_FIRST_FEMALE_TOT));
			strcpy(lname,  extract_from_list(LIST_LAST_TOT));
		} else if ((*target).nation == WALLARISH) {
			strcpy(fname, extract_from_list(LIST_FIRST_FEMALE_WAL));
			strcpy(lname,  extract_from_list(LIST_LAST_WAL));
		} else if ((*target).nation == USSAIRIC) {
			strcpy(fname, extract_from_list(LIST_FIRST_FEMALE_USS));
			strcpy(lname, extract_from_list(LIST_LAST_USS));
		} else if ((*target).nation == SINPOURI) {
			strcpy(fname, extract_from_list(LIST_FIRST_FEMALE_SIN));
			strcpy(lname, extract_from_list(LIST_LAST_SIN));
		}
	}
	strcpy((*target).first_name,fname);
	strcpy((*target).last_name,lname);
}

char *describe_person( person *guy ) { //makes an output string out of person (like "John Doe, Ardesian male")
	char *str = NULL;

	str = (char *)calloc(100,sizeof(char));
	if (str == NULL) {
		exit(-1);
	}

	sprintf(str,"%s %s, %s %s",(*guy).first_name,(*guy).last_name, nation_to_string((*guy).nation), gender_to_string((*guy).gender));
	return str;
}