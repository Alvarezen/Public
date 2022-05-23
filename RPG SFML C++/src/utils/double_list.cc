/**
  * @file double_list.cc
  * @brief mka_list file of the game
  * @details that is use to do a list at dynamic memory
  * @author Alvaro Vazquez Carmona <vazquezca@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#include "mka_list.h"

namespace MKA {

	void CreateDoubleList(List **double_list) {
		*double_list = NULL;
	}

	bool EmptyList(List *list) {
		return NULL == list;
	}

	bool EqualInfo(void *data1, void *data2) {
		return data1 == data2;
	}

	void InsertNodeList(List **list, void *info) {

		List *aux = (List*)malloc(sizeof(List));
		aux->info = info;
		aux->prev = NULL;
		aux->next = *list;
		if (!EmptyList(*list)) {
			(*list)->prev = aux;
		}

		*list = aux;

	}

	List *IndexList(List *list, int pos) {

		if (!EmptyList(list)) {
			int i = 0;
			List *aux = NULL;
			for (aux = list; NULL != aux && i != pos && pos >= 0; aux = aux->next) {
				i++;
			}

			return aux;
		} else {
			return NULL;
		}

	}

	void *IndexListInfo(List *list, int pos) {

		if (!EmptyList(list)) {
			int i = 0;
			List *aux = NULL;
			for (aux = list; NULL != aux && i != pos && pos >= 0; aux = aux->next) {
				i++;
			}

			return aux->info;
		} else {
			return NULL;
		}

	}

	List *SeekOnList(List *list, void *value) {

		if (!EmptyList(list)) {
			List *aux = NULL;
			int i = 0;
			for (aux = list; NULL != aux && EqualInfo(aux->info, value); aux = aux->next) {
				++i;
			}
			return aux;
		} else {
			return NULL;
		}


	}

	uint8_t DeleteNodeList(List **list, int pos) {

		if (!EmptyList(*list)) {

			List *aux = NULL;
			if(NULL != (aux = IndexList(*list, pos))){

				if (NULL != aux->next && NULL != aux->prev) {

					aux->prev->next = aux->next;
					aux->next->prev = aux->prev;

				}
				if (NULL == aux->next && NULL != aux->prev) {

					aux->prev->next = NULL;

				}

				if (NULL != aux->next && NULL == aux->prev) {

					aux->next->prev = NULL;
					(*list) = aux->next;

				}

				if (NULL == aux->next && NULL == aux->prev) {

					(*list) = NULL;

				}

				free(aux);

				return 1;

			} else {

				return 0;

			}

		} else {

			return 0;

		}

	}

	int ListSize(List *list) {

		int i = 0;

		for (List *aux = list; NULL != aux; aux = aux->next) {
			++i;
		}
		return i;

	}

	void EraseList(List **list) {

		for (int i = 0; i < ListSize(*list); i++) {
			DeleteNodeList(list, i);
			i--;
		}

	}

	List* FirstAtList(List* list){

		if (!EmptyList(list)) {

			return list;

		} else {

			return NULL;

		}

	}

	List* LastAtList(List* list){

		if (!EmptyList(list)) {
			int i = 0;
			List* aux = NULL;
			for (aux = list; NULL != aux; aux = aux->next) {
				i++;

				if(NULL == aux->next){

					return aux;

				}

			}

			return NULL;

		} else {
			return NULL;
		}

	}

	List* IndexListReverse(List* list, int pos){

		if (!EmptyList(list)) {
			int i = 0;
			List *aux = NULL;
			for (aux = LastAtList(list);
			NULL != aux && i != pos && pos >= 0; aux = aux->prev) {
				i++;
			}

			return aux;
		} else {
			return NULL;
		}

	}

	void* IndexListInfoReverse(List* list, int pos){

		if (!EmptyList(list)) {
			int i = 0;
			List *aux = NULL;
			for (aux = LastAtList(list);
			NULL != aux && i != pos && pos >= 0; aux = aux->prev) {
				i++;
			}

			return aux->info;
		} else {
			return NULL;
		}

	}

}
