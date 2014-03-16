/*****************************************************************************
 * FILE: string.h                                                            *
 * AUTHOR: Toni Schornboeck <schornboeck@c-plusplus.de>                      *
 *****************************************************************************
 * Implementierung eines strings fuer die CTL                                *
 *****************************************************************************
 * Diese Datei darf frei unter der                                           *
 * GPL (http://www.gnu.org/copyleft/gpl.html) verwendet werden.              *
 *****************************************************************************/

#include "ctl.h"

struct CTL_STRING {
	size_t	BlockSize;
	char*	string;
	size_t	size;
	size_t	alloc;

};
typedef struct CTL_STRING ctl_string;

ctl_string* ctl_StringInitSize(int BlockSize)
{
	ctl_string* s=malloc(sizeof(ctl_string));
	if(!s)
	{
		return NULL;
	}
	s->BlockSize	= BlockSize;
	s->string		= malloc(s->BlockSize);
	if(!s->string)
	{
		ctl_errno	= CTL_OUT_OF_MEMORY;
		s->size		= 1;
		s->alloc	= 0;
		return NULL;
	}
	s->alloc		= s->BlockSize;
	s->size			= 0;
	s->string[0]	= '\0';
	return s;
}

ctl_string* ctl_StringInit(void)
{
	return ctl_StringInitSize(CTL_SIZE);
}

ctl_string* ctl_StringInitCopy(ctl_string* str)
{
	ctl_string* s=malloc(sizeof(ctl_string));
	if(!s)
	{
		return NULL;
	}
	s->string=malloc(str->alloc);
	if(!s->string)
	{
		ctl_errno	= CTL_OUT_OF_MEMORY;
		s->size		= 0;
		s->alloc	= 0;
		return NULL;
	}
	strcpy(s->string,str->string);
	s->alloc	= str->alloc;
	s->BlockSize= str->BlockSize;
	s->size		= str->size;
	return s;
}

void ctl_StringFree(ctl_string* s)
{
	free(s->string);
	free(s);
}

int ctl_StringSet(ctl_string* s, const char* string)
{
	size_t len,alloc;
	char* secure;
	len=strlen(string);
	if(s->alloc<len)
	{
		alloc = (len/s->BlockSize+1)*s->BlockSize;
		secure=realloc(s->string,alloc);
		if(!secure)
		{
			ctl_errno=CTL_OUT_OF_MEMORY;
			return 1;
		}
		s->alloc=alloc;
		s->string=secure;
	}
	strcpy(s->string,string);
	s->size=len;
	return 0;
}

int ctl_StringSetString(ctl_string* s, ctl_string* string)
{
	size_t len;
	char* secure;
	if(s->alloc<string->size)
	{
		len = (string->size/s->BlockSize+1)*s->BlockSize;
		secure=realloc(s->string,len);
		if(!secure)
		{
			ctl_errno=CTL_OUT_OF_MEMORY;
			return 1;
		}
		s->alloc=len;
		s->string=secure;
	}
	strcpy(s->string,string->string);
	s->size=string->size;
	return 0;
}

int ctl_StringAppend(ctl_string* s, const char* string)
{
	size_t len=strlen(string);
	size_t size=s->size+len;
	if(size>=s->alloc)
	{
		size_t alloc;
		char* secure;
		alloc = (size/s->BlockSize+1)*s->BlockSize;
		secure=realloc(s->string,alloc);
		if(!secure)
		{
			ctl_errno=CTL_OUT_OF_MEMORY;
			s->size-=len;
			return 1;
		}
		CTL_GROW_ALLOC_SIZE(s);
		s->alloc=alloc;
		s->string=secure;
	}
	strcpy(s->string+s->size-1,string);
	s->size=size;
	return 0;
}

char ctl_StringGetAt(ctl_string* s, size_t pos)
{
	CTL_RANGE(pos>=s->size)
	{
		ctl_errno	= CTL_OUT_OF_RANGE;
		return 0;
	}
	return s->string[pos];
}

int ctl_StringSetAt(ctl_string* s, size_t pos, char value)
{
	CTL_RANGE(pos>=s->size)
	{
		ctl_errno	= CTL_OUT_OF_RANGE;
		return 0;
	}
	s->string[pos]=value;
	return 0;
}

int ctl_StringInsertAt(ctl_string* s, size_t pos, char value)
{
	CTL_RANGE(pos>=s->size)
	{
		ctl_errno=CTL_WRONG_VALUE;
		return 1;
	}
	if(s->size>=s->alloc)
	{
		char* secure;
		s->alloc+=s->BlockSize;
		secure=realloc(s->string,s->alloc);
		if(!secure)
		{
			ctl_errno=CTL_OUT_OF_MEMORY;
			s->alloc-=s->BlockSize;
			return 1;
		}
		CTL_GROW_ALLOC_SIZE(s);
		s->string=secure;
	}
	++s->size;
	memmove(&s->string[pos+1],&s->string[pos],s->size-pos);
	s->string[pos]=value;
	s->string[s->size]=0;
	return 0;
}

int ctl_StringGetSubStr(ctl_string* s, size_t begin, size_t end, char* string)
{
	CTL_RANGE(end>=s->size)
	{
		ctl_errno=CTL_OUT_OF_RANGE;
		return 1;
	}
	strncpy(string,s->string+begin,end-begin+1);
	string[end-begin+1]='\0';
	return 0;
}

int ctl_StringSetSubStr(ctl_string* s, size_t begin, size_t end, char* string)
{
	size_t alloc;
	size_t len2=strlen(string);
	size_t len1=end-begin;
	size_t diff=len2-len1;
	int a=0;
	CTL_RANGE(end>=s->size)
	{
		ctl_errno=CTL_OUT_OF_RANGE;
		return 1;
	}
	if(!diff)
	{
		size_t i;
		for(i=0;i<len1;++i,++begin)
		{
			s->string[begin]=string[i];
		}
		return 0;
	}
	if(diff+s->size>s->alloc)
	{
		char* secure;
		alloc = ((s->size+diff)/s->BlockSize+1)*s->BlockSize;
		secure=realloc(s->string,alloc);
		if(!secure)
		{
			ctl_errno=CTL_OUT_OF_MEMORY;
			return 1;
		}
		CTL_GROW_ALLOC_SIZE(s);
		s->alloc=alloc;
		s->string=secure;
	}
	memmove(s->string+begin+len2,s->string+end,s->size-end);
	strcpy(s->string+begin,string);
	s->size+=diff;
	return 0;
}

int ctl_StringCompare(ctl_string* s, const char* string)
{
	return strcmp(s->string,string);
}

int ctl_StringCmpNoCase(ctl_string* s, const char* string)
{
	size_t i=0;
	while(s->string[i]&&string[i])
	{
		if(tolower(s->string[i])!=tolower(string[i]))
		{
			return tolower(s->string[i])-tolower(string[i]);
		}
		++i;
	}
	return s->string[i]-string[i];
}

size_t ctl_StringFindChar(ctl_string* s, char value)
{
	char* temp;
	temp=strchr(s->string,value);
	if(!temp)
	{
		ctl_errno = CTL_NOT_FOUND;
		return 0;
	}
	return temp-s->string;
}

size_t ctl_StringFindNextChar(ctl_string* s, size_t pos, char value)
{
	char* temp;
	CTL_RANGE(pos>=s->size)
	{
		ctl_errno = CTL_OUT_OF_RANGE;
		return 0;
	}
	temp=strchr(s->string+pos,value);
	if(!temp)
	{
		ctl_errno = CTL_NOT_FOUND;
		return 0;
	}
	return temp-s->string;
}

size_t ctl_StringFindStr(ctl_string* s, const char* string)
{
	char* temp;
	temp=strstr(s->string,string);
	if(!temp)
	{
		ctl_errno = CTL_NOT_FOUND;
		return 0;
	}
	return temp-s->string;
}

size_t ctl_StringFindNextStr(ctl_string* s, size_t pos, const char* string)
{
	char* temp;
	CTL_RANGE(pos>=s->size)
	{
		ctl_errno = CTL_OUT_OF_RANGE;
		return 0;
	}
	temp=strstr(s->string+pos,string);
	if(!temp)
	{
		ctl_errno = CTL_NOT_FOUND;
		return 0;
	}
	return temp-s->string;
}
