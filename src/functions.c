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
		return SLEBRIAN;
	} else if (tmp<0.94) { //wallarish: 3%
		return WALLARISH;
	} else if (tmp<0.96) { //totnan: 2%
		return TOTNAN;
	} else if (tmp<0.98) { //ussairic: 2%
		return USSAIRIC;
	} else { //sinpouri: 2%
		return SINPOURI;
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

char *extract_from_list ( const char *list_path ) { //chooses a random name from the list
	FILE *fp = NULL;
	fp = fopen(list_path, "r");
	if (fp == NULL) exit(-1);

	char *str = NULL;
	str=(char *)calloc(64, sizeof(char));
	if (str == NULL) exit(-1);

	int len;
	fscanf(fp,"%d",&len);
	len = rand_val(1,len+1);
	for (int i = 0; i<len; i++) {
		strcpy(str,"");
		fscanf(fp,"%s",str);
	}

	fclose(fp);

	return str;
}

int check_flag ( char flags, const char sample ) {
	if ((flags & sample) == sample) return 1;
	else return 0;
}

char *expand_string( char *str, int pos ) {
	int len = strlen(str);
	char *newstr = NULL;
	newstr = (char *)calloc(20, sizeof(char));
	if (newstr == NULL) exit(-1);
	for (int i = 0; i<len+2; i++) {
		if (i<(pos+1)) newstr[i] = str[i];
		else newstr[i] = str[i-1];
	}
	return newstr;
}

void mess_up_with_name( char *name, const char flags ) {
	for (int i = 0;; i++) {
		if (name[i] == '\0') break;
		else {
			switch (tolower(name[i])) {
				case 'e':
					if (check_flag(flags, FLAG_NAMERULE_COMMON) || check_flag(flags, FLAG_NAMERULE_SINPOURI)) {
						if (take_chance(0.4)) {
							name[i] = 'i';
						}
					}
				break;
				case 'l':
					if (check_flag(flags, FLAG_NAMERULE_COMMON)) {
						if (take_chance(0.4)) {
							strcpy(name,expand_string(name,i));
							i++;
						}
					}
				break;
				case 't':
					if (check_flag(flags, FLAG_NAMERULE_COMMON)) {
						if (take_chance(0.4)) {
							strcpy(name,expand_string(name,i));
							i++;
							name[i]='h';
						}
					}
				break;
				case 'x':
					if (check_flag(flags, FLAG_NAMERULE_SLEBRIAN)) {
						if (take_chance(0.5)) {
							strcpy(name,expand_string(name,i));
							name[i]='k';
							i++;
							name[i]='s';
						}
					}
				break;
				default:;
				break;
			}
		}
	}
	name[0] = toupper(name[0]);
}

void generate_person( person *target ) { //creates a random person
	target->age = rand_val(10,80);
	target->nation = return_nation();
	char *fname = NULL;
	fname=(char *)calloc(20,sizeof(char));
	char *lname = NULL;
	lname=(char *)calloc(20,sizeof(char));
	if (take_chance(0.5)) {
		target->gender = MALE;
		switch (target->nation) {
		case ARDESIAN:
			strcpy(fname, extract_from_list(LIST_FIRST_MALE_ARD));
			if (take_chance(0.1)) {
				strcpy(lname, "Mc");
			} else strcpy(lname, "");
			strcat(lname, extract_from_list(LIST_LAST_ARD));
		break;
		case SLEBRIAN:
			strcpy(fname, extract_from_list(LIST_FIRST_MALE_SLE));
			strcpy(lname, extract_from_list(LIST_LAST_SLE));
		break;
		case TOTNAN:
			strcpy(fname, extract_from_list(LIST_FIRST_MALE_TOT));
			strcpy(lname, extract_from_list(LIST_LAST_TOT));
		break;
		case WALLARISH:
			strcpy(fname, extract_from_list(LIST_FIRST_MALE_WAL));
			strcpy(lname, extract_from_list(LIST_LAST_WAL));
		break;
		case USSAIRIC:
			strcpy(fname, extract_from_list(LIST_FIRST_MALE_USS));
			if (take_chance(0.4)) {
				strcpy(lname, "al-");
			} else strcpy(lname, "");
			strcat(lname, extract_from_list(LIST_LAST_USS));
		break;
		case SINPOURI:
			strcpy(fname, extract_from_list(LIST_FIRST_MALE_SIN));
			strcpy(lname, extract_from_list(LIST_LAST_SIN));
		break;
		}
	} else {
		target->gender = FEMALE;
		switch (target->nation) {
		case ARDESIAN:
			strcpy(fname, extract_from_list(LIST_FIRST_FEMALE_ARD));
			if (take_chance(0.1)) {
				strcpy(lname, "Mc");
			} else strcpy(lname, "");
			strcat(lname, extract_from_list(LIST_LAST_ARD));
		break;
		case SLEBRIAN:
			strcpy(fname, extract_from_list(LIST_FIRST_FEMALE_SLE));
			strcpy(lname, extract_from_list(LIST_LAST_SLE));
			strcat(lname, "a");
		break;
		case TOTNAN:
			strcpy(fname, extract_from_list(LIST_FIRST_FEMALE_TOT));
			strcpy(lname, extract_from_list(LIST_LAST_TOT));
		break;
		case WALLARISH:
			strcpy(fname, extract_from_list(LIST_FIRST_FEMALE_WAL));
			strcpy(lname, extract_from_list(LIST_LAST_WAL));
		break;
		case USSAIRIC:
			strcpy(fname, extract_from_list(LIST_FIRST_FEMALE_USS));
			strcpy(lname, extract_from_list(LIST_LAST_USS));
		break;
		case SINPOURI:
			strcpy(fname, extract_from_list(LIST_FIRST_FEMALE_SIN));
			strcpy(lname, extract_from_list(LIST_LAST_SIN));
		break;
		}
	}
	mess_up_with_name(fname, FULLFLAG);
	mess_up_with_name(lname, FULLFLAG);
	strcpy(target->first_name,fname);
	strcpy(target->last_name,lname);
}

void generate_flat ( flat *flt, unsigned char id ) {
	flt->flat_id = id;
}

void generate_house ( house *hs, unsigned char id ) {
	hs->flat_number = rand_val(1,5);
	hs->house_id = id;
	hs->flats = (flat *)calloc(hs->flat_number,sizeof(flat));
	if (hs->flats == NULL) {
		exit(-1);
	}
	for (int i = 0; i<(hs->flat_number); i++) {
		generate_flat(&(hs->flats[i]), i);
	}
}

void generate_street( street *stt, unsigned char id ) {
	stt->street_id = id;
	if (take_chance(0.7)) {
		strcpy(stt->street_name,extract_from_list(LIST_LAST_ARD));
		strcat(stt->street_name," St.");
	} else if (take_chance(0.5)) {
		strcpy(stt->street_name,extract_from_list(LIST_LAST_ARD));
		strcat(stt->street_name," Sq.");
	} else {
		unsigned char num = rand_val(1,11);
		char postf[5];
		switch (num) {
			case 1:
				strcpy(postf,"st");
			break;
			case 2:
				strcpy(postf,"nd");
			break;
			case 3:
				strcpy(postf,"rd");
			break;
			default:
				strcpy(postf,"th");
			break;
		}
		sprintf(stt->street_name,"%d%s Ave", num, postf);
	}
	stt->house_number = rand_val(5,100);
	stt->houses = (house *)calloc(stt->house_number,sizeof(flat));
	if (stt->houses == NULL) {
		exit(-1);
	}
	for (int i = 0; i<(stt->house_number); i++) {
		generate_house(&(stt->houses[i]),i);
	}
}

char *describe_person( person *guy ) { //makes an output string out of person (like "John Doe, Ardesian male")
	char *str = NULL;
	char article[2];

	str = (char *)calloc(256,sizeof(char));
	if (str == NULL) {
		exit(-1);
	}

	if (((guy->nation) == ARDESIAN) || ((guy->nation) == USSAIRIC))
		strcpy(article,"an");
	else
		strcpy(article,"a");

	sprintf(str,"%s %s is %s %s %s, %d years old, living at %d %s, apartment %d",guy->first_name,guy->last_name, article, nation_to_string(guy->nation), gender_to_string(guy->gender), guy->age, guy->home_address.house_id, guy->home_address.street_name, guy->home_address.flat_id+1);
	return str;
}