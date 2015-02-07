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

	population = (person*)calloc(100, sizeof(person));
	if (population == NULL) {
		exit(-1);
	}

	for (int i = 0; i<100; i++) {
		generate_person(&(population[i]));
		printf("%s\n",describe_person(&(population[i])));
	}

	return 0;
}