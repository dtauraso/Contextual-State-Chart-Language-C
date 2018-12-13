struct Names* makeName(char* name);

struct Names* addName(struct Names* names, char* next_name);
struct Names* makeName2(char* name_1, char* name_2);
state_x_y_hash_table* ht_new2();
void ht_insert2(state_x_y_hash_table* ht,
	struct Names* key,
	level_id_state_id* value);
level_id_state_id* newPoint(int level_id, int state_id);
level_id_state_id* ht_search2(state_x_y_hash_table* ht, struct Names* key);
