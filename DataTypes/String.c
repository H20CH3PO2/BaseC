#include "String.h"

String* callocString();

String* createString(char* data);

void freeString(String* str);

void initializeUpdateString(String* str);

void updateString(String* str);

void initializeString(String* str);

void initializeDataInString(String* str, char* data);

void freeMethodString(String* str);

String* copyMethodString(String* str);

char* toCString(String* str);

char* dumpMethodString(String* str);

int isUpdate(String* str);

size_t sizeMethodString(String* str);

void appendMethodString(String* strOne, String* strTwo);

void initializeSizeInString(String* str, Size size);

void initializeAppendInString(String* str, Append append);

String* callocString()
{
	return (String*)calloc(1, sizeof(String));
}

String* createString(char* data)
{
	String* result = callocString();
	initializeString(result);
	initializeDataInString(result, data);
	return result;
}

void freeString(String* str)
{
	freeBase((Base*)str);
}

void initializeUpdateString(String* str)
{
	str->update = UPDATE_STRING;
}

void updateString(String* str)
{
	initializeUpdateString(str);
}

void initializeString(String* str)
{
	Base* base = (Base*)str;
	initializeTypeName(base, TYPE_NAME_STRING);
	initializeFree(base, (Free)freeMethodString);
	initializeCopy(base, (Copy)copyMethodString);
	initializeToString(base, (_ToString)toStringMethodBase);
	initializeDump(base, (Dump)dumpMethodString);
	initializeUpdateString(str);
	initializeSizeInString(str, (Size)sizeMethodString);
	initializeAppendInString(str, (Append)appendMethodString);
}

void initializeDataInString(String* str, char* data)
{
	str->data = createCopyOfString(data);
}

void freeMethodString(String* str)
{
	free(str->data);
	freeMethodBase((Base*)str);
}

String* copyMethodString(String* str)
{
	return createString(str->data);
}

char* toCString(String* str)
{
	return str->data;
}

char* dumpMethodString(String* str)
{
	char* result = concatenateStringsWithSeparator(TYPE_NAME_STRING, toCString(str), SEPARATOR);
	return result;
}

int isUpdate(String* str)
{
	return str->update == UPDATE_STRING;
}

size_t sizeMethodString(String* str)
{
	static size_t size;
	if (isUpdate(str)) {
		size = strlen(str->data);
		return size;
	}
	return size;
}

void appendMethodString(String* strOne, String* strTwo)
{
	char* oldData = toCString(strOne);
	char* newData = concatenateStrings(oldData, toCString(strTwo));
	strOne->data = newData;
	updateString(strOne);
	free(oldData);
}

void initializeSizeInString(String* str, Size size)
{
	str->size = size;
}

void initializeAppendInString(String* str, Append append)
{
	str->append = append;
}

String* copyString(String* str)
{
	return (String*)copyBase((Base*)str);
}

char* toStringTypeString(String* str)
{
	return toStringBase((Base*)str);
}

char* dumpString(String* str)
{
	return dumpBase((Base*)str);
}

size_t sizeString(String* str)
{
	return str->size((Base*)str);
}

void appendString(String* destination, String* source)
{
	destination->append((Container*)destination, (Base*)source);
}