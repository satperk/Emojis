//COLLABS WITH CHRIS VARGHESE cv12
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Return your favorite emoji.  Do not allocate new memory.
// (This should **really** be your favorite emoji, we plan to use this later in the semester. :))
char *emoji_favorite() {
  return "\xF0\x9F\x98\xAD";
}


// Count the number of emoji in the UTF-8 string `utf8str`, returning the count.  You should
// consider everything in the ranges starting from (and including) U+1F000 up to (and including) U+1FAFF.
int emoji_count(const unsigned char *utf8str) {
int emoji_count = 0;
int lower_b = 4036984960;
int upper_b = 4036996031;
//printf(utf8str);
char* is_emoji = strtok(utf8str, " ");

while (is_emoji != NULL) {
unsigned int val = 0;
for (int i = 0; i < strlen(is_emoji); i++) {
val = (val << 8) | ((unsigned int)(is_emoji[i]) & 0xFF);
}
if (val >= lower_b && val <= upper_b) {
emoji_count = emoji_count + 1;
}
is_emoji = strtok(NULL, " ");
}

return emoji_count;
}


// Return a random emoji stored in new heap memory you have allocated.  Make sure what
// you return is a valid C-string that contains only one random emoji.
char *emoji_random_alloc() {
char rando_emoji[5];
int upper_b = 4036995737;
int lower_b = 4036984960;
int random = rand() % (upper_b - lower_b + 1) + lower_b;

rando_emoji[0] = (random >> 24) & 0xFF;
rando_emoji[1] = (random >> 16) & 0xFF;
rando_emoji[2] = (random >> 8) & 0xFF;
rando_emoji[3] = random & 0xFF;
rando_emoji[4] = '\0';

char* c = malloc(strlen(rando_emoji));
strcpy(c , rando_emoji);
return c;
}


// Modify the UTF-8 string `utf8str` to invert the FIRST character (which may be up to 4 bytes)
// in the string if it the first character is an emoji.  At a minimum:
// - Invert "😊" U+1F60A ("\xF0\x9F\x98\x8A") into ANY non-smiling face.
// - Choose at least five more emoji to invert.
void emoji_invertChar(unsigned char *utf8str) {
//smiling -> crying
if (strcmp(utf8str, "\xF0\x9F\x98\x8A") == 0) {
strcpy(utf8str, "\xF0\x9F\x98\xA2");
}

//kissing -> smoke out of nose
if (strcmp(utf8str, "\xF0\x9F\x98\x98") == 0) {
strcpy(utf8str, " \xF0\x9F\x98\xA4");
}

//smirk -> unamused
if (strcmp(utf8str, "\xF0\x9F\x98\x8F") == 0) {
strcpy(utf8str, "\xF0\x9F\x98\x92");
}

//winky tongue -> angry
if (strcmp(utf8str, "\xF0\x9F\x98\x9C") == 0) {
strcpy(utf8str, "\xF0\x9F\x98\xA1");
}

//heart eyes -> tears streaming
if (strcmp(utf8str, "\xF0\x9F\x98\x8D") == 0) {
strcpy(utf8str, "\xF0\x9F\x98\xAD");
}

//kissing -> mask on
if (strcmp(utf8str, "\xF0\x9F\x98\x98") == 0) {
strcpy(utf8str, "\xF0\x9F\x98\xB7");
}
}


// Modify the UTF-8 string `utf8str` to invert ALL of the character by calling your
// `emoji_invertChar` function on each character.
void emoji_invertAll(unsigned char *utf8str) {
char* a = malloc(strlen(utf8str));
int emoji_val = 4;
int normal_val = 1;

for (int i = 0; i <= strlen(utf8str)-4; i++) {

char *is_emoji = (char*) malloc(utf8str + 1);
strncpy(is_emoji, utf8str + 1, 4);

if (!isEmoji(is_emoji)) {
strncat(a, is_emoji, normal_val);

} else {
emoji_invertChar(is_emoji);
strncat(a, is_emoji, emoji_val);

}
}
strcpy(utf8str, a);
}

int isEmoji(const char *s) {
unsigned int val = 0;
for(int i=0; i<strlen(s); i++) {
val = (val << 8) | ((unsigned int)(s[i]) & 0xFF);
}

return (
(val >= 14844092 /* U+203C */ && val <= 14912153 /* U+3299 */) ||
(val >= 4036984960 /* U+1F000 */ && val <= 4036996031 /* U+1FAFF */ )
);
}

// Reads the full contents of the file `fileName, inverts all emojis, and
// returns a newly allocated string with the inverted file's content.
unsigned char *emoji_invertFile_alloc(const char *fileName) {
FILE* myfile = fopen(fileName, 'r');
long length;

fseek(myfile, 0, SEEK_END);
length = ftell(myfile);
rewind(myfile);

char* new_file = (char*) calloc(1, sizeof(char)*length + 1);
if (length > 0) {
fread(new_file, 1, length, myfile);
new_file[length] = '\0';
}

fclose(myfile);
emoji_invertAll(new_file);
return new_file;
}
