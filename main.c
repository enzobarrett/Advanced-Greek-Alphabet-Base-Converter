/*
 * Enzo Barrett
 * 
 * By using the entire lower and uppercase greek alphabet,
 * this programs allows the user to convert between bases
 * up to base 58.
 *
 * Usage:
 *
 */

#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <assert.h>

// stuct to hold greek characters with decimal value
struct greekCharacters {
    wchar_t c;
    int value;
} extChars[48];

// initialize extended characters array
void init() {
    // tmp char
    wchar_t c;

    // array index counter
    int i = 0;

    // decimal value counter
    int decValue = 10;

    // loop through uppercase greeks
    for (c = L'\u0391'; c <= L'\u03A9'; c++) {
        // skip 3A2 because of unicode quirkiness
        if (c != L'\u03A2') {
            extChars[i] = (struct greekCharacters){c, decValue};
            i++; decValue++;
        }
    }

    // loop through lowercase greeks
    for (c = L'\u03B1'; c <= L'\u03C9'; c++){
        extChars[i] = (struct greekCharacters){c, decValue};
        i++; decValue++;
    }
}

// char_to_int(digit, radix)
// digit: char to be converted
//
// find value of character in greekCharacters stuct
// uses a linear search, TODO: implement binary search
int char_to_int (wchar_t digit) {
    int x;

    printf("%lc", digit);
    //if ((int)digit >= 0x30 && (int)digit <= 0x39) 
    //    return (int)digit-0x30;

    // find matching record in struct
    for (int i = 0; i < 48; i++) {
        if ((int)extChars[i].c == (int)digit)
            printf("%d", extChars[i].value);
            return extChars[i].value;
    }

    return -1;
}

// ascii_to_int(valueOfPrefix, radix)
// valueOfPrefix: used for recursion, set to zero
// radix: deprecated, set to 48
//
// convert unicode string entered into stdin to base 10
// radix value is always set to 48
int ascii_to_int (int valueOfPrefix, int radix) { 
    wchar_t c;
    c = getwchar();

    if (c == '\n') { 
        return valueOfPrefix; 
    } else { 
        if (valueOfPrefix == 0) { 
            return ascii_to_int(char_to_int(c), radix); 
        } 
        return ascii_to_int (valueOfPrefix * radix + char_to_int(c), radix); 
    } 
}

// test some functions
void test() {
    // char_to_int
    wchar_t c = L'\u0391';
    assert(char_to_int(c) == 10);
    c = L'\u0392';
    assert(char_to_int(c) == 11);
    c = L'\u0393';
    assert(char_to_int(c) == 12);
    c = L'\u0394';
    assert(char_to_int(c) == 13);
    c = L'\u0395';
    assert(char_to_int(c) == 14);
}

int main() {
    // set locale
    printf("Locale is: %s\n", setlocale(LC_ALL, ""));

    // init data stuctures
    init();

    int radix = 16;

    puts("Enter your number, then press enter:");
    printf("Base 10: %d\n", ascii_to_int(0, radix));

    //test();

    return (0);
}


