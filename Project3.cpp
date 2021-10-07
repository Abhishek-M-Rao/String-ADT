// String ADT <Project3.cpp>
// EE 312 Project 3 submission by
// Abhishek Rao
// amr7999
// Slip days used: 0
// Fall 2021
// Copy and paste this file at the top of all your submitted source code files.  Do not turn this in by itself.

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "UTString.h"

/*
 * Helper macro to find the signature of a UTString
 * Treat this like a function that takes a UTString*
 * Accesses a uint32_t from where the signature should be located
 */
#define CHECK(s) (*(uint32_t*) ((s)->string + (s)->length + 1))

/*
 * Checks if a UTString is valid or not.
 */
bool isOurs(const UTString* s) {
    if (CHECK(s) == SIGNATURE) { return true; }
    else { return false; }
}

/*
 * Allocate a utstring on the heap.
 * Initialize the string correctly by copying src.
 * Return a pointer to the UTString.
 */
UTString* utstrdup(const char* src) {
    int strLength;
    int index;
    UTString* stuPtr= (UTString*)malloc(sizeof(UTString));
    strLength = strlen(src);
    stuPtr -> length = strLength;
    stuPtr -> capacity = strLength;
    char* temp = (char*)malloc(strLength+5);
    for(index = 0; index < strLength; ++index){
        temp[index] = src[index];
    }
    temp[index] = '\0';
    //temp[++index] = (char)~0xde;
    //temp[++index] = (char)~0xad;
    //temp[++index] = (char)~0xbe;
    //temp[++index] = (char)~0xef;
    stuPtr -> string = temp;
    CHECK(stuPtr) = SIGNATURE;
    return stuPtr;
}

/*
 * Returns the length of s.
 *  s must be a valid UTString.
 */
uint32_t utstrlen(const UTString* s) {
    assert(isOurs(s));
    return s -> length;
}

/*
 * Append the string suffix to the UTString s.
 *  s must be a valid UTString.
 * Do not allocate any additional storage: only append as many characters
 *  as will actually fit in s.
 * Update the length of s.
 * Return s with the above changes. */
UTString* utstrcat(UTString* s, const char* suffix) {
    assert(isOurs(s));
    int index;
    char* pointStr = s -> string;
    for(index = s -> length; ((suffix[index - (s->length)] != '\0') && (index < (s->capacity))); ++index){
        pointStr[index] = suffix[index - (s->length)];
    }
    pointStr[index] = '\0';
    s -> length = index;
    s -> string = pointStr;
    CHECK(s) = SIGNATURE;
    return s;
}

/*
 * Copy src into dst.
 *  dst must be a valid UTString.
 *  src is an ordinary string.
 * Do not allocate any additional storage: only copy as many characters
 *  as will actually fit in dst.
 * Update the length of dst.
 * Return dst with the above changes.
 */
UTString* utstrcpy(UTString* dst, const char* src) {
    assert(isOurs(dst));
    int index;
    int strCap = dst -> capacity;
    char* pointStr = dst -> string;
    for(index = 0; (index < (strCap)) && (src[index] != '\0'); ++index){
        pointStr[index] = src[index];
    }
    //add here
    if(src[index] == '\0'){
        for(int i = index; pointStr[i] != '\0'; i++){
            pointStr[i] = '\0';
        }
    } else{
        pointStr[index] = '\0';
    }
    dst -> length = (index);
    dst -> string = pointStr; //do I need this?
    CHECK(dst) = SIGNATURE;
    return dst;
}

/*
 * Free all memory associated with the given UTString.
 */
void utstrfree(UTString* self) {
    assert(isOurs(self));
    free(self -> string); //fails here sigfault
    free(self);
}

/*
 * Make s have at least as much capacity as new_capacity.
 *  s must be a valid UTString.
 * If s has enough capacity already, do nothing.
 * If s does not have enough capacity, then allocate enough capacity,
 *  copy the old string and the null terminator, free the old string,
 *  and update all relevant metadata.
 * Return s with the above changes.
 */
UTString* utstrrealloc(UTString* s, uint32_t new_capacity) {
    assert(isOurs(s));
    if(new_capacity <= (s->capacity)){
        return s;
    }
    char* strNew = (char*)malloc(new_capacity+5);
    char* strOld = s -> string;
    int oldLen = strlen(strOld);
    for(int index = 0; index < oldLen; ++index){
        strNew[index] = strOld[index];
    }
    strNew[oldLen] = '\0';
    s -> string = strNew;
    s -> capacity = new_capacity;
    CHECK(s) = SIGNATURE;
    free(strOld);
    return s;
}
