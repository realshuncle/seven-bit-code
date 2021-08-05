# seven-bit-code

This program is designed to encrypt and decrypt text using a seven-bit code.

For each group of 7 consecutive characters in the text, a "key" is formed, which is a "seven-bit code" formed from the least significant bits of these characters. In this case, the most significant bits of the next character are shifted to the "vacated" places of the least significant bits of the symbol. So, at the first character of the group, one most significant bit of the next character “comes” to the position of the least significant bit, while all the bits of this next character are shifted one position to the left and two least significant bits are “freed” (one - as a result of “extracting” a bit for "Key", and the second - as a result of the shift). Etc. Thus, when at the seventh character its least significant bit is moved to the place of the most significant one, then the "seven-bit code" will be written in place of its "freed" low-order bits.
