#include "header.h"
#include "functions.h"

//person sample_guy = { "John", "Doe", ARDESIAN, MALE };
person *population = NULL;
street *city = NULL;

void on_exit () {
	if (population != NULL) free(population);
	if (city != NULL) free(city);
}

int main(int argc, char const *argv[]) {
	atexit(on_exit);

	population = (person *)calloc(PEOPLE, sizeof(person));
	if (population == NULL) {
		exit(-1);
	}

	city = (street *)calloc(STREETS, sizeof(street));
	if (city == NULL) {
		exit(-1);
	}

	for (int i = 0; i<STREETS; ++i) {
		generate_street(&(city[i]),i);
	}

	for (int i = 0; i<PEOPLE; ++i) {
		generate_person(&(population[i]));
		population[i].home_address.street_id = rand_val(0, STREETS);
		strcpy(population[i].home_address.street_name, city[population[i].home_address.street_id].street_name);
		population[i].home_address.house_id = rand_val(0, city[population[i].home_address.street_id].house_number);
		population[i].home_address.flat_id = rand_val(0, city[population[i].home_address.street_id].houses[population[i].home_address.house_id].flat_number);
		printf("%d - %s\n",i,describe_person(&(population[i])));
	}

	return 0;
}