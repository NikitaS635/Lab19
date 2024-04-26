#ifndef STRING__H
#define STRING__H
#include <stddef.h>
#include <ctype.h>
#include <stdbool.h>
#define MAX_STRING_SIZE 1000 // Максимальный размер строки
#define MAX_N_WORDS_IN_STRING 100
#define MAX_WORD_SIZE 20
// Объявление структуры WordDescriptor
typedef struct {
    char *begin; // Начало слова
    char *end;   // Конец слова
} WordDescriptor;
typedef struct BagOfWords {
    WordDescriptor words[MAX_N_WORDS_IN_STRING];
    size_t size;
} BagOfWords;

typedef enum {
    EMPTY_STRING,
    NOT_FOUND_A_WORD_WITH_A,
    FIRST_WORD_WITH_A,
    WORD_FOUND
} WordBeforeFirstWordWithAReturnCode;

void replace(char *source, char *w1, char *w2);
void wordDescriptorToString(WordDescriptor word, char *destination);
// Функция для определения наличия пары слов с одинаковым набором букв
bool hasPairWithSameLetters(const char *str);
bool hasDuplicateWords(const char *str);
WordDescriptor lastWordInFirstStringInSecondString(char *s1, char *s2);
bool areWordsLexicographicallyOrdered(char *sentence);
bool isPalindrome(char *word);
void reverseWords(char *str);
extern char _stringBuffer[MAX_STRING_SIZE + 1]; // Объявление глобальной переменной
void getBagOfWords(BagOfWords *bag, char *s);
void alternateWords(char *s1, char *s2, char *result);
char* replaceDigitsWithSpaces(const char *inputString);
int getWord(char *beginSearch, WordDescriptor *word);
void digitToStart(WordDescriptor word);
char* find(char *begin, char *end, int ch);
char* findNonSpace(char *begin);
char* findSpace(char *begin);
char* findNonSpaceReverse(char *rbegin, const char *rend);
char* findSpaceReverse(char *rbegin, const char *rend);
int string_length(const char *str);
size_t strlen_(const char *begin);
int my_strcmp(const char *lhs, const char *rhs);
char* copy(char *beginSource, char *endSource, char *beginDestination);
char* copyIf(const char *beginSource, const char *endSource, char *beginDestination, int (*f)(int));
char* copyIfReverse(char *rbeginSource, const char *rendSource, char *beginDestination, int (*f)(int));
// Функция для удаления пробельных символов из строки
void removeNonLetters(char *s);


// Функция для тестирования
void assertString(const char *expected, char *got,
                  const char *fileName, const char *funcName,
                  int line);
// Функция для удаления лишних пробелов между словами
void removeExtraSpaces(char *s);

#endif // STRING__H
