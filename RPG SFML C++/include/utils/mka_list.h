/**
  * @file mka_list.h
  * @brief mka_list file of the game
  * @details that is use to do a list at dynamic memory
  * @author Alvaro Vazquez Carmona <vazquezca@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#ifndef __MKA_LIST__
#define __MKA_LIST__ 1

#include <stdlib.h>
#include <stdint.h>

namespace MKA {

	struct List {

		void *info;
		List *next;
		List *prev;

	};

	void CreateDoubleList(List **double_list);
	bool EmptyList(List *list);
	bool EqualInfo(void *data1, void *data2);
	void InsertNodeList(List **list, void *info);
	List *IndexList(List *list, int pos);
	void *IndexListInfo(List *list, int pos);
	List *SeekOnList(List *list, void *value);
	uint8_t DeleteNodeList(List **list, int pos);
	int ListSize(List *list);
	void EraseList(List **list);
	List* FirstAtList(List *list);
	List* LastAtList(List *list);
	List* IndexListReverse(List* list, int pos);
	void* IndexListInfoReverse(List* list, int pos);

}



#endif // !__MKA_LIST__
