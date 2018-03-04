#ifdef __cplusplus
	extern "C"{
#endif

#ifndef __map__
	#define __map__
	struct _data{
		void* value;
	}typedef data;
	typedef struct _data *data;
	#define _map_enter_methods
	struct map_enter{
		_map_enter_methods;
	} typedef map_enter;

	#define _map_methods \
		void (*insert)(struct map* this_map, data * d);\
		void (*delet)(struct map* this_map);\
		struct map_enter* (*search)(struct map* this_map, data* d);\
		void (*remove)(struct map* this_map, map_enter *);\
		struct map_enter* (*get_next)(struct map* this_map, struct map_enter* );\
		struct map_enter* (*get_prev)(struct map* this_map, struct map_enter* );\
		struct map_enter* (*first)(struct map* this_map);\
		struct map_enter* (*last)(struct map* this_map);\
		struct map_enter* (*end)(struct map* this_map);

	struct map{
		_map_methods;
	} typedef map;
#endif


#ifdef __cplusplus
	}
#endif
