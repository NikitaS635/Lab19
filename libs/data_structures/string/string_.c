#include "string_.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h> // Для использования isspace
#include <stdbool.h>
#include <stdlib.h>

char _stringBuffer[MAX_STRING_SIZE + 1]; // Определение глобальной переменной
// Функция для определения длины строки
int string_length(const char *str) {
    int length = 0;
    // Пока не встретится нулевой символ, увеличиваем длину
    while (*str != '\0') {
        length++;
        str++;
    }
    return length;
}

// Функция для определения длины строки (используя арифметику указателей)
size_t strlen_(const char *begin) {
    const char *end = begin;
    while (*end != '\0')
        end++;
    return end - begin;
}

// Функция для поиска первого вхождения символа ch в строке между begin и end
char* find(char *begin, char *end, int ch) {
    while (begin != end && *begin != ch)
        begin++;
    return begin;
}

// Функция для поиска первого непробельного символа в строке, начиная с begin
char* findNonSpace(char *begin) {
    while (*begin != '\0' && isspace(*begin))
        begin++;
    return begin;
}

// Функция для поиска первого пробельного символа в строке, начиная с begin
char* findSpace(char *begin) {
    while (*begin != '\0' && !isspace(*begin))
        begin++;
    return begin;
}

// Функция для поиска последнего непробельного символа в строке между rbegin и rend
char* findNonSpaceReverse(char *rbegin, const char *rend) {
    while (rbegin != rend && isspace(*rbegin))
        rbegin--;
    return rbegin;
}

// Функция для поиска последнего пробельного символа в строке между rbegin и rend
char* findSpaceReverse(char *rbegin, const char *rend) {
    while (rbegin != rend && !isspace(*rbegin))
        rbegin--;
    return rbegin;
}

// Функция для сравнения двух строк lhs и rhs
int my_strcmp(const char *lhs, const char *rhs) {
    while (*lhs && *rhs && *lhs == *rhs) {
        lhs++;
        rhs++;
    }
    return *lhs - *rhs;
}

// Функция для копирования строки
char* copy(char *beginSource, char *endSource, char *beginDestination) {
    while (beginSource < endSource) {
        *beginDestination = *beginSource;
        beginDestination++;
        beginSource++;
    }
    // Завершаем строку нулевым символом
    *beginDestination = '\0';
    return beginDestination;
}

// Функция для копирования элементов, удовлетворяющих условию предиката
char* copyIf(const char *beginSource, const char *endSource, char *beginDestination, int (*f)(int)) {
    while (beginSource != endSource) {
        if (f(*beginSource)) {
            *beginDestination = *beginSource;
            beginDestination++;
        }
        beginSource++;
    }
    return beginDestination;
}

// Функция для копирования только символов, удовлетворяющих предикату f, из строки между rbeginSource и rendSource в beginDestination в обратном порядке
char* copyIfReverse(char *rbeginSource, const char *rendSource, char *beginDestination, int (*f)(int)) {
    while (rbeginSource != rendSource) {
        if (f(*rbeginSource)) {
            *beginDestination = *rbeginSource;
            beginDestination++;
        }
        rbeginSource--;
    }
    return beginDestination;
}

// Функция для удаления пробельных символов из строки
void removeNonLetters(char *s) {
    // Получаем длину строки
    size_t length = strlen_(s);
    // Копируем только символы, не являющиеся пробельными, в исходную строку
    char *destination = copyIf(s, s + length, s, isgraph);
    // Устанавливаем нулевой символ в конце строки
    *destination = '\0';
}


// Функция для тестирования
void assertString(const char *expected, char *got,
                  const char *fileName, const char *funcName,
                  int line) {
    // Сравниваем ожидаемую и полученную строки
    if (strcmp(expected, got) != 0) {
        // Если строки отличаются, выводим сообщение об ошибке
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%s\"\n", expected);
        fprintf(stderr, "Got: \"%s\"\n\n", got);
    } else {
        // Иначе выводим сообщение об успешном прохождении теста
        fprintf(stderr, "%s - OK\n", funcName);
    }
}

// Функция для удаления лишних пробелов между словами
void removeExtraSpaces(char *s) {
    // Указатель для записи символов в строку без лишних пробелов
    char *writePtr = s;
    // Флаг, указывающий, был ли предыдущий символ пробелом
    bool previousSpace = false;

    // Читаем символы из строки
    while (*s != '\0') {
        // Если текущий символ не пробел
        if (*s != ' ') {
            // Записываем его в новую строку
            *writePtr = *s;
            // Перемещаем указатель записи вперед
            writePtr++;
            // Сбрасываем флаг пробела
            previousSpace = false;
        }
            // Если текущий символ - пробел
        else {
            // Если предыдущий символ не был пробелом
            if (!previousSpace) {
                // Записываем пробел в новую строку
                *writePtr = ' ';
                // Перемещаем указатель записи вперед
                writePtr++;
            }
            // Устанавливаем флаг пробела
            previousSpace = true;
        }
        // Переходим к следующему символу
        s++;
    }

    // Устанавливаем нулевой символ в конце новой строки
    *writePtr = '\0';
}


int getWord(char *beginSearch, WordDescriptor *word) {
    // Находим начало слова (первый непробельный символ)
    while (*beginSearch != '\0' && isspace(*beginSearch)) {
        beginSearch++;
    }

    if (*beginSearch == '\0') {
        // Если достигнут конец строки, слово не найдено
        return 0;
    }

    // Записываем начало слова
    word->begin = beginSearch;

    // Находим конец слова (первый пробельный символ или конец строки)
    while (*beginSearch != '\0' && !isspace(*beginSearch)) {
        beginSearch++;
    }

    // Записываем конец слова
    word->end = beginSearch;

    return 1;
}

void digitToStart(WordDescriptor word) {
    char *endStringBuffer = copy(word.begin, word.end, _stringBuffer); // Копируем слово во временный буфер

    // Перемещаем цифры в начало слова
    char *recPosition = copyIfReverse(endStringBuffer - 1, _stringBuffer - 1, word.begin, isdigit);

    // Перемещаем буквы в конец слова
    copyIf(_stringBuffer, endStringBuffer, recPosition, isalpha);
}
char* replaceDigitsWithSpaces(const char *inputString) {
    char *resultString = (char*)malloc(MAX_STRING_SIZE * sizeof(char)); // Выделение памяти для новой строки
    if (resultString == NULL) {
        return NULL; // В случае ошибки выделения памяти возвращаем NULL
    }

    int inputIndex = 0;
    int resultIndex = 0;

    while (inputString[inputIndex] != '\0' && resultIndex < MAX_STRING_SIZE - 1) {
        if (isdigit(inputString[inputIndex])) {
            int numSpaces = inputString[inputIndex] - '0'; // Вычисляем количество пробелов
            for (int i = 0; i < numSpaces; i++) {
                resultString[resultIndex++] = ' '; // Заменяем цифру на пробелы
            }
        } else {
            resultString[resultIndex++] = inputString[inputIndex]; // Копируем символ без изменений
        }
        inputIndex++;
    }

    resultString[resultIndex] = '\0'; // Добавляем завершающий нулевой символ

    return resultString;
}

bool areWordsLexicographicallyOrdered(char *sentence) {
    char *word = strtok(sentence, " ");
    char *nextWord;

    while (word != NULL) {
        nextWord = strtok(NULL, " ");

        if (nextWord != NULL && strcmp(word, nextWord) > 0) {
            return false;
        }

        word = nextWord;
    }

    return true;
}

void getBagOfWords(BagOfWords *bag, char *s) {
    bag->size = 0; // Инициализируем размер сумки нулем

    // Указатель на начало текущего слова
    char *currentWord = s;

    // Проходимся по строке, пока не достигнем ее конца
    while (*s != '\0') {
        // Если текущий символ не пробел и не конец строки, то двигаемся дальше
        if (*s != ' ' && *(s + 1) != '\0') {
            s++;
        } else {
            // Иначе, если текущий символ пробел или конец строки,
            // то это конец текущего слова
            WordDescriptor word = {currentWord, s + 1};
            bag->words[bag->size++] = word;

            // Перемещаем указатель на начало следующего слова
            currentWord = s + 1;
            s++;
        }
    }
}

// Функция для проверки, является ли слово палиндромом
bool isPalindrome(char *word) {
    int length = strlen(word);
    for (int i = 0; i < length / 2; i++) {
        if (word[i] != word[length - i - 1]) {
            return false;
        }
    }
    return true;
}

// Функция для получения следующего слова из строки

// Функция для формирования строки из чередующихся слов
void alternateWords(char *s1, char *s2, char *result) {
    WordDescriptor word1, word2;
    bool isW1Found, isW2Found;
    char *beginSearch1 = s1, *beginSearch2 = s2;
    char *currentResult = result;

    while ((isW1Found = getWord(beginSearch1, &word1)),
            (isW2Found = getWord(beginSearch2, &word2)),
            isW1Found || isW2Found) {
        // Если найдено слово в первой строке, добавляем его в строку-результат
        if (isW1Found) {
            strncpy(currentResult, word1.begin, word1.end - word1.begin);
            currentResult += word1.end - word1.begin;
            *currentResult = ' '; // Добавляем пробел между словами
            currentResult++;
            beginSearch1 = word1.end;
        }
        // Если найдено слово во второй строке, добавляем его в строку-результат
        if (isW2Found) {
            strncpy(currentResult, word2.begin, word2.end - word2.begin);
            currentResult += word2.end - word2.begin;
            *currentResult = ' '; // Добавляем пробел между словами
            currentResult++;
            beginSearch2 = word2.end;
        }
    }
    // Завершаем строку-результат нулевым символом
    *currentResult = '\0';
}

// Функция для обратного преобразования порядка слов в строке
void reverseWords(char *str) {
    // Находим длину строки
    int len = strlen(str);

    // Индекс для начала слова
    int start = 0;

    // Проходим по строке
    for (int i = 0; i <= len; i++) {
        // Если текущий символ не пробел и не нулевой символ,
        // то это начало слова или конец строки
        if (str[i] == ' ' || str[i] == '\0') {
            // Индекс конца слова
            int end = i - 1;

            // Обращаем порядок символов в слове
            while (start < end) {
                char temp = str[start];
                str[start] = str[end];
                str[end] = temp;
                start++;
                end--;
            }

            // Передвигаем начало на следующее слово
            start = i + 1;
        }
    }

    // Обращаем порядок всей строки
    int i = 0, j = len - 1;
    while (i < j) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}
void wordDescriptorToString(WordDescriptor word, char *destination) {
    size_t length = word.end - word.begin;
    strncpy(destination, word.begin, length);
    destination[length] = '\0';
}



WordDescriptor lastWordInFirstStringInSecondString(char *s1, char *s2) {
    BagOfWords bag;
    getBagOfWords(&bag, s2);

    WordDescriptor lastMatch;
    lastMatch.begin = NULL;
    lastMatch.end = NULL;

    char *start = NULL;
    char *end = NULL;
    char *current = s1;

    while (*current != '\0') {
        // Пропускаем пробелы перед словом
        while (*current != '\0' && isspace(*current)) {
            current++;
        }

        if (*current == '\0') {
            break; // Достигнут конец строки
        }

        start = current; // Начало текущего слова

        // Ищем конец текущего слова
        while (*current != '\0' && !isspace(*current)) {
            current++;
        }

        end = current; // Конец текущего слова

        // Проверяем, есть ли текущее слово во второй строке
        for (size_t i = 0; i < bag.size; i++) {
            if (bag.words[i].begin != NULL && bag.words[i].end != NULL) {
                if (strncmp(start, bag.words[i].begin, end - start) == 0 &&
                    (bag.words[i].end - bag.words[i].begin) == (end - start)) {
                    lastMatch = bag.words[i];
                }
            }
        }

        // Переходим к следующему слову
        current = end;
    }

    return lastMatch;
}

// Вспомогательная функция для сравнения слов без учета регистра
int compareWordsIgnoreCase(const char *word1, const char *word2) {
    while (*word1 && *word2) {
        if (tolower(*word1) != tolower(*word2)) {
            return 0; // Слова не равны
        }
        word1++;
        word2++;
    }
    return (*word1 == '\0' && *word2 == '\0'); // Проверка окончания обоих слов
}

// Функция для определения наличия одинаковых слов в строке
bool hasDuplicateWords(const char *str) {
    if (str == NULL || *str == '\0') {
        return false; // Пустая строка или NULL
    }

    char tempStr[100]; // Временный буфер для работы со строкой
    strcpy(tempStr, str);

    const char *delimiters = " ,.;:!?\n\t"; // Разделители слов

    char *word = strtok(tempStr, delimiters); // Получение первого слова

    while (word != NULL) {
        // Приводим слово к нижнему регистру для корректного сравнения
        for (char *p = word; *p; ++p) {
            *p = tolower(*p);
        }

        // Проверяем текущее слово на наличие дубликата в оставшейся части строки
        const char *nextWord = strtok(NULL, delimiters); // Следующее слово
        while (nextWord != NULL) {
            if (compareWordsIgnoreCase(word, nextWord)) {
                return true; // Найден дубликат
            }
            nextWord = strtok(NULL, delimiters); // Получаем следующее слово
        }

        word = strtok(NULL, delimiters); // Получаем следующее слово
    }

    return false; // Дубликатов не найдено
}

// Функция для сортировки букв в слове
void sortWord(char *word) {
    int len = strlen(word);
    for (int i = 0; i < len - 1; ++i) {
        for (int j = i + 1; j < len; ++j) {
            if (tolower(word[i]) > tolower(word[j])) {
                char temp = word[i];
                word[i] = word[j];
                word[j] = temp;
            }
        }
    }
}

// Функция для определения наличия пары слов с одинаковым набором букв
bool hasPairWithSameLetters(const char *str) {
    if (str == NULL || *str == '\0') {
        return false; // Пустая строка или NULL
    }

    char buffer[100]; // Буфер для работы со строкой
    strcpy(buffer, str);

    const char *delimiters = " ,.;:!?\n\t"; // Разделители слов

    char *word = strtok(buffer, delimiters); // Получение первого слова
    bool foundPair = false;

    while (word != NULL) {
        char sortedWord[100];
        strcpy(sortedWord, word);
        sortWord(sortedWord); // Сортируем буквы слова

        char *nextWord = strtok(NULL, delimiters); // Следующее слово
        while (nextWord != NULL) {
            char sortedNextWord[100];
            strcpy(sortedNextWord, nextWord);
            sortWord(sortedNextWord); // Сортируем буквы следующего слова

            if (strcmp(sortedWord, sortedNextWord) == 0) {
                foundPair = true;
                break;
            }

            nextWord = strtok(NULL, delimiters); // Получаем следующее слово
        }

        if (foundPair) {
            break;
        }

        word = strtok(NULL, delimiters); // Получаем следующее слово
    }

    return foundPair;
}

// Функция для поиска конца строки
static char* getEndOfString(char *source) {
    while (*source != '\0') {
        source++;
    }
    return source;
}

// Функция для копирования строки
static void copy2(char *source, char *end, char *destination) {
    while (source < end) {
        *destination++ = *source++;
    }
    *destination = '\0';
}

void replace(char *source, char *w1, char *w2) {
    size_t w1Size = strlen(w1);
    size_t w2Size = strlen(w2);
    WordDescriptor word1 = {w1, w1 + w1Size};
    WordDescriptor word2 = {w2, w2 + w2Size};
    char *readPtr, *recPtr;

    if (w1Size >= w2Size) {
        // Если w1 длиннее или равно w2, заменяем непосредственно в source
        readPtr = source;
        recPtr = source;
    } else {
        // Если w1 короче w2, используем буфер для замены
        char _stringBuffer[MAX_WORD_SIZE];
        copy(source, getEndOfString(source), _stringBuffer);
        readPtr = _stringBuffer;
        recPtr = source;
    }

    // Пока не достигнут конец строки
    while (*readPtr != '\0') {
        // Если текущее слово равно w1, заменяем его на w2
        if (strncmp(readPtr, w1, w1Size) == 0) {
            // Когда находим слово w1, копируем вместо него слово w2
            strcpy(recPtr, w2);
            recPtr += w2Size;
            readPtr += w1Size;
        } else {
            // Копируем символ из исходной строки в выходную
            *recPtr++ = *readPtr++;
        }
    }
    // Завершаем строку нулевым символом
    *recPtr = '\0';
}
