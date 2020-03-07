#include "simple_vector.h"

int main() {

	struct Linked_List * vec = NULL;
	vec_push(&vec, "Aaron");
	vec_push(&vec, "Anthony");
	vec_push(&vec, "Valoroso");

	vec_pop(&vec, 1);
	
	vec_listall(vec);
	vec_cleanup(&vec);

	return 0;
}
