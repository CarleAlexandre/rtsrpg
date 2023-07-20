#include "engine.h"

char	*generateName(EntityTemplate stereotype, int affix) {
	char	*name = NULL;

	(void)stereotype;
	switch (affix) {
		case 0:
			name = (char *)malloc(7);
			name[6] = 0x00;
			memcpy(name, "Zombie", 6);
			break;
		case 1:
			name = (char *)malloc(7);
			name[6] = 0x00;
			memcpy(name, "Oldies", 6);
			break;
		case 2:
			name = (char *)malloc(10);
			name[9] = 0x00;
			memcpy(name, "Crackhead", 9);
			break;
		case 3:
			name = (char *)malloc(10);
			name[9] = 0x00;
			memcpy(name, "Warren B.", 9);
			break;
		case 4:
			name = (char *)malloc(4);
			name[3] = 0x00;
			memcpy(name, "XQC", 3);
			break;
		default:
			break;
	}
	return (name);
}

Texture2D	generateTexture(EntityTemplate stereotype) {
	Texture2D text = {0};
	(void)stereotype;

	return (text);
}

Entity	*createEntity(EntityTemplate stereotype, Vector2 pos, int affix) {
	Entity *new;

	new = malloc(sizeof(Entity));
	new->pos = pos;
	new->next = NULL;
	new->life = stereotype.life;
	new->damage = stereotype.damage;
	new->loot = stereotype.loot;
	new->armor = stereotype.armor;
	new->speed = stereotype.speed;
	new->toPos = pos;
	new->name = generateName(stereotype, affix);
	new->text = generateTexture(stereotype);
	switch (affix) {
		case 1:
			new->damage -= 2;
			break;
		case 2:
			new->damage += 2;
			break;
		case 3:
			//need to introduce a function to multiply loot table
			break;
		case 4:
			new->speed += 2;
			break;
		default:
			break ;
	}
	return (new);
}

Entity *lastEntity(Entity **pentity) {
	Entity *ptr;

	ptr = *pentity;
	while(ptr->next != NULL) {
		ptr = ptr->next;
	}
	return (ptr);
}

/*
 *	this function act as a spawn,
 *	it spawn u16 n entity at f64 x, y coordinate (map coordinate)
 *	f32 r for spawn radius 
 *	and stereotype you can see it like a vkCreateInfp struct
 *	return the first element of a linked list with each entity created
 *	you can now give this struct to the updateEntity function (should)
 * */
void	spawnEntity(Entity **pentity, u16 n, f32 x, f32 y, u32 r, EntityTemplate stereotype) {
	Vector2	pos;
	int		r_num = 0;
	Entity	*ptr;
	int		affix = 0;

	srand(time(NULL));
	ptr = lastEntity(pentity);
	for (int i = 0; i <= n; i++) {
		r_num = rand();
		affix = r_num % 5;
		//need to use r_num to % the enum of prefix to change stereotype stats
		pos.x = (r_num - 11) % r;
		pos.y = (r_num + 7) % r;
		if (r_num % 2 == 0)
			pos.x = -pos.x;
		if (r_num % 3 == 0)
			pos.y = -pos.y;
		pos.x += x;
		pos.y += y;
		ptr->next = createEntity(stereotype, pos, affix);
	}
}

//need to create a for each function to automate the process of creating and dstroying entity
u32	foreachEntity(Entity **ptr, u32 fun(Entity **, void *, f64 delta_time), void *arg, f64 delta_time) {
	Entity *iterator = NULL;

	iterator = *ptr;
	while (iterator->next != NULL) {
		fun(&iterator, arg, delta_time);
		iterator = iterator->next;
	}
	return (fun(&iterator, arg, delta_time));
}

u32	destroyEntity(Entity **entity) {
	Entity *ptr;

	ptr = (* entity)->next;
	free(*entity);
	*entity = ptr;
	return (0);
}
