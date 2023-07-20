#include "engine.h"

u32	*rollLootDice(LootTable *table) {
	u32	*loot;

	return (loot);
}

LootTable	*addLootEntry(LootTable *table, u32 id, f32 drop_rate) {
	u32*	id_lst;
	f32*	rate_lst;
	u32		newsize_byte;
	newsize_byte = table->size * 4;
	id_lst = (u32 *)malloc(newsize_byte + 4);
	rate_lst = (f32 *)malloc(newsize_byte + 4);
	memcpy(memcpy(id_lst, table->item_id, newsize_byte), &id, 4);
	memcpy(memcpy(rate_lst, table->drop_rate, newsize_byte), &drop_rate, 4);
	table->drop_rate = rate_lst;
	table->item_id = id_lst;
	table->size++;
	return (table);
}

/*
 *	generateLoot from a lootTable and store it in loot, loot should loot_size allocated to it.
 *	
 * */
void	generateLoot(int loot_size, LootTable *loot_table, time_t time_arg, u32 *loot) {
	f32		roll;
	f32		cumulative_prob = 0.0;
	time_t	seed = time_arg * 1000;

	// Initialize random number generator
	srand((unsigned int) seed);

	// Generate loot items
    for (int i = 0; i < loot_table->size; i++) {
        roll = (float) rand() / (float)RAND_MAX;
        for (int j = 0; j < loot_table->size; j++) {
            cumulative_prob += loot_table->drop_rate[j];
            if (roll <= cumulative_prob) {
                loot[i] = loot_table->item_id[j];
                break;
            }
        }
    }
}