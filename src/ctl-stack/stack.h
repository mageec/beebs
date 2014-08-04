/*****************************************************************************
 * FILE: stack.h                                                             *
 * AUTHOR: Toni Schornboeck <schornboeck@c-plusplus.de>                      *
 *****************************************************************************
 * Implementierung eines FixedSize Stack fuer die CTL                        *
 *****************************************************************************
 * Diese Datei darf frei unter der                                           *
 * GPL (http://www.gnu.org/copyleft/gpl.html) verwendet werden.              *
 *****************************************************************************/

#include "ctl.h"

#define MAKE_STACK(type)							\
struct CTL_##type##STACK {							\
	type*	value;									\
	size_t	size;									\
	size_t	first;									\
	size_t	alloc;									\
};													\
													\
typedef struct CTL_##type##STACK ctl_##type##Stack;	\
													\
ctl_##type##Stack* ctl_##type##StackInitSize(int BlockSize)\
{													\
	ctl_##type##Stack* s=malloc(sizeof(ctl_##type##Stack));\
	if(!s)											\
	{												\
		return NULL;								\
	}												\
	s->alloc		= BlockSize;					\
	s->value		= malloc(BlockSize*sizeof(type));\
	if(!s->value)									\
	{												\
		return NULL;								\
	}												\
	s->first		= 0;							\
	s->size			= 0;							\
	return s;										\
}													\
													\
ctl_##type##Stack* ctl_##type##StackInit(void)		\
{													\
	return ctl_##type##StackInitSize(CTL_SIZE);		\
}													\
													\
ctl_##type##Stack* ctl_##type##StackInitCopy(ctl_##type##Stack* stack)\
{													\
	ctl_##type##Stack* s=malloc(sizeof(ctl_##type##Stack));\
	if(!s)											\
	{												\
		return NULL;								\
	}												\
	s->alloc		= stack->alloc;					\
	s->value		= malloc(stack->alloc*sizeof(type));\
	if(!s->value)									\
	{												\
		return NULL;								\
	}												\
	s->first		= stack->first;					\
	s->size			= stack->size;					\
	return s;										\
}													\
													\
void ctl_##type##StackFree(ctl_##type##Stack* s)	\
{													\
	free(s->value);									\
	free(s);										\
}													\
													\
int ctl_##type##StackPush(ctl_##type##Stack* s, type value)\
{													\
	if(++s->size>s->alloc)							\
	{												\
		s->size=s->alloc;							\
	}												\
	if(++s->first==s->size)							\
	{												\
		s->first=0;									\
	}												\
	s->value[s->first]=value;						\
	return 0;										\
}													\
													\
int ctl_##type##StackPop(ctl_##type##Stack* s, type* value)\
{													\
	if(s->size==0)									\
	{												\
		ctl_errno=CTL_OUT_OF_RANGE;					\
		return 1;									\
	}												\
													\
	if(value)*value=s->value[s->first];				\
	--s->size;										\
	if(s->size)										\
	{												\
		if(!s->first)								\
		{											\
			s->first=s->size-1;						\
			return 0;								\
		}											\
		--s->first;									\
	}												\
	return 0;										\
}

